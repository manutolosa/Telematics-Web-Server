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

void isGET(struct Parser my_parser){
    //printf("Recibí un GET\n");

    //char* ruta = "resources/img/2017-12-19-19-22-29.jpg";
    //char* ruta = "resources/index.html";

    //char response[64] = "\nHTTP /1.1 200 OK\nServer: TWS/1.0 ()\nConnection Type: Upgrade\n\n";
    //send(client_socket, response, sizeof(response), 0);
    //printf("%s", response);
    char* ruta = URI_checker(my_parser);
   // printf("RUTA: %s\n", ruta);
    

    FILE *response_FILE = fopen(ruta, "rb");
    FILE *response_GENERATION = fopen("response_GENERATION.txt", "a");

    if (response_FILE == NULL){
        perror("HTTP /1.1 404 File/Page not found :(");
    }else{
        fputs("\n", response_GENERATION);

        while(!feof(response_FILE)){
            int char_leido = fgetc(response_FILE);
            fputc(char_leido, response_GENERATION);
        };

    }   
    printf("\n");
    fclose(response_FILE);
    fclose(response_GENERATION);
    modify_logger(my_parser);

};



void isPOST(struct Parser my_parser){
    printf("Recibí un POST\n");
    modify_logger(my_parser);
};

void isHEAD(struct Parser my_parser){
    printf("Recibí un HEAD\n");
    modify_logger(my_parser);
};

void method_checker(struct Parser my_parser){
    //printf("%s\n", my_parser.method);

    if (strcmp(my_parser.method, "GET") == 0){
        isGET(my_parser);

      }else if (strcmp(my_parser.method, "POST") == 0){
        printf("Recibí un POST\n");
        isPOST(my_parser);

      }else if(strcmp(my_parser.method, "HEAD") == 0){
        printf("Recibí un HEAD\n");
        isHEAD(my_parser);
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

void modify_logger(struct Parser my_parser){


    FILE *logger_FILE = fopen("logger.txt", "a+");
    if (logger_FILE == NULL){
        perror("No se pudo modificar el logger");
    }else{
        fputs("A ", logger_FILE);
        fputs(my_parser.method, logger_FILE);
        fputs(" was processed\n", logger_FILE);

    }
    fclose(logger_FILE);
/*
    fopen("logger.txt", "r");
    printf("El contenido del logger es:\n");
    while(!feof(logger_FILE)){
        int char_leido = fgetc(logger_FILE);
        printf("%c", char_leido);
    };      
    //printf("\n");
    fclose(logger_FILE);
*/
}