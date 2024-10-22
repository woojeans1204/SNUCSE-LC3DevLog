# 테스트 실행 파일 생성
add_executable(MathModuleTests MathModuleTests.cpp)
add_executable(UtilityModuleTests UtilityModuleTests.cpp)
add_executable(StringModuleTests StringModuleTests.cpp)

# 테스트 실행 파일이 각 모듈을 링크하도록 설정
target_link_libraries(MathModuleTests PRIVATE MathModule)
target_link_libraries(UtilityModuleTests PRIVATE UtilityModule)
target_link_libraries(StringModuleTests PRIVATE StringModule)