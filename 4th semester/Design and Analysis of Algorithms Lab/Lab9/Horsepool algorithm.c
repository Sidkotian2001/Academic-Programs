#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int size = 1000;
int Table[1000];
int key1 = 0;
void shifttable(char p[], int m) {
	int i;
	
	for (i = 0; i < size; i++) {
		Table[i] = m;
	}

	for (i = 0; i < m - 1; i++) {
		Table[p[i]] = m - 1 - i;
	}
}

int HorsepoolMatching(char p[], char t[], int m, int n) {
	shifttable(p, m);

	int i = m - 1, k;

	while (i <= n - 1) {
		k = 0;
		while (k <= m - 1 && p[m - 1 - k] == t[i - k]) {
			k++;
			key1++;
		}
		if (k == m) {
			printf("%d\n", key1);
			return i - m + 1;
		}
		else {
			i = i + Table[t[i]];
		}
	}
	printf("%d\n", key1);
	return -1;
}

int main() {
	char text[200] = "JIM_SAW_ME_IN_A_BARBERSHOP";
	char pat[200] = "BARBER";
	char pat2[200] = "SHOP";

	int pos1 = HorsepoolMatching(pat, text, strlen(pat), strlen(text));
	int pos2 = HorsepoolMatching(pat2, text, strlen(pat2), strlen(text));

	printf("%d %d\n", pos1, pos2);

	return 0;
}