#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define TEXT_SZ 2048

struct shared_use_st{
	int written_by_you;
	char some_text[TEXT_SZ];
};

int main() {
	int running = 1;
	void *shared_memory = (void*)0;
	struct shared_use_st *shared_stuff;
	char buffer[BUFSIZ];
	int shmid;
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit (EXIT_FAILURE);
	}
	shared_memory = shmat(shmid, (void*)0, 0);
	if (shared_memory == (void*)-1) {
		fprintf(stderr, "shmat falied\n");
		exit (EXIT_FAILURE);
	}
	printf("memory attached at %X\n", (int)shared_memory);
	shared_stuff = (struct shared_use_st*)shared_memory;
	while (running) {
		while (shared_stuff->written_by_you == 1) {
			sleep(1);
			printf("waiting for client...\n");
		}
		printf("enter some text\n");
		fgets(buffer, BUFSIZ, stdin);
		strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
		shared_stuff->written_by_you = 1;
		if (strncmp(buffer, "end", 3) == 0) {
			running = 0;
		}
	}
	int re;
	if ((re = shmdt(shared_memory)) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}