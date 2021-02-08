#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#include<arpa/inet.h>
#include<netinet/in.h>

#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>

void str_echo(FILE *fp, int sockfd){
	int buffSize = 1024;
	char* buffer = malloc(buffSize);
	
	while(fgets(buffer, buffSize, fp) != NULL){
		send(sockfd, buffer, buffSize, 0);
		
		if(recv(sockfd, buffer, buffSize, 0) >= 0){
			fputs(buffer, stdout);
		}
	}
}

int main(int argc, char*argv[]){
	int sockfd, conn;
	socklen_t addrlen;
	struct sockaddr_in address;
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
		printf("Socket Created %d!\n", sockfd);
		
	address.sin_family = AF_INET;
	address.sin_port = htons(15001);
	
	inet_pton(AF_INET, argv[1], &address.sin_addr.s_addr);
	
//	addrlen = sizeof(address);
	if((conn = connect(sockfd, (struct sockaddr*)&address, sizeof(address))) == 0)
		printf("Connected to Server!\n");
	else 
		printf("Connection failed!\n");

	str_echo(stdin, sockfd);
	
	return 0;
}

/*#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#include<arpa/inet.h>
#include<netinet/in.h>

void str_cli(FILE *fp,int sockfd){
	int bufs=1024,cont;
	char *buff = malloc(bufs);

	while((fgets(buff,bufs,fp)!=NULL)){
		send(sockfd,buff,bufs,0);

		if((cont = recv(sockfd,buff,bufs,0)) >=0)
			fputs(buff,stdout);
	}

	printf("str cli\n");

	printf("\nEOF\n");
}
		
int main(int argc, char* argv[]){
	int create_socket,ret;

	struct sockaddr_in address;

	if((create_socket = socket(AF_INET,SOCK_STREAM,0)) >0)
		printf("Socket created\n");
	else
		printf("Socket creation error");

	address.sin_family = AF_INET;
	address.sin_port = htons(15001);

	inet_pton(AF_INET,argv[1],&address.sin_addr);

	if( (ret=connect(create_socket,(struct sockaddr *) &address,sizeof(address))) == 0)
		printf("Connected\n");
	else
		printf("Error in connect");

	//if(ret==ETIMEDOUT)
	//	printf("Timeout\n");
	//if(ret==EPROTOTYPE)
	//	printf(" Prototype error\n");
	//if(ret==ENOTSOCK)
	//	printf("Not socke error");
	
	str_cli(stdin,create_socket);

	return 0;
}
*/
