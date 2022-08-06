#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 2048

char* command(char* str, const char target)
{
	char* np, * s, * error;

	if ((np = strchr(str, target)) != NULL)
	{
		s = np;
		error = np;
		if (strchr(++error, target) != NULL)
		{
			printf("[ERROR]: \"%c\" repetition\n", target);
			return NULL;
		}

		while (!isalpha(*s))
		{
			s--;
		}

		while (isalpha(*s) && s > str)
		{
			s--;
		}

		if (!isalpha(*s))
		{
			s++;
		}

		printf("command name: ");
		while (isalpha(*s))
		{
			printf("%c", *s++);
		}
		printf("\n");

		file_print(np, target);

		return np;
	}
	else
	{
		if (target == '<')
		{
			printf("input: console");
		}

		if (target == '>')
		{
			printf("output: console");
		}
		printf("\n");

		return NULL;
	}
}

void file_print(char* str,const char target)
{
	while (!isalpha(*str) && *str)
	{
		str++;
	}

	if (*str != '\0')
	{
		if (target == '<')
		{
			printf("input: ");
		}

		if (target == '>')
		{
			printf("output: ");
		}

		while (isalpha(*str))
		{
			printf("%c", *str++);
		}
		printf("\n");
	}
}

void pipe(char* str, char* p, const char target)
{
	char* np, * error;

	if ((np = strchr(str, '|')) != NULL)
	{
		error = np;

		if ((strchr(++error, '|')) != NULL)
		{
			printf("[ERROR]: \"|\" repetition\n");
			return;
		}

		file_print(p, target);
	}
}

int main()
{
	char s[MAX];
	char* str = s;
	char* input,* output;

	while (fgets(s, MAX, stdin) != NULL)
	{
		input = command(str, '<');
		if (input)
		{
			output = command(str, '>');

			pipe(str, input, '<');

			if (output)
			{
				pipe(str, output, '>');
			}
		}
	}

	return 0;
}
