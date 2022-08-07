#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treeptr;
int ldeptharr[100];
int rdeptharr[100];
int c1 = 0, c2 = 0;
typedef struct tree {
	int data;
	treeptr left;
	treeptr right;	
}TREE;

treeptr insert(treeptr root, int data) {
	if (!(root)) {
		treeptr newnode = (treeptr)malloc(sizeof(TREE));
		newnode->data = data;
		newnode->left = NULL;
		newnode->right = NULL;
		return newnode;;
	}

	treeptr temp = root;
	if (temp->data > data) {
		temp->left = insert(temp->left, data);
	}
	else {
		temp->right = insert(temp->right, data);
	}
	return root;
}
void display(treeptr root) {
	if (!(root)) {
		return;
	}
	display(root->left);
	printf("%d ", root->data);
	display(root->right);
}

int findheight(treeptr root) {
	if (!root) {
		return -1;
	}
	else {
		int ldepth = 1 + findheight(root->left);
		int rdepth = 1 + findheight(root->right);
		ldeptharr[c1++] = ldepth;
		rdeptharr[c2++] = rdepth;
		if (ldepth > rdepth) {
			return ldepth;
		}
		else {
			return rdepth;
		}
	}
}
int main() {
	treeptr root;
	root = NULL;
	root = insert(root, 10);
	root = insert(root, 5);
	root = insert(root, 20);
	root = insert(root, 7);
	root = insert(root, 25);
	root = insert(root, 6);
	display(root);
	int height = findheight(root);
	int max = ldeptharr[0] + rdeptharr[0];
	printf("\n the height of the tree is : %d\n", height);
	for (int i = 0; i < c1; i++) {
		if (max < ldeptharr[i] + rdeptharr[i]) {
			max = ldeptharr[i] + rdeptharr[i];
		}
	}
	printf("%d\n", max);
	return 0;
}