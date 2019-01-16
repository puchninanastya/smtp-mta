#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "rexprs.h"
#include "server_fsm_handlers.h"
#include "server.h"
#include "config.h"
#include "error_fail.h"
#include "helpers.h"
#include "my_socket.h"

extern struct server my_server;

int send_message_to_client( int client_fd, const char* response )
{
    printf( "Trying to send message to client with fd %d...\n", client_fd );
    //const char* message_to_send = "OK!\r\n";
    ssize_t actual_sent = send( client_fd, response, strlen( response ), 0 );
    if ( actual_sent < 0 ) {
        fail_on_error( "Can not sent data to client!" );
    }
    printf( "Message \"%s\" sent to client.\n", response );
    return 0;
}

int HANDLE_ACCEPTED( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle accepted.\n" );
    fcntl( client_fd, F_SETFL, O_NONBLOCK );
    if ( my_server.max_fd >= my_server.clients_size ) {
        printf( "Reallocing clients array.\n" );
        my_server.clients = realloc( my_server.clients,
                ( my_server.max_fd / CLIENTS_REALLOC_STEP + 1) * CLIENTS_REALLOC_STEP
                * sizeof( client_info* ) );
        my_server.clients_size += CLIENTS_REALLOC_STEP;
    }
    client_info* client = malloc( sizeof( client_info ) );
    memset( client, 0, sizeof( client_info ) );
    client->buffer = malloc( BUFFER_SIZE );
    memset( client->buffer, 0, BUFFER_SIZE );
    client->buffer_data_size = 0;
    client->smtp_state = SMTP_SERVER_ST_READY;
    my_server.clients[ client_fd ] = client;
    printf( "New client current smtp state: %d\n", my_server.clients[ client_fd ]->smtp_state );
    return nextState;
}

int HANDLE_CMND_HELO( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handling command HELO...\n" );
    client_info* client = my_server.clients[ client_fd ];

    // TODO: add DNS checking

    /* compare command data address and real client ip address */

    char* host = find_domain( client->buffer );
    printf( "Debug: Host: %s\n", host );

    char* host_ip = get_socket_ip_address( client_fd );
    printf( "Debug: Peer's IP address is: %s\n", host_ip );

    if ( strcmp( host, host_ip ) == 0 ) {
        printf( "Client's (%d) address is verified.\r\n", client_fd );
    } else {
        // it doesn't matter
        printf( "Client's (%d) address is not verified!\r\n", client_fd );
    }

    send_message_to_client( client_fd, RE_RESP_OK );

    printf( "Handling command HELO finished.\n" );
    return nextState;
}

int HANDLE_CMND_EHLO( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle command EHLO.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}

int HANDLE_CMND_MAIL( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle command MAIL.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}

int HANDLE_CMND_RCPT( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle command RCPT.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}

int HANDLE_CMND_DATA( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle command DATA.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}

int HANDLE_MAIL_DATA( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle mail data.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}

int HANDLE_MAIL_SAVED( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle mail saved.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}

int HANDLE_MAIL_END( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle mail end.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}

int HANDLE_CMND_RSET( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle command RSET.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}

int HANDLE_CLOSE( int client_fd, te_smtp_server_state nextState )
{
    printf( "Handle close.\n" );
    send_message_to_client( client_fd, RE_RESP_OK );
    return nextState;
}
