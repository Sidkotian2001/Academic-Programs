#include <stdio.h>
#include <stdlib.h>

int pop_arr[7];
typedef struct stack{
	int arr[20];
	int top;
}STACK;

void init(STACK *s) {
	s->top = -1;
}
void push(STACK *s, int n) {
	s->arr[++(s->top)] = n;
}
int pop(STACK *s) {
	if (s->top == -1) {
		printf("Empty stack\n");
		return -1;
	}
	int x = s->arr[s->top];
	s->top = s->top - 1;
	return x;
}

void display() {
	for (int i = 6; i >= 0; i--) {
		printf("%d ", pop_arr[i]);
	}
}
void dfs(STACK *s, int adj_mat[][7], int visit[], int v) {
	static int c1 = 0, c2 = 0;
	if (visit[v] == 0) {
		push(s, v);
		visit[v] = 1;
	}
	for (int i = 0; i < 7; i++) {
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
int adj_mat[7][7] = {{0, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 1, 1, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 0}};
	int visit[7] = {0,0,0,0,0,0,0};
	STACK *s;
	s = (STACK*)malloc(sizeof(STACK));
	init(s);
	dfs(s, adj_mat, visit, 3);
	printf("\n");
	return 0;
}