#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sqlite3.h>

typedef struct users
{
   char username[20] ;
   char password[20] ;
} User ;

bool room_ip( sqlite3 * db , char room[7] , char * ipp )
{
    if (!strcmp (room,"")) return false ;
    sqlite3_stmt* statement ;
    int rc ;

    const char *sql_find_room_ip = "SELECT classroom , ip FROM classes" ;
    rc = sqlite3_prepare_v2(db, sql_find_room_ip, strlen(sql_find_room_ip), &statement, NULL);

    if (rc == SQLITE_OK) {

        while(sqlite3_step(statement) == SQLITE_ROW) {

            const char * roomdb = (const char *)sqlite3_column_text(statement, 0) ;
            const char * ipdb = (const char *)sqlite3_column_text(statement, 1) ;

            if((strcmp(roomdb, room) == 0)) {
                    strcpy(ipp,ipdb) ;
                    return true ;
                } }



    }
    sqlite3_finalize(statement);

    return false ;
}

bool verify_user (sqlite3* db , User user )
{
    sqlite3_stmt* statement;
    int rc;

    const char * sql_select_user ="SELECT username, password FROM user" ;

    rc = sqlite3_prepare_v2(db, sql_select_user, strlen(sql_select_user), &statement, NULL);

    if(rc == SQLITE_OK) {

        while(sqlite3_step(statement) == SQLITE_ROW) {

            const char * userdb = (const char *)sqlite3_column_text(statement, 0) ;
            const char * passdb = (const char *)sqlite3_column_text(statement, 1) ;

            if((!strcmp(userdb, user.username)) && ( !strcmp(passdb , user.password)) ) {
                    return true ;
                }

                }
            }
    sqlite3_finalize(statement);

    return false ;
        }


int main (void)
{
    printf("content-type: text/html \n\n");

    User user ;
    sqlite3 * db ;
    int rc = sqlite3_open("/usr/lib/cgi-bin/easyshowAdmin.db", &db);
    if(rc != SQLITE_OK) {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char oldlogin[20] ;
    char oldpwd [20] ;
    char room[7] ;

    char * logindata ;
    logindata = getenv("QUERY_STRING") ;
    //char * len_ = getenv("CONTENT_LENGTH");
   // long int  len = strtol(len_, NULL, 10);
  //  logindata = malloc(len + 1);
    //fgets(logindata, len + 1 , stdin);
    sscanf(logindata,"login=%[^&]&pwd=%[^&]&room=%[^&]",oldlogin, oldpwd,room) ;
    strcpy(user.username, oldlogin ) ;
    strcpy(user.password , oldpwd) ;

    if(verify_user(db, user))
    {
        char * ip ;
        ip = (char *)malloc(40) ;
        if(room_ip(db , room , ip ))
        {
            printf("%s",ip) ;
        }
        else printf("0.0.0.0") ;
    }
    else printf("0.0.0.1");

return 0 ;
}
