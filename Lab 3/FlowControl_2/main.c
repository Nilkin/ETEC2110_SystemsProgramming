//Name: Thomas Gilman
//Class: ETEC 2110
//Section: 01
//Assignment: 3.2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char StringInput[255], encryptionKey[64];

void crypt(char* message, char* keyPntr , int message_length)
{   //strlen gives number of chars but index starts at 0
    int keyLen = strlen(encryptionKey)-1;

    //xor message char with key char
    for(int index = 0; index < message_length; index++)
    {
        if(*keyPntr == encryptionKey[keyLen])
        {   //Pointer at end of list
            message[index] ^= *keyPntr;
            keyPntr = encryptionKey;
        }
        else
            message[index] ^= *keyPntr;

        keyPntr++;
    }
    printf("\nHere is the encrypted Message: %s\n\n",StringInput);
}

int main( )
{

    printf("input your message please:\n\n");
    fgets(StringInput,sizeof(StringInput),stdin);

    printf("\nNow input your encryption key:\n\n");
    fgets(encryptionKey,sizeof(encryptionKey),stdin);

    int StringLen = strlen(StringInput);

    //encrypt the message
    crypt(&StringInput,&encryptionKey,StringLen);
    //decrypt the message
    crypt(&StringInput,&encryptionKey,StringLen);

    return 0;
}
