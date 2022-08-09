#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	int tmp, max = pow(2, 26);
	char* data;
	char file_name[80];

	FILE* fpd;

	srand((unsigned)time(NULL));

	for (int i = 0; i < 10; i++)
	{
		tmp = rand();
	}

	for (int buff_size = 256; buff_size <= max; buff_size = buff_size * 4)
	{
		data = malloc(buff_size);
		char* s = data;

		for (int i = 0; i < buff_size - 1; i++)
		{
			for (int r = rand() % (256 - 16) + 16; r > 0 && i < buff_size - 1; r--, i++)
			{
				*s++ = rand() % (127 - 32) + 32;
			}

			if (i < buff_size - 1)
			{
				*s++ = '\n';
			}
			*s = '\0';
		}

		if (buff_size / 1024 > 0)
		{
			if (buff_size / 1024 / 1024 > 0)
			{
				sprintf(file_name, "%d%s.txt", buff_size / 1024 / 1024, "MBytes");
			}
			else
			{
				sprintf(file_name, "%d%s.txt", buff_size / 1024, "KBytes");
			}
		}
		else
		{
			sprintf(file_name, "%d%s.txt", buff_size, "Bytes");
		}

		fpd = fopen(file_name, "w");

		fputs(data, fpd);

		fclose(fpd);

		free(data);
	}

	return 0;
}
