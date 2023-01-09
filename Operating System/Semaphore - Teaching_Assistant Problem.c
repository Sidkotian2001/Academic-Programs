#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex, empty, full;
int hall_chairs[3], c = 0;
int students[10];
void *student(void *params) {
	// int stu = (int)params;
	printf("Hello");
	sem_wait(&empty);
	// hall_chairs[(c++) % 3] = stu;

	sem_wait(&full);
	sem_post(&empty);

	sem_wait(&mutex);
	printf("Student in class is : %d", c++);
	c += 1;
	sleep(1);
	sem_post(&mutex);

	sem_post(&full);


}



int main() {
	int n = 10;

	pthread_t threads[n], thread2;
	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, 3);
	sem_init(&full, 0, 1);
	// pthread_create(&thread2, 0, teacher);
	for (int i = 0; i < n; i++) {
		pthread_create(&threads[i], 0, student,0 );		
	}
	// pthread_join(thread2, 0);
	for (int i = 0; i < n; i++) {
		pthread_join(threads[i], 0);
	}

	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
}