#include "Server.h"
#include "Parser.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void launch(struct Server *my_server){


   //char* server_msg = "Trying INADDR_ANY...\nConnected to Telematis Web Server.";
   char client_request[1048];

   while(1){
      printf("====== WAITING FOR CONNECTION ========\n");
      int address_len = sizeof(my_server->address);

      //Before to create a new socket, we need to accept the server socket.
      //Hold the client server -> When you accept the connection, what you get back is the client socket.
      int client_socket = accept(my_server->socket, (struct sockaddr *)&my_server->address, (socklen_t *)&address_len );

      //Now we have a client that we can send data to:
     // send(client_socket, server_msg, strlen(server_msg), 0);
      //write(client_socket, server_msg, strlen(server_msg));

      read(client_socket, client_request, sizeof(client_request));
      //recv(client_socket, &client_request, sizeof(client_request), 0); 
      printf("%s",client_request);
      struct Parser my_parser = parser_constructor(client_request);
      version_checker(my_parser);
      method_checker(my_parser, client_socket);
      close(client_socket);
      

      

         
         
   /*
      //Saving our request in a file i order to be parsing it later
      FILE *request_FILE = fopen("request.txt", "wb");
      if (request_FILE == NULL){
           perror("HTTP /1.1 400 Bad Request :(");
        }else{
            fgets(client_request, sizeof(client_request), request_FILE);
             
            fclose(request_FILE);
            printf("Se ha cerrado el archivo");
            printf("El contenido del archivo es:\n");
            fopen("request.txt", "r");

            while(!feof(request_FILE)){
               int char_leido = fgetc(request_FILE);
               printf("%c", char_leido);
            };
   
         }

       */  
   
   };
      

};


int main(int argc, char* argv[]) {

   struct Server my_server = server_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10 , launch);
   my_server.launch(&my_server);

   //while(!feof(html_data)){
   //   int char_leido = fgetc(html_data);
   //   printf("%c", char_leido);
   //};


   //File poiter to hold the data
   //FILE *html_data = fopen("resources/index.html", "rb");
   
   return 0;
}