#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t my_strlcpy(char* dst,const char* src, size_t size)
{
    const char* s = src;
    size_t n = size;

    if (n != 0)
    {
        while (--n)
        {
            if ((*dst++ = *s++) == '\0')
            {
                break;
            }
        }
    }

    if (n == 0)
    {
        if (size != 0)
        {
            *dst = '\0';
        }

        while (*s++);
    }

    return (s - src - 1);
}

char* my_strdup(const char* s)
{
    size_t n = strlen(s) + 1;
    char* src = malloc(n);
    char* t = src;

    //strcpy(src, s);
    while (*src++ = *s++);

    return t;
}

int main(void)
{
    char s[12];
    char a[5];
    char b[20];
    char* s1 = "01234567890";
    char* s2 = "abcdefghijklmnopqrstuvwxyz";

    int len = my_strlcpy(s, s1, sizeof(s));
    int len1 = my_strlcpy(a, s1, sizeof(a));
    int len2 = my_strlcpy(b, s1, sizeof(b));

    printf("my_strlcpy:\n");

    printf("copy-text:%s   len:%d   str-in-buf:%s   buf-size:%ld   len-str-in-buf:%ld\n", s1, len, s, sizeof(s), strlen(s));
    printf("copy-text:%s   len:%d   str-in-buf:%s   buf-size:%ld   len-str-in-buf:%ld\n", s1, len, a, sizeof(a), strlen(a));
    printf("copy-text:%s   len:%d   str-in-buf:%s   buf-size:%ld   len-str-in-buf:%ld\n", s1, len, b, sizeof(b), strlen(b));

    printf("\n\n");

    strncpy(s, s1, sizeof(s));/*手元にmacOS デバイスがないです。 strlcpy は使用できない。代わりに strncpy を使用します。*/
    strncpy(a, s1, sizeof(a)-1);
    strncpy(b, s1, sizeof(b));

    printf("strncpy:\n");

    printf("copy-text:%s   len:%d   str-in-buf:%s   buf-size:%ld   len-str-in-buf:%ld\n", s1, len, s, sizeof(s), strlen(s));
    printf("copy-text:%s   len:%d   str-in-buf:%s   buf-size:%ld   len-str-in-buf:%ld\n", s1, len, a, sizeof(a), strlen(a));
    printf("copy-text:%s   len:%d   str-in-buf:%s   buf-size:%ld   len-str-in-buf:%ld\n", s1, len, b, sizeof(b), strlen(b));

    printf("\n\n");

    char* str = my_strdup(s2);
    char* str1 = strdup(s2);

    printf("my_strdup:\n");
    printf("copy-text: %s   str-in-buf: %s\n", s2, str);
    printf("\n\n");

    printf("strdup:\n");
    printf("copy-text: %s   str-in-buf: %s\n", s2, str1);
    printf("\n\n");

    free(str);
    free(str1);

    //system("PAUSE");
    return 0;
}
