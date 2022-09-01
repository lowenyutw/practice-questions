#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(int argc, char* argv[])
{
	int fd, lines, err;
	struct stat fs;
	size_t maplen;
	char* p_map, * s, * np;

	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s [lines] [file]\n", argv[0]);
		exit(-1);
	}

	err = sscanf(argv[1], "%d", &lines);
	if (err < 0)
	{
		perror(argv[1]);
		exit(-1);
	}

	fd = open(argv[2], O_RDONLY);
	if (fd < 0)
	{
		perror(argv[2]);
		exit(-1);
	}

	if (fstat(fd, &fs) < 0)
	{
		perror("fstat");
		exit(-1);
	}

	for (maplen = fs.st_size; maplen % sysconf(_SC_PAGESIZE) != 0; maplen++);

	p_map = (char*)mmap(NULL, maplen, PROT_READ, MAP_PRIVATE, fd, 0);
	if (p_map == MAP_FAILED)
	{
		perror("mmap");
		exit(-1);
	}

	close(fd);

	s = p_map;

	for (int i = 0; i < lines; i++)
	{
		if ((np = strchr(s, '\n')) != NULL)
		{
			while(s <= np)
			{
				printf("%c", *s++);

			}
		}
		else
		{
			printf("%s", s);
			break;
		}
	}

	err = munmap(p_map, maplen);
	if (err)
	{
		perror("munmap");
		exit(-1);
	}

	return 0;
}
