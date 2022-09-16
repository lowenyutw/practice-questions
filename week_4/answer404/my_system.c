#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

void my_system(const char *argv[])
{
    char **str = argv;
    str++;
    if(execvp(str[0], str) < 0)
    {
        perror("execve");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    pid_t child;
    int status;

    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s \"[OPTION]\"\n", argv[0]);
        exit(1);
    }

    if((child = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }

    if(child == 0)
    {
        my_system(argv);
    }
    else
    {
        if (wait(&status) < 0)
        {
            perror("wait");
            exit(1);
        }
    }

    return status;
}