#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pipe1[2], pipe2[2], status, max, num = 0 ,i = 0;
    pid_t child;
    char buf[100];

    if (argc != 2 || (max = atoi(argv[1])) < 1)
    {
        fprintf(stderr, "Useage: %s number", argv[0]);
        exit(1);
    }

    if (pipe(pipe1) < 0 || pipe(pipe2) < 0)
    {
        perror("pipe");
        exit(1);
    }

    if ((child = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }

    if (child == 0)
    {
        close(pipe1[0]);
        close(pipe2[1]);
        while(num < max)
        {            
            printf("%d", i % 10);
            fflush(stdout);

            i++;
            num++;
            
            if (write(pipe1[1], &num, sizeof(num)) < 0)
            {
                perror("child_write");
                exit(1);
            }
            if (read(pipe2[0], &num, sizeof(num)) < 0)
            {
                perror("child_read");
                exit(1);
            }
        }
        exit(0);
    }
    else
    {
        close(pipe1[1]);
        close(pipe2[0]);
        while (num < max)
        {
            if (read(pipe1[0], &num, sizeof(num)) < 0)
            {
                perror("parent_write");
                exit(1);
            }
            
            if (num < max)
            {
                printf("%c", (char)(i%26)+97);
                fflush(stdout);
            }

            i++;
            num++;

            if (write(pipe2[1], &num, sizeof(num)) < 0)
            {
                perror("parent_read");
                exit(1);
            }
        }

        wait(&status);

        printf("\n");
    }

    return 0;
}