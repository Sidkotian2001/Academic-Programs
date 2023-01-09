#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t customer, barber;
pthread_mutex_t seat;
int free1 = 10;

void *barb(void *args) {
	while (1) {
		sem_wait(&customer);
		pthread_mutex_lock(&seat);
		if (free1 < 10) {
			free1++;
		}
		sleep(1);
		printf("cutting complete ! Free seatd : %d\n", free1);
		sem_post(&barber);
		pthread_mutex_unlock(&seat);
	}
}

void *cust(void *args) {
	while (1) {
		pthread_mutex_lock(&seat);
		if (free1 > 0) {
			free1--;
			printf("customer waiting free seats are : %d\n", free1);
			sem_post(&customer);
			pthread_mutex_unlock(&seat);
			sem_wait(&barber);
		}
		else {
			pthread_mutex_unlock(&seat);
		}
	}
	
}

int main() {
	pthread_t t[2];
	sem_init(&barber, 0, 1);
	sem_init(&customer, 0, 1);
	pthread_mutex_init(&seat, 0);
	pthread_create(&t[0], 0, &barb, 0);
	pthread_create(&t[1], 0, &cust, 0);
	pthread_join(t[0], 0);
	pthread_join(t[1], 0);
	sem_destroy(&barber);
	sem_destroy(&customer);
	pthread_mutex_destroy(&seat);
	return 0;
}