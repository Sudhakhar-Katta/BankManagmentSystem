#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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

void create_bank_account(char* name){
    int len= strlen(name);
    User_Account* account1= (User_Account*) malloc(sizeof(User_Account));
    
     account1->name=strndup(name,len);

     free(account1->name);
     free(account1);
}

void deposit_money(User_Account* account1,double money){
    account1->balance=money;
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
    free(account1);
}

int main(){

    User_Account account;
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
            scanf("%s",&name);
            create_bank_account(name);
            break;
        case 2:
            printf("How much money would you like to deposit: ");
            scanf("%lf",&money);
            deposit_money(&account,money);
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