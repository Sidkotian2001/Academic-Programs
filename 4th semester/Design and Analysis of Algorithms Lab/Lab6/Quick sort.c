#include <stdio.h>
#include <stdlib.h>
int opcount = 0;
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int hoarepartition(int arr[], int l, int r) {
	int p = arr[l];
	int i = l;
	int j = r + 1;
	int temp;
	int c =0;
	while (i <= j) {
		opcount++;
		while (arr[++i] < p && i <= j) {
			opcount++;}
		while (arr[--j] > p && i <= j){opcount++;}
		swap(&arr[i], &arr[j]);
	}
	swap(&arr[i], &arr[j]);
	swap(&arr[l], &arr[j]);


	return j;
}

void quicksort(int arr[], int l, int r) {
	if (l < r) {

		int s = hoarepartition(arr, l, r);
		quicksort(arr, l, s - 1);
		quicksort(arr, s + 1, r);
	}
}
int main() {
	int n = 5;
	int arr[] = {12,43,3,2,54};
	int l = 0;
	quicksort(arr, 0, n - 1);
	
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n%d", opcount);
	printf("\n");

	return 0;
}