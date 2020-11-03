#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<time.h>

// void str_echo(int connfd, int port){
//	int n;
//	int bufferSize = 1024;
//	char *buffer = malloc(bufferSize);
//	char buffer[1024];
//	while((n = recv(connfd, buffer, bufferSize, 0)) > 0){
//		printf("Client %d: %s\n", port, buffer);
//		send(connfd, buffer, n, 0);
//	}
// }

int main(){
	int listenfd, connfd, pid;
	socklen_t addrlen;
	char fname[256];
	time_t ticks;
	//listenfd -- parent		connfd   -- child
	struct sockaddr_in address, cliaddr;
	
//	use if condition here ensure safe termination
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Socket created successfully!\n");
	
//	STAR
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(15000);
	
	addrlen = sizeof(address);
	if(bind(listenfd, (struct sockaddr*) &address, addrlen) != 0){
		printf("Server Crashed!\n");
	} else {
		printf("Server is listening after bind().\n");
	}
	
	listen(listenfd, 1100);
	
	getsockname(listenfd, (struct sockaddr *)&address, &addrlen);
	printf("The server %s is connected, binded at port no %d\n", inet_ntoa(address.sin_addr), htons(address.sin_port));
	
	while(1){
		addrlen = sizeof(struct sockaddr_in);
		
		connfd = accept(listenfd, (struct sockaddr*) &address, &addrlen);
		
		if(connfd > 0)
			printf("The client's IP is %s and port no is %d\n",
										inet_ntoa(address.sin_addr), htons(address.sin_port));
		
		ticks = time(&ticks);
		snprintf(fname, sizeof(fname), "Current time is = %s", ctime(&ticks));
		send(connfd, fname, 37, 0);
		printf("Current time = %s", ctime(&ticks));
		close(connfd);
	}
	return 0;
}
