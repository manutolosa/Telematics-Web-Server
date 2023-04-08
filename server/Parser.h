#ifndef Parser_h
#define Parser_h

#include "Server.h"

struct Parser{


    char* request_line;
    char* method;
    char* URI;
    char* version; 
    
};

struct Parser parser_constructor(char* request_line);

void method_checker(struct Parser my_parser, int client_socket);    
char* URI_checker(struct Parser my_parser);                                                                 
void version_checker(struct Parser my_parser);  

void isGET(struct Parser my_parser, int client_socket);                                  
void isPOST(struct Parser my_parser);                                   
void isHEAD(struct Parser my_parser);  

void modify_logger(struct Parser my_parser);
   
#endif
