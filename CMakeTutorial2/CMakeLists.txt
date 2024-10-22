cmake_minimum_required(VERSION 3.10)
project(MyModularProject VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 서브 디렉토리 포함
add_subdirectory(MathModule)
add_subdirectory(UtilityModule)

# 메인 프로그램을 위한 실행 파일 생성
add_executable(MainProgram main.cpp)

# 메인 프로그램이 MathModule과 UtilityModule을 사용할 수 있도록 링크
target_link_libraries(MainProgram PUBLIC MathModule UtilityModule)