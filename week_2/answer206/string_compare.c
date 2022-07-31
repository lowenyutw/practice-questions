#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int my_strcmp(const char* s1, const char* s2)
{
	while (*s1)
	{
		if (*s1 > *s2)
		{
			return *s1 - *s2;
		}

		if (*s1 < *s2)
		{
			return *s1 - *s2;
		}

		s1++;
		s2++;
	}

	if (*s2 != '\0')
	{
		return *s1 - *s2;
	}

	return 0;
}

int my_strcasecmp(const char* s1, const char* s2)
{
	while (*s1)
	{
		if (*s1 >= 97 && *s1 <= 122 && *s2 >= 97 && *s2 <= 122)
		{
			if (*s1 - 32 > *s2 - 32)
			{
				return *s1 - *s2;
			}

			if (*s1 - 32 < *s2 - 32)
			{
				return *s1 - *s2;
			}
		}

		else if (*s1 >= 97 && *s1 <= 122)
		{
			if (*s1 - 32 > *s2)
			{
				return *s1 - *s2;
			}

			if (*s1 - 32 < *s2)
			{
				return *s1 - *s2;
			}
		}

		else if (*s2 >= 97 && *s2 <= 122)
		{
			if (*s1 > *s2 - 32)
			{
				return *s1 - *s2;
			}

			if (*s1 < *s2 - 32)
			{
				return *s1 - *s2;
			}
		}

		else
		{
			if (*s1 > *s2)
			{
				return *s1 - *s2;;
			}

			if (*s1 < *s2)
			{
				return *s1 - *s2;
			}
		}

		s1++;
		s2++;
	}

	if (*s2 != '\0')
	{
		return *s1 - *s2;
	}

        return 0;
}


int main()
{
	int len1, len2;
	char* a1 = "AAAaaAaAAaa";
	char* a2 = "AAAAAAaAAAa";

	char* b1 = "aaabbb6437Gceq";
	char* b2 = "aaabbb6437Gceq";

	char* c1 = "ABC";
	char* c2 = "aBCd";

	len1 = strcmp(a1, a2);
	len2 = my_strcmp(a1, a2);
	printf("a1: %s   a2: %s\n\nstrcmp-compare-a1-to-a2: %d\nmy_strcmp-compare-a1-to-a2: %d\n\n\n",a1, a2, len1, len2);

	len1 = strcmp(b1, b2);
	len2 = my_strcmp(b1, b2);
	printf("b1: %s   b2: %s\n\nstrcmp-compare-b1-to-b2: %d\nmy_strcmp-compare-b1-to-b2: %d\n\n\n", b1, b2, len1, len2);

	len1 = strcmp(c1, c2);
	len2 = my_strcmp(c1, c2);
	printf("c1: %s   c2: %s\n\nstrcmp-compare-c1-to-c2: %d\nmy_strcmp-compare-c1-to-c2: %d\n\n\n", c1, c2, len1, len2);

	len1 = strcasecmp(a1, a2);
	len2 = my_strcasecmp(a1, a2);
	printf("a1: %s   a2: %s\n\nstrcasecmp-compare-a1-to-a2: %d\nmy_strcasecmp-compare-a1-to-a2: %d\n\n\n", a1, a2, len1, len2);

	len1 = strcasecmp(b1, b2);
	len2 = my_strcasecmp(b1, b2);
	printf("b1: %s   b2: %s\n\nstrcasecmp-compare-b1-to-b2: %d\nmy_strcasecmp-compare-b1-to-b2: %d\n\n\n", b1, b2, len1, len2);

	len1 = strcasecmp(c1, c2);
	len2 = my_strcasecmp(c1, c2);
	printf("c1: %s   c2: %s\n\nstrcasecmp-compare-c1-to-c2: %d\nmy_strcasecmp-compare-c1-to-c2: %d\n\n\n", c1, c2, len1, len2);

	//system("PAUSE");
	return 0;
}
