#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int accountNumber;
    char name[50];
    double balance;
} User_Account;

int accountCount = 0;  // Global counter for accounts

void save_to_file(User_Account* accounts, int count) {
    FILE* file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2lf\n", accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
    fclose(file);
}

void load_from_file(User_Account* accounts) {
    FILE* file = fopen("accounts.txt", "r");
    if (file == NULL) {
        file = fopen("accounts.txt", "w");
        if (file == NULL) {
            printf("Error creating accounts file.\n");
            return;
        }
        fclose(file);
        printf("Created new accounts file.\n");
        return;
    }
    while (fscanf(file, "%d %s %lf", &accounts[accountCount].accountNumber, accounts[accountCount].name, &accounts[accountCount].balance) == 3) {
        accountCount++;
    }
    fclose(file);
}

void create_bank_account(User_Account* accounts) {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts. Limit reached.\n");
        return;
    }

    accounts[accountCount].accountNumber = accountCount + 1;
    printf("Enter name: ");
    scanf("%49s", accounts[accountCount].name);
    accounts[accountCount].balance = 0.0;
    printf("Account created successfully. Account Number: %d\n", accounts[accountCount].accountNumber);
    accountCount++;
}

User_Account* find_account(User_Account* accounts, int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return &accounts[i];
        }
    }
    return NULL;
}

void deposit_money(User_Account* account, double money) {
    account->balance += money;
    printf("Deposit successful.\n");
}

void withdraw_money(User_Account* account, double money) {
    if (account->balance < money) {
        printf("Insufficient balance.\n");
    } 
    else if (money < 0) {
        printf("Invalid withdrawal amount.\n");
    }else {
        account->balance -= money;
        printf("Withdrawal successful.\n");
    }
}

void display_account(User_Account* account) {
    printf("Account Number: %d\n", account->accountNumber);
    printf("Name: %s\n", account->name);
    printf("Balance: %.2lf\n", account->balance);
}

void delete_account(User_Account* accounts, int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            for (int j = i; j < accountCount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountCount--;
            printf("Account deleted successfully.\n");
            return;
        }
    }
    printf("Account not found.\n");
}

int main() {
    User_Account accounts[MAX_ACCOUNTS];
    int choice, accountNumber;
    double money;

    printf("Welcome to Katta's Bank\n");
    load_from_file(accounts);

    do {
        printf("\n1. Open a Bank Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Display Account Details\n");
        printf("5. Delete Account\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_bank_account(accounts);
                save_to_file(accounts, accountCount);
                break;
            case 2:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                User_Account* acc = find_account(accounts, accountNumber);
                if (acc) {
                    printf("Enter deposit amount: ");
                    scanf("%lf", &money);
                    deposit_money(acc, money);
                    save_to_file(accounts, accountCount);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                acc = find_account(accounts, accountNumber);
                if (acc) {
                    printf("Enter withdrawal amount: ");
                    scanf("%lf", &money);
                    withdraw_money(acc, money);
                    save_to_file(accounts, accountCount);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 4:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                acc = find_account(accounts, accountNumber);
                if (acc) {
                    display_account(acc);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 5:
                printf("Enter account number to delete: ");
                scanf("%d", &accountNumber);
                delete_account(accounts, accountNumber);
                save_to_file(accounts, accountCount);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}