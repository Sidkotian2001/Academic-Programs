#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void fcfs(int order[], int curr, int n) {
	int i;
	int seek_time[1000];
	int total_seek_time = 0;
	for(i = 0; i < n; i++) {
		seek_time[i] = abs(curr - order[i]);
		total_seek_time = total_seek_time + seek_time[i];
		curr = order[i];
	}
	for (i = 0; i < n; i++) {
		printf("%d ", seek_time[i]);
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

	fcfs(arr, curr, n);
}