#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#include "my_socket.h"
#include "../common/error_fail.h"

int create_socket_on_port( int port ) 
{
    int result;

    if ( ( result = socket( AF_INET, SOCK_STREAM, 0 ) ) == 0 ) { 
        fail_on_error();
    } 

    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 
       
    if ( bind( result, ( struct sockaddr * ) &address,  
                                 sizeof( address ) ) <0 ) { 
        fail_on_error();
    } 

    return result;
}