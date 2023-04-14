#include "Cliente.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(){

    char request[1024]; 
    char* response;

   struct Client my_client = client_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);

    if ( (connect(my_client.socket, (struct sockaddr*)&my_client.address, sizeof(my_client.address))) < 0){
    perror("Failed to connect to the remote socket...");

   };

   //receive data from the server.
   char server_response[256];
   recv(my_client.socket, &server_response, sizeof(server_response), 0); 


    //Print out the server's response
    printf("%s\n", server_response);

    
   while(1){
   fgets(request, sizeof(request), stdin);
   send(my_client.socket, request, sizeof(request),0);
   // close(my_client.socket);
   recv(my_client.socket, &response, sizeof(response),0);
   printf("%s\n",response);
   };
   return 0;
}