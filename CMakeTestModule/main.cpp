#include "MathFunctions.h"
#include "Logger.h"
#include "StringFunctions.h"

int main()
{
    int mathResultAdd = MathFunctions::add(5, 3);
    Logger::log("The result of 5 + 3 is " + std::to_string(mathResultAdd));

    int mathResultSubtract = MathFunctions::subtract(9, 4);
    Logger::log("The result of 9 - 4 is " + std::to_string(mathResultSubtract));

    std::string original = "Hello, LC-3!";
    std::string upper = StringFunctions::toUpperCase(original);
    Logger::log("Uppercase: " + upper);

    std::string lower = StringFunctions::toLowerCase(original);
    Logger::log("Lowercase: " + lower);

    return 0;
}