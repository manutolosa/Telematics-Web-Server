#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void launch(struct Server *my_server){

   //char buffer[30000];
   char server_msg[30] = "HTTP1.1/ 200 OK";
   char client_request[1048];

   while(1){
      printf("====== WAITING FOR CONNECTION ========\n");
      int address_len = sizeof(my_server->address);

      //Before to create a new socket, we need to accept the server socket.
      //Hold the client server -> When you accept the connection, what you get back is the client socket.
      int client_socket = accept(my_server->socket, (struct sockaddr *)&my_server->address, (socklen_t *)&address_len );

      //Now we have a client that we can send data to:
      send(client_socket, server_msg, sizeof(server_msg), 0);
      //close(my_server->socket);

      while(1){
         read(client_socket, client_request, sizeof(client_request));
         printf("%s\n", client_request);
      };


   };

   


};

int main(){

   struct Server my_server = server_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10 , launch);
   my_server.launch(&my_server);

   
}