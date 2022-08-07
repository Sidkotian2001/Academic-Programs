#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 10200

int createserversocket(struct sockaddr_in seraddr, int sockfd) {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = htons(INADDR_ANY);
	seraddr.sin_port = htons(PORTNO);
	bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
	
	listen(sockfd, 5);
	return sockfd;
}

void performservertask(struct sockaddr_in cliaddr, int sockfd) {
	int newsockfd, clilen = sizeof(clilen), n = 1;

	while (1) {
		char buf[256];
		clilen = sizeof(clilen);
		printf("server %d waiting\n", sockfd);
		newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
		if (fork() == 0) {
			n = read(newsockfd, buf, sizeof(buf));
			printf("The message from the client: %s\n", buf);
			n = write(newsockfd, buf, sizeof(buf));
			close(newsockfd);
			exit(0);
		}
		else {
			close(newsockfd);
		}
	}
	
}
int main() {
	int sockfd, newsockfd, portno;
	struct sockaddr_in seraddr, cliaddr;

	sockfd = createserversocket(seraddr, sockfd);

	
	performservertask(cliaddr, sockfd);
}