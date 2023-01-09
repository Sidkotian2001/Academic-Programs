#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int opcount = 0;
int nodes = 0;
typedef struct tree* treeptr;

typedef struct tree {
	int data;
	treeptr left;
	treeptr right;
}TREE;

treeptr insertnode(treeptr root,int data, char str[]) {
	treeptr newnode = (treeptr)malloc(sizeof(TREE));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = data;
	if(!root) {
		root = newnode;
		return root;
	}
	treeptr temp = root;
	int i;
	for (i = 0; i < strlen(str) - 1; i++) {
		if(str[i] == 'l'){
			temp = temp->left;
		}
		if(str[i] == 'r') {
			temp = temp->right;
		}
	}
	if (str[i] == 'l' && temp->left == NULL) {
		temp->left = newnode;
	}
	else if (str[i] == 'r' && temp->right == NULL) {
		temp->right = newnode;
	}
	return root;
}

void display_count(treeptr root) {
	
	if (!root) {
		return;
	}
	opcount++;
	display_count(root->left);
	nodes++;
	display_count(root->right);
}

int main() {
	treeptr root = NULL;
	int n;
	char str[20];
	int i = 0;
	do {
		printf("Enter data ");
		scanf("%d", &n);
		printf("enter position ");
		scanf("%s", str);
		root = insertnode(root, n, str);
		i++;
	}while(n != -1);
	display_count(root);
	printf("\nThe number of nodes is : %d", nodes);
	printf("\nThe opcount : %d", opcount);
	return 0;
}