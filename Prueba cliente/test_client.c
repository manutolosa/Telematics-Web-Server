#include "Cliente.h"
#include <stdio.h>
#include <unistd.h>



int main(){

   struct Client my_client = client_contructor(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
    close(my_client.socket);
   
}