#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main (int argc, char *argv[]){

	struct sockaddr_in server, client;
	int client_socket, socket_desc, c, read_size;
	char *message, *client_message;

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_desc == -1) puts ("fail");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8080);

	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0){
		puts("bind failed");
	}

	puts("binded");

	listen(socket_desc, 3);

	puts("waiting for connection");

	c = sizeof(struct sockaddr_in);
	
	while(client_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)){			
		read_size = recv(client_socket, client_message, 2000, 0);
		puts("connection accepted");
		
		client_message[read_size] = '\0';

		message = "helo back from kekistan";
		puts(client_message);

		write(client_socket, message, strlen(message));
	}

	if(client_socket < 0){
		puts("accept fail");
	}

	return 0;

}
