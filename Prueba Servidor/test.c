#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct datos{
	int dclient_socket;
	char drequest[1048];
};

void* request_handler(void* datos){
   struct datos *d2 = (struct datos*)datos;
   printf("Entrò correctamente al hilo\n");
   printf(" Request: %s\n", (*d2).drequest);
   /**
    * Aqui debe ir el parsing
   */
   if(strcmp((*d2).drequest,"EXIT\n") == 0){ //Hay que tener cuidado, la funcion fgets deja almacenado los saltos de linea \n
      printf("Connection should end\n");
      close((*d2).dclient_socket);  //cierra conexion con el cliente
   }
   return NULL;
}



void launch(struct Server *my_server){
   pthread_t thread_request; 
   char request[1048];
   char server_msg[30] = "HTTP1.1/ 200 OK";

   while(1){
      printf("====== WAITING FOR CONNECTION ========\n");
      int address_len = sizeof(my_server->address);

      //Before to create a new socket, we need to accept the server socket.
      //Hold the client server -> When you accept the connection, what you get back is the client socket.
      int client_socket = accept(my_server->socket, (struct sockaddr *)&my_server->address, (socklen_t *)&address_len );

      //Now we have a client that we can send data to:
      send(client_socket, server_msg, sizeof(server_msg), 0);
      //close(my_server->socket);

      struct datos d1;
      d1.dclient_socket = client_socket;



      while(1){
      read(client_socket, request, sizeof(request));
      strcpy(d1.drequest,request);
      pthread_create(&thread_request,NULL,request_handler,(void *)&d1); //Mando a un nuevo hilo la ultima request
      //printf("%s", request);
      printf("Salio del hilo\n"); 
      }
      close(my_server->socket);
   };

   


};

int main(){

   struct Server my_server = server_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10 , launch);
   my_server.launch(&my_server);

   
}