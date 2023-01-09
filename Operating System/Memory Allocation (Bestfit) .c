#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bestFit(int blockSize[], int m, int processSize[], int n) {
	int allocation[n];
    memset(allocation, -1, sizeof(allocation));

    for (int i=0; i<n; i++)
    {
        // Find the best fit block for current process
        int bestIdx = -1;
        for (int j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = bestIdx;

            // Reduce available memory in this block.
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf("\t%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d",allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    } 
}
int main() {
	int blockSize[] = {200, 560, 100, 300, 600, 700};
	int processSize[] = {212, 100, 417, 160, 420, 500};
    int m = sizeof(blockSize)/sizeof(blockSize[0]);
    int n = sizeof(processSize)/sizeof(processSize[0]);

    bestFit(blockSize, m, processSize, n);

    return 0 ;
}