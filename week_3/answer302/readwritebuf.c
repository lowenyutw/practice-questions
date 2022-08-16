#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

double copy_time(int fps, int fpd, int max)
{
	double start, end;
	int c;
	char* s = malloc(max);

	start = clock();

	while ((c = read(fps, s, max)) > 0)
	{
		write(fpd, s, c);
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
	int fps, fpd;
	double time_consume[10] = { 0 }, average_time = 0;
	int data_max = sizeof time_consume / sizeof time_consume[0];

	if (argc < 2 || argc > 3)
	{
		fprintf(stderr, "Usage: %s dst_file\n", argv[0]);
		exit(1);
	}

	fpd = open(argv[1], O_WRONLY | O_TRUNC);
	if (fpd < 0)
	{
		perror(argv[1]);
		exit(1);
	}

	fps = open(argv[2], O_RDONLY);
	if (fps < 0)
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

			if ((fps = open(file_name, O_RDONLY) < 0))
			{
				perror(file_name);
				exit(1);
			}

			for (int i = 0; i < 10; i++)
			{
				fps = open(file_name, O_RDONLY);
				fpd = open(argv[1], O_WRONLY | O_TRUNC);

				time_consume[i] = copy_time(fps, fpd, 65536);

				close(fps);
				close(fpd);
			}

			result_print(file_name, time_consume, data_max);
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			fps = open(argv[2], O_RDONLY);
			fpd = open(argv[1], O_WRONLY | O_TRUNC);

			time_consume[i] = copy_time(fps, fpd, 65536);

			close(fps);
			close(fpd);
		}

		result_print(argv[2], time_consume, data_max);
	}

	return 0;
}
