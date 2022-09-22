#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char **strfind(int *num, char *argv[], char *target)
{
    int i;
    char **str = argv;
    for (; *num > 0; *num -= 1)
    {
        if (strcmp(*str, target) != 0)
        {
            str++;
        }
        else
        {
            *str = NULL;
            *num -= 1;
            return str + 1;
        }
    }
    fprintf(stderr, "\"%s\" target not find\n", target);
    exit(1);
}

int main(int argc, char *argv[])
{
    pid_t child;
    int status, num = argc;
    char **strthen = argv;
    char **strelse = argv;

    if (argc < 0)
    {
        fprintf(stderr, "Usage:%s test [option] then [option] else [option]\n", argv[0]);
        exit(1);
    }

    strthen = strfind(&num, argv, "then");
    strelse = strfind(&num, strthen, "else");

    if ((child = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (child == 0)
    {
        execvp(argv[1], argv + 1);
    }
    else
    {
        wait(&status);
        if (WEXITSTATUS(status) == 0)
        {
            execvp(strthen[0], strthen);
        }
        else if (WEXITSTATUS(status) == 1)
        {
            execvp(strelse[0], strelse);
        }
        else
        {
            fprintf(stderr, "execvp: error\n");
            exit(1);
        }
    }

    return 0;
}