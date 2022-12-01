#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 10200
void sort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

}

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
	int newsockfd, clilen = sizeof(clilen), n = 1, pid;

	while (1) {
		int size, num, arr[5];
		clilen = sizeof(clilen);
		printf("server %d waiting\n", sockfd);
		newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);

		if (fork() == 0) {


				int i = 0;
				n = read(newsockfd, &arr, sizeof(arr));

				sort(arr, sizeof(arr) / sizeof(arr[0]));
	
				pid = getpid();
				write(newsockfd, &arr, sizeof(arr));
				write(newsockfd, &pid, sizeof(pid));

			
			
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