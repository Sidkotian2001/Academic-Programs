#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sjf(int burst_time[], int arrival_time[], int n) {
	int waiting_time[100], turnaround_time[100], remaining_time[100];
	int time = 0, counter = 0, burst_sum = 0, i, pos;
	int min_burst_time = burst_time[0], min_arrival_time = arrival_time[0];
	printf("The order of execution is : \n");

	for (i = 0 ; i < n; i++) {
		burst_sum = burst_sum + burst_time[i];
		remaining_time[i] = burst_time[i];
	}
	int min = INT_MAX, check = 0, complete = 0;
	while (complete != n) {

		for (i = 0; i < n; i++) {
			if (arrival_time[i] <= time && 
				remaining_time[i] < min && 
				remaining_time[i] > 0) 
			{
				min = remaining_time[i];
				pos = i;
				check = 1;
			}
		}

		if (check == 0) {
			time++;
			continue;
		} 

		remaining_time[pos] -= 1;
		printf("%d ", pos + 1);
		min = remaining_time[pos];
		if (min == 0) {
			min = INT_MAX;
		}
		if (remaining_time[pos] == 0) {
			complete += 1;
			check = 0;
			int finish_time = time + 1;

			waiting_time[pos] = finish_time - burst_time[pos] - arrival_time[pos];
			if (waiting_time[pos] < 0) {
				waiting_time[pos] = 0;
			}
			turnaround_time[pos] = waiting_time[pos] + burst_time[pos];
		}
		

		time += 1;
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