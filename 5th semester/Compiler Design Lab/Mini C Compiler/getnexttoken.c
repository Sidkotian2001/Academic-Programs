#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "processors.h"


typedef struct token {
	char* token_name;
	int index;
	unsigned int row, col;
	char* type;
}tok;

char special_symbols[100] = {',', '#','$', '&', '(', ')', '.', ':', ';', '?', '@', '\\', '[', ']', '^', '_', '`', '{', '|', '}', '~'};
char keywords[32][10] = {"auto","break","case","char","const","continue","default",
						"do","double","else","enum","extern","float","for","goto",
						"if","int","long","register","return","short","signed",
						"sizeof","static","struct","switch","typedef","union",
						"unsigned","void","volatile","while"};
char arith_operators[5] = {'+', '-', '*', '/', '%'};
int count = 0, col_difference = 0;
char buf[BUFSIZ];
int flag = 1;
int forward = 0, begin = 0;

tok* init_token(int row_num) {
	tok* t = (tok*)malloc(sizeof(tok));
	t->token_name = (char*)malloc(sizeof(t->token_name) + 1);
	t->type = (char*)malloc(sizeof(t->type) + 1);
	t->row = row_num + 1;
	return t;
}

int search_special(char ch){
	int len = sizeof(special_symbols) / sizeof(char);
	for (int i = 0 ; i < len; i++) {
		if (special_symbols[i] == ch) {
			return 1;
		}
	}
	return 0;
}

int search_arithmetic(char ch) {
	for (int i = 0; i < 5; i++) {
		if (arith_operators[i] == ch) {
			return 1;
		}
	}
	return 0;
}

int search_keyword(char* str) {
	for (int i = 0; i < 32; i++) {
		if (strcmp(str, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int check_relational_assignment(tok *t, int begin, int forward) {
	char str[5];
	if (buf[forward] == '=') {
		str[0] = buf[forward];
		forward++;
		if (buf[forward] == '=') {
			str[1] = buf[forward];
			str[2] = '\0';
			t->type = "relational operator";
		}
		else {
			//retract
			forward--;
			str[1] = '\0';
			t->type = "assignment operator";
		}
		
		t->token_name = str;
		t->index = count++;
		t->col = begin + 1 - col_difference;
	}

	//buf[forward] == '<' || buf[forward] == '>' || buf[forward] =='!'
	else {
		str[0] = buf[forward];
		forward++;
		if(buf[forward] == '=') {
			str[1] = buf[forward];
			str[2] = '\0';
			t->type = "relational operator";
		}
		else if (buf[forward] == '!') {
			t->type = "logical operator";
			str[1] = '\0';
		}
		else {
			//retract
			forward--;
			t->type = "relational operator";
			str[1] = '\0';
		}
		t->token_name = str;
		t->index = count++;
		t->col = begin + 1 - col_difference;
	}
	
	forward++;
	return forward;
}

int check_arithmetic(tok* t, int begin, int forward) {
	char str[5];
	str[0] = buf[forward];
	if (buf[forward] == '+') {
		forward++;
		if (buf[forward] == '+') {
			str[1] = buf[forward];
			str[2] = '\0';
		}
		else {
			forward--;
			str[1] = '\0';
		}
	}
	else if (buf[forward] == '-') {
		forward++;
		if (buf[forward] == '-') {
			str[1] = buf[forward];
			str[2] = '\0';
		}
		else {
			forward--;
			str[1] = '\0';
		}
	}
	else {
		str[1] = '\0';
	}
	t->token_name = str;
	t->index = count++;
	t->col = begin + 1 - col_difference;
	t->type = "arithmetic operator";

	forward++;
	return forward;
}

int check_logical(tok *t, int begin, int forward) {
	char str[100];
	str[0] = buf[forward];

	if (buf[forward] == '&') {
		forward++;
		if (buf[forward] == '&') {
			str[1] = buf[forward];
		}
	}
	else if (buf[forward] == '|') {
		forward++;
		if (buf[forward] == '|') {
			str[1] = buf[forward];
		}
	}
	str[2] = '\0';
	t->token_name = str;
	t->index = count++;
	t->col = begin + 1 - col_difference;
	t->type = "logical operator";

	forward++;
	return forward;
}

int check_special(tok *t, int begin, int forward) {
	char str[3];
	if (search_special(buf[forward])) {
		str[0] = buf[forward];
		str[1] = '\0';
		t->token_name = str;
		t->index = count++;
		t->col = begin + 1 - col_difference;
		t->type = "special symbol";
	}

	forward++;
	return forward;
}

int check_number_constant(tok* t, int begin, int forward) {
	char str[BUFSIZ];
	int i = 0;
	do {
		str[i] = buf[forward];
		i++;
		forward++;
	} while (isdigit(buf[forward]));


	if (buf[forward] == '.') {
		do {
			str[i] = buf[forward];
			i++;
			forward++;
		} while (isdigit(buf[forward]));
	}

	else if (buf[forward] == 'E') {
		str[i] = buf[forward];
		i++;
		forward++;
		if (buf[forward] == '+' || buf[forward] == '-') {
			str[i] = buf[forward];
			i++;
			forward++;
		}
		do {
			str[i] = buf[forward];
			i++;
			forward++;
		} while (isdigit(buf[forward]));
	}
	str[i] = '\0';
	t->token_name = str;
	t->type = "constant";
	t->index = count++;
	t->col = begin + 1 - col_difference;

	return forward;
}

int check_char_constant(tok *t, int begin, int forward) {
	char str[5];
	int i = 0;
	do {
		str[i] = buf[forward];
		i++;
		forward++;
	}while(buf[forward] != '\'');

	str[i] = buf[forward];
	str[i + 1] = '\0';

	t->token_name = str;
	t->type = "constant";
	t->col = begin + 1 - col_difference;
	t->index = count++;

	forward++;
	return forward;
}

int check_string_literal(tok* t, int begin, int forward) {
	char str[BUFSIZ];
	int i = 0;

	do {
		str[i] = buf[forward];
		forward++;
		i++;
	} while (buf[forward] != '"');
	str[i] = buf[forward];
	str[i + 1] = '\0';
	
	t->token_name = str;
	t->type = "string literal";
	t->index = count++;
	t->col = begin + 1 - col_difference;
	
	forward++;
	return forward;
}

int check_identifiers_keywords(tok* t, int begin, int forward) {
	char str[BUFSIZ];
	int i = 0;
	do {
		str[i] = buf[forward];
		forward++;
		i++;
	} while (isalpha(buf[forward]) || isdigit(buf[forward]) || buf[forward] == '_');
	str[i] = '\0';

	if (search_keyword(str)) {
		t->type = "keyword";
	}
	else {
		t->type = "identifier";
	}
	t->token_name = str;
	t->index = count++;
	t->col = begin + 1 - col_difference;
	return forward;

}


tok* getNextToken() {
	
	int row_num = 0;

	static int count = 0;
	char temp[100];
	// static int begin = 0, forward = 0;
	char str[BUFSIZ];
	//Initialize the token
	tok* t = init_token(row_num);

	if (buf[forward] == '\n') {
		row_num++;
		col_difference = forward + 1;
		forward++;
		begin = forward;
		return getNextToken();
	}
	//check for string literals
	else if (buf[forward] == '"') {
		forward = check_string_literal(t, begin, forward);
		begin = forward;

	}

	//check for char constants
	else if (buf[forward] == '\'') {
		forward = check_char_constant(t, begin, forward);
		begin = forward;
	}

	//CHECK FOR IDENTIFIERS OR KEYWORDS
	else if (isalpha(buf[forward]) || buf[forward] == '_') {
		forward = check_identifiers_keywords(t, begin, forward);
		begin = forward;
	}

	//check for number constants
	else if (isdigit(buf[forward])) {
		forward = check_number_constant(t, begin, forward);
		begin = forward;
	}

	//check for assignment or relational
	else if (buf[forward] == '=' || buf[forward] == '<' || buf[forward] == '>' || buf[forward] =='!') {
		forward = check_relational_assignment(t, begin, forward);
		begin = forward;
	}

	//check for logical 
	else if (buf[forward] == '&' || buf[forward] == '|') {
		forward = check_logical(t, begin, forward);
		begin = forward;
	}

	//check for arithmetic
	else if (search_arithmetic(buf[forward])) {
		forward = check_arithmetic(t, begin, forward);
		begin = forward;
	}

	//check for special symbols
	//Won't enter if statement if not special symbol only
	else if (search_special(buf[forward])) {
		forward = check_special(t, begin, forward);
		begin = forward;
	}

	//forward pointer encounters a blankspace
	else if (buf[forward] == ' ') {
		forward++;
		begin = forward;
		return getNextToken();
	}
	// printtoken(t);
	//Deal with this case of forward++ which might happen twice
	// forward++;
	if (buf[forward] == EOF) {
		flag = 0;
	}
	return t;
	
}



void generatebuffer(FILE *fa) {
	int ca = getc(fa);
	int i = 0;
	int row_num = 0;
	while (ca != EOF) {
		buf[i] = ca;
		i++;
		ca = fgetc(fa);
	}
	buf[i] = ca;
}

void printtoken() {
	while (flag) {
		tok* T = getNextToken();
		// if (t == NULL) {
		// 	continue;
		// }
		printf("<%s, %d, %d, %s>\n", T->token_name, T->row, T->col, T->type);
		// printf("hello");
	}
}

// int main() {
// 	FILE *fa, *fb;
// 	fa = fopen("solved1.c", "r");
// 	fb = fopen("file2.c", "w");
	
// 	if (fa == NULL || fb == NULL) {
// 		printf("Cannot open file\n");
// 		exit(0);
// 	}
	
// 	remove_comments(fa, fb);
// 	fclose(fa);
// 	fclose(fb);
// 	fa = fopen("file2.c", "r");
// 	if (fa == NULL) {
// 		printf("cannot open fil\n");
// 		exit(0);
// 	}
// 	generatebuffer(fa);
// 	printtoken();

// 	return 0;
// }
