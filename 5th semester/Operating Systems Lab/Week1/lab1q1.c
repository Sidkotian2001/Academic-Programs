#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	char str[500];
	char const *substr = argv[1];
	char c;
	int in = open("file1.txt", O_RDONLY);
	int i = 0;
	while (read(in, &c, 1) == 1) {
		if (c != '\n') {
			str[i] = c;
			i++;
		}
		else {
			if (strstr(str, substr) != NULL) {
				write(2, str, sizeof(str));
				write(2, "\n", 1);
			}
			i = 0;
		}
		
	}
	return 0;
}