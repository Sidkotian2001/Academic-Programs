#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *prime(void *arg) {
	int *arr = (int*)arg;
	int a = arr[0], b = arr[1];
	for (int i = a; i < b; i++) {
		int count = 0;
		for (int j = 1; j <= i; j++) {
			if (i % j == 0) {
				count++;
			}
		}
		if (count == 2) {
			printf("%d ", i);
		}
	}
}

int main() {
	int arr[2];
	printf("Enter the first number\n");
	scanf("%d", &arr[0]);
	printf("Enter the end number\n");
	scanf("%d", &arr[1]);

	pthread_t thread;
	pthread_create(&thread, 0, prime, (void*)arr);
	pthread_join(thread, 0);
	return 0;
}