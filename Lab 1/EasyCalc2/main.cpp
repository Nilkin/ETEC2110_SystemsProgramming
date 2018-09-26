#include <iostream>
#include <string>
#include <array>

using namespace std;


int NumList[];
std::string OpList[];

public int NumberAsker(int timesToAsk)
{

}
//std::string delimiter = ("+-*/");
std::string firstNum, secondNum, Op;
int numOne, numTwo, TimesToAsk;
//take a string and parse it to find the different numbers to perform an operation on
int main()
{
    while(Op!="esc")
    {
        std::cout << "Operators: +,-,*,/  \nhow many numbers do you want?:" << std::endl;
        std::getline(std::cin,TimesToAsk);

        //set array lengths
        int NumList[TimesToAsk];
        std::string OpList[TimesToAsk-1];

        int*OpIter;
        for(int i;i<=TimesToAsk;i++)
        {
            int numIn;
            std::string OpChar;
            std::cout<<"Whats the "<<i<<" number"<<endl;
            std::getline(std::cin,numIn);
            NumList[i]=numIn;
            std::cout<<"Whats the Operation to perform?"<<endl;
            std::getline(std::cin, OpChar);
            if(i!=timesToAsk)
                OpList[i]=OpChar;
        }


    std::cout<<OpList<<endl;
        //Outputs the equation between two numbers based on the operator specified
        std::cout << "Here is the equation you put in: \n"<<numOne<<Op<<numTwo<<std::endl;
        if(Op=="+"){
            cout<<numOne+numTwo<<endl;
        }
        else if(Op=="-"){
            cout<<numOne-numTwo<<endl;
        }
        else if(Op=="*"){
            cout<<numOne*numTwo<<endl;
        }
        else if(Op=="/"){
            cout<<numOne/numTwo<<endl;
        }
        else
            cout<<"Unknown Operator entered"<<endl;
    }
    return 0;
}
