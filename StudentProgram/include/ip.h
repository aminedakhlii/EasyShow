#ifndef IP_H
#define IP_H

static size_t handle_response(void *ptr, size_t size, size_t nmemb, void *stream) ;

int get_room_ip(const char username[20] , const char roomnbr[7] , char * ip) ;

#endif
