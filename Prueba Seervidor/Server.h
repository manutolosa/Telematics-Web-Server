#ifndef Server_h
#define Server_h

#include <winsock2.h>
#include <ws2tcpip.h>



   struct Server{
      int domain;
      int service;
      int protocol;
      int port;
      u_long interf;
      int backlog;

      struct sockaddr_in address;

      int socket;

      void(*launch)(struct Server *server); //Member function to launch the server -> Is a poiter to a function

   };

   struct Server server_contructor(int domain, int service, int protocol, int port, u_long interf, int backlog, void (*launch)(struct Server *server));   
   


#endif 