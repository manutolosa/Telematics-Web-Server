#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>s



char* response = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
char buffer_response[262144] = {"\0"};
char client_request[1048];

struct Token{

    char* method;
    char* URI;
    char* version; 

};


void HTTP_handler(struct Token my_token, char* request_line, int client_socket){

    my_token.method = strtok(request_line, " ");
    my_token.URI = strtok(NULL, " ");
    my_token.version = strtok(NULL, " "); 
    

    if(strcmp(my_token.version, "HTTP/1.1\n") < 0 || strcmp(my_token.version, "HTTP/1.1\n") > 0){
      perror("HTTP/1.1 400 Bad request -> Version");
    }else{
      printf("La versión fue verificada\n");
    }

    
    for(int i = 0; i < strlen(my_token.URI); i++ ){
        my_token.URI[i] = my_token.URI[i+1];
    }

    printf("%s", my_token.URI);
    
    

    
    if (strcmp(my_token.method, "GET") == 0){
        printf("Recibí un GET\n");
        FILE* file = fopen(my_token.URI, "r");

	    if (file == NULL) {
            perror("HTTP/1.1 404 File Not found :(");
	    }else {
		    printf("%s does exist \n", my_token.URI);
	}

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* temp = malloc(sizeof(char) * (fsize+1));
    fread(temp,fsize,1,file);
    strcpy(buffer_response,response);
    strcat(buffer_response,temp);
    printf("buffer: ");
    printf("%s",buffer_response);
    
	fclose(file);
    send(client_socket, buffer_response, strlen(buffer_response), 0);



    }else if (strcmp(my_token.method, "POST") == 0){
        printf("Recibí un POST\n");

    }else if(strcmp(my_token.method, "HEAD") == 0){
        printf("Recibí un HEAD\n");
    }else{
        perror("HTTP/1.1 400 Bad request -> Method");
    }

    
};   
    


void launch(struct Server *my_server){


   //char* server_msg = "Trying INADDR_ANY...\nConnected to Telematis Web Server.";
   

   while(1){
      printf("\n====== WAITING FOR CONNECTION ========\n");
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
      struct Token my_token;
      HTTP_handler(my_token, client_request, client_socket);
      
      
      

      close(client_socket);
      


   
   };
      

};


int main(int argc, char* argv[]) {

   struct Server my_server = server_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10 , launch);
   my_server.launch(&my_server);
   
   return 0;
}