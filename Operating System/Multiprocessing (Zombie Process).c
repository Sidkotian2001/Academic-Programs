#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	printf("Starting parent process\n");
	int r_val= fork();

	switch(r_val){
		case -1:{
			perror("[*] fork\n");
			exit(EXIT_FAILURE);
		}
		break;

		case 0: {
			printf("[**] Inside child process\n");

            // getting and printing PID
            pid_t curr_ppid = getppid();
            printf("[**] Current parent: %d\n", curr_ppid);

            // Sleeping...
            for(int i = 0; i < 10; i++) {
                sleep(1);
                printf("[**] Sleeping child for %d seconds...\n", i + 1);
            }

            // getting and printing PID
            curr_ppid = getppid();
            printf("[**] Current parent: %d\n", curr_ppid);

            // exiting from the child program
            exit(0);
		}
		break;

		default: {
            // showing the current running process
            printf("[**] Executing ps\n");
            execl("/bin/ps", "ps", NULL);

            // exiting from the parent program
            exit(0);
        }
	}
}