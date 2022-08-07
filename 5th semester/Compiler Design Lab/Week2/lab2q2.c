#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fa, *fb, *fc;
	int ca, cb;

	fa = fopen("file1.c", "r");
	fc = fopen("file1.c", "r");
	if (fa == NULL) {
		printf("Cannot open file\n");
		exit(0);
	}
	fb = fopen("file2.txt", "w+");
	ca = getc(fa);
	int cc, count = 0;
	while (ca != EOF) {
		
		if (ca == '#' && (cc == '\n' || cc == 0)) {

			while (ca != '\n') {
				ca = getc(fa);
				count++;
			}

		}
		else {
			putc(ca, fb);
			ca = getc(fa);
			count++;
		}
		fseek(fc, count - 1, SEEK_SET);
		cc = getc(fc);
	}

	fclose (fa);
	fclose (fb);
	return 0;
}