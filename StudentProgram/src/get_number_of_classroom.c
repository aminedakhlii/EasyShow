#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <curl/curl.h>
#include "get.h"

int share_request(char * ip)
{
    pid_t n = fork() ;
    char addr[100] = "rtp://" ;
    strcat(addr , ip) ;
    strcat(addr , ":1234") ;
    if(n == 0)
    {
    execl("/usr/bin/ffmpeg", "ffmpeg" , "-f", "alsa", "-ac", "2", "-i",
          "pulse","-f", "x11grab","-r","30","-s" ,"1366x768","-i" ,":0.0","-acodec" ,"pcm_s16le",
          "-vcodec" ,"libx264","-preset" ,"ultrafast","-tune", "zerolatency","-crf" ,"0","-threads",
          "0","-f","rtp_mpegts",addr, NULL ) ;
    }

    FILE * prid = fopen("/usr/lib/cgi-bin/pid.txt" , "w") ;
    fprintf(prid , "%i" , n) ;
    fclose(prid) ;
}
