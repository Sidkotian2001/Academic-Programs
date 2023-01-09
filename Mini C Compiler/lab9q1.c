#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "getnexttoken.c"

void valid();
void invalid();
void program();
void declarations();
void data_type();
void identifier_list();
void id_list_prime();
void statement_list();
void statement();
void decision_stat();
void looping_stat();
void assign_stat();
void dprime();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

tok* t;

void valid() {
	printf("Code has compiled successfully\n");
	exit(EXIT_SUCCESS);
}
void invalid(int n, char* expected_token) {
	printf("Error at %d \n", n);
	printf("Expected token : %s\n", expected_token);
	printf("Token is : %s\n", t->token_name);
	printf("Positin is : %d %d\n", t->row, t->col);
	exit(EXIT_FAILURE);
}

void program() {
	t = getNextToken();
	while (strcmp(t->token_name, "main") != 0) {
		t = getNextToken();
	}
	if (strcmp(t->token_name, "main") == 0) {
		t = getNextToken();
		if (strcmp(t->token_name, "(") == 0) {
			t = getNextToken();
			if (strcmp(t->token_name, ")") == 0) {
				t = getNextToken();
				if (strcmp(t->token_name, "{") == 0) {
					t = getNextToken();
					declarations();
					statement_list();
					if (strcmp(t->token_name, "}") == 0) {
						t = getNextToken();
						valid();
					}
					else {
						invalid(0, "}");
					}
				}
				else {
					invalid(1, "{");
				}
			}
			else {
				invalid(2, ")");
			}
		}
		else {
			invalid(3, "(");	
		}
	}
	else {
		invalid(4, "main");
	}
}

void declarations() {
	//To handle epsilon in declarations
	if (strcmp(t->token_name, "int") != 0 && strcmp(t->token_name, "char") != 0 && strcmp(t->token_name, "float") != 0) {
		return;
	}
	data_type();
	identifier_list();
	if (strcmp(t->token_name, ";") == 0) {
		t = getNextToken();
		declarations();
	}
	else {
		invalid(15, ";");
	}
}

void data_type() {
	if (strcmp(t->token_name, "int") == 0) {
		t = getNextToken();
	}
	else if (strcmp(t->token_name, "char") == 0) {
		t = getNextToken();
	}
	else if (strcmp(t->token_name, "float") == 0) {
		t = getNextToken();
	}
	else {
		invalid(16, "basic data type");
	}
}

void identifier_list() {
	if (strcmp(t->type, "identifier") == 0) {
		t = getNextToken();
		id_list_prime();
	}
	else {
		invalid(5, "identifier");
	}
}

void id_list_prime() {
	if (strcmp(t->token_name, ",") == 0) {
		t = getNextToken();
		identifier_list();
	}
	else if (strcmp(t->token_name, "[") == 0) {
		t = getNextToken();
		if (strcmp(t->type, "constant") == 0) {
			t = getNextToken();
			if (strcmp(t->token_name, "]") == 0) {
				t = getNextToken();
				if (strcmp(t->token_name, ",") == 0) {
					t = getNextToken();
					identifier_list();
				}
				//No else becuause id[number] is a production
			}
			else {
				invalid(6, "]");
			}
		}
		else {
			invalid(7, "numeric constant");
		}
	}
}

void statement_list() {
	//Not dealt with epsilon production
	if (strcmp(t->token_name, "}") == 0) {
		return;
	}
	statement();
	statement_list();
}

void statement() {
	if (strcmp(t->type, "identifier") == 0) {
		assign_stat();
		if (strcmp(t->token_name, ";") == 0) {
			t = getNextToken();
		}
	}
	else if (strcmp(t->token_name, "if") == 0) {
		decision_stat();
	}	
	else if (strcmp(t->token_name, "for") == 0 || strcmp(t->token_name, "while") == 0) {
		looping_stat();
	}
	else {
		invalid(45, "identifier, decision_stat, looping_stat");
	}
}

void decision_stat() {
	if (strcmp(t->token_name, "if") == 0) {
		t = getNextToken();
		if (strcmp(t->token_name, "(") == 0) {
			t = getNextToken();
			expn();
			if (strcmp(t->token_name, ")") == 0) {
				t = getNextToken();
				if (strcmp(t->token_name, "{") == 0) {
					t = getNextToken();
					statement_list();
					if (strcmp(t->token_name, "}") == 0) {
						t = getNextToken();
						dprime();
					}
					else {
						invalid(20, "}");
					}
				}
				else {
					invalid(21, "{");
				}
			}
			else {
				invalid(22, ")");
			}
		}
		else {
			invalid(23, "(");
		}
	}
}

void dprime() {
	if (strcmp(t->token_name, "else") == 0) {
		t = getNextToken();
		if (strcmp(t->token_name, "{") == 0) {
			t = getNextToken();
			statement_list();
			if (strcmp(t->token_name, "}") == 0) {
				t = getNextToken();
			}
			else {
				invalid(25, "}");
			}
		}
		else {
			invalid(26, "{");
		}
	}
}

void looping_stat() {
	if (strcmp(t->token_name, "while") == 0) {
		t = getNextToken();
		if (strcmp(t->token_name, "(") == 0) {
			t = getNextToken();
			expn();
			if (strcmp(t->token_name, ")") == 0) {
				t = getNextToken();
				if (strcmp(t->token_name, "{") == 0) {
					t = getNextToken();
					statement_list();
					if (strcmp(t->token_name, "}") == 0) {
						t = getNextToken();
					}
					else {
						invalid(27, "}");
					}
				}
				else {
					invalid(28, "{");
				}
			}
			else {
				invalid(29, ")");
			}
		}
		else {
			invalid(30, "(");
		}
	}
	else if (strcmp(t->token_name, "for") == 0) {
		t = getNextToken();
		if (strcmp(t->token_name, "(") == 0) {
			t = getNextToken();
			assign_stat();
			if (strcmp(t->token_name, ";") == 0) {
				t = getNextToken();
				expn();
				if (strcmp(t->token_name, ";") == 0) {
					t = getNextToken();
					assign_stat();
					if (strcmp(t->token_name, ")") == 0) {
						t = getNextToken();
						if (strcmp(t->token_name, "{") == 0) {
							t = getNextToken();
							statement_list();
							if (strcmp(t->token_name, "}") == 0) {
								t = getNextToken();
							}
							else {
								invalid(31, "}");
							}
						}
						else {
							invalid(32, "{");
						}
					}
					else {
						invalid(33, ")");
					}
				}
				else {
					invalid(34, ";");
				}
			}
			else {
				invalid(35, ";");
			}
		}
		else {
			invalid(36, "(");
		}
	}
}

void assign_stat() {
	if (strcmp(t->type, "identifier") == 0) {
		t = getNextToken();
		if (strcmp(t->token_name, "=") == 0) {
			t = getNextToken();
			expn();
		}
		else {
			invalid(9, "=");
		}
	}
	else {
		return;
	}
}

void expn() {
	simple_exp();
	eprime();
}

void eprime() {
	//To handle epsilon production in eprime()
	if (strcmp(t->type, "relational operator") != 0) {
		return;
	}
	relop();
	simple_exp();
}

void simple_exp() {
	term();
	seprime();
}

void seprime() {
	//To handle epsilon production in seprime()
	if (strcmp(t->token_name, "+") != 0 && strcmp(t->token_name, "-") != 0) {
		return;
	}
	addop();
	term();
	seprime();
}
void term() {
	factor();
	tprime();
}

void tprime() {
	//To handle epsilon production in tprime()
	if (strcmp(t->token_name, "*") != 0 && strcmp(t->token_name, "/") != 0 && strcmp(t->token_name, "%") != 0) {
		return;
	}
	mulop();
	factor();
	tprime();
}

void factor() {
	if (strcmp(t->type, "identifier") == 0) {
		t = getNextToken();
	}
	else if (strcmp(t->type, "constant") == 0) {
		t = getNextToken();
	}
	else {
		invalid(11, "numeric constant");
	}
}

void relop() {
	if (strcmp(t->type, "relational operator") == 0) {
		t = getNextToken();
	}
	else {
		invalid(12, "relational operator");
	}
}

void addop() {
	if (strcmp(t->token_name, "+") == 0) {
		t = getNextToken();
	}
	else if (strcmp(t->token_name, "-") == 0) {
		t = getNextToken();
	}
	else {
		invalid(13, "arithmetic operator");
	}
}

void mulop() {
	if (strcmp(t->token_name, "*") == 0) {
		t = getNextToken();
	}
	else if (strcmp(t->token_name, "/") == 0) {
		t = getNextToken();
	}
	else if (strcmp(t->token_name, "%") == 0) {
		t = getNextToken();
	}
	else {
		invalid(14, "arithmetic operator");
	}
}

void printtable() {
	int i = 0;
	while (buf[i] != EOF) {
		printf("%c", buf[i]);
		i++;
	}

}

int main() {
	FILE *fa, *fb, *fc;
	fa = fopen("sample_input_file.c", "r");
	fb = fopen("modified_input_file.c", "w+");
	
	if (fa == NULL) {
		printf("Cannot open input file\n");
		exit(-1);
	}
	if (fb == NULL) {
		printf("Cannot open modified input file\n");
		exit(-1);
	}
	remove_comments(fa, fb);
	fclose(fa);
	fclose(fb);
	
	fa = fopen("modified_input_file.c", "r");
	if (fa == NULL) {
		printf("cannot open modififed input file\n");
		exit(0);
	}
	generatebuffer(fa);
	// printtable();
	printtoken();
	forward = 0;
	begin = 0;
	program();
	// printf("End \n");
	return 0;
}
