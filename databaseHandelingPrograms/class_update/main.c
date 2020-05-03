#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sqlite3.h>

typedef struct classes
{
    char roomnumber[7] ;
    char ip[20] ;
} Room ;

bool delete_room_data(sqlite3 * db , char room[7])
{
    sqlite3_stmt* statement;
    int rc;
    char sql_delete_room[250];
    sprintf(sql_delete_room,
            "DELETE FROM classes WHERE classroom = '%s'",
            room);
    rc = sqlite3_prepare_v2(db, sql_delete_room, strlen(sql_delete_room), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);


    }
    else printf("%s",sqlite3_errmsg(db)) ;
    sqlite3_finalize(statement);
    return true;

}

bool insert_Room (sqlite3 * db , Room * room )
{
    sqlite3_stmt* statement;
    int rc;

    // Prepare the SQL query to insert the new user
    char sql_insert_room[250];
    sprintf(sql_insert_room,
            "INSERT INTO classes (classroom, ip) VALUES ('%s', '%s')",
            room->roomnumber,
            room->ip);

    // Execute the previous query to insert a new line into the 'user' table
    rc = sqlite3_prepare_v2(db, sql_insert_room, strlen(sql_insert_room), &statement, NULL);
    if(rc == SQLITE_OK) {
        rc = sqlite3_step(statement);


    }
    sqlite3_finalize(statement);
    return true;

}
bool create_room_table(sqlite3* db)
{
    sqlite3_stmt* statement;
    int rc;

    // SQL query to create the 'user' table
    const char* sql_create_user_table = "CREATE TABLE IF NOT EXISTS classes ("
                                        "classroom TEXT,"
                                        "ip TEXT);";

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



int main ()
{
    printf("content-type: text/html \n\n");

    Room nroom ;
    sqlite3 * db ;
    int rc = sqlite3_open("/usr/lib/cgi-bin/easyshowAdmin.db", &db);
    if(rc != SQLITE_OK) {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if(!create_room_table(db)) {
        sqlite3_close(db);
        return 1;
    }

    char updateroom[7] ;
    char updateip[20] ;

// the classroom data sent from the datashow program



    char * roomdata = getenv("QUERY_STRING") ;

    sscanf(roomdata, "classroom=%[^&]&ip=%[^&]",updateroom,updateip) ;
    strcpy(nroom.roomnumber, updateroom ) ;
    strcpy(nroom.ip , updateip) ;
    delete_room_data(db , updateroom);
    if(!insert_Room(db, &nroom))
        printf("sOrry \n");

    return 0 ;
}
