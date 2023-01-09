#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex, empty, full;
int arr[10], r = 0, f = 0;
void *producer(void *args) {
	for (int i = 0; i < 10; i++) {
		sem_wait(&empty);

		sem_wait(&mutex);
		printf("Produced item : %d\n", i);
		arr[(++r) % 5] = i;
		sleep(1);
		sem_post(&mutex);

		sem_post(&full);
	}
}

void *consumer(void *args) {
	for (int i = 0; i < 10; i++) {
		sem_wait(&full);

		sem_wait(&mutex);
		int item = arr[(++f) % 5];
		printf("consumed item : %d\n", i);
		sleep(1);
		sem_post(&mutex);

		sem_post(&empty);
	}
}

int main() {
	pthread_t thread1, thread2;
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 1);
	sem_init(&empty, 0, 5);

	pthread_create(&thread1, 0, producer, 0);
	pthread_create(&thread2, 0, consumer, 0);

	pthread_join(thread1, 0);
	pthread_join(thread2, 0);

	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	return 0;
}