//Name: Thomas Gilman
//Class: ETEC 2110
//Section: 01
//Assignment: 1.4
int printf(const char *format,...);

#define begin { printf("\n");
#define end return 0; }

const char * write(x) //writes what you put in
{
    printf(x);
}
const char * writeln(x) //writes what you put in followed by a newline char
    printf(x);
    printf("\n");
}

main()
begin
    write("First");
    write("Line");
    writeln(" ");
    writeln("My name is: Thomas Gilman");
    writeln("A quote I like is by Benjamin Franklin \n'Without continual growth and progress, such words as improvement, achievement, and success have no meaning.'");
end
