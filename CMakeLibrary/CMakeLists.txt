# 최상위 CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(MyCMakeLibraryProject VERSION 1.0 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 서브 디렉토리 포함
add_subdirectory(src/MathModule)
add_subdirectory(src/UtilityModule)
add_subdirectory(tests)

# 모든 모듈의 소스 파일을 하나의 라이브러리로 통합
add_library(MyLibrary STATIC
    src/MathModule/MathFunctions.cpp
    src/UtilityModule/Logger.cpp
)

# 헤더 파일 포함 경로 설정
target_include_directories(MyLibrary PUBLIC
    src/MathModule
    src/UtilityModule
)