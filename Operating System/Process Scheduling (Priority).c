#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

void priority_schedule(int burst_time[], int arrival_time[], int priority[], int n) {
	int waiting_time[100], turnaround_time[100], remaining_time[100];
	int complete = 0, pos, time = 0, i, max_priority = INT_MAX, check = 0;
	for (int i = 0; i < n; i++) {
		remaining_time[i] = burst_time[i];
	}
	while (complete != n) {
		for (i = 0; i < n; i++) {
			if (arrival_time[i] <= time &&
				priority[i] < max_priority && 
				remaining_time[i] > 0
				) {
				max_priority = priority[i];
				pos = i;
				check = 1;
			}
		}

		if (check == 0) {
			time += 1;
			continue;
		}
		printf("%d ", pos + 1);
		remaining_time[pos] -= 1;

		if (remaining_time[pos] == 0) {
			complete += 1;
			waiting_time[pos] = time + 1 - arrival_time[pos] - burst_time[pos];
			if (waiting_time[pos] < 0) {
				waiting_time[pos] = 0;
			}
			turnaround_time[pos] = waiting_time[pos] + burst_time[pos];
			max_priority = INT_MAX;
			check = 0;
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
	int arrival_time[100], burst_time[100], priority[100];
	int n;
	printf("Enter the number of processes\n");
	scanf("%d", &n);
	printf("Enter the arrival burst priority\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arrival_time[i]);
		scanf("%d", &burst_time[i]);
		scanf("%d", &priority[i]);
	}

	priority_schedule(burst_time, arrival_time, priority, n);

	return 0;
}	