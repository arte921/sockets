#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main (int argc, char *argv[]){
	
	struct sockaddr_in server;
	char server_reply[200];

	int socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_desc == -1) {
	       	puts("big fail");
		return 1;
	}
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);

	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0){
		puts("big bad");
		return 1;
	}

	puts("connected");
	
	//char *message = "GET / HTTP/1.1\r\n\r\n";
	
	char *message = "ghelo from them interwebz";

	if(send(socket_desc, message, strlen(message), 0) < 0){
		puts("send fail");
		return 1;
	}

	puts("sent data");
	
	if(recv(socket_desc, server_reply, 2000, 0) < 0){
		puts("recieve failed");
	}

	puts("recieved reply");
	puts(server_reply);

	return 0;

}






