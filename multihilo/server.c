#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>

struct datos{
	int dclient_socket;
	char dhttp_header[4096];
};

void* connection_handler(void* datos){
	struct datos *d2 = (struct datos*)datos;
	printf("Hilo creado\n");
	printf(" http_header: %s\n", (*d2).dhttp_header);

	while(1){
	send((*d2).dclient_socket,(*d2).dhttp_header, sizeof((*d2).dhttp_header), 0);
	close((*d2).dclient_socket);	
	}

	exit(0);
}
//Definimos el socket
int main(){
	FILE *html_data;
	html_data = fopen("index.html", "r");	//"el html a renderizar"

	char buffer[128];
	char response_data[2048] = {"\0"};
	while(fgets(buffer,sizeof(buffer),html_data)){
		strcat(response_data,buffer);	
	}
	

	char http_header[4096] = "HTTP/1.1 200 OK\r\n\n"; //respuesta
	strcat(http_header, response_data);

	//Creamos el socket
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	//Definimos la direccion
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8001); //puerto
	server_address.sin_addr.s_addr = INADDR_ANY; //cualquier direccion

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	printf("HTTP Server Initialized\nPort: %d\n", 8001);
	listen(server_socket, 5);

	int client_socket;
	pthread_t hilo_socket;


	struct datos d1;
	while(1){
	client_socket = accept(server_socket,NULL,NULL);
	d1.dclient_socket = client_socket;	
	strcpy(d1.dhttp_header,http_header);
	pthread_create(&hilo_socket,NULL,connection_handler,(void *)&d1 );
	//send(client_socket, http_header, sizeof(http_header), 0);
			
	
	}
	return 0;
}
