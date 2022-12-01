#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>


#define PORTNO 10200
int createserversocket(struct sockaddr_in seraddr, int sockfd) {

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = INADDR_ANY;
	seraddr.sin_port = htons(PORTNO);

	bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
	listen(sockfd, 5);

	return sockfd;
}
void performservertask(struct sockaddr_in cliaddr, int sockfd) {
	int newsockfd, clilen = sizeof(int), n = 1;

	printf("Server waiting\n");
	newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
	char ip[INET_ADDRSTRLEN];	
	
	while (1) {
		char buf[256];
		printf("SERVER WAITING....\n");
		n = read(newsockfd, buf, sizeof(buf));
		printf("MESSAGE FROM CLIENT : %s\n", buf);
		int i = 0;
		if (strcmp(buf, "quit") == 0) {
			return;
		}
		while (buf[i] != '\0') {
			buf[i] = toupper(buf[i]);
			i++;
		}
		n = write(newsockfd, buf, sizeof(buf));
		puts(buf);
		inet_ntop(AF_INET, &(cliaddr.sin_addr), ip, INET_ADDRSTRLEN);
		printf("connection established with IP : %s\n PORT : %d\n",ip, ntohs(cliaddr.sin_port));
	}
}


int main() {
	int sockfd, newsockfd, portno;
	struct sockaddr_in seraddr, cliaddr;

	sockfd = createserversocket(seraddr, sockfd);

	
	performservertask(cliaddr, sockfd);

}