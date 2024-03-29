#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 2048

int main()
{
	char s[MAX];
	char* str, * np,* input,* output;
	char console[] = "console";
	int pipe, in, out;

	printf("Usage: [command_1] [redirection_1] [file_1] [command_2] [redirection_2] [file_2]\n");
	while (fgets(s, MAX, stdin) != NULL)
	{
		str = s;
		input = console;
		output = console;
		pipe = 0;
		in = 0;
		out = 0;

		*(str + (strlen(str) - 1)) = '\0';

		if ((np = strchr(str,  '|')) != NULL)
		{
			pipe = 1;
			*np = ' ';
		}

		if ((np = strstr(str, " < ")) != NULL)
		{
			in = 1;
			*np = '\0';

			while (isalpha(*str) == 0)
			{
				str++;
			}

			printf("command name:%s\n",str);

			str = np + 3;
			input = np + 3;

			while (*str != '\0' && *str != ' ')
			{
				str++;
			}

			*str = '\0';

			printf("input:%s\n", input);

			while (isalpha(*str) == 0)
			{
				str++;
			}

			if ((np = strstr(str, " > ")) != NULL)
			{
				out = 1;
				*np = '\0';

				printf("command name:%s\n", str);

				str = np + 3;
				output = np + 3;

				while (*str != '\0' && *str != ' ')
				{
					str++;
				}

				*str = '\0';

				printf("output:%s\n", output);
			}
		}
		else
		{
			printf("command name:%s\ninput:%s\n", str, input);
		}

		if (pipe)
		{
			if (in)
			{
				printf("input:%s\n", input);
			}

			if (out)
			{
				printf("output:%s\n", output);
			}
		}
		printf("\n");
	}

	return 0;
}
