#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>

void str_cli(FILE *fp, int sockfd){
	int buffsize = 1024, cont;
	char* buffer = malloc(buffsize);
	char* buffer1 = malloc(buffsize);
	while(fgets(buffer, buffsize, fp) != NULL){
	//DOUBT! if I put sizeof(buffer) instead of 1024, it only sends 8 chars at max in the buffer.
		send(sockfd, buffer, 1024, 0);
		
		if((cont = recv(sockfd, buffer1, buffsize, 0)) > 0){
			fputs(buffer1, stdout);
		}
	}
	printf("\nEOF\n");
}

int main(int argc, char *argv[]){
	int sockfd;
	
	struct sockaddr_in address;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0){
		printf("Socket created successfully!\n");
	}
	
	address.sin_family = AF_INET;
	address.sin_port = htons(15001);
	
	//STAR
	inet_pton(AF_INET, argv[1], &address.sin_addr);
	
	if(connect(sockfd, (struct sockaddr*) &address, sizeof(address)) == 0){
		printf("connected successfully!\n");
	}
	
	str_cli(stdin, sockfd);
	
	return close(sockfd);
}
