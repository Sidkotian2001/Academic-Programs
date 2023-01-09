#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_comments(FILE *fa, FILE *fb) {
	int ca, cb;
	ca = getc(fa);
	while (ca != EOF) {
		if (ca == ' ') {
			putc(ca, fb);
			while (ca == ' ') {
				ca = getc(fa);
			}
		}
	
		if (ca == '/') {
			cb = getc(fa);
			if (cb == '/') {
				while (ca != '\n') {
					ca = getc(fa);
				}
			}
			else if (cb == '*') {
				do {
					while (ca != '*') {
						ca = getc(fa);
					}
					ca = getc(fa); 
				}while (ca != '/');
			}
			else {
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else if (ca == '"') {
			putc(ca, fb);
			ca = getc(fa);
			while (ca != '"') {
				putc(ca, fb);
				ca = getc(fa);
			}
			putc(ca, fb);
		}
		else if (ca == '#') {

			while (ca != '\n') {
				ca = getc(fa);
			}

		}
		else if (ca == '\t') {
			ca = getc(fa);
			while (ca == '\t') {
				ca = getc(fa);
			}
			continue;
		}
		else {
			putc(ca, fb);

		}

		ca = getc(fa);
	}
}