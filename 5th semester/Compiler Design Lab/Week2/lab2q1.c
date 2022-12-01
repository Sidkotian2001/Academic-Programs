//That takes a file as input and replaces blank spaces and tabs by single space and writes the output to a file.
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fa, *fb;
	int ca, cb;

	fa = fopen("file1.txt", "r");
	if (fa == NULL) {
		printf("Cannot open file \n");
		exit(1);
	}

	fb = fopen("file2.txt", "w");
	ca = getc(fa);
	while (ca != EOF) {
		if (ca == ' ') {
			putc(ca, fb);
			while (ca == ' ') {
				ca = getc(fa);
			}
		}
		else if (ca == '\t') {
			putc(ca, fb);
			while (ca == '\t') {
				ca = getc(fa);
			}
		}
		else {
			putc(ca, fb);
			ca = getc(fa);
		}
	}

	fclose(fa);
	fclose(fb);
	return 0;
}
