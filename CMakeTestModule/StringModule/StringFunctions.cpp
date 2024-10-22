#include "StringFunctions.h"
#include <algorithm>
std::string StringFunctions::toUpperCase(const std::string &input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string StringFunctions::toLowerCase(const std::string &input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
