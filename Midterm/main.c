//Thomas Gilman
//ETEC 2110_51
//28th February 2018
//Fix to bug in code
#include <stdio.h>
#include <stdlib.h>

/*
    There was an issue where if size was 1, it would get stuck in the loop where (j < size - 2)
    this was causing it to try and print a huge number, so you needed a case for if size was 1
    to just print a * so it didnt break.
*/

void pyramid2(unsigned int size)
{
    int i, j;

    for(i = 1 ; i <= size ; i++)
    {
        if(i==size)
        {
            printf("* ");
            return;
        }
        for(j = 0 ; j < size-i; j++)
        {
            printf(" ");
        }
        if(i == 1)
            printf("* ");
        if(i > 1 && i < size)
        {
            for(j = 0 ; j < i; j++)
            {
                if(j == 0)
                    printf("/ ");
                else if(j == i-1)
                    printf("\\ ");
                else
                    printf("* ");
            }
        }
        if(i == size)
        {
            printf("* ");
            for(j = 0; j < size - 2 ; j++)
            {
                printf("--");
            }
            printf("* ");
        }
        printf("\n");
    }
}

int main()
{
    pyramid2(1);
    return 0;
}
