#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <sys/wait.h>
#include <curl/curl.h>
#include "share.h"
#include "curl.h"
#include "ip.h"
#include "get.h"
#include <pthread.h>
#include <glib.h>

void sendData ( )
{
    CURL *curl_handle ;

    CURLcode res;

    char * ip ;

    ip = (char *)malloc(20) ;

    char *  room ;

    room = (char *)malloc(7) ;


    ipaddr(ip) ;

    classroom(room) ;

    curl_global_init(CURL_GLOBAL_DEFAULT);

     curl_handle = curl_easy_init();

     char request[100] = "127.0.0.1/cgi-bin/classes_handle?classroom=" ;

     strcat(request , room) ;
     strcat(request , "&ip=") ;
     strcat(request , ip) ;
     free(ip) ;
     free(room);
     printf("%s\n", request);

     curl_easy_setopt(curl_handle, CURLOPT_URL, request);

     curl_easy_perform(curl_handle);


             curl_easy_cleanup(curl_handle);

              curl_global_cleanup();
}



struct user_info
{
   GtkWidget * u_name ;
   GtkWidget * pass ;
} ;

struct new_user_info
{
   GtkWidget * new_name ;
   GtkWidget * new_lastname ;
   GtkWidget * new_username ;
   GtkWidget * new_pass ;
   GtkWidget * new_mail ;
   GtkWidget * new_pass_confirmation ;
   GtkWidget * roomn ;

} ;


void blo9(GtkWidget *button, gpointer data )
{

}

void sharing_screen_window(GtkWidget *button, gpointer data )
{

    GtkWidget *window2 , *btn , *label2  , *fixed2 ;

    struct user_info *d = data ;

    const char * username ;
    username = (char *)malloc(20) ;
    username = gtk_entry_get_text(GTK_ENTRY(d->u_name));

    const char * password ;
    password = (char *)malloc(20) ;
    password = gtk_entry_get_text(GTK_ENTRY(d->pass)) ;

    const char * roomnum ;
    roomnum = (char *)malloc(7) ;

    classroom(roomnum) ;

    char * ip ;
    ip= (char*)malloc(40) ;

    ipaddr(ip) ;


    int ret = curl_function(username , password, roomnum);

    if(ret == 0)
    {

        FILE * user = fopen("/usr/lib/cgi-bin/user.txt" , "r") ;
        int i = 0 ;
        char ch ;
        char usn[100] ;
        while ((ch = getc(user)) != EOF )
        {
            usn[i] = ch ;
            i++;
        }
        usn[i] = '\0' ;
        fclose(user) ;

    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
    gtk_window_set_title(GTK_WINDOW(window2), "Sharing screen page");
    gtk_window_set_default_size(GTK_WINDOW(window2), 400 , 200);
    gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);

    fixed2 = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window2), fixed2);

    if (strcmp(usn , "") != 0)
    strcat (usn , " is now sharing his screen with you") ;
    else
    strcat(usn , "no one is sharing") ;
    label2 = gtk_label_new(usn);
    gtk_fixed_put(GTK_FIXED(fixed2), label2, 20 , 50);
    gtk_widget_set_size_request(label2 , 80 , 30);


    btn = gtk_button_new_with_label("Refresh");
    g_signal_connect(btn , "clicked", G_CALLBACK(blo9), NULL);
    gtk_fixed_put(GTK_FIXED(fixed2), btn , 220 , 100);
    gtk_widget_set_size_request(btn , 100 , 30);

    char no[1] ="0" ;

    if (strcmp(usn , "no one is sharing") != 0 )
               {
        btn = gtk_button_new_with_label("STOP");
    g_signal_connect(btn , "clicked", G_CALLBACK(stop), NULL);
    gtk_fixed_put(GTK_FIXED(fixed2), btn , 270 , 50);
    gtk_widget_set_size_request(btn , 100 , 30);
}


    GtkWidget * Qbtn = gtk_button_new_with_label("Quit");
    g_signal_connect(Qbtn , "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed2), Qbtn, 120 , 100);
    gtk_widget_set_size_request(Qbtn , 100 , 30);


    g_signal_connect(G_OBJECT(window2), "destroy",
          G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window2);
    }
    else if(ret == -1 )
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
    else if(ret == -2 )
    {

    GtkWidget *window4 , *label4 ;


        window4 = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
        gtk_window_set_title(GTK_WINDOW(window4), "ERROR LOGIN FAILED");
        gtk_window_set_default_size(GTK_WINDOW(window4), 300 , 50);
        gtk_window_set_position(GTK_WINDOW(window4), GTK_WIN_POS_CENTER);
        label4 =gtk_label_new("Error while logging in") ;
        GtkWidget * fixed4 = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window4), fixed4);
        gtk_fixed_put(GTK_FIXED(fixed4), label4, 87 , 15 );

        gtk_widget_show_all(window4);
    }
printf("%s\n",ip);

}


void new_user_window(GtkWidget * button  , gpointer data2)
{
    GtkWidget *window5 , *label5 ;

    struct new_user_info *s = data2 ;


    const char * new_user_username ;
    new_user_username = (char *)malloc(20) ;
    new_user_username = gtk_entry_get_text(GTK_ENTRY(s->new_username)) ;


    const  char * new_user_lastname ;
    new_user_lastname = (char *)malloc(20) ;
    new_user_lastname = gtk_entry_get_text(GTK_ENTRY(s->new_lastname)) ;

    const char * new_user_firstname ;
    new_user_firstname = (char *)malloc(20) ;
    new_user_firstname = gtk_entry_get_text(GTK_ENTRY(s->new_name));

    const char * new_user_mail ;
    new_user_mail = (char *)malloc(50) ;
    new_user_mail = gtk_entry_get_text(GTK_ENTRY(s->new_mail));

    const char * new_user_pass ;
    new_user_pass = (char *)malloc(20) ;
    new_user_pass = gtk_entry_get_text(GTK_ENTRY(s->new_pass));

    const char * new_user_pc ;
    new_user_pc = (char*)malloc(20) ;
    new_user_pc = gtk_entry_get_text(GTK_ENTRY(s->new_pass_confirmation));




    if (strcmp(gtk_entry_get_text(GTK_ENTRY(s->new_pass)),gtk_entry_get_text(GTK_ENTRY(s->new_pass_confirmation))) == 0 && strcmp(gtk_entry_get_text(GTK_ENTRY(s->new_pass_confirmation)),"") != 0)
    {
        send_user_info(new_user_username , new_user_firstname ,new_user_lastname , new_user_pass) ;

        GtkWidget * window4 = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
        gtk_window_set_title(GTK_WINDOW(window4), "ERROR LOGIN FAILED");
        gtk_window_set_default_size(GTK_WINDOW(window4), 300 , 50);
        gtk_window_set_position(GTK_WINDOW(window4), GTK_WIN_POS_CENTER);
        GtkWidget* label4 =gtk_label_new("Welcome to Easyshow") ;
        GtkWidget * fixed4 = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window4), fixed4);
        gtk_fixed_put(GTK_FIXED(fixed4), label4, 87 , 15 );
        //GtkWidget * signin = gtk_button_new_with_label("Sign in");
       // g_signal_connect(signin, "clicked", G_CALLBACK(sharing_screen_window),  d);
       // gtk_fixed_put(GTK_FIXED(fixed4), signin, 87 , 25);
       // gtk_widget_set_size_request(signin , 190 , 40);

        gtk_widget_show_all(window4);
    }
    else
    {



        window5 = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
        gtk_window_set_title(GTK_WINDOW(window5), "ERROR LOGIN FAILED");
        gtk_window_set_default_size(GTK_WINDOW(window5), 300 , 50);
        gtk_window_set_position(GTK_WINDOW(window5), GTK_WIN_POS_CENTER);
        label5 =gtk_label_new("Password confirmation Failed") ;
        GtkWidget * fixed5 = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window5), fixed5);
        gtk_fixed_put(GTK_FIXED(fixed5), label5, 87 , 15 );

        gtk_widget_show_all(window5);
    }


}


void sharingScreenRequest(GtkWidget *w, GdkEvent *e)
{


    gtk_widget_show_all(w);
}


void main(int argc , char* argv[])
{
    (void) argc ;
    (void) argv ;


    FILE * reques = fopen("/usr/lib/cgi-bin/request.txt" , "w") ;
    fprintf(reques , "0") ;
    fclose(reques) ;

    FILE * usr = fopen("/usr/lib/cgi-bin/user.txt" , "w") ;
    fprintf(usr , "") ;
    fclose(usr) ;

    char *  croom ;

    croom = (char *)malloc(7) ;

    classroom(croom) ;

    sendData();

    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *Login_button, *Quit_button , *signin_button;
    GtkWidget *label_user;
    GtkWidget * label_signin;
    GtkWidget * image ;
    GdkColor color;

    struct user_info  user ;
    struct new_user_info new_user ;

    gdk_threads_init();

    gtk_init(&argc, &argv);


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Login page");
    gtk_window_set_default_size(GTK_WINDOW(window), 850 , 450);
    gtk_window_set_resizable(window , FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);


    gdk_color_parse("#FFFffa", &color);


    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

   image = gtk_image_new_from_file("background.png");
    gtk_fixed_put(GTK_FIXED(fixed) , image , 0 , 0);


    gtk_widget_modify_text ( GTK_WIDGET(label_signin), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font (label_signin, pango_font_description_from_string ("Monospace 20"));




    user.u_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(user.u_name), "Username");
    gtk_fixed_put(GTK_FIXED(fixed), user.u_name, 360 , 20);

    user.pass = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(user.pass), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(user.pass), 0);
    gtk_fixed_put(GTK_FIXED(fixed), user.pass, 540 , 20);



    new_user.new_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_user.new_name), "Name");
    gtk_fixed_put(GTK_FIXED(fixed), new_user.new_name, 470 , 200);

    new_user.new_lastname = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_user.new_lastname), "Last name");
    gtk_fixed_put(GTK_FIXED(fixed), new_user.new_lastname, 650 , 200);

    new_user.new_mail = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_user.new_mail), "E-mail address");
    gtk_fixed_put(GTK_FIXED(fixed), new_user.new_mail, 470 , 250);

    new_user.new_username = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_user.new_username), "Username");
    gtk_fixed_put(GTK_FIXED(fixed), new_user.new_username, 650 , 250);


    new_user.new_pass = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_user.new_pass), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(new_user.new_pass), 0);
    gtk_fixed_put(GTK_FIXED(fixed), new_user.new_pass, 470 , 300);

    new_user.new_pass_confirmation = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_user.new_pass_confirmation), "Confirm password");
    gtk_entry_set_visibility(GTK_ENTRY(new_user.new_pass_confirmation), 0);
    gtk_fixed_put(GTK_FIXED(fixed), new_user.new_pass_confirmation, 650 , 300);


    Login_button = gtk_button_new_with_label("Log in");
    g_signal_connect(Login_button, "clicked", G_CALLBACK(sharing_screen_window), &user );
    gtk_fixed_put(GTK_FIXED(fixed), Login_button, 720 , 20);
    gtk_widget_set_size_request(Login_button , 100 , 30);

    signin_button = gtk_button_new_with_label("Sign in");
    g_signal_connect(signin_button, "clicked", G_CALLBACK(new_user_window), &new_user);
    gtk_fixed_put(GTK_FIXED(fixed), signin_button, 550 , 370);
    gtk_widget_set_size_request(signin_button , 190 , 40);


    g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    GtkWidget *  window5 = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
    gtk_window_set_title(GTK_WINDOW(window5), "REQUEST");
    gtk_window_set_default_size(GTK_WINDOW(window5), 300 , 50);
    gtk_window_set_position(GTK_WINDOW(window5), GTK_WIN_POS_CENTER);
    GtkWidget *  label5 = gtk_label_new("Sharing Request") ;
    GtkWidget * fixed5 = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window5), fixed5);
    gtk_fixed_put(GTK_FIXED(fixed5), label5, 70 , 15 );


    g_signal_new("sharing-screen-request",
                     G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
                     0, NULL, NULL,
                     g_cclosure_marshal_VOID__POINTER,
                     G_TYPE_NONE, 1, G_TYPE_POINTER);




    g_signal_connect(G_OBJECT(window5), "sharing-screen-request",
                     G_CALLBACK(sharingScreenRequest), window5);


     GThread * thread = g_thread_new ("worker", listenfunction , window5);



    gtk_main();


    g_thread_unref (thread);



}
