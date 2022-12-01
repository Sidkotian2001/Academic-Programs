#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    char str[500];
    char c;

    int in = open(argv[1], O_RDONLY);
    FILE *fb = fopen("file2", "w+");

    while (read(in, &c, 1) == 1) {
        // c = fgetc(fa);
        fputc(c, fb);    
    }
    return 0;
    
}