#include <stdio.h>

char *ps = "Hello";

int main(void)
{
    int i = 0;

    ps[1] = 'h';//Segmentation fault

    printf("%s\n", ps);

    while (*ps) {
            printf("[%d] = %c\n", i, *ps);
            i++;
            ps++;
    }

    return 0;
}
