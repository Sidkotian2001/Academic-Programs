#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct matrix {
	int arr[100][100];
	int row_arr[100];
	int col_arr[100];
	int r;
	int c;
};
void *row_sum(void *params) {
	struct matrix* m = (struct matrix*)params;
	int count = 0;
	for (int i = 0; i < m->r; i++) {
		int sum = 0;
		for (int j = 0; j < m->c; j++) {
			sum = sum + m->arr[i][j];
		}
		m->row_arr[count] = sum;
		count++;
	}

	return (void*)1;
}

void *col_sum(void *params) {
	struct matrix* m = (struct matrix*)params;
	int count = 0;
	for (int i = 0; i < m->c; i++) {
		int sum = 0;
		for (int j = 0; j < m->r; j++) {
			sum = sum + m->arr[j][i];
		}
		m->col_arr[count] = sum;
		count++;
	}

	return (void*)1;
}

int main() {
	pthread_t thread1, thread2;
	struct matrix *m = (struct matrix*)malloc(sizeof(struct matrix));
	int row, col;
	printf("Etner the number of rows and coloumns\n");
	scanf("%d", &row);
	scanf("%d", &col);
	printf("Enter the elemtns\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf("%d", &(m->arr[i][j]));
		}
	}
	m->r = row;
	m->c = col;
	pthread_create(&thread1, 0, &row_sum, (void*)m);
	pthread_create(&thread2, 0, &col_sum, (void*)m);

	int sum_r, sum_c;
	pthread_join(thread1, (void**)&sum_r);
	pthread_join(thread2, (void**)&sum_c);

	printf("\nThe row and column sum \n");
	for (int i = 0; i < m->r; i++) {
		printf("%d ", m->row_arr[i]);
	}
	printf("\n");
	for (int i = 0; i < m->c; i++) {
		printf("%d ", m->col_arr[i]);
	}
	printf("\n");

	return 0;
}