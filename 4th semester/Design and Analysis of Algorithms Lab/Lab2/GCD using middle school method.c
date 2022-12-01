#include <stdio.h>
#include <math.h>

void sieve(int arr[], int n) {
	int i, num, temp, opcount = 0;
	for (i = 0; i < (n - 1); i++) {
		arr[i] = i + 2;
	}
	for (i = 0; i < sqrt(n); i++) {
		if (arr[i] != 0) {
			num = arr[i];
			temp = 2 * num;
			while(temp <= n) {
				opcount++;
				if (arr[temp - 2] != 0) {
					arr[temp - 2] = 0;
				} 
				temp = temp + num;
			}
		}
	}
	printf("The basic operation is executed : %d times\n", opcount);
}

int middle_school(int n, int m, int min) {
	int i, opcount = 0, gcd = 1;
	int arr[min];
	
	sieve(arr, min);

	for (i = 0; i < min; i++) {
		if (arr[i] == 0) {
			continue;
		}
		if (n % arr[i] == 0 && m % arr[i] == 0) {
			gcd = gcd * arr[i];
			n = n / arr[i];
			m = m / arr[i];
		}
	}

	return gcd;
}

int main() {
	int n, m, gcd;
	printf("First number\n");
	scanf("%d", &n);

	printf("Second number\n");
	scanf("%d", &m);

	int min = m > n ? n : m;

	gcd = middle_school(n, m, min);

	printf("gcd : %d\n", gcd);

	return 0;
}