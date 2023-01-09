#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void fcfs(int burst_time[], int arrival_time[], int n) {
	int waiting_time[100], turnaroundtime[100], avgtime[100];

	int time_of_start[100], order[100];
	int next_arrival_time = arrival_time[0], i, pos;
	int counter = 0;
	int time = 0;
	printf("The order of execution is : \n");
	while (counter < n) { 
		for (i = 0; i < n; i++) {
			if (arrival_time[i] < next_arrival_time) {
				next_arrival_time = arrival_time[i];
				pos = i;
			}
		}
		while (time < next_arrival_time) {
			time++;
		}
		printf("%d ", pos + 1);
		
		waiting_time[counter] = time - next_arrival_time;
		turnaroundtime[counter] = waiting_time[counter] + burst_time[pos];
		time = time + burst_time[pos];

		arrival_time[pos] = 9999;
		next_arrival_time = 9999;
		counter++;
	}
	double sum_wait = 0, sum_turn = 0;
	for (i = 0; i < n; i++) {
		sum_wait = sum_wait + waiting_time[i];
		sum_turn = sum_turn + turnaroundtime[i];
	}
	double avg_wait = sum_wait / n, avg_turn = sum_turn / n;
	printf("\nThe average waiting time is : %f", avg_wait);
	printf("\nThe average turnaroundtime is : %f\n" , avg_turn);
	for (i = 0; i < n; i++) {
		printf("%d %d\n", waiting_time[i], turnaroundtime[i]);
	}
}
int main() {
	int burst[100], arrival[100];
	int n;
	printf("Enter number of processes\n");
	scanf("%d", &n);
	printf("Enter burst and arrival\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &burst[i]);
		scanf("%d", &arrival[i]);
	}

	fcfs(burst, arrival, n);
}