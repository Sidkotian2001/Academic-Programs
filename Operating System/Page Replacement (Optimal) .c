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

void optimal(char *ref, int n) {
	int arr[7];
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
		if (found) {
			printf("Page hit\n");
			continue;
		}
		if (!placed && !found) {
			int distance, max_distance = -1, pos;
			int c = 0;

			while (c < n) {
				int j;
				for (j = i; j < strlen(ref); j++) {
					if (arr[c] == ref[j] - '0') {
						break;
					}	
				}
				distance = j - i;
				if (distance > max_distance) {
					max_distance = distance;
					pos = c;
				}
				c++;
			}
			
			arr[pos] = page;
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

	optimal(str,n);
	return 0;
}