#include "Cliente.h"
#include <stdio.h>
#include <unistd.h>



int main(){

    char request[1048]; 

   struct Client my_client = client_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);

   while(1){
   scanf("\n %s", request);
   send(my_client.socket,request,sizeof(request),0);
   // close(my_client.socket);
   };
   return 0;
}