#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct my_arr {
	int n;
	int arr[1000];
};

void* sum_odd(void* params) {
	struct my_arr *obj = (struct my_arr*)params;
	int sum = 0;
	for (int i = 0; i < obj->n; i++) {
		if (obj->arr[i] % 2 != 0) {
			sum = sum + obj->arr[i];
		}
	}

	return (void*)sum;
}

void* sum_even(void* params) {
	struct my_arr *obj = (struct my_arr*)params;
	int sum = 0;
	for (int i = 0; i < obj->n; i++) {
		if (obj->arr[i] % 2 == 0) {
			sum = sum + obj->arr[i];
		}
	}

	return (void*)sum;
}

int main() {
	pthread_t thread1, thread2;
	struct my_arr* obj;
	obj = (struct my_arr*)malloc(sizeof(struct my_arr));
	fprintf(stdout, "enter the size of the array\n");
	scanf("%d", &(obj->n));
	write(1, "Enter the elements\n", sizeof("Enter the elements\n"));
	for (int i = 0; i < obj->n; i++) {
		scanf("%d", &(obj->arr[i]));
	}

	pthread_create(&thread1, 0, &sum_odd, (void*)obj);
	pthread_create(&thread2, 0, &sum_even, (void*)obj);
	
	int odd_sum, even_sum;
	pthread_join(thread1, (void**)&odd_sum);
	pthread_join(thread2, (void**)&even_sum);

	printf("The odd sum : %d the even sum : %d\n", odd_sum, even_sum);

	return 0;
}