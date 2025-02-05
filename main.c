#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* name;
    double balance;
} User_Account;

void save_to_file(User_Account* account) {
    FILE* file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s\n%.2lf", account->name, account->balance);
    fclose(file);
}

void load_from_file(User_Account* account) {
    FILE* file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("No existing account found.\n");
        return;
    }
    char name[100];
    double balance;
    if (fscanf(file, "%s\n%lf", name, &balance) == 2) {
        if (account->name != NULL) {
            free(account->name);
        }
        account->name = strdup(name);
        account->balance = balance;
        printf("Account loaded successfully.\n");
    }
    fclose(file);
}

char* strndup(const char *s, size_t len) {
    size_t actual_len = strnlen(s, len);
    char *dup_str = (char*) malloc(actual_len + 1);

    if (dup_str != NULL) {
        memcpy(dup_str, s, actual_len);
        dup_str[actual_len] = '\0';
    }

    return dup_str;
}

void create_bank_account(User_Account* account1, char* name) {
    account1->name = strdup(name);
    account1->balance = 0.00;
}

void deposit_money(User_Account* account1, double money) {
    account1->balance += money;
}

void withdraw_money(User_Account* account1, double money) {
    if (account1->balance < money) {
        printf("Insufficient balance.\n");
    } else {
        account1->balance -= money;
    }
}

void display_account(User_Account* account1) {
    printf("Name: %s\n", account1->name);
    printf("Balance: %.2lf\n", account1->balance);
}

void delete_account(User_Account* account1) {
    free(account1->name);
    account1->name = NULL;
    account1->balance = 0.0;
}

int main() {
    User_Account account = {NULL, 0.0};
    int choice;
    char name[100];
    double money;

    printf("Welcome to Katta's Bank\n");
    
    load_from_file(&account);

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
                printf("Enter your name: ");
                scanf("%99s", name);
                create_bank_account(&account, name);
                printf("Account created successfully.\n");
                save_to_file(&account);
                break;
            case 2:
                printf("Enter deposit amount: ");
                scanf("%lf", &money);
                deposit_money(&account, money);
                printf("Deposit successful.\n");
                save_to_file(&account);
                break;
            case 3:
                printf("Enter withdrawal amount: ");
                scanf("%lf", &money);
                withdraw_money(&account, money);
                save_to_file(&account);
                break;
            case 4:
                display_account(&account);
                break;
            case 5:
                delete_account(&account);
                printf("Account deleted successfully.\n");
                save_to_file(&account);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    if (account.name != NULL) {
        free(account.name);
    }
    return 0;
}
