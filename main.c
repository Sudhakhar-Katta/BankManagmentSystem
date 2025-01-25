#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char* name;
    int balance;
}User_Account;

void create_account(char* name){
    int len= strlen(name);
    User_Account* account1= (User_Account*) malloc((len+1)* sizeof(User_Account));
    
    for(int i=0; i<len;i++){
        account1[i] =   name[i];
    }

}


int main(){
    int entry_question;
    char* name;
    

    printf("Welcome to Katta's Bank");

    printf("Press 1 to open a bank account at Katta's\n ");
    printf("Press 2 to deposit money into your account\n ");
    printf("Press 3 to withdraw money into your account\n ");
    printf("Press 4 to know your current balance\n ");
    printf("Press 5 to transfer your funds into a different account\n");    
    printf("Press 6 to delete your account\n ");

    printf("Enter your choice; ");
    scanf("%d",&entry_question);

    switch(entry_question){
        case 1:
            printf("What is your name: ");
            scanf("%s",&name);
            create_bank_account(*(name));
            break;
        case 2:
           // deposit_money();
            break;
        case 3:
           // withdraw_money();
            break;
        case 4:
           // display_current_balance();
            break;
        case 5:
           // transfer_funds();
            break;
        case 6:
          //  delete_account();
            break;
        default:
            exit(0);
    }



}