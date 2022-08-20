#include<stdio.h>

#include <stdlib.h>
int balance_factor[100];
int c = 0;
typedef struct node
{
	int info;
	struct node *left,*right;
}NODE;
NODE* create(NODE *bnode,int x)
{
	NODE *getnode;
	if(bnode==NULL)
	{
		bnode=(NODE*) malloc(sizeof(NODE));
		bnode->info=x;
		bnode->left=bnode->right=NULL;
	}
	else if(x>bnode->info)
		bnode->right=create(bnode->right,x);
	else if(x<bnode->info)
		bnode->left=create(bnode->left,x);
	else
	{
		printf("Duplicate node\n");
		exit(0);
	}
	return(bnode);
}

int findheight(NODE *root) {
	if (!root) {
		return -1;
	}
	else {
		int ldepth = 1 + findheight(root->left);
		int rdepth = 1 + findheight(root->right);
		balance_factor[c++] = ldepth - rdepth;
		if (ldepth > rdepth) {
			return ldepth;
		}
		else {
			return rdepth;
		}
	}
}
void main()
{
	int n,x,ch,i,g;
	NODE *root;
	root=NULL;
	while(1)
	{
		printf(" 1. Insert\n 2. All traversals\n 3. Exit\n");
		printf("Enter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: 
			printf("Enter node (do not enter duplicate nodes):\n");
			scanf("%d",&x);
			root=create(root,x);
			break;
			case 2:
			g = findheight(root);
			for (int i = 0; i < c; i++) {
				printf("%d ", balance_factor[i]);
			}
			printf("\n");
			break;
			case 3: 
			exit(0);
		}
	}
}