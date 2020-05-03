#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get.h"

int classroom (const char * room)
{
    
    char ch ;
    char cro[10] ;
    FILE * roomnumber ; 
    int i = 0 ; 
    
    roomnumber = fopen("room.txt", "r") ; 
    while ((ch = getc(roomnumber)) != '\n' )
    {   
        cro[i] = ch ;
        i++ ; 
    
}
    cro[i] = '\0' ;
    strcpy(room , cro) ;
    return 0 ;
    
}
