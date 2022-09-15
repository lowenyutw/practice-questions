#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int my_system(const char *argv[])
{
    if(execve("/bin/sh", &argv[1], environ) < 0)
    {
        perror("execve");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    pid_t child;
    int status;

    if(argc < 4)
    {
        fprintf(stderr, "Usage: %s sh -c \"[OPTION]\"\n", argv[0]);
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