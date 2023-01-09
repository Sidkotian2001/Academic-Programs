#include <stdio.h>
#include <stdlib.h>

void sjf(int burst_time[], int arrival_time[], int n) {
	int waiting_time[100], turnaround_time[100];
	int time = 0, counter = 0, i, pos;
	int min_burst_time = burst_time[0];
	printf("The order of execution is : \n");
	while (counter < n) {
		for (i = 0; i < n; i++) {
			if (burst_time[i] < min_burst_time ) {
				min_burst_time = burst_time[i];
				pos = i;
			}
		}
		printf("%d ", pos + 1);
		waiting_time[pos] = time - arrival_time[counter];
		turnaround_time[pos] = waiting_time[pos] + burst_time[pos];

		time += burst_time[pos];
		burst_time[pos] = 9999;
		min_burst_time = 9999;
		counter++;
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
	int burst[100], arrival[100];
	int n;
	printf("Enter number of processes\n");
	scanf("%d", &n);
	printf("Enter burst and arrival\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &burst[i]);
		scanf("%d", &arrival[i]);
	}

	sjf(burst, arrival, n);
}