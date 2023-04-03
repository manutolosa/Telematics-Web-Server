#include "Server.h"
#include <stdio.h>
#include <unistd.h>

void launch(struct Server *server){

   char buffer[30000];
   //char *hello = "HTTP1.1/ 200 OK"

   while(1){
      prinf("====== WAITING FOR CONNECTION ========\n");
      int address_len = sizeof(server->address);

      //Before to create a new socket, we need to accept the server socket.
      int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_len );

      read(new_socket, buffer, 30000);
      printf("%s\n", buffer);

   };

   


};

int main(){

   struct Server my_server = server_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10 , launch);
   my_server.launch(&my_server);
}