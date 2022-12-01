#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int n;
void *even(void *arg) {
	int *arr = (int*)arg;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] % 2 == 0) {
			sum = sum + arr[i];
		}
		
	}

	return (void**)sum;
}

void *odd(void *arg) {
	int *arr = (int*)arg;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] % 2 != 0) {
			sum = sum + arr[i];
		}
		
	}

	return (void**)sum;
}

int main() {

	printf("Enter size\n");
	scanf("%d", &n);
	printf("Enter the values\n");
	int *arr = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	pthread_t thread1, thread2;
	pthread_create(&thread1, 0, even, (void*)arr);
	pthread_create(&thread2, 0, odd, (void*)arr);
	int sum1, sum2;
	pthread_join(thread1, (void**)&sum1);
	pthread_join(thread2, (void**)&sum2);

	printf("The even sum : %d\nThe even sum : %d\n", sum1, sum2);
	return 0;

}