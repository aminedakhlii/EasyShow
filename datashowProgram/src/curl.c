#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <time.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "curl.h"
#include "ip.h"


static size_t handle_response(void *ptr, size_t size, size_t nmemb, void *stream)
{
    char* response = (char*) stream;
    strncpy(response, ptr, nmemb);

    return nmemb;
}

static size_t handle_listening(void *ptr, size_t size, size_t nmemb, void *stream)
{
    char* listen = (char*) stream;
    strncpy(listen, ptr, nmemb);

    return nmemb;
}

gpointer listenfunction (gpointer arg) {

 GtkWidget * window = (GtkWidget*) arg ;

    int k = 1 ;
    while (1)
    {

        FILE * req = fopen("/usr/lib/cgi-bin/request.txt" , "r") ;
        int i = 0 ;
        char ch ;
        char cro[20] ;
        while ((ch = getc(req)) != EOF )
        {
            cro[i] = ch ;
            i++;
        }
        cro[i] = '\0';
        fclose(req) ;

        int n = atoi(cro) ;

        printf("%i ,, %i\n",n,k);
        fflush(stdout);

       if (k == n)
       {

           printf(" i 'm here") ;

               g_signal_emit_by_name(window, "sharing-screen-request");


              /* char * ip = (char*)malloc(20) ;

               ipaddr(ip) ;

               char addr[30] = "vlc rtp://" ;
               strcat (addr , ip) ;
               strcat (addr , ":1234") ;


             system(addr) ;*/


           k++ ;


           //g_idle_add (TRUE , window);

       }

  sleep(1) ;

    }
    return NULL;
}

int send_user_info(const char user[20] , const char fname[20]  ,const char Lname[20] , const char pwd[20])
{

    CURL *curl_handle ;

    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_handle = curl_easy_init();

    char request[200] = "127.0.0.1/cgi-bin/sign_in?new_name=" ;

    strcat ( request , fname );
    strcat (request, "&new_lastname=");
    strcat (request , Lname );
    strcat (request , "&new_username=" );
    strcat (request , user );
    strcat (request , "&newpwd=" );
    strcat (request , pwd );

    printf("%s",request);

    curl_easy_setopt(curl_handle, CURLOPT_URL, request);


    curl_easy_perform(curl_handle);


    /* cleanup curl stuff */
     curl_easy_cleanup(curl_handle);

      curl_global_cleanup();
}


int curl_function(const char user[20] , const char pass[20] , const char room[20]  )
{

  CURL *curl_handle ;

  CURLcode res;



  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl_handle = curl_easy_init();


    char request2[70] = "127.0.0.1/cgi-bin/Log_in?login=" ;

    strcat ( request2 , user );
    strcat (request2, "&pwd=");
    strcat (request2 , pass );
    strcat (request2 , "&room=" );
    strcat (request2 , room );

    printf("%s\n",request2) ;

    curl_easy_setopt(curl_handle, CURLOPT_URL, request2);


   // curl_easy_setopt(curl_handle , CURLOPT_POSTFIELDS , request2);

  //  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)strlen(request2)/2);

    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, handle_response);

    char *response ;
    response = (char*)malloc(500) ;

    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response);


    curl_easy_perform(curl_handle);


    /* cleanup curl stuff */
     curl_easy_cleanup(curl_handle);

      curl_global_cleanup();





     if (strcmp(response,"0.0.0.1") == 0)
     { free(response) ;
          return -2 ;
}
 else
         return 0 ;

}
