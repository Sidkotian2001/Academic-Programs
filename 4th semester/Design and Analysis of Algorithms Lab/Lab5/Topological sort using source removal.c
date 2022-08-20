#include <stdio.h>
#include <stdlib.h>




void topological(int del, int n, int adj_mat[][n]) {
int i, j, k = 0;
int col_sum, flag1 = 0, flag2 = 0;
for (int a = 0; a < n; a++) {
k = 0;
flag2 = 0;
for (i = 0; i < n; i++) {
col_sum = 0;
flag1 = 0;
for (j = 0; j < n; j++) {
if (adj_mat[i][j] != -1) {
flag1 = 1;
col_sum = col_sum + adj_mat[j][i];
}
}
if (col_sum == 0 && flag1 == 1) {
flag2 = 1;
printf("%d ", k);
break;
}
k++;
}
if (flag2 == 0) {
break;
}
i = k;
for (j = 0; j < n; j++) {
adj_mat[i][j] = -1;
adj_mat[j][i] = -1;
}



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
topological(0, 7, adj_mat);
return 0;
}