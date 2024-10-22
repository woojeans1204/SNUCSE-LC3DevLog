#include "../MathModule/MathFunctions.h"
#include <cassert>
#include <iostream>

void test_add()
{
    assert(MathFunctions::add(2, 3) == 5);
    assert(MathFunctions::add(-1, 1) == 0);
    std::cout << "test_add passed." << std::endl;
}
void test_subtract()
{
    assert(MathFunctions::subtract(5, 3) == 2);
    assert(MathFunctions::subtract(0, 0) == 0);
    std::cout << "test_subtract passed." << std::endl;
}

int main()
{
    test_add();
    test_subtract();
    return 0;
}