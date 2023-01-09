#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

void roundrobin(int burst_time[], int arrival_time[], int n, int quantum) {
	int waiting_time[100], turnaround_time[100], remaining_time[100], priority[100];
	int complete = 0, pos, time = 0, i, check = 0, time_quantum = 0;
	int within_quantum = 0, min_arrival_time = arrival_time[0];
	for (int i = 0; i < n; i++) {
		remaining_time[i] = burst_time[i];
		priority[i] = n - i - 1;
	}
	int max_priority = priority[0] - 1;
	printf("The order is : \n");
	while (complete != n) {
		
		for (i = 0; i < n; i++) {
			if (arrival_time[i] <= time &&
				priority[i] > max_priority &&
				remaining_time[i] > 0) 
			{
				max_priority = priority[i];
				pos = i;
				within_quantum = 1;
			}
		}
		printf("%d ", pos + 1);
		while (within_quantum == 1) {
			if (time_quantum == quantum || remaining_time[pos] == 0) {
				within_quantum = 0;
				time_quantum = 0;
				max_priority = priority[pos] - 1;

				for (int j = 0; j < n; j++) {
					priority[j] += 1;
				}
				priority[pos] = 0;
				
			}
			else {

				remaining_time[pos] -= 1;
				time += 1;
				time_quantum += 1;
			}
		}


		if (remaining_time[pos] == 0) {
			complete += 1;
			waiting_time[pos] = time + 1 - burst_time[pos] - arrival_time[pos];
			if (waiting_time[pos] < 0) {
				waiting_time[pos] = 0;
			}
			turnaround_time[pos] = waiting_time[pos] + burst_time[pos];
			priority[pos] = -1;
		}	
	}

	double sum_wait = 0, sum_turn = 0;
	for (i = 0; i < n; i++) {
		sum_wait = sum_wait + waiting_time[i];
		sum_turn = sum_turn + turnaround_time[i];
	}
	double avg_wait = sum_wait / n, avg_turn = sum_turn / n;
	printf("\nThe average waiting time is : %f", avg_wait);
	printf("\nThe average turnaroundtime is : %f\n" , avg_turn);
	for (i = 0; i < n; i++) {
		printf("%d %d\n", waiting_time[i], turnaround_time[i]);
	}

}

int main() {
	int arrival_time[100], burst_time[100], priority[100];
	int n, quantum;
	printf("Enter the number of processes\n");
	scanf("%d", &n);
	printf("Enter the quantum\n");
	scanf("%d", &quantum);
	printf("Enter the arrival burst\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arrival_time[i]);
		scanf("%d", &burst_time[i]);
	}

	roundrobin(burst_time, arrival_time, n, quantum);

	return 0;
}	