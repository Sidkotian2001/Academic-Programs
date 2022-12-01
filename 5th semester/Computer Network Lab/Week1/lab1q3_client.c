#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>

#define PORTNO 10200

int createclientsocket(struct sockaddr_in address, int sockfd) {
	int len, result;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
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
	

    while (n) {
        printf("\nSEND A SENTENCE\t");
        gets(ch);
        ch[strlen(ch)] = '\0';

        write(sockfd, ch, strlen(ch));

        printf("MESSAGE RECEIVED FROM THE SERVER IS : \n");
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