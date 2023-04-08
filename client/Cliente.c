#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>

struct Client client_contructor(int domain, int service, int protocol, int port, unsigned long interf){

    struct Client client;

    client.domain = domain;
    client.service = service;
    client.protocol = protocol;
    client.port = port;
    client.interf = interf;

    client.address.sin_family = domain;
    client.address.sin_port = htons(port); //It converts our integer port into bytes that are going to refer a network port
    client.address.sin_addr.s_addr = htonl(interf); // The real   Client address that we are going to be connecting to...
                                                   // When sending INADD_ANY We are using any address that is running in our local machine 


   //now we can use the  parameters of the address to create the sockets for the server
   client.socket = socket(domain, service, protocol);

   //SOCKET socket(int af, int type, int protocol) -> Creates a socket communication with the network 

   if ( (connect(client.socket, (struct sockaddr*)&client.address, sizeof(client.address))) < 0){
    perror("Failed to connect to the remote socket...");

   };

   //receive data from the server.
   char server_response[256];
   recv(client.socket, &server_response, sizeof(server_response), 0); 


    //Print out the server's response
    printf("%s\n", server_response);
   return client;   
};