#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    fork();
    fork();
    fork();
    printf("Hello.\n");
    wait(NULL);
    return 0;
}