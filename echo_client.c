#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>

void str_echo(int connfd, int port){
	int n;
	int bufferSize = 1024;
//	char *buffer = malloc(bufferSize);
	char *buffer;
	while((n = recv(connfd, buffer, bufferSize, 0)) >= 0){
		printf("Client %d: ", port);
		fputs(buffer, stdout);
		printf("\n");
		send(connfd, buffer, n, 0);
	}
}

int main(){
	int listenfd, connfd, pid;
	socklen_t addrlen;
	//listenfd -- parent
	//connfd   -- child
	struct sockaddr_in address;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Socket created successfully!\n");
	
//	STAR	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(15001);
	
	addrlen = sizeof(address);
	if(bind(listenfd, (struct sockaddr*) &address, addrlen) != 0){
		printf("Server Crashed!\n");
	} else {
		printf("Server is listening after bind().\n");
	}
	
	listen(listenfd, 1100);	
	
	while(1){
		addrlen = sizeof(struct sockaddr_in);
		
		connfd = accept(listenfd, (struct sockaddr*) &address, &addrlen);
		
		if(connfd > 0)
			printf("The client %s connected successfully!\n",
										inet_ntoa(address.sin_addr));
		if((pid = fork()) == 0){
			printf("Inside child process...\n");
			close(listenfd);
			str_echo(connfd, htons(address.sin_port));
			exit(0);
		}
		
		close(connfd);
	}
	return 0;
}
