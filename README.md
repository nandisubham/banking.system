# Bank Account Management System

A console-based Bank Account Management System written in C for the CSE-101 Fundamentals of Computing and Programming in C project.

## Features

- Create a customer account with a unique account number
- Deposit money
- Withdraw money with an insufficient-balance check
- Check an account balance
- Search for an account
- Display all stored accounts
- View transaction history for an account

## Concepts Used

- C structures and functions
- `while` loops and `switch` statements
- Character arrays (strings)
- File handling with `fopen`, `fread`, `fwrite`, `fseek`, `fprintf`, and `fscanf`

## Requirements

- A C compiler such as GCC
- Windows, Linux, or macOS terminal

## Compile and Run

### Windows (MinGW GCC)

```bash
gcc Group1_BankAccountManagementSystem.c -o bank
bank.exe
```

### Linux / macOS

```bash
gcc Group1_BankAccountManagementSystem.c -o bank
./bank
```

## Data Files

When the program runs, it creates/uses:

- `accounts.dat` — stores account records in binary format
- `transactions.txt` — stores transaction history in text format

Keep these files in the same directory as the running program if you want to retain your data between runs. They are generated automatically and are excluded from this repository by `.gitignore`.

## Menu

1. Create Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Search Account
6. Display All Accounts
7. Transaction History
8. Exit

## Note

This is an educational project demonstrating basic C programming and file handling. It is not intended for real banking or storing real financial information.
