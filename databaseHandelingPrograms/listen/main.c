#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


int main (void)
{
    printf("content-type: text/html \n\n");
    char user[10] ="xxx" ;
    char ch ;
    char cro[5] ;
 FILE * request = fopen("/usr/lib/cgi-bin/request.txt" , "r" ) ;
 int i = 0 ;
 while ((ch = getc(request)) != '\n' )
 {
     cro[i] = ch ;
     i++ ;

}
 if (strcmp(cro , "yes") == 0)
 {
     printf("%s wants to share his screen!",user) ;
 }
 else {
     printf("no");
 }
 fclose(request) ;



return 0 ;
}
