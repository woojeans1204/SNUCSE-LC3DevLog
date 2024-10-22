#include "MathFunctions.h"
#include "Logger.h"

int main()
{
    int result = MathFunctions::add(5, 3);
    Logger::log("The result of 5 + 3 is " + std::to_string(result));

    result = MathFunctions::subtract(9, 4);
    Logger::log("The result of 9 - 4 is " + std::to_string(result));

    return 0;
}