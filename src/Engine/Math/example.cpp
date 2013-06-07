#include <iostream>
#include "MathFormula.h"

int main_mathtester( int argc, const char* argv[] )
{
    char str[ 500 ];
    float x, result;

    // get math expression from input
    std::cout << "f(x) := ";
    std::cin.getline( str, 500 );
    std::cout << std::endl;

    try
    {
        // create MathFormula object with given expression
        MathFormula fun( str );

        while ( true )
        {
            // get value of parameter
            std::cout << "x = ";
            std::cin >> x;

            // calculate result
            result = fun( x );

            // print result
            std::cout << "f(x) = " << result << std::endl << std::endl;
        }
    }
    catch ( std::exception& e )
    {
        std::cout << "Error occured: " << e.what() << std::endl;
    }

    return 0;
}
