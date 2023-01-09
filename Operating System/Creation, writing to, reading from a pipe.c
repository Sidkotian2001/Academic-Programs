#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *find_sum(void *arg) {
	int n = (int)arg;
	int sum = 0;
	printf("Enter values\n");
	int *arr = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] >=0) {
			sum = sum + arr[i];
		}
	}

	return (void**)sum;
}

int main() {
	int n, sum;
	printf("Enter number of elements\n");
	scanf("%d", &n);
	
	pthread_t thread;
	pthread_create(&thread, 0, find_sum, (void*)n);
	pthread_join(thread, (void**)&sum);
	printf("the sum is : %d\n", sum);
	return 0;
}