#include "Cliente.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char request[1048]; 
char response[1048];
int main(){
   struct Client my_client = client_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
   while(1){
   fgets(request, sizeof(request),stdin);
   
   send(my_client.socket,request,sizeof(request),0);

  // while(1){
   recv(my_client.socket, &response, sizeof(response),0);
   //   }
      printf("%s\n",response);
   }
   return 0;
}