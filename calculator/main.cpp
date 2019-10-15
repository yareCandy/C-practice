#include <iostream>
#include "calculator.hpp"

int main()
{
    Calculator calc(std::cin);
    try{
        calc.output(std::cout);
    }
    catch(Calculator::error e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}