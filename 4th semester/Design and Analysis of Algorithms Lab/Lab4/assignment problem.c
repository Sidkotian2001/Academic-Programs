#include <stdio.h>
#include <string.h>
int n = 4;
int fact = 24;
int cost_matrix[4][4] = {{9,2,7,9},
						{6,4,3,8},
						{5,8,1,6},
						{4,5,6,7}};
int cost_array[24];
int opcount = 0;
void compute_cost(char *a) {
	static int count = 0;
	int sum = 0;
	char new_str[n];
	for (int i = 0; i < n; i++) {
		//opcount++;
		sum = sum + cost_matrix[i][a[i] - '0'];
		new_str[i] = a[i] + 1;
	}
	printf("The cost of %s is %d\n", new_str, sum);
	cost_array[count++] = sum;
}
int find_minimum() {
	int min = cost_array[0];
	for (int i = 0; i < fact; i++) {
		if (cost_array[i] < min) {
			min = cost_array[i];
		}
	}
	return min;
}
void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void permute(char *a, int start_index, int end_index)
{
	if (start_index == end_index){
		compute_cost(a);
		return;
	}

	for (int i = start_index; i <= end_index; i++)
	{
		opcount++;
		swap((a+start_index), (a+i));
		permute(a, start_index+1, end_index);
		swap((a+start_index), (a+i)); //backtrack
	}

}

int main()
{
	
	char str[] = "0123";
	int len = strlen(str);
	permute(str, 0, len - 1);
	int min = find_minimum();
	printf("the optimal solution is : %d\n", min);
	printf("%d\n", opcount);
	return 0;
}
