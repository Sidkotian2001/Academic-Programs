#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fptr1, *fptr2, *fptr3;
	char filename[100], c1, c2;
	// printf("Enter the first filename\n");
	// scanf("%s", filename);
	fptr1 = fopen("file4", "r");

	// printf("Enter the second filename\n");
	// scanf("%s", filename);
	fptr2 = fopen("file5", "r");

	if (fptr1 == NULL || fptr2 == NULL) {
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	// printf("Enter the third filename\n");
	// scanf("%s", filename);
	fptr3 = fopen("file6", "w+");

	c1 = fgetc(fptr1);
	c2 = fgetc(fptr2);
	printf("Started the process\n");
	while (c1 != EOF && c2 != EOF) {
		
		while (c1 != '\n') {
			fputc(c1, fptr3);
			c1 = fgetc(fptr1);
			printf("hello\n");
		}
		fputc(c1, fptr3);
		c1 = fgetc(fptr1);
		

		while (c2 != '\n') {
			fputc(c2, fptr3);
			c2 = fgetc(fptr2);
			printf("hellasdfo\n");
		}
		fputc(c2, fptr3);
		c2 = fgetc(fptr2);
		
		
	}
	printf("Ended\n");
	if (c1 == EOF) {
		while (c2 != EOF) {
			fputc(c2, fptr3);
			c2 = fgetc(fptr2);
		}
	}
	else {
		while (c1 != EOF) {
			fputc(c1, fptr3);
			c1 = fgetc(fptr1);
		}
	}

	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);

	return 0;
}