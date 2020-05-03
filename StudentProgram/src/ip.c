#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "ip.h"

static size_t handle_response(void *ptr, size_t size, size_t nmemb, void *stream)
{
    char* response = (char*) stream;
    strncpy(response, ptr, nmemb);

    return nmemb;
}

int get_room_ip(const char username[20] , const char roomnbr[7] , char * ip)
{
    char request[50] = "user=" ;
    strcat(request , username) ;
    strcat(request , "&room=") ;
    strcat(request , roomnbr) ;

    CURL *curl_handle ;

    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle , CURLOPT_URL , "127.0.0.1/cgi-bin/Roomip");

    curl_easy_setopt(curl_handle , CURLOPT_POSTFIELDS , request);

    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, handle_response);

    char *response ;
    response = (char*)malloc(300) ;

    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response);


    curl_easy_perform(curl_handle);


    /* cleanup curl stuff */
     curl_easy_cleanup(curl_handle);

      curl_global_cleanup();


      strcpy(ip,response) ;
      free(response) ;

      if (strcmp(ip,"0.0.0.0") == 0)

         return -1 ;

     else if (strcmp(ip,"0.0.0.1") == 0)
          return -2 ;

 else
         return 0 ;
}
