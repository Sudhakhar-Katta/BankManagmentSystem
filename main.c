#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>


typedef struct{
    char* name;
    double balance;
}User_Account;

char* strndup(const char *s, size_t len) {
    size_t actual_len = strnlen(s, len);
    char *dup_str = (char*) malloc(actual_len + 1); // allocate space for the string plus the null terminator

    if (dup_str != NULL) {
        memcpy(dup_str, s, actual_len);  // copy up to `actual_len` characters from `s`
        dup_str[actual_len] = '\0';  // null-terminate the copied string
    }

    return dup_str;  // return the duplicated string
}

void create_bank_account(User_Account* account1,char* name){
    
     account1->name=strdup(name);
     account1->balance=0.00;

    
}

void deposit_money(User_Account* account1,double money){
    account1->balance+=money;
}

void withdraw_money(User_Account* account1,double money){
    if(account1->balance<0){
        printf("You do not have the balance");
        exit(0);
    }else{
        account1->balance-=money;
    }
}

void display_account(User_Account* account1){
    printf("Name\n: %c ",account1->name);
    printf("Balance\n: %.2lf",account1->balance);
}

void delete_account(User_Account* account1){
    free(account1->name);
    account1->name=NULL;
    account1->balance=0.0;
}

int main(){

    User_Account account= {NULL,0.0};
    int entry_question;
    char name[100];
    double money;
    

    printf("Welcome to Katta's Bank\n");

    printf("Press 1 to open a bank account at Katta's\n ");
    printf("Press 2 to deposit money into your account\n ");
    printf("Press 3 to withdraw money into your account\n ");
    printf("Press 4 to know your current balance\n ");
    printf("Press 5 to transfer your funds into a different account\n");    
    printf("Press 6 to delete your account\n ");

    printf("Enter your choice: ");
    scanf("%d",&entry_question);


    switch(entry_question){
        case 1:
            printf("What is your name: ");
            scanf("%99s",&name);
            create_bank_account(&account,&name);
            break;
        case 2:
            printf("How much money would you like to deposit: ");
            scanf("%lf",&money);
            deposit_money(&account,money);
            printf("Money deposited successfully.\n");
            break;
        case 3:
            printf("How much money would you like to withdraw: ");
            scanf("%lf",&money);
            withdraw_money(&account,money);
            break;
        case 4:
           display_account(&account);
            break;
        case 5:
           // transfer_funds();
            break;
        case 6:
            delete_account(&account);
            break;
        default:
            exit(0);
    }



}