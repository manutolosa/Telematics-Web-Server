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
    char buffer[262144] = {"\0"};
    char response[64] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
    strcpy(buffer,response);
    //strcat(buffer,response);
   // send(client_socket, response, sizeof(response), 0);
    //printf("%s", response);
    char* ruta = URI_checker(my_parser);
   // printf("RUTA: %s\n", ruta);
    
    
 //   FILE *response_FILE = fopen(ruta, "r");
 //   if (response_FILE == NULL){
 //       perror("HTTP /1.1 404 File/Page not found :(");
 //   }else{
  //      int index = 0;
   //     while(!feof(response_FILE)){
    //        buffer[index] = fgetc(response_FILE);
     //       index++;
      //      //printf("%c", char_leido);
       // };

   // }
    FILE* file = fopen(ruta, "r");

	if (file == NULL) {
		perror("HTTP /1.1 404 File/Page not found :(");
	}else {
		printf("%s does exist \n", ruta);
	}

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* temp = malloc(sizeof(char) * (fsize+1));
	char ch;
	int i = 0;
	//while((ch = fgetc(file)) != EOF) {
//		temp[i] = ch;
//		i++;
//	}
    fread(temp,fsize,1,file);
       
    //send(client_socket, temp, fsize, 0);
    
	fclose(file);
    printf("%s",temp);
    strcat(buffer,temp);
    
	
    //strcat(response, "\r\n\r\n");   
    //printf("\n");
    //char html[1028];
    //strcat(html,response);
    //strcpy(html,"<html><body>Este es un test</body></html>\n");
    //printf("%s",html);
    //char buffer2[1084] = "<html><body>Este es un test</body></html>\n";
    send(client_socket, buffer, sizeof(buffer), 0);
    //fclose(response_FILE);
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

void method_checker(struct Parser my_parser, int client_socket){
    //printf("%s\n", my_parser.method);
    
    if (strcmp(my_parser.method, "GET") == 0){
        isGET(my_parser, client_socket);

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
       // perror("HTTP/1.1 400 Bad Request -> Version\n");
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