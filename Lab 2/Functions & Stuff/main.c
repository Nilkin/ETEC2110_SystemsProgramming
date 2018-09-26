#include <stdio.h>
#include <stdlib.h>
//Name: Thomas Gilman
//Class: ETEC 2110
//Section: 01
//Assignment: 2

//shifts through the sizeof memory(unsigned char) through all 8 bits from msb->lsb and bitwise & it if toggled
void printBinary(unsigned char ch)
{
    for(short i=1;i<=(sizeof(ch)*8);i++)
    {
        printf("%i",(ch>>((sizeof(ch)*8)-i))&1);
    }
}
void printHex(unsigned char ch)
{
    printf("0x%0x",ch); //x is the specifier for (unsigned hexadecimal integer)
}

unsigned char Letter=65;

int main()
{
    printf("Num\tChar\tBin\t\tHex\n");
    while(Letter!=91)
    {
        printf("%d\t%c\t",Letter,Letter);
        printBinary(Letter);
        printf("\t");
        printHex(Letter);
        printf("\n"); //new line
        ++Letter;
    }
    return 0;
}
