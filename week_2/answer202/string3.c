#include <stdio.h>

#define LINE_LEN 5

int main(void)
{
    char line_buf[LINE_LEN];


    /*line_buffは[5]に設定されているため、
    読み取ることができるのは4文字のみであり、
    文字列終端を表す'\0'が最後に追加されます。*/
    while (fgets(line_buf, LINE_LEN, stdin) != NULL)
    {
        /*putsは文字列の後に改行を出力します。*/
        puts(line_buf);
    }

    return 0;
}
