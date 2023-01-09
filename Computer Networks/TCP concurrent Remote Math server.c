#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

#define PORTNO 10200

float operation(int op1, int op2, char operator) {
    // int op1 = arr[0];
    // int op2 = arr[1];
    switch(operator) {
        case '+':
        return op1 + op2;
        case '-':
        return op1 - op2;
        case '*':
        return op1 * op2;
        case '/':
        return op1 / op2;
        case '%':
        return op1 % op2;
        default:
        return -1;
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
	int newsockfd, clilen = sizeof(clilen), n = 1;

	while (1) {
		int size, num;
        char arr[5];
        int op1, op2;
        char operator;
		clilen = sizeof(clilen);
		printf("server %d waiting\n", sockfd);
		newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);

		if (fork() == 0) {
            int i = 0;
            // n = read(newsockfd, &arr, sizeof(arr));
            n = read(newsockfd, &op1, sizeof(op1));
            n = read(newsockfd, &op2, sizeof(op2));
            n = read(newsockfd, &operator, sizeof(operator));

            printf("Message received\n");
            float result = operation(op1, op2, operator);

            write(newsockfd, &result, sizeof(result));
			
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