#include "../UtilityModule/Logger.h"
#include <iostream>

void test_log()
{
    std::cout << "Testing Logger::log..." << std::endl;
    Logger::log("This is a test log message.");
    // 수동으로 로그 메시지를 확인해야 합니다.
}

int main()
{
    test_log();
    return 0;
}