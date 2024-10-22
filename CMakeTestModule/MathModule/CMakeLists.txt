# MathModule 라이브러리 생성
add_library(MathModule MathFunctions.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
