#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fptr1, *fptr2;
	char filename[100], c;

	printf("Enter the name of the file\n");
	scanf("%s", filename);

	fptr1 = fopen(filename, "r");

	if (fptr1 == NULL) {
		printf("Cannot open the file\n");
		exit(0);
	}

	printf("Enter the name of the file to be written\n");
	scanf("%s", filename);

	fptr2 = fopen(filename, "w+");
	int offset = -1;

	fseek(fptr1, offset, SEEK_END);
	while (ftell(fptr1) != SEEK_SET) {
		c = fgetc(fptr1);
		fputc(c, fptr2);
		offset--;
		fseek(fptr1, offset, SEEK_END);
	}
	c = fgetc(fptr1);
	fputc(c, fptr2);
	printf("The current position is : %ld\n", ftell(fptr1));
	return 0;
}