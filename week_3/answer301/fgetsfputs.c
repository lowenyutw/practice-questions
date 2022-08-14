#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double copy_time(FILE* fps, FILE* fpd, int max)
{
	double start, end;
	int c;
	char* s = malloc(max);

	start = clock();

	while (fgets(s, max, fps) != NULL)
	{
		fputs(s, fpd);
	}

	end = clock();

	free(s);

	return (end - start) / CLOCKS_PER_SEC;
}

void result_print(char* file_name, double* time_consume, int max)
{
	double total_time = 0;

	printf("File: %s\n", file_name);
	for (int i = 0; i < max; i++)
	{
		total_time = total_time + *time_consume++;
		//printf("%d: Use time: %lf\n", i + 1, *time_consume++);
	}
	printf("ten times average: %lf(s)\n\n", total_time / max);
}

int main(int argc, char* argv[])
{
	FILE* fps, * fpd;
	double time_consume[10] = { 0 }, average_time = 0;
	int data_max = sizeof time_consume / sizeof time_consume[0];

	if (argc < 2 || argc > 3)
	{
		fprintf(stderr, "Usage: %s dst_file\n", argv[0]);
		exit(1);
	}

	fpd = fopen(argv[1], "w");
	if (fpd == NULL)
	{
		perror(argv[1]);
		exit(1);
	}

	fps = fopen(argv[2], "r");
	if (fps == NULL)
	{
		char file_name[80];
		int max = 67108864;

		for (int data_size = 256; data_size <= max; data_size = data_size * 4)
		{
			if (data_size / 1024 > 0)
			{
				if (data_size / 1024 / 1024 > 0)
				{
					sprintf(file_name, "%dMBytes.txt", data_size / 1024 / 1024);
				}
				else
				{
					sprintf(file_name, "%dKBytes.txt", data_size / 1024);
				}
			}
			else
			{
				sprintf(file_name, "%dBytes.txt", data_size);
			}

			if ((fps = fopen(file_name, "r")) == NULL)
			{
				perror(file_name);
				exit(1);
			}

			for (int i = 0; i < 10; i++)
			{
				fps = fopen(file_name, "r");
				fpd = fopen(argv[1], "w");

				time_consume[i] = copy_time(fps, fpd, 65536);

				fclose(fps);
				fclose(fpd);
			}

			result_print(file_name, time_consume, data_max);
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			fps = fopen(argv[2], "r");
			fpd = fopen(argv[1], "w");

			time_consume[i] = copy_time(fps, fpd, 65536);

			fclose(fps);
			fclose(fpd);
		}

		result_print(argv[2], time_consume, data_max);
	}

	return 0;
}
