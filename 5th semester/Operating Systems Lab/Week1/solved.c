#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *ftptr1, *ftptr2;
	char filename[100], c;
	printf("Enter the name of the file\n");
	scanf("%s", filename);

	ftptr1 = fopen(filename, "r");
	if (ftptr1 == NULL) {
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

	printf("Enter the filename to open for writing \n");
	scanf("%s", filename);

	ftptr2 = fopen(filename, "w+");
	c = fgetc(ftptr1);

	while (c != EOF) {
		fputc(c, ftptr2);
		c = fgetc(ftptr1);
	}

	printf("\ncontents copied to file %s", filename);

	fclose(ftptr1);
	fclose(ftptr2);

	return 0;
}