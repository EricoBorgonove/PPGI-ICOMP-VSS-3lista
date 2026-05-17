#include <stdint.h>

struct foo {
    uint16_t bar[2];
    uint8_t baz;
};

int main() {
    struct foo qux;

    qux.bar[0] = 10;
    qux.bar[1] = 20;
    qux.baz = 'C';

    struct foo *quux = &qux;
    quux++;
    quux->baz = 'D';

    return 0;
}