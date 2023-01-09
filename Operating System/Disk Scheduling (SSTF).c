#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void sstf(int order[], int curr, int n) {
	int i;
	int temp[1000], seek_time[1000];
	int dist, total_seek_time = 0, min_dist = INT_MAX, pos = 0;
	
	for (i = 0; i < n; i++) {
		temp[i] = order[i];
		dist = abs(curr - order[i]);
		if (dist < min_dist) {
			min_dist = dist;
			pos = i;
		}
	}
	curr = order[pos];
	seek_time[pos] = min_dist;
	temp[pos] = INT_MAX;
	int complete = 1;
	while (complete < n) {
		min_dist = INT_MAX;
		for (i = 0; i < n; i++) {
			dist = abs(curr - temp[i]);
			if (dist < min_dist) {
				min_dist = dist;
				pos = i;
			}
		}
		curr = order[pos];
		seek_time[pos] = min_dist;
		curr = order[pos];
		temp[pos] = INT_MAX;
		complete += 1;
	}


	for (i = 0; i < n; i++) {
		printf("%d ", seek_time[i]);
		total_seek_time = total_seek_time + seek_time[i];
	}
	

	printf("\nThe total_seek_time : %d", total_seek_time);
}

int main() {
	int n, curr;
	int arr[1025];
	printf("Enter number of request\n");
	scanf("%d", &n);
	for (int i = 0 ; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	printf("Enter current position\n");
	scanf("%d", &curr);

	sstf(arr, curr, n);
}