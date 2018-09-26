//Thomas Gilman
//ETEC 2110_51
//28th February 2018
//Midterm part 3
#include <stdio.h>
#include <stdlib.h>

void rotateStrinPrint(char* string, unsigned int num_positions)
{
    while(num_positions--)
    {
        char* firstChar = string;
        *string++;
        printf("%s\n",string);
    }
}

/*void pyramid(unsigned int size)
{
    int numStars = 1, spaces = ((size*2) - numStars);
    while(size--)
    {
        while(spaces--)
        {
            if(size/numStars == spaces)
                printf(" ");
            else
                printf("%c",'*');
        }
        printf("\n");
        numStars++;
        spaces = (size*2) - numStars;
    }
}
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
