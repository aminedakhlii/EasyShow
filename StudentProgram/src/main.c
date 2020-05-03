/*
 * Copyright (c) 2019 Amine Dakhli <amine.dakhli@medtech.tn>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "ip.h"
#include <curl/curl.h>
#include "curl.h"

struct student_info
{
    GtkWidget * room_nbr ;
    GtkWidget * username ;
    int * pid ;
} ;

void stop( GtkWidget * button , gpointer data)
{
    int i = 0 , n ;
    char ch ; char cro[20] ;
    FILE * prid = fopen("/usr/lib/cgi-bin/pid.txt" , "r") ;
    while ((ch = getc(prid)) != EOF )
    {
        cro[i] = ch ;
        i++ ;

   }
   n = atoi(cro) ;
    fclose(prid) ;
    struct student_info * studentdata = data ;
    kill(n,SIGKILL)  ;

}

void share ( GtkWidget * button , gpointer data)
{
    struct student_info * studentdata = data ;
    const char * username ;

    FILE * request1 ;
    request1 = fopen("/usr/lib/cgi-bin/request.txt" , "r");
    int i = 0 ;
    char ch ;
    char cro[20] ;
    while ((ch = getc(request1)) != EOF )
    {
        cro[i] = ch ;
        i++ ;

    }
    cro[i] = '\0' ;
    fclose(request1) ;

    int n = atoi(cro) ;
    n ++ ;
    char string[50] ;
    sprintf(string , "%i" , n) ;

    FILE * hhh = fopen("/usr/lib/cgi-bin/request.txt" , "w") ;
    fprintf(hhh , string) ;
    fclose(hhh) ;

    username = (char *)malloc(20) ;
    username = gtk_entry_get_text(GTK_ENTRY(studentdata->username)) ;

    FILE * usr = fopen("/usr/lib/cgi-bin/user.txt" , "w") ;
    fprintf(usr , username) ;
    fclose(usr) ;

    const  char * roomnbr ;
    roomnbr = (char *)malloc(7) ;
    roomnbr = gtk_entry_get_text(GTK_ENTRY(studentdata->room_nbr)) ;

    const int * pid = studentdata->pid ;

    char * ip ;
    ip = (char *)malloc(30) ;
    get_room_ip( username ,roomnbr, ip) ;
    printf("%s\n",ip) ;
    if(strcmp(ip , "0.0.0.0") == 0)
    {
        GtkWidget *window3 , *label3 ;


            window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
            gtk_window_set_title(GTK_WINDOW(window3), "ERROR GETTING ROOM IP");
            gtk_window_set_default_size(GTK_WINDOW(window3), 300 , 200);
            gtk_window_set_position(GTK_WINDOW(window3), GTK_WIN_POS_CENTER);
            label3 =gtk_label_new("Error while getting the room ip address :\n invalid room name");
            GtkWidget * fixed3 = gtk_fixed_new();
            gtk_container_add(GTK_CONTAINER(window3), fixed3);
            gtk_fixed_put(GTK_FIXED(fixed3), label3, 30 , 15 );
            gtk_widget_show_all(window3);
    }
else
    share_request(ip) ;

}

int main(int argc, char *argv[]){




    gtk_init(&argc , &argv);

    struct student_info student ;
    student.pid = 0 ;
    GtkWidget *window , *fixed ,*label1 , *label2 ,*label3, *btn , *qbtn , *field1 , *field2 ;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
    gtk_window_set_title(GTK_WINDOW(window), "EasyShow Student");
    gtk_window_set_default_size(GTK_WINDOW(window), 350 , 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    label1 =gtk_label_new("Welcome To EasyShow Student");
    gtk_widget_modify_font (label1, pango_font_description_from_string ("monospaced 15"));
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_fixed_put(GTK_FIXED(fixed), label1, 31 , 27 );
    label2 = gtk_label_new("Enter your username here :") ;
    gtk_fixed_put(GTK_FIXED(fixed), label2 , 95 , 110 );

    student.username = gtk_entry_new() ;
    gtk_entry_set_placeholder_text(GTK_ENTRY( student.username), "username");
    gtk_fixed_put(GTK_FIXED(fixed) ,  student.username , 95 , 150 );
    label3 = gtk_label_new("Enter the classroom here :") ;
    gtk_fixed_put(GTK_FIXED(fixed), label3 , 95 , 220 );

    student.room_nbr = gtk_entry_new() ;
    gtk_entry_set_placeholder_text(GTK_ENTRY(student.room_nbr), "classroom");
    gtk_fixed_put(GTK_FIXED(fixed) , student.room_nbr , 95 , 260 );

    btn = gtk_button_new_with_label("Start sharing") ;
    g_signal_connect (btn , "clicked" , G_CALLBACK (share) , &student) ;
    gtk_fixed_put(GTK_FIXED(fixed) , btn , 130 , 322);
    gtk_widget_set_size_request(btn , 100 , 30);


    qbtn = gtk_button_new_with_label("Stop sharing") ;
    g_signal_connect(qbtn , "clicked" , G_CALLBACK(stop) , &student) ;
    gtk_fixed_put(GTK_FIXED(fixed), qbtn , 130 , 370);
    g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
    gtk_widget_set_size_request(qbtn , 100 , 30);
    gtk_widget_show_all(window);

    gtk_main();


return 0;
}
