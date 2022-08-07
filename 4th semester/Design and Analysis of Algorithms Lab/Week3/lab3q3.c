#include <stdio.h>
#include <math.h>

void find_partition(int arr[], int n) {
	int pow_set_size = pow(2, n) - 1, sum, i, j, total_sum = 0;

	for (i = 0; i < n; i++) {
		total_sum = total_sum + arr[i];
	}

	if (total_sum % 2 != 0) {
		printf("The sum is odd\n");
		return;
	}

	for (i = 0; i < pow_set_size; i++) {
		if (i == 0) {
			continue;
		}
		sum = 0;
		for (j = 0; j < n; j++) {
			if (i & (1<<j)) {
				sum = sum + arr[j];
			}
		}
		if (sum == total_sum / 2) {
			for (j = 0; j < n; j++) {
				if (i & (1 << j)) {
					printf("%d,", arr[j]);
				}
			}
			printf("\n");
		}
	}
}
int main() {
	int n, i, j;
	printf("Size : ");
	scanf("%d", &n);

	int a[n];

	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	find_partition(a, n);
	return 0;
}