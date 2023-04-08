#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Parser parser_constructor(char* request_line){

    struct Parser parser;
    parser.method = strtok(request_line, " ");
    parser.URI = strtok(NULL, " ");
    parser.version = strtok(NULL, " "); 
    
    

    return parser;
};

void isGET(struct Parser my_parser, int client_socket){
    //printf("Recibí un GET\n");

    //char* ruta = "resources/img/2017-12-19-19-22-29.jpg";
    //char* ruta = "resources/index.html";

    char response[64] = "\nHTTP /1.1 200 OK\nServer: TWS/1.0 ()\nConnection Type: Upgrade\n\n";
    //send(client_socket, response, sizeof(response), 0);
    printf("%s\n", response);
    char* ruta = URI_checker(my_parser);
   // printf("RUTA: %s\n", ruta);
    

    FILE *response_FILE = fopen(ruta, "r");
    if (response_FILE == NULL){
        perror("HTTP /1.1 404 File/Page not found :(");
    }else{

        while(!feof(response_FILE)){
            int char_leido = fgetc(response_FILE);
            printf("%c", char_leido);
        };

    }      

};



void isPOST(){
    printf("Recibí un POST\n");
};

void isHEAD(){
    printf("Recibí un HEAD\n");
};

void method_checker(struct Parser my_parser, int client_socket){
    //printf("%s\n", my_parser.method);
    
    if (strcmp(my_parser.method, "GET") == 0){
        isGET(my_parser, client_socket);

    }else if (strcmp(my_parser.method, "POST") == 0){
        printf("Recibí un POST\n");
        isPOST();

    }else if(strcmp(my_parser.method, "HEAD") == 0){
        printf("Recibí un HEAD\n");
        isHEAD();
    }else{
        perror("HTTP/1.1 400 Bad Request -> Method\n");
    }


    
};      


void version_checker(struct Parser my_parser){
    //printf("%s", my_parser.version);

    if(strcmp(my_parser.version, "HTTP/1.1\n") < 0 || strcmp(my_parser.version, "HTTP/1.1\n") > 0){
        perror("HTTP/1.1 400 Bad Request -> Version\n");
    }

};

char* URI_checker(struct Parser my_parser){
    for(int i = 0; i < strlen(my_parser.URI); i++ ){
        my_parser.URI[i] = my_parser.URI[i+1];
    }
    
    return my_parser.URI;

};