#include <stdio.h>
#include <string.h>

int main() {
	char str[20], pat[20];
	printf ("The string : \n");
	scanf("%s", str);

	printf("The pattern : \n");
	scanf(" %s", pat);

	int l1, l2, i, j, pos = 0, flag = 0, opcount = 0;

	l1 = strlen(str);
	l2 = strlen(pat);

	for (i = 0; i <= l1 - l2; i++) {

		if (str[i] == pat[0]) {
			flag = 1;
			for (j = 0; j < l2; j++) {
				opcount++;
				if (str[i + j] != pat[j]) {
					flag = 0;
					break;
				}
			}
			if (flag == 0) {
				continue;
			}
			else {
				pos = i;
				break;
			}
		}
	}

	if (flag == 1) {
		printf("The strin is located at position %d\n", pos);
	}
	else {
		printf("Not found\n");
	}

	printf("Opcount : %d", opcount);

	return 0;
}