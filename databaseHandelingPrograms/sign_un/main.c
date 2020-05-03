#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sqlite3.h>

typedef struct users
{
   char username[20] ;
   char password[20] ;
} User ;

typedef struct full_user_info
{
   char name[20];
   char lastname[20];
   char username[20];
   char passwd[20];

} Uinfo ;

bool create_info_table(sqlite3 * db)
{
    sqlite3_stmt* statement;
    int rc;
    const char* sql_create_info_table = "CREATE TABLE IF NOT EXISTS users_full_info ("
                                        "name TEXT NOT NULL,"
                                        "lastname TEXT,"
                                        "username TEXT,"
                                        "password);";

    // Execute the previous query to create the 'user' table
    rc = sqlite3_prepare_v2(db, sql_create_info_table, strlen(sql_create_info_table), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);
        sqlite3_finalize(statement);

    } else {
        printf("Can't initialize the database: %s\n", sqlite3_errmsg(db));
        return false;
    }
    sqlite3_finalize(statement);

    return true;
}

bool insert_nuser(sqlite3 * db , Uinfo * user)
{
    sqlite3_stmt* statement;
    int rc;

    // Prepare the SQL query to insert the new user
    char sql_insert_info[250];
    sprintf(sql_insert_info,
            "INSERT INTO users_full_info (name, lastname, username, password) VALUES ('%s', '%s', '%s', '%s')",
            user->name,
            user->lastname,
            user->username,
            user->passwd) ;

    rc = sqlite3_prepare_v2(db, sql_insert_info, strlen(sql_insert_info), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);


    }

    sqlite3_finalize(statement);
    return true;
}

bool create_user_table(sqlite3* db)
{
    sqlite3_stmt* statement;
    int rc;

    // SQL query to create the 'user' table
    const char* sql_create_user_table = "CREATE TABLE IF NOT EXISTS user ("
                                        "username TEXT NOT NULL,"
                                        "password TEXT);";

    // Execute the previous query to create the 'user' table
    rc = sqlite3_prepare_v2(db, sql_create_user_table, strlen(sql_create_user_table), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);
        sqlite3_finalize(statement);

    } else {
        printf("Can't initialize the database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_finalize(statement);

    return true;
}

bool insert_user(sqlite3* db, User* user)
{
    sqlite3_stmt* statement;
    int rc;

    // Prepare the SQL query to insert the new user
    char sql_insert_user[250];
    sprintf(sql_insert_user,
            "INSERT INTO user (username, password) VALUES ('%s', '%s')",
            user->username,
            user->password);

    // Execute the previous query to insert a new line into the 'user' table
    rc = sqlite3_prepare_v2(db, sql_insert_user, strlen(sql_insert_user), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);
    }

    sqlite3_finalize(statement);
    return true;
}


int main (void)
{
    printf("content-type: text/html \n\n");

    User new_user ;
    sqlite3 * db ;
    int rc = sqlite3_open("/usr/lib/cgi-bin/easyshowAdmin.db", &db);
    if(rc != SQLITE_OK) {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if(!create_user_table(db)) {
        sqlite3_close(db);
        return 1;
    }

    if(!create_info_table(db)) {
        sqlite3_close(db);
        return 1;
    }

    char name[20] , lastn[20] , uname[20] , npwd[20] ;

    char *signdata = getenv("QUERY_STRING") ;

sscanf(signdata,"new_name=%[^&]&new_lastname=%[^&]&new_username=%[^&]&newpwd=%[^&]",
       name, lastn , uname , npwd);

Uinfo newsigned ;

strcpy(newsigned.name, name ) ;
strcpy(newsigned.lastname , lastn) ;
strcpy(newsigned.username, uname ) ;
strcpy(newsigned.passwd , npwd) ;



if(!insert_nuser(db, &newsigned))
    printf("sOrry \n");
else {
    strcpy(new_user.username, uname ) ;
    strcpy(new_user.password , npwd) ;
    if(!insert_user(db, &new_user))
        printf("sOrry \n");

}

    sqlite3_close(db);
}
