#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void SCAN(int request[], int curr, int n) {
	int i, j, c1 = 0, c2 = 0, counter = 0;
	int seek_sequence[1000], left[1000], right[1000];
	int dist, total_seek_time = 0, min_dist = INT_MAX, pos = 0;
	
	int start_side = 1;

	left[0] = 0;
	c1 += 1;
	right[0] = 199;
	c2 += 1;

	for (i = 0; i < n; i++) {
		if (curr > request[i]) {
			left[c1] = request[i];
			c1 += 1;
		}
		else {
			right[c2] = request[i];
			c2 += 1;
		}
	}

	int temp;
	for (i = 0; i < c1 - 1; i++) {
		for (j = 0; j < c1- i - 1; j++) {
			if (left[j] > left[j + 1]) {
				temp = left[j];
				left[j] = left[j + 1];
				left[j + 1] = temp;
			}
		}	
	}
	for (i = 0; i < c2 - 1; i++) {
		for (j = 0; j < c2 - i - 1; j++) {
			if (right[j] > right[j + 1]) {
				temp = right[j];
				right[j] = right[j + 1];
				right[j + 1] = temp;
			}
		}	
	}

	for (i = 0; i < c2; i++) {
		seek_sequence[counter] = right[i];
		total_seek_time += abs(curr - right[i]);
		curr = right[i];
		counter += 1;
	}


	for (i = 0; i < c1; i++) {
		seek_sequence[counter] = left[i];
		total_seek_time += abs(curr - left[i]);
		curr = left[i];
		counter += 1;
	}
		
	



	for (i = 0; i < c1 + c2; i++) {
		printf("%d ", seek_sequence[i]);
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

	SCAN(arr, curr, n);
}