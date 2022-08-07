#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int a = 43;
    float b = 5.6;
    char c = 's';
    char str[] = "hello";
    double e = 89.4444;
    printf("int : %d\n", a);
    printf("char : %c\n", c);
    printf("string : %s\n", str);
    printf("float : %g\n", b);
    printf("double : %f\n", e);
    printf("unsigned octal : %o\n", a);
    printf("unsigned hex : %x\n", a);

    return 0;
}