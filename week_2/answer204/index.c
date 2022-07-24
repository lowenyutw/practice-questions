#include <stdio.h>
#include <string.h>
#include <sys/param.h>

int main(void)
{
    int i;
    char line_buf[MAXPATHLEN];
    char* p, * np;

    while (fgets(line_buf, MAXPATHLEN, stdin) != NULL) {
        i = 0;
        p = line_buf;
        int max = strlen(p) - 2;

        if (*(p + max) == '/')
        {
            *(p + max) = 0;
        }

        if (*p == '/')
        {
            printf("%d: %c\n", i++, *p);
            *p = 0;
            p++;
        }

        while ((np = strchr(p, '/')) != NULL) {
            *np = '\0';
            printf("%d: %s\n", i++, p);
            p = np + 1;
        }
        printf("%d: %s\n", i, p);
    }

    return 0;
}
