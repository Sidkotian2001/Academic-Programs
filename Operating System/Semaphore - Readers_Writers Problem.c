#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wait;
pthread_mutex_t mutex_sem;
int count = 1, numreader = 0;

void *writer(void *wrno) {
	sem_wait(&wait);
	count *= 2;
	printf("writer %d modified count to %d \n", (*((int*)wrno)), count);
	sem_post(&wait);
}

void *reader(void *rno) {
	pthread_mutex_lock(&mutex_sem);
	numreader++;

	if (numreader == 1) {
		sem_wait(&wait);
	}
	pthread_mutex_unlock(&mutex_sem);
	printf("Reader %d read count as %d\n", *((int*)rno), count);
	pthread_mutex_lock(&mutex_sem);
	numreader--;
	if (numreader == 0) {
		sem_post(&wait);
	}
	pthread_mutex_unlock(&mutex_sem);
}

int main() {
	pthread_t read[10], write[5];
	pthread_mutex_init(&mutex_sem, NULL);
	sem_init(&wait, 0, 1);
	int a[10] = {1,2,3,4,5,6,7,8,9,10};

	for (int i = 0; i < 10; i++) {
		pthread_create(&read[i], 0, reader, &a[i]);
	}
	for (int i = 0; i < 5; i++) {
		pthread_create(&write[i], 0, writer, &a[i]);
	}
	for (int i = 0; i < 10; i++) {
		pthread_join(read[i], 0);
	}
	for (int i = 0; i < 5; i++) {
		pthread_join(write[i], 0);
	}

	pthread_mutex_destroy(&mutex_sem);
	sem_destroy(&wait);
	return 0;
}