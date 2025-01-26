#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    //Opening a connection to the database

    sqlite3* db;
    
    int rc=sqlite3_open("my_database.db",&db);// Tries to open my_database.db, and if it does not exist it create it

    if(rc != SQLITE_OK){// If the operation of opening a database was not succesfull then print cannot open data and put and error message
        fprintf(stderr,"Cannot open data: %s\n",sqlite3_errmsg(db));
        return 1;
    }

    //Writing as sql commands
    const char* sql = "INSERT INTO User_Account (name, balance) VALUES (?, ?);";
    // The placeholder(?) is where the inputs will be added

    //Preparing the Command- need to complile sql command so sqlite will be able to execute it

    sqlite3_stmt *stmt;
    rc=sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if(rc != SQLITE_OK){
        fprintf(stderr,"Failed to prepare statmemt: %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;

        char* name=(char*) malloc(50* sizeof(char));
        int balance;

        if(name==NULL){
            fprintf(stderr,"Memory allocation failed\n");
            return 1;
        }
        sqlite3_bind_text(stmt,1,name,-1,SQLITE_STATIC);
        sqlite3_bind_int(stmt,2,balance);

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(name);
    }

}