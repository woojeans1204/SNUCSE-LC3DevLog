// tests/TestMain.cpp

#include "MathFunctions.h"
#include "Logger.h"
#include <cassert>
#include <iostream>

int main()
{
    // MathModule 테스트
    int sum = MathFunctions::add(5, 3);
    assert(sum == 8);
    Logger::log("MathFunctions::add(5, 3) passed.");

    int difference = MathFunctions::subtract(10, 4);
    assert(difference == 6);
    Logger::log("MathFunctions::subtract(10, 4) passed.");

    // 추가 테스트 예시
    int sum_neg = MathFunctions::add(-2, -3);
    assert(sum_neg == -5);
    Logger::log("MathFunctions::add(-2, -3) passed.");

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}