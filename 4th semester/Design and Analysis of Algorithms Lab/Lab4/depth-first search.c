#include <stdio.h>
#include <stdlib.h>

char push_arr[8], pop_arr[8];
typedef struct stack{
	char arr[20];
	int top;
}STACK;

void init(STACK *s) {
	s->top = -1;
}
void push(STACK *s, char n) {
	s->arr[++(s->top)] = n;
}
char pop(STACK *s) {
	if (s->top == -1) {
		printf("Empty stack\n");
		return -1;
	}
	char x = s->arr[s->top];
	s->top = s->top - 1;
	return x;
}

void display() {
	printf("The push order : \n");
	for (int i = 0; i < 8; i++) {
		printf("%c ", push_arr[i]);
	}
	printf("\nThe pop order : \n");
	for (int i = 0; i < 8; i++) {
		printf("%c ", pop_arr[i]);
	}
}
void dfs(STACK *s, int adj_mat[][8], int visit[], int v) {
	static int c1 = 0, c2 = 0;
	if (visit[v] == 0) {
		push(s, v + 97);
		push_arr[c1++] = s->arr[s->top];
		visit[v] = 1;
	}
	for (int i = 0; i < 8; i++) {
		if (adj_mat[v][i] == 1 && visit[i] == 0) {
			dfs(s, adj_mat, visit, i);
		}
	}
	pop_arr[c2++] = pop(s);

	if (s->top == -1) {
		display();
		return;
	}
}
int main() {
	int adj_mat[8][8] = {{0,1,0,0,1,1,0,0},
				{1,0,0,0,0,1,1,0},
				{0,0,0,1,0,0,1,0},
				{0,0,1,0,0,0,0,1},
				{1,0,0,0,0,1,0,0},
				{1,1,0,0,1,0,0,0},
				{0,1,1,0,0,0,0,1},
				{0,0,0,1,0,0,1,0}};
	int visit[8] = {0,0,0,0,0,0,0,0};
	STACK *s;
	s = (STACK*)malloc(sizeof(STACK));
	init(s);
	dfs(s, adj_mat, visit, s->arr[s->top]);
	printf("\n");
	return 0;
}