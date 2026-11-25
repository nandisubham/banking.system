#include <stdio.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

// Function declarations
void createAccount();
void deposit();
void withdraw();
void checkBalance();
void searchAccount();
void displayAccounts();
void transactionHistory();
void saveTransaction(int, char[], float, float);

int main()
{
    int choice;

    while (1) {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Search Account\n");
        printf("6. Display All Accounts\n");
        printf("7. Transaction History\n");
        printf("8. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                searchAccount();
                break;
            case 6:
                displayAccounts();
                break;
            case 7:
                transactionHistory();
                break;
            case 8:
                printf("Thank you for using our bank!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

// Create a new account
void createAccount()
{
    struct Account a, temp;
    FILE *fp;
    int found = 0;

    fp = fopen("accounts.dat", "ab+");
    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &a.accNo);

    rewind(fp);
    while (fread(&temp, sizeof(temp), 1, fp) == 1) {
        if (temp.accNo == a.accNo) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Account number already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter customer name: ");
    scanf(" %49[^\n]", a.name);
    printf("Enter initial balance: ");
    scanf("%f", &a.balance);

    if (a.balance < 0) {
        printf("Invalid initial balance!\n");
        fclose(fp);
        return;
    }

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("\nAccount created successfully!\n");
    saveTransaction(a.accNo, "Opening", a.balance, a.balance);
}

// Deposit money
void deposit()
{
    struct Account a;
    FILE *fp;
    int no, found = 0;
    float amount;

    fp = fopen("accounts.dat", "rb+");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &no);

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == no) {
            found = 1;

            printf("Enter deposit amount: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Invalid amount!\n");
                break;
            }

            a.balance = a.balance + amount;
            fseek(fp, -(long)sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            printf("Deposit successful!\n");
            printf("New balance: %.2f\n", a.balance);
            saveTransaction(no, "Deposit", amount, a.balance);
            break;
        }
    }

    if (!found)
        printf("Account not found!\n");

    fclose(fp);
}

// Withdraw money
void withdraw()
{
    struct Account a;
    FILE *fp;
    int no, found = 0;
    float amount;

    fp = fopen("accounts.dat", "rb+");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &no);

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == no) {
            found = 1;
            printf("Enter withdrawal amount: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Invalid amount!\n");
            } else if (amount > a.balance) {
                printf("Insufficient balance!\n");
            } else {
                a.balance = a.balance - amount;
                fseek(fp, -(long)sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);
                printf("Withdrawal successful!\n");
                printf("Remaining balance: %.2f\n", a.balance);
                saveTransaction(no, "Withdrawal", amount, a.balance);
            }
            break;
        }
    }

    if (!found)
        printf("Account not found!\n");

    fclose(fp);
}

// Check balance
void checkBalance()
{
    struct Account a;
    FILE *fp;
    int no, found = 0;

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &no);

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == no) {
            found = 1;
            printf("\nAccount Number: %d\n", a.accNo);
            printf("Customer Name: %s\n", a.name);
            printf("Balance: %.2f\n", a.balance);
            break;
        }
    }

    if (!found)
        printf("Account not found!\n");

    fclose(fp);
}

// Search account
void searchAccount()
{
    checkBalance();
}

// Display all accounts
void displayAccounts()
{
    struct Account a;
    FILE *fp;

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    printf("\n===== ALL BANK ACCOUNTS =====\n");
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        printf("\nAccount Number: %d\n", a.accNo);
        printf("Customer Name: %s\n", a.name);
        printf("Balance: %.2f\n", a.balance);
    }

    fclose(fp);
}

// Save transaction details
void saveTransaction(int no, char type[], float amount, float balance)
{
    FILE *fp;

    fp = fopen("transactions.txt", "a");
    if (fp == NULL) {
        printf("Transaction file error!\n");
        return;
    }

    fprintf(fp, "%d %s %.2f %.2f\n", no, type, amount, balance);
    fclose(fp);
}

// Display transaction history
void transactionHistory()
{
    FILE *fp;
    int no, acc;
    char type[20];
    float amount, balance;
    int found = 0;

    fp = fopen("transactions.txt", "r");
    if (fp == NULL) {
        printf("No transaction history found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &no);

    printf("\n===== TRANSACTION HISTORY =====\n");
    while (fscanf(fp, "%d %19s %f %f", &acc, type, &amount, &balance) == 4) {
        if (acc == no) {
            found = 1;
            printf("\nTransaction: %s\n", type);
            printf("Amount: %.2f\n", amount);
            printf("Balance: %.2f\n", balance);
        }
    }

    if (!found)
        printf("No transactions found!\n");

    fclose(fp);
}
