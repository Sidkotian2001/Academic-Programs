#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, m, i, j, k, c = 0;
    n = 5; // Number of processes
    m = 3; // Number of resources
    int alloc[5][3] = { { 0, 1, 0 }, // P0    // Allocation Matrix
                        { 2, 0, 0 }, // P1
                        { 3, 0, 2 }, // P2
                        { 2, 1, 1 }, // P3
                        { 0, 0, 2 } }; // P4
 
    int max[5][3] = { { 7, 5, 3 }, // P0    // MAX Matrix
                      { 3, 2, 2 }, // P1
                      { 9, 0, 2 }, // P2
                      { 2, 2, 2 }, // P3
                      { 4, 3, 3 } }; // P4
 
    int avail[3] = { 3, 3, 2 }; // Available Resources

    int f[n], sequence[n], flag = 0;
    for (i = 0; i < n; i++) {
    	f[i] = 0;
    }

    int need[n][m];
    for (i = 0; i < n; i++) {
    	for (j = 0; j < m; j++) {
    		need[i][j] = max[i][j] - alloc[i][j];
    	}
    }

    for (k = 0;k < n; k++) {
    	for (i = 0; i < n; i++) {
    		flag = 0;
    		if (f[i] == 0) {

    			for (j = 0; j < m;j++) {
	    			if (need[i][j] > avail[j]) {
	    				flag = 1;
	    				break;
	    			}
    			}

    			if (flag == 0) {
    				f[i] = 1;
    				sequence[c] = i + 1;
    				c += 1;
    				for (j = 0; j < m; j++) {
    					avail[j] += alloc[i][j];
    				}

    			}
    		}
    		
    	}
    }
    flag = 1;
    for (i = 0;i < n; i++) {
    	if (f[i] == 0) {
    		flag = 0;
    		printf("Unsafe system\n");
    	}
    }
    if (flag == 1) {
    	printf("Safe sequence : \n");
    	for (i = 0; i < n; i++) {
    		printf("%d ", sequence[i]);
    	}
    	printf("\n");
    }

    return 0;

}