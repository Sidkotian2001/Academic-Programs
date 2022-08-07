#include <stdio.h>
#include <stdlib.h>

int main() {
	int a, b;
	printf("Enter the first number\n");
	scanf("%d", &a);

	printf("Enter the second number\n");
	scanf("%d", &b);

	int max;

	if (a > b) {
		max = a;
	}
	else if (a < b) {
		max = b;
	}

	for (int i = max; i > 0; i--) {
		if ((a % i == 0) && (b % i == 0)) {
			max = i;
			break;
		}
	}

	printf("The gcd is : %d\n", max);

	return 0;
}