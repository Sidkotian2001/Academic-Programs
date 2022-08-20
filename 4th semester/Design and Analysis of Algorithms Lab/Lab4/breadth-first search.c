#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int visit[8] = {0,0,0,0,0,0,0,0};
int enqueue_order[8];
int dequeue_order[8];

typedef struct Queue {
	int arr[MAX];
	int front;
	int rear;
}queue;

void init(queue * q) {
	q->front = -1;
	q->rear = -1;
}

void enqueue(queue *q, int data) {
	if (q->rear == MAX - 1) {
		printf("Queue is full\n");
		return;
	}
	q->arr[q->rear++] = data;
}
int dequeue(queue *q) {
	int data;
	if (q->front == q->rear) {
		printf("The queue is empty\n");
		return -1;
	}
	data = q->arr[q->front++];
	if (q->front == q->rear) {
		init(q);
	}
	return data;
}

void display() {
	int i;
	printf("enqueue_order : \n");
	for (i = 0; i < 8; i++) {
		printf("%d ", enqueue_order[i]);
	}
	printf("\ndequeue_order : \n");
	for (i = 0; i < 8; i++) {
		printf("%d ", dequeue_order[i]);
	}
	printf("\n");
}
void bfs(queue *q, int adj_mat[][8], int v) {
	static int c1 = 0, c2 = 0;
	if(q->front == q->rear) {
		return;
	}

	for (int i = 0; i < 8; i++) {
		if (visit[i] == 0 && adj_mat[v][i] == 1) {
			enqueue(q, i);
			enqueue_order[++c1] = i;
			visit[i] = 1;
		}
	}
	int x = dequeue(q);
	dequeue_order[c2++] = x;
	bfs(q, adj_mat, q->arr[q->front]);

}
int main() {
	int v = 0, start = 0;
	int adj_mat[8][8] = {{0,1,0,0,1,1,0,0},
				{1,0,0,0,0,1,1,0},
				{0,0,0,1,0,0,1,0},
				{0,0,1,0,0,0,0,1},
				{1,0,0,0,0,1,0,0},
				{1,1,0,0,1,0,0,0},
				{0,1,1,0,0,0,0,1},
				{0,0,0,1,0,0,1,0}};
	queue *q = (queue*)malloc(sizeof(queue));
	init(q);
	enqueue(q, v);
	visit[v] = 1;
	enqueue_order[0] = v;
	bfs(q, adj_mat,v);
	display();
	return 0;
}