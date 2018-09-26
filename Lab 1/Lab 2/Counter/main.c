//Name: Thomas Gilman
//Class: ETEC 2110
//Section: 01
//Assignment: 2.1

int printf(const char *format,...); //save time by just making this function rather than including stdio.h

unsigned long Average = 0;
unsigned long Range = 100000000;
unsigned long long Sum = 0; //expecting a really big number

void findSum()
{
    for(unsigned long i=0;i<Range;i++)
        Sum+=i;
}
void getAverage()
{
    Average = Sum/Range;
}

int main()
{
    findSum();
    getAverage();
    printf("The range is: %d\n",Range);
    printf("The Sum is: %llu\n",Sum); //llu = long long unsigned int
    printf("The Average is: %d\n", Average);
    return 0;
}
