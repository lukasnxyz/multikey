#include <stdio.h>

typedef struct {
    char letter;
    int num;
} Test;

int main() {
    static Test tests[] = {
        {'d', 36},
        {'c', 34},
    };
    printf("%c\n", tests[0].letter);

    return 0;
}
