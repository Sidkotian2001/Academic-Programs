#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *arr;

void *fib(void *arg) {
	int n = (int) arg;
	int n1 = 0, n2 = 1;
	printf("The series is : \n");
	arr = (int*)calloc(n, sizeof(int));
	for (int i = 1; i < n; i++) {
		arr[i] = n1 + n2;
		n1 = n2;
		n2 = arr[i];
	}
	return (void**)arr;
}

int main() {
	int n ;
	printf("Enter a number\n");
	scanf("%d", &n);
	pthread_t thread;
	pthread_create(&thread, 0, fib, (void*)n);
	pthread_join(thread, (void**)&arr);
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}