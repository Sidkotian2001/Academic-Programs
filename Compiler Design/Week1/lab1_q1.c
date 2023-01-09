//To count the number of lines and characters in a file.
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fptr1, *fptr2;
	char filename[100], c;

	printf("Enter the name of the file\n");
	scanf("%s", filename);

	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL) {
		printf("Cannot open file\n");
		exit(0);
	}

	c = fgetc(fptr1);
	int line_count = 0, word_count = 0;
	while (c != EOF) {
		if (c == '\n') {
			line_count++;
		}
		else {
			word_count++;
		}
		c = fgetc(fptr1);
	}

	printf("The number of lines is : %d\n", line_count);
	printf("The number of words is : %d\n", word_count);

	fclose(fptr1);

	return 0;
}
