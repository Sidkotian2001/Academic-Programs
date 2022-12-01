#include <stdio.h>
#include <string.h>
int count = 0;
/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/* Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
void permute(char *a, int start_index, int end_index)
{
	if (start_index == end_index){
		count++;
		printf("%s\n", a);
		return;
	}
	
	for (int i = start_index; i <= end_index; i++)
	{
		swap((a+start_index), (a+i));
		permute(a, start_index+1, end_index);
		swap((a+start_index), (a+i)); //backtrack
	}

}

/* Driver program to test above functions */
int main()
{
	char str[] = "ABCD";
	int n = strlen(str);
	permute(str, 0, n-1);
	printf("%d\n", count);
	return 0;
}
