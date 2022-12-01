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
	seraddr.sin_addr.s_addr = htons(INADDR_ANY);
	seraddr.sin_port = PORTNO;
	bind(sockfd,(struct sockaddr*)&seraddr, sizeof(seraddr));
	listen(sockfd, 5);

	return sockfd;
}
void performservertask(struct sockaddr_in cliaddr, int sockfd) {
	int newsockfd, clilen = sizeof(clilen), n = 1;
	char *buf;

	time_t rawtime;
	struct tm *time_info;
	int hr, m, sec, pid;

	

	printf("SERVER WAITING");
	newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr, &clilen);
	n = read(newsockfd, buf, sizeof(buf));

	time(&rawtime);
	time_info = localtime(&rawtime);
	buf = asctime(time_info);
	printf("The current time is : %s", buf);

	hr = time_info->tm_hour;
	m = time_info->tm_min;
	sec = time_info->tm_sec;
	pid = getpid();

	write(newsockfd, &hr, sizeof(hr));
	write(newsockfd, &m, sizeof(m));
	write(newsockfd, &sec, sizeof(sec));
	write(newsockfd, &pid, sizeof(pid));

}


int main() {
	int sockfd, newsockfd, portno;
	struct sockaddr_in seraddr, cliaddr;

	sockfd = createserversocket(seraddr, sockfd);

	
	performservertask(cliaddr, sockfd);

}