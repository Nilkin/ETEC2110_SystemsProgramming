//Name: Thomas Gilman
//Class: ETEC 2110
//Section: 01
//Assignment: 1.3
int printf(const char *format,...);

//my Defines for writename and quote
#define WRITENAME printf("My name is: Thomas Gilman\n\n")
#define WRITEQUOTE printf("A quote I like is by Benjamin Franklin \n'Without continual growth and progress, such words as improvement, achievement, and success have no meaning.'\n")
int main()
{
    WRITENAME; //writes my name
    WRITEQUOTE; //writes my quote
    return 0;
}
