#include <stdio.h>
#include <ctype.h>

int wc(char* str)
{
    int num = 0;
    while (*str)
    {
        if (*str >= 65 && *str <= 90 || *str >= 97 && *str <= 122)
        {
            while (*str >= 65 && *str <= 90 || *str >= 97 && *str <= 122 || *str == 45)
            {
                *str++;
            }

            num++;
        }
        while (!(*str >= 65 && *str <= 90 || *str >= 97 && *str <= 122))
        {
            if (*str == 0)
            {
                break;
            }

            *str++;
        }
    }

    return num;
}

int main(void)
{
    char* str;

    str = "University of Tsukuba"; // 3
    printf("%d\n", wc(str));

    str = "Hello\tworld!\nGood-bye\tworld!\n\n"; // 4
    printf("%d\n", wc(str));

    str = "    Ten little Indians standin' in a line;\n"
        "        One toddled home and then there were nine.\n"
        "    Nine little Indians swingin' on a gate;\n"
        "        One tumbled off and then there were eight.\n"; // 30
    printf("%d\n", wc(str));

    return 0;
}
