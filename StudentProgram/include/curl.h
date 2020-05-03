#include <gtk/gtk.h>

#ifndef CURL_H
#define CURL_H
struct User
{
   GtkWidget * new_name ;
   GtkWidget * new_lastname ;
   GtkWidget * new_username ;
   GtkWidget * new_pass ;
   GtkWidget * new_mail ;
   GtkWidget * new_pass_confirmation ;
} ;

static size_t handle_listening(void *ptr, size_t size, size_t nmemb, void *stream) ;
int listenfunction () ;
int curl_function(const char user[20] , const char pass [20] , const char room[20] , char * ip) ;
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);

int send_user_info(const char user[20] , const char fname[20]  ,const char Lname[20] , const char pwd[20]) ;


#endif
