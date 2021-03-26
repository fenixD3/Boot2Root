#include <stdio.h>

typedef signed int int32_t;
typedef unsigned int uint32_t;

int32_t func4(uint32_t a1) {
    int32_t result = 1;
    if (a1 >= 2) {
        int32_t v1 = func4(a1 - 1);
        result = func4(a1 - 2) + v1;
    }
    return result;
}

int main(void) {
    uint32_t i = 2;
    while (func4(i) != 55) {
        i++;
    }
    printf("%d\n", i);
    return 0;
}