#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <sys/wait.h>
#include <string.h>
#include "share.h"

void stop (GtkWidget *button , gpointer data)
{
    FILE * stop = fopen("/usr/lib/cgi-bin/pid.txt" , "r") ;
    int i = 0 ;
    char ch ;
    char cro[20] ;
    while ((ch = getc(stop)) != EOF )
    {
        cro[i] = ch ;
        i++;
    }
    cro[i] = '\0';
    fclose(stop) ;
    int pid = atoi(cro) ;
    kill(pid , SIGKILL) ;

}


int share(GtkWidget *button , gpointer data) {

    char  * ip = data ;
    pid_t n = fork() ;
    char addr[100] = "rtp://" ;
    strcat(addr , ip) ;
    strcat(addr , ":1234") ;
    if(n == 0)
    {
    execl("/usr/bin/ffmpeg", "ffmpeg" , "-f", "alsa", "-ac", "2", "-i",
          "pulse","-f", "x11grab","-r","30","-s" ,"1366x768","-i" ,":0.0","-acodec" ,"pcm_s16le",
          "-vcodec" ,"libx264","-preset" ,"ultrafast","-tune", "zerolatency","-crf" ,"0","-threads",
          "0","-f" ,"rtp_mpegts" ,addr, NULL ) ;

    CURL *curl ;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_easy_init() ;

    curl_easy_setopt( curl , CURLOPT_URL , "127.0.0.1/listen?state=yes") ;

    curl_easy_perform(curl) ;

    curl_easy_cleanup(curl);

 curl_global_cleanup();

    }



  return n ;
}
