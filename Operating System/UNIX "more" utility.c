#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	char str[500];
	
	char c;
	int in = open(argv[1], O_RDONLY);
	int i = 0;
	int l_count = 0;
	while (read(in, &c, 1) == 1) {
		if (c != '\n') {
			str[i] = c;
			i++;
		}
		else {
			l_count++;
			write(2, str, sizeof(str));
			write(2, "\n", 1);
			if (l_count == 20) {
				fgetc(stdin);
			}
			i = 0;
		}
		
	}
	
	return 0;
}