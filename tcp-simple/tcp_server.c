/*
 * WORKFLOW:
 *    socket() --> bind() --> listen() --> accept() --> send/recv()
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main () {

    char server_message[256] = "You have reached the server!";

    // create the server socket file descriptor
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);


    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to a specified IP and port
    bind(server_socket,
            (struct sockaddr *) &server_address,
            sizeof(server_address));

    listen(server_socket, 5);

    /*
     * accept connection from client
     * accept(int socket,
     *       struct client_address,
     *       int size_of_client_address)
     *
     */
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);



    /*
     * send message to client
     *
     * send(int client_socket,
     *      char * data,
     *      int size_of_data,
     *      int flag);
     */

    send(client_socket, server_message, sizeof(server_message), 0);

    // close the socket
    close(server_socket);

    return 0;
}
