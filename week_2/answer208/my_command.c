#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 2048

int main()
{
	char s[MAX];
	char* str, * np;

	while (fgets(s, MAX, stdin) != NULL)
	{
		str = s;
		*(str + (strlen(str) - 1)) = '\0';

		if ((np = strstr(str, " < ")) != NULL)
		{
			printf("command name:");
			while (str < np)
			{
				printf("%c", *str++);
			}

			printf("\ninput:%s\n\n", np + 3);
		}

		else
		{
			printf("command name:%s\ninput: console\n\n", str);
		}
	}

	return 0;
}
