#include <stdio.h>

#define MAX 10

void test()
{
    int i, total;

    total = 0;
    for (i = 1; i <= MAX; i++) {
            total += i;
    }

    printf("total = %d\n", total);
}
