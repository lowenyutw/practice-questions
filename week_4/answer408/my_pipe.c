#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status, max, child_max, num = 0, i = 0, child_out = 0;
    pid_t child;

    if (argc != 3 || (max = atoi(argv[1])) < 1 || (child_max = atoi(argv[2])) < 0)
    {
        fprintf(stderr, "Useage: %s number", argv[0]);
        exit(1);
    }

    for (int out = 1; num < max; out++)
    {
        for (int j = 0; j < child_max && num < max; j++)
        {
            int pipe1[2];

            if (pipe(pipe1) < 0)
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

                for (int x = 0; x < out; child_out++, x++)
                {
                    printf("%d", child_out % 10);
                }
                fflush(stdout);

                num += out;

                if (write(pipe1[1], &num, sizeof(num)) < 0)
                {
                    perror("child_write");
                    exit(1);
                }

                if (write(pipe1[1], &child_out, sizeof(child_out)) < 0)
                {
                    perror("child_write");
                    exit(1);
                }

                exit(0);
            }
            else
            {

                close(pipe1[1]);

                if (read(pipe1[0], &num, sizeof(num)) < 0)
                {
                    perror("parent_write");
                    exit(1);
                }

                if (read(pipe1[0], &child_out, sizeof(child_out)) < 0)
                {
                    perror("parent_write");
                    exit(1);
                }

                if (num < max)
                {
                    printf("%c", (char)(i % 26) + 97);
                    fflush(stdout);
                }

                i++;
                num++;
                wait(&status);
            }
        }
    }

    printf("\n");
    return 0;
}