#include <stdio.h>

int main() {
	int n, i, j, temp, opcount = 0;
	printf("Size : \n");
	scanf("%d", &n);

	int a[n];

	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			opcount++;
			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	for (i = 0 ; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("Opcount : %d\n", opcount);

	return 0;
}