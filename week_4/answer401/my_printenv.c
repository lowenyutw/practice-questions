#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char **var;
    extern char **environ;

    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [OPTION]\n", argv[0]);
        exit(-1);
    }

    if (argc == 2)
    {
        printf("%s=%s\n", argv[1], getenv(argv[1]));
    }
    else
    {
        for (var = environ; *var != NULL; var++)
        {
            printf("%s\t\n", *var);
        }
    }

    return 0;
}