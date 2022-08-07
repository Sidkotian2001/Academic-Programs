#include <stdio.h>
#include <stdlib.h>

typedef struct node* treeptr;

typedef struct node {
	int data;
	treeptr llink;
	treeptr rlink;
}Node;

typedef struct stack {
	int arr[10];
	int top;
}Stack;

void init(Stack *s) {
	s->top = -1;
}
int isempty(Stack *s) {
	if (s->top == -1) {
		return 1;
	}
	return 0;
}
int isfull(Stack *s) {
	if (s->top == 10 -1 ) {
		return 1;
	}
	return 0;
}
void push(Stack *s, int d) {
	if (isfull(s)) {
		printf("Stack if full\n");
	}
	else {
		s->top++;
		s->arr[s->top] = d;
	}
}

int pop (Stack *s) {
	if (isempty(s)) {
		printf("The stack is empyu\n");
	}
	int d = arr[top];
	top--;
	return d;
}

treeptr insertnode(treeptr *root, int d) {
	treeptr newnode = (treeptr)malloc(sizeof(Node));
	newnode->data = d;
	newnode->llink = NULL;
	newnode->rlink = NULL;

	if ((*root) == NULL) {
		*root = newnode;
	}
	else {
		treeptr curr = *root, prev;
		while (curr != NULL) {

			if (curr->data > d) {
				prev = curr;
				curr = curr->llink;
			}
			else if (curr->data < d){
				prev = curr;
				curr = curr->rlink;
			}
			else {
				printf("Key is already there\n");
				break;
			}
		}

		if (prev->data > d) {
			prev->llink = newnode;
		}
		else {
			prev->rlink = newnode;
		}
		//printf("%d ", prev->data);
	}

	return *root;
}

void display(treeptr *root) {
	treeptr curr = *root, prev;
	while (curr != NULL) {
		if (curr->llink == 	NULL)
	}
}

int main() {
	treeptr root;

	root = insertnode(&root, 10);
	root = insertnode(&root, 20);
	root = insertnode(&root, 5);
	root = insertnode(&root, 30);
	root = insertnode(&root, 7);

	display(root);

	return 0;
}