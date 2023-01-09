#include <stdio.h>

int findpart(int a[], int n, int sum)
{
	if (sum == 0)
		return 1;
	if (n == 0 && sum != 0)
		return 0;


	if (a[n - 1] > sum)
		return findpart(a, n - 1, sum);

	return findpart(a, n - 1, sum)
		|| findpart(a, n - 1, sum - a[n - 1]);
}


int main()
{
	int n, sum = 0;
	printf("Enter size\n");
	scanf("%d", &n);

	int a[n];

	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		sum = sum + a[i];
	}

	if (sum % 2 != 0) {
		printf("Error odd sum\n");
		return 0;
	}

	if (findpart(a, n, sum / 2) == 1)
		printf("Can be Partitioned\n");
	else
		printf("Can't be Partitioned\n");
	return 0;
}
