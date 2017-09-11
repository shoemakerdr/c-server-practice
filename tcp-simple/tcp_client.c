#include <stdio.h>
#include <stdlib.h>

// For definitions and API for socket functions
#include <sys/types.h>
#include <sys/socket.h>

// For structures for storing address information
#include <netinet/in.h>

int main () {

    // Create socket. Int holds socket descriptor which has information about our socket
    int network_socket;

    /* Call socket function, store result in network_socket int
     *
     * socket(int domain, int type, int protocol)
     *
     * AF_INET is domain of the socket. AF_INET is constant, essentially meaning
     * 'the internet'
     *
     * SOCK_STREAM is the type of socket, specifically a steaming socket.
     *
     * 0 refers to the protocol of a given type. Usually most types only have 
     * one protocol, so 0 is given as a default. In this case, 0 means TCP
     */
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // declare a structure to specify connection server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    // htons puts the integer port number in proper network byte order
    server_address.sin_port = htons(9000);
    /* 
     * sin_addr is a structure that holds the address information
     *
     * s_addr is the actual address
     *
     * INADDR_ANY is any address on our local machine
     */
    server_address.sin_addr.s_addr = INADDR_ANY;

    /* Call connect with server address information
     * 
     * connect returns an integer-- anything other than 0 is an error
     * 
     * connect(int socket, struct sockaddr * address_of_server, int size)
     *
     * Network_socket is the socket were connecting from
     *
     * The second argument is a pointer to the address of the server. This
     * needs to be cast as a sockaddr struct pointer since it is a sockaddr_in struct
     * currently. The '&' gets the address in memory of the server_address struct
     * and the '(struct sockaddr *)' casts it to a sockaddr pointer.
     *
     * The third argument is just the size of the server address struct.
     *
     */
    int connection_status = connect(network_socket,
            (struct sockaddr *) &server_address,
            sizeof(server_address));

    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket \n\n");
    }

    /* Receive data from the socket
     *
     * recv(int socket, char * response_buffer, int size_of_response_buffer, int flag)
     *
     * response buffer is the address of a buffer to hold the response from the server
     *
     * the flag is usually set to 0
     * 
     */
    char server_response[256];

    recv(network_socket, &server_response, sizeof(server_response), 0);


    // print out response from the server
    
    printf("The server sent the data: %s\n\n", server_response);

    // close socket
    close(network_socket);


    return 0;
}

