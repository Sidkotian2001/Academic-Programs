#include <stdio.h>
#include <stdlib.h>

int main() {
	int v, e;

	printf("Enter the number of vertices\n");
	scanf("%d", &v);

	printf("Enter the number of edges\n");
	scanf("%d", &e);

	int max_edges = (v * (v - 1)) / 2;
	if (e > max_edges) {
		printf("Error max edges can be %d", max_edges);
		exit(0);
	}
	int adjmat[v][v];

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			adjmat[i][j] = 0;
		}
	}

	char v1, v2;

	int m,n;

	char vertices_array[v];

	for (int i = 0; i < e; i++) {

		printf("Enter the vertex to be connected\n");
		scanf(" %c", &v1);
		printf("Enter vertex it is connected to \n");
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

		adjmat[m][n] = 1;
	}

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			printf("%d ", adjmat[i][j]);
		}
		printf("\n");
	}
 

	return 0;
}