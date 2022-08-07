#include <stdio.h>
#include <stdlib.h>

typedef struct node* listptr;

typedef struct node {
	char data;
	listptr link;
}Node;

//Insert to the list
void insertnode(listptr* head, char d) {

	listptr newnode = (listptr)malloc(sizeof(struct node));
	newnode->data = d;
	newnode->link = NULL;
	if ((*head) == NULL) {
		(*head) = newnode;
	}
	else {
		listptr temp;
		temp = (*head);

		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = newnode;
	}
}

void printlist(listptr* head) {
	listptr temp = (*head);

	while (temp != NULL) {
		printf("%c --> " , temp->data);
		temp = temp->link;
	}
}

int main() {
	int v , e ;
	char v1, v2;
	int m, n;

	printf("Enter the number of vertices\n");
	scanf("%d", &v);

	printf("Enter the number of edges\n");
	scanf("%d", &e);

	listptr adjlist[e];

	for (int i = 0; i < e; i++) {
		adjlist[i] = NULL;
	}

	int choice = 0;
	
	while(1) {

		printf("Enter 1.Enter 2.Exit\n");
		scanf("%d", &choice);

		if (choice == 2) {
			break;
		}
		printf("Enter the vertex to be connected\n");
		scanf(" %c", &v1);

		printf("Enter the vertex connected to \n");
		scanf(" %c", &v2);


		if (v1 - 'a' > v - 1 || v2 - 'a' > v - 1) {
			printf("Error incorrect vertex is entered\n");
			exit(0);
		}
		if (v1 == v2) {
			printf("Error same vertex cannot be connected\n");
			continue;
		}

		m = v1 - 'a';
		n = v2 - 'a';

		insertnode(&adjlist[m], v2);
 
	}

	for (int i = 0; i < e; i++) {
		printf("vertex %d -->", i+1);
		printlist(&adjlist[i]);
		printf("\n");
	}

	return 0;
}

