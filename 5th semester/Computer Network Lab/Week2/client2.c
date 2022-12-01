#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

#define PORTNO 10200

int createclientsocket(struct sockaddr_in address, int sockfd) {
	int len, result;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htons(INADDR_ANY);
	address.sin_port = htons(PORTNO);
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr*)&address, len);
	if (result == -1) {
		perror("\nCLIENT ERROR");
		exit(1);
	}

	return sockfd;
}

void performclienttask(int sockfd) {
	int n;
	char ch[256], buf[256];
	while(1) {
		printf("\nENTER THE SENTENCE\n");
		gets(ch);
		ch[strlen(ch)] = '\0';
		write(sockfd, ch, strlen(ch));
		printf("msg SENT BACK FROM SERVER IS.....");
		n = read(sockfd, buf, sizeof(buf));
		puts(buf);
	}
	
}

int main() {
	int sockfd;
	struct sockaddr_in address;

	sockfd = createclientsocket(address, sockfd);
	
	performclienttask(sockfd);

}