//Name: Thomas Gilman
//Class: ETEC 2110
//Section: 01
//Assignment: 3.1

#include <stdio.h>
#include <stdlib.h>

void printCharStats(char *text)
{
    int vowels = 0, consonants = 0, spaces = 0, digits = 0;
    int upperCaseL = 0, lowerCaseL = 0, totalChars = 0;
    while(*text++) //parse through the string till the null terminator
    {
        if(*text > 64 && *text < 91) //upperCase A-Z char
        {
            if(*text == 'A' || *text == 'E' || *text == 'I' || *text == 'O' || *text == 'U')
                vowels++;
            else
                consonants++;

            upperCaseL++;
        }
        else if(*text > 96 && *text < 123) //lowerCase A-Z char
        {
            if(*text == 'a' || *text == 'e' || *text == 'i' || *text == 'o' || *text == 'u')
                vowels++;
            else
                consonants++;

            lowerCaseL++;
        }
        else if(*text == 32)
            spaces++;
        else if(*text > 47 && *text <58)
            digits++;

        totalChars++;
    }
    printf("Vowels: %d\nConsonants: %d\nSpaces: %d\nDigits: %d\nUpperCaseLetters: %d\nLowerCaseLetters: %d\nTotalChars: %d"
           ,vowels,consonants,spaces,digits,upperCaseL,lowerCaseL,totalChars);
}

char myString[255];

int main()
{
    printf("input your string:\n");
    fgets(myString,sizeof(myString),stdin);

    printCharStats(&myString);
    return 0;
}
