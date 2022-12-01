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
	int n, size = 5, num, pid;
	char ch[256];
	int arr[5];
	int s_arr[5];

		// printf("Enter the size of the array\n");
		// scanf("%d", &size);

		for (int i = 0; i < size; i++) {
			printf("Enter the elements\n");
			scanf("%d", &arr[i]);
			
		}
		write(sockfd, &arr, sizeof(arr));
		printf("Sending msg to server\n");
		printf("msg SENT BACK FROM SERVER IS.....");
		n = read(sockfd, &s_arr, sizeof(s_arr));
		n = read(sockfd, &pid, sizeof(pid));
		if (n) {
			printf("received msg from server\n");
		}
		for (int i = 0; i < sizeof(s_arr) / sizeof(s_arr[0]); i++) {
			printf("%d ", s_arr[i]);
		}

		printf("Process id : %d", pid);
	
	
}

int main() {
	int sockfd;
	struct sockaddr_in address;

	sockfd = createclientsocket(address, sockfd);
	
	performclienttask(sockfd);

}