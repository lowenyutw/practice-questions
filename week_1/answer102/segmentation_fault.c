#include <stdio.h>

int *segmentation_fault_1(void)
{
    int *i = 5;

    printf("%d", *i);//Segmentation fault
    //printf("%d", i)
}

int *segmentation_fault_2(void)
{
    int *i = 5;

    return *i;//Segmentation fault 
    //return i
}

int *segmentation_fault_3(void)
{
    char *i;

    *i = "123456";//Segmentation fault 
    //i = "123456";
}


int *segmentation_fault_4(void)
{
    char *i = "123456";

    i[1] = 'c';//Segmentation fault 
}

char segmentation_fault_5(void)
{
    char c[5];

    printf("%c\n", c[1800000]);//Segmentation fault 
}

int main(void)
{
    segmentation_fault_5();

    return 0;
}
