#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void printarr(int arr[],int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void fifo(char *ref, int n) {
	int arr[7], counter = 0;
	for (int i = 0; i < n; i++) {
		arr[i] = -1;
	}
	for (int i = 0; i < strlen(ref); i++) {
		int found = 0, placed = 0;
		int page = ref[i] - '0';
		printf("Current page : %d\n", page);
		

		for (int j = 0; j < n; j++) {
			if (arr[j] == page) {
				found = 1;
				break;
			}
			if (arr[j] == -1) {
				arr[j] = page;
				placed = 1;
				break;
			}
		}

		if (!placed && !found) {
			arr[counter] = page;
			counter = (counter + 1) % n;
		}
		printarr(arr, n);
	}
}

int main() {
	int n;

    printf("Enter the number of frames\n");
    scanf("%d", &n);

    //The order of pages
	char *str = "70120304230321201701";
	int len = strlen(str);

	fifo(str,n);
	return 0;
}