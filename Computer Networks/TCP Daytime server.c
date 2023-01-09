#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define PORTNO 10200
int createserversocket(struct sockaddr_in seraddr, int sockfd) {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr("172.16.48.54");
	seraddr.sin_port = htons(PORTNO);
	bind(sockfd,(struct sockaddr*)&seraddr, sizeof(seraddr));
	listen(sockfd, 5);

	return sockfd;
}
void performservertask(struct sockaddr_in cliaddr, int sockfd) {
	int newsockfd, clilen = sizeof(clilen), n = 1;
	char* str;

	struct tm *ptr;
	time_t lt;
	lt = time(NULL);
	ptr = localtime(&lt);
	str = asctime(ptr);

	printf("SERVER WAITING");
	newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr, &clilen);
	n = read(newsockfd, str, sizeof(str));
	printf("\nTIME SENT BACK TO CLIENT IS %s \n", str);
	n = write(newsockfd, str, sizeof(str));

	n = read(sockfd, str, sizeof(str));
	puts(str);
}


int main() {
	int sockfd, newsockfd, portno;
	struct sockaddr_in seraddr, cliaddr;

	sockfd = createserversocket(seraddr, sockfd);

	
	performservertask(cliaddr, sockfd);

}