#include <stdlib.h>

int main() {
    char *p = malloc(5);
    char *q = malloc(5);

    p = q;

    free(p);

    p = malloc(5);

    free(p);

    return 0;
}