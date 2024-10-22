#include "../StringModule/StringFunctions.h"
#include <cassert>
#include <iostream>

void test_toUpperCase()
{
    std::string input = "Hello, World!";
    std::string expected = "HELLO, WORLD!";
    assert(StringFunctions::toUpperCase(input) == expected);
    std::cout << "test_toUpperCase passed." << std::endl;
}

void test_toLowerCase()
{
    std::string input = "Hello, World!";
    std::string expected = "hello, world!";
    assert(StringFunctions::toLowerCase(input) == expected);
    std::cout << "test_toLowerCase passed." << std::endl;
}

int main()
{
    test_toUpperCase();
    test_toLowerCase();
    return 0;
}