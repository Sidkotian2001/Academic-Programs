#include <stdio.h>
#include <stdlib.h> 

char keywords[32][100] = {"auto", 	"else", 	"long", 	"switch"
					"break", 	"enum", 	"register," 	"typedef",
					"case", 	"extern", 	"return", 	"union",
					"char", 	"float", 	"short",	"unsigned",
					"const", 	"for",	"signed", 	"void",
					"continue", 	"goto", 	"sizeof", 	"volatile",
					"default", 	"if", 	"static", 	"while",
					"do", 	"int", 	"struct", 	"_Packed",
					"double"};

// void search(char c) {
// 	for (int i = 0; i < 32; i++) {
// 		if (key)
// 	}
// }

int main() {

	FILE *fa, *fb;
	int ca, cb;

	fa = fopen("file1.c", "r");
	if (fa == NULL) {
		printf("Cannot open file \n");
		exit(1);
	}
	
	fb = fopen("file2.txt", "w");
	ca = getc(fa);
	int i = 0;
	char temp[100];

	while (ca != EOF) {
		temp[i] = ca;
		i++;
		if (ca == ' ' || ca == '\n') {
			// while(ca == ' ' || ca == '\n' || ca == '\t') {
			// 	ca = fgetc(fa);
			// }
			temp[i] = '\0';
			printf("%s\n", temp);
			i = 0;
		}

		
		ca = getc(fa);
	}

	fclose(fa);
	// fclose(fb);
	return 0;
}