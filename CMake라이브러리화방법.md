알겠습니다! CMake를 사용하여 **라이브러리(.c/.h 또는 .cpp/.h 형태)**를 생성하고, 이를 다른 모듈이나 실행 파일에서 사용할 수 있도록 설정하는 방법을 자세히 설명드리겠습니다. 이 과정에서는 **CMakeLists.txt** 파일의 작성, 프로젝트 구조 설정, 빌드 과정, 그리고 CMake의 핵심 개념들(타겟, 링크, 접근 지정자 등)을 포함하여 설명하겠습니다.

## 목차

1. [프로젝트 구조](#1-프로젝트-구조)
2. [CMakeLists.txt 파일 구성](#2-cmakelists.txt-파일-구성)
   - [최상위 `CMakeLists.txt`](#최상위-cmakelists.txt)
   - [각 모듈의 `CMakeLists.txt`](#각-모듈의-cmakelists.txt)
3. [라이브러리 생성 이해하기](#3-라이브러리-생성-이해하기)
   - [정적 라이브러리(Static Library)](#정적-라이브러리static-library)
   - [동적 라이브러리(Dynamic Library)](#동적-라이브러리dynamic-library)
4. [헤더 파일 포함 경로 설정](#4-헤더-파일-포함-경로-설정)
5. [타겟과 링크](#5-타겟과-링크)
   - [타겟(Target) 이해하기](#타겟target-이해하기)
   - [링크(Link) 이해하기](#링크link-이해하기)
6. [빌드 과정](#6-빌드-과정)
7. [실제 예제](#7-실제-예제)
8. [요약](#8-요약)
9. [추가 참고 자료](#9-추가-참고-자료)

---

## 1. 프로젝트 구조

먼저, 프로젝트의 디렉토리 구조를 정의하겠습니다. 이 예제에서는 **MathModule**, **UtilityModule**, **StringModule**이라는 세 가지 라이브러리와 이를 테스트하는 **Tests** 디렉토리를 포함합니다.

```
MyModularProject/
├── CMakeLists.txt
├── main.cpp
├── MathModule/
│   ├── CMakeLists.txt
│   ├── MathFunctions.h
│   └── MathFunctions.cpp
├── UtilityModule/
│   ├── CMakeLists.txt
│   ├── Logger.h
│   └── Logger.cpp
├── StringModule/
│   ├── CMakeLists.txt
│   ├── StringFunctions.h
│   └── StringFunctions.cpp
└── Tests/
    ├── CMakeLists.txt
    ├── MathModuleTests.cpp
    ├── UtilityModuleTests.cpp
    └── StringModuleTests.cpp
```

각 모듈과 테스트 디렉토리에는 별도의 `CMakeLists.txt` 파일이 존재하며, 최상위 디렉토리의 `CMakeLists.txt`에서 이를 포함합니다.

---

## 2. CMakeLists.txt 파일 구성

### 최상위 `CMakeLists.txt`

최상위 `CMakeLists.txt` 파일은 전체 프로젝트의 빌드 설정을 정의합니다. 이 파일에서는 프로젝트 이름, C++ 표준, 서브디렉토리 포함, 실행 파일 생성 및 라이브러리 링크 등을 설정합니다.

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyModularProject VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 서브 디렉토리 포함
add_subdirectory(MathModule)
add_subdirectory(UtilityModule)
add_subdirectory(StringModule)
add_subdirectory(Tests)

# 메인 프로그램을 위한 실행 파일 생성
add_executable(MainProgram main.cpp)

# 메인 프로그램이 MathModule, UtilityModule, StringModule을 사용할 수 있도록 링크
target_link_libraries(MainProgram PRIVATE MathModule UtilityModule StringModule)
```

#### 설명:

- `cmake_minimum_required(VERSION 3.10)`: 사용하려는 최소 CMake 버전을 지정합니다.
- `project(MyModularProject VERSION 1.0)`: 프로젝트의 이름과 버전을 정의합니다.
- `set(CMAKE_CXX_STANDARD 11)`: C++ 표준을 C++11로 설정합니다.
- `add_subdirectory(...)`: 서브디렉토리의 `CMakeLists.txt`를 포함하여 각 모듈을 빌드에 포함시킵니다.
- `add_executable(MainProgram main.cpp)`: `main.cpp`를 사용하여 `MainProgram` 실행 파일을 생성합니다.
- `target_link_libraries(...)`: `MainProgram`이 각 모듈을 링크하여 사용할 수 있도록 설정합니다.

### 각 모듈의 `CMakeLists.txt`

각 모듈 디렉토리(`MathModule`, `UtilityModule`, `StringModule`)에는 해당 모듈의 라이브러리를 생성하기 위한 `CMakeLists.txt` 파일이 있습니다. 여기서는 `MathModule`을 예로 들어 설명하겠습니다. 다른 모듈들도 유사하게 구성됩니다.

#### `MathModule/CMakeLists.txt`

```cmake
# MathModule 라이브러리 생성
add_library(MathModule STATIC MathFunctions.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

#### 설명:

- `add_library(MathModule STATIC MathFunctions.cpp)`: `MathModule`이라는 이름의 정적 라이브러리를 생성하며, `MathFunctions.cpp` 파일을 포함합니다.
  - **STATIC**: 정적 라이브러리를 의미하며, 컴파일 시점에 실행 파일에 포함됩니다. 생성된 라이브러리는 `.lib` (Windows) 또는 `.a` (Unix) 파일로 나타납니다.
  - **SHARED**: 동적 라이브러리를 생성할 때 사용하며, 생성된 라이브러리는 `.dll` (Windows), `.so` (Unix), `.dylib` (macOS) 파일로 나타납니다.
- `target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})`: `MathModule` 라이브러리가 헤더 파일을 찾을 수 있는 경로를 지정합니다.
  - **PUBLIC**: 이 포함 경로가 `MathModule`을 링크하는 모든 타겟에 전파됩니다.

#### 다른 모듈의 예

`UtilityModule/CMakeLists.txt`:

```cmake
# UtilityModule 라이브러리 생성
add_library(UtilityModule STATIC Logger.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(UtilityModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 스레드 라이브러리 링크 (Logger에 mutex 사용)
find_package(Threads REQUIRED)
target_link_libraries(UtilityModule PRIVATE Threads::Threads)
```

`StringModule/CMakeLists.txt`:

```cmake
# StringModule 라이브러리 생성
add_library(StringModule STATIC StringFunctions.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(StringModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

---

## 3. 라이브러리 생성 이해하기

### 정적 라이브러리 (Static Library)

- **정의**: 정적 라이브러리는 컴파일 시점에 실행 파일에 포함되는 라이브러리입니다. 한 번 링크되면 별도의 라이브러리 파일이 필요 없습니다.
- **확장자**:
  - Windows: `.lib`
  - Unix/Linux: `.a`

### 동적 라이브러리 (Dynamic Library)

- **정의**: 동적 라이브러리는 실행 시점에 로드되는 라이브러리입니다. 여러 실행 파일에서 공유할 수 있으며, 실행 파일과는 별도로 배포해야 합니다.
- **확장자**:
  - Windows: `.dll`
  - Unix/Linux: `.so`
  - macOS: `.dylib`

### 라이브러리 생성 명령어

- **정적 라이브러리 생성**:
  ```cmake
  add_library(LibraryName STATIC source1.cpp source2.cpp)
  ```
- **동적 라이브러리 생성**:
  ```cmake
  add_library(LibraryName SHARED source1.cpp source2.cpp)
  ```

---

## 4. 헤더 파일 포함 경로 설정

`target_include_directories` 명령어는 특정 타겟이 헤더 파일을 찾을 수 있는 디렉토리를 지정합니다. 이 설정은 컴파일러에게 추가적인 헤더 파일 경로를 알려주는 역할을 합니다.

```cmake
target_include_directories(TargetName [INTERFACE|PUBLIC|PRIVATE] path1 path2 ...)
```

- **PUBLIC**: 현재 타겟과 이를 링크하는 모든 타겟에 포함 경로를 전파합니다.
- **PRIVATE**: 현재 타겟에만 포함 경로를 설정하며, 이를 링크하는 타겟에는 전파하지 않습니다.
- **INTERFACE**: 현재 타겟에는 포함 경로를 설정하지 않지만, 이를 링크하는 타겟에만 전파합니다.

### 예시

```cmake
target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

- **MathModule**이 사용하는 헤더 파일들이 현재 소스 디렉토리에 있기 때문에, `PUBLIC`으로 설정하여 이를 사용하는 모든 타겟이 헤더 파일을 찾을 수 있도록 합니다.

---

## 5. 타겟과 링크

### 타겟(Target) 이해하기

CMake에서 **타겟**은 빌드할 수 있는 단위로, 주로 **실행 파일** 또는 **라이브러리**를 의미합니다. 타겟은 소스 파일, 포함 디렉토리, 링크 라이브러리 등의 속성을 포함합니다.

- **실행 파일 타겟**:
  ```cmake
  add_executable(MyExecutable main.cpp)
  ```
- **라이브러리 타겟**:
  ```cmake
  add_library(MyLibrary STATIC lib.cpp)
  ```

### 링크(Link) 이해하기

링크는 타겟이 다른 라이브러리나 타겟과의 종속성을 정의하는 것을 의미합니다. 링크를 통해 한 타겟이 다른 타겟의 기능을 사용할 수 있게 됩니다.

```cmake
target_link_libraries(MyExecutable PRIVATE MyLibrary)
```

#### 접근 지정자의 의미

- **PRIVATE**: 링크된 라이브러리가 현재 타겟에만 영향을 미칩니다.
- **PUBLIC**: 링크된 라이브러리가 현재 타겟과 이를 링크하는 모든 타겟에 영향을 미칩니다.
- **INTERFACE**: 링크된 라이브러리가 현재 타겟에는 영향을 미치지 않지만, 이를 링크하는 타겟에만 영향을 미칩니다.

### 예시

```cmake
# 메인 프로그램이 MathModule, UtilityModule, StringModule을 PRIVATE으로 링크
target_link_libraries(MainProgram PRIVATE MathModule UtilityModule StringModule)
```

- **PRIVATE**: `MainProgram`이 각 모듈을 사용하지만, `MainProgram`을 링크하는 다른 타겟이 있을 경우 각 모듈의 의존성이 전파되지 않습니다.

---

## 6. 빌드 과정

빌드 과정은 소스 코드를 컴파일하여 실행 파일이나 라이브러리를 생성하는 일련의 과정입니다. CMake를 사용하면 이 과정을 자동화하고 관리할 수 있습니다.

### 빌드 단계

1. **설정 단계 (Configuration Stage)**:

   - `cmake` 명령어를 실행하여 프로젝트의 빌드 설정을 구성합니다.
   - `CMakeLists.txt` 파일을 읽고, 프로젝트의 타겟, 라이브러리, 의존성을 파악합니다.
   - 플랫폼에 맞는 빌드 시스템 파일(Makefile, Visual Studio 솔루션 파일 등)을 생성합니다.

2. **빌드 단계 (Build Stage)**:
   - 생성된 빌드 시스템 파일을 사용하여 실제로 소스 코드를 컴파일하고 링크합니다.
   - 예를 들어, `make` 명령어를 사용하여 Makefile 기반 프로젝트를 빌드하거나, `cmake --build .` 명령어를 사용하여 자동으로 적절한 빌드 명령어를 실행합니다.

### 빌드 명령어

```bash
# 빌드 디렉토리 생성 및 이동
mkdir build
cd build

# CMake 설정 단계
cmake ..

# 빌드 실행
cmake --build .
```

- **`mkdir build && cd build`**: 빌드 출력을 위한 별도의 디렉토리를 생성하고 이동합니다.
- **`cmake ..`**: 상위 디렉토리의 `CMakeLists.txt` 파일을 읽어 빌드 설정을 구성합니다.
- **`cmake --build .`**: 설정된 빌드 시스템을 사용하여 프로젝트를 실제로 빌드합니다.

---

## 7. 실제 예제

이제 실제 예제를 통해 CMake를 사용하여 라이브러리를 생성하고, 이를 다른 타겟(실행 파일)에서 사용하는 방법을 살펴보겠습니다.

### 프로젝트 구조

```
MyModularProject/
├── CMakeLists.txt
├── main.cpp
├── MathModule/
│   ├── CMakeLists.txt
│   ├── MathFunctions.h
│   └── MathFunctions.cpp
├── UtilityModule/
│   ├── CMakeLists.txt
│   ├── Logger.h
│   └── Logger.cpp
├── StringModule/
│   ├── CMakeLists.txt
│   ├── StringFunctions.h
│   └── StringFunctions.cpp
└── Tests/
    ├── CMakeLists.txt
    ├── MathModuleTests.cpp
    ├── UtilityModuleTests.cpp
    └── StringModuleTests.cpp
```

### 각 파일의 내용

#### 1. 최상위 `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyModularProject VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 서브 디렉토리 포함
add_subdirectory(MathModule)
add_subdirectory(UtilityModule)
add_subdirectory(StringModule)
add_subdirectory(Tests)

# 메인 프로그램을 위한 실행 파일 생성
add_executable(MainProgram main.cpp)

# 메인 프로그램이 MathModule, UtilityModule, StringModule을 PRIVATE으로 링크
target_link_libraries(MainProgram PRIVATE MathModule UtilityModule StringModule)
```

#### 2. `MathModule/CMakeLists.txt`

```cmake
# MathModule 라이브러리 생성 (정적 라이브러리)
add_library(MathModule STATIC MathFunctions.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

#### 3. `UtilityModule/CMakeLists.txt`

```cmake
# UtilityModule 라이브러리 생성 (정적 라이브러리)
add_library(UtilityModule STATIC Logger.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(UtilityModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 스레드 라이브러리 링크 (Logger에 mutex 사용)
find_package(Threads REQUIRED)
target_link_libraries(UtilityModule PRIVATE Threads::Threads)
```

#### 4. `StringModule/CMakeLists.txt`

```cmake
# StringModule 라이브러리 생성 (정적 라이브러리)
add_library(StringModule STATIC StringFunctions.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(StringModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

#### 5. `Tests/CMakeLists.txt`

```cmake
# 테스트 실행 파일 생성
add_executable(MathModuleTests MathModuleTests.cpp)
add_executable(UtilityModuleTests UtilityModuleTests.cpp)
add_executable(StringModuleTests StringModuleTests.cpp)

# 각 테스트 실행 파일이 해당 모듈을 PRIVATE으로 링크
target_link_libraries(MathModuleTests PRIVATE MathModule)
target_link_libraries(UtilityModuleTests PRIVATE UtilityModule)
target_link_libraries(StringModuleTests PRIVATE StringModule)

# 테스트 실행 파일이 독립적으로 실행될 수 있도록 각 모듈의 헤더 파일 경로 포함
target_include_directories(MathModuleTests PRIVATE ../MathModule)
target_include_directories(UtilityModuleTests PRIVATE ../UtilityModule)
target_include_directories(StringModuleTests PRIVATE ../StringModule)
```

#### 6. `MathModule/MathFunctions.h`

```cpp
#pragma once

class MathFunctions {
public:
    static int add(int a, int b);
    static int subtract(int a, int b);
};
```

#### 7. `MathModule/MathFunctions.cpp`

```cpp
#include "MathFunctions.h"

int MathFunctions::add(int a, int b) {
    return a + b;
}

int MathFunctions::subtract(int a, int b) {
    return a - b;
}
```

#### 8. `UtilityModule/Logger.h`

```cpp
#pragma once
#include <string>

class Logger {
public:
    static void log(const std::string& message);
    static void setLogFile(const std::string& filePath);
};
```

#### 9. `UtilityModule/Logger.cpp`

```cpp
#include "Logger.h"
#include <fstream>
#include <mutex>

static std::string logFilePath = "app.log"; // 기본 로그 파일
static std::mutex logMutex;

void Logger::setLogFile(const std::string& filePath) {
    logFilePath = filePath;
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::ofstream ofs(logFilePath, std::ofstream::out | std::ofstream::app);
    if (ofs.is_open()) {
        ofs << "LOG: " << message << std::endl;
    }
}
```

#### 10. `StringModule/StringFunctions.h`

```cpp
#pragma once
#include <string>

class StringFunctions {
public:
    static std::string toUpperCase(const std::string& input);
    static std::string toLowerCase(const std::string& input);
};
```

#### 11. `StringModule/StringFunctions.cpp`

```cpp
#include "StringFunctions.h"
#include <algorithm>

std::string StringFunctions::toUpperCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string StringFunctions::toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
```

#### 12. `main.cpp`

```cpp
#include "MathFunctions.h"
#include "Logger.h"
#include "StringFunctions.h"

int main()
{
    // MathModule 사용
    int mathResultAdd = MathFunctions::add(5, 3);
    Logger::log("The result of 5 + 3 is " + std::to_string(mathResultAdd));

    int mathResultSubtract = MathFunctions::subtract(9, 4);
    Logger::log("The result of 9 - 4 is " + std::to_string(mathResultSubtract));

    // StringModule 사용
    std::string original = "Hello, LC-3!";
    std::string upper = StringFunctions::toUpperCase(original);
    Logger::log("Uppercase: " + upper);

    std::string lower = StringFunctions::toLowerCase(original);
    Logger::log("Lowercase: " + lower);

    return 0;
}
```

#### 13. 테스트 코드 예제

##### `Tests/MathModuleTests.cpp`

```cpp
#include "../MathModule/MathFunctions.h"
#include <cassert>
#include <iostream>

void test_add() {
    assert(MathFunctions::add(2, 3) == 5);
    assert(MathFunctions::add(-1, 1) == 0);
    assert(MathFunctions::add(-2, -3) == -5);
    std::cout << "test_add passed." << std::endl;
}

void test_subtract() {
    assert(MathFunctions::subtract(5, 3) == 2);
    assert(MathFunctions::subtract(0, 0) == 0);
    assert(MathFunctions::subtract(-5, -3) == -2);
    std::cout << "test_subtract passed." << std::endl;
}

int main() {
    std::cout << "Running MathModule Tests..." << std::endl;
    test_add();
    test_subtract();
    std::cout << "All MathModule Tests Passed!" << std::endl;
    return 0;
}
```

##### `Tests/UtilityModuleTests.cpp`

```cpp
#include "../UtilityModule/Logger.h"
#include <cassert>
#include <fstream>
#include <iostream>

void test_log() {
    std::cout << "Testing Logger::log..." << std::endl;

    // 테스트용 로그 파일 경로 설정
    const std::string testLogFile = "test_log.txt";

    // Logger에 테스트 로그 파일 설정
    Logger::setLogFile(testLogFile);

    // 테스트 로그 메시지 기록
    Logger::log("This is a test log message.");

    // 로그 파일에서 메시지 읽기
    std::ifstream ifs(testLogFile);
    std::string loggedMessage;
    std::getline(ifs, loggedMessage);
    ifs.close();

    // 예상되는 로그 메시지 확인
    assert(loggedMessage == "LOG: This is a test log message.");
    std::cout << "test_log passed." << std::endl;
}

int main() {
    std::cout << "Running UtilityModule Tests..." << std::endl;
    test_log();
    std::cout << "All UtilityModule Tests Passed!" << std::endl;
    return 0;
}
```

##### `Tests/StringModuleTests.cpp`

```cpp
#include "../StringModule/StringFunctions.h"
#include <cassert>
#include <iostream>

void test_toUpperCase() {
    std::string input = "Hello, World!";
    std::string expected = "HELLO, WORLD!";
    assert(StringFunctions::toUpperCase(input) == expected);

    input = "c++ programming";
    expected = "C++ PROGRAMMING";
    assert(StringFunctions::toUpperCase(input) == expected);

    input = "123abcDEF";
    expected = "123ABCDEF";
    assert(StringFunctions::toUpperCase(input) == expected);

    std::cout << "test_toUpperCase passed." << std::endl;
}

void test_toLowerCase() {
    std::string input = "Hello, World!";
    std::string expected = "hello, world!";
    assert(StringFunctions::toLowerCase(input) == expected);

    input = "C++ PROGRAMMING";
    expected = "c++ programming";
    assert(StringFunctions::toLowerCase(input) == expected);

    input = "123ABCdef";
    expected = "123abcdef";
    assert(StringFunctions::toLowerCase(input) == expected);

    std::cout << "test_toLowerCase passed." << std::endl;
}

int main() {
    std::cout << "Running StringModule Tests..." << std::endl;
    test_toUpperCase();
    test_toLowerCase();
    std::cout << "All StringModule Tests Passed!" << std::endl;
    return 0;
}
```

---

## 8. 요약

- **프로젝트 구조**: 각 모듈(라이브러리)과 테스트 디렉토리가 별도의 `CMakeLists.txt` 파일을 가지며, 최상위 `CMakeLists.txt`에서 이를 포함합니다.
- **라이브러리 생성**: `add_library` 명령어를 사용하여 정적 또는 동적 라이브러리를 생성합니다.
- **헤더 파일 포함 경로**: `target_include_directories` 명령어를 사용하여 헤더 파일 경로를 설정하고, `PUBLIC`, `PRIVATE`, `INTERFACE` 접근 지정자를 통해 의존성을 관리합니다.
- **타겟 링크**: `target_link_libraries` 명령어를 사용하여 타겟 간의 링크(의존성)를 설정합니다.
- **빌드 과정**: CMake를 사용하여 설정 단계와 빌드 단계를 거쳐 소스 코드를 컴파일하고 링크합니다.
- **테스트**: 각 모듈별로 테스트 실행 파일을 생성하고, 이를 통해 모듈의 기능을 검증합니다.

---

## 9. 추가 참고 자료

- **CMake 공식 문서**:
  - [CMake Documentation](https://cmake.org/documentation/)
- **CMake Tutorials**:
  - [Official CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
  - [Modern CMake by Example](https://cliutils.gitlab.io/modern-cmake/)
- **CMake 접근 지정자 이해하기**:
  - [CMake Target Properties](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties)

---

## 추가 설명: 빌드 결과물

빌드 과정 후, 생성되는 결과물은 다음과 같습니다:

- **라이브러리**:
  - **MathModule**: `libMathModule.a` (Unix/Linux), `MathModule.lib` (Windows)
  - **UtilityModule**: `libUtilityModule.a` (Unix/Linux), `UtilityModule.lib` (Windows)
  - **StringModule**: `libStringModule.a` (Unix/Linux), `StringModule.lib` (Windows)
- **실행 파일**:
  - **MainProgram**: `MainProgram` (Unix/Linux), `MainProgram.exe` (Windows)
- **테스트 실행 파일**:
  - **MathModuleTests**: `MathModuleTests` (Unix/Linux), `MathModuleTests.exe` (Windows)
  - **UtilityModuleTests**: `UtilityModuleTests` (Unix/Linux), `UtilityModuleTests.exe` (Windows)
  - **StringModuleTests**: `StringModuleTests` (Unix/Linux), `StringModuleTests.exe` (Windows)
- **로그 파일**:
  - **UtilityModuleTests**가 실행되면 `test_log.txt` 파일이 생성되어 로그 메시지가 기록됩니다.

이러한 결과물을 통해 각 모듈이 독립적으로 빌드되고, 테스트를 통해 기능이 검증되었음을 확인할 수 있습니다.

---

## 문제 해결을 위한 팁

- **빌드 시 오류 발생 시**:
  - **헤더 파일 경로 확인**: `target_include_directories` 설정이 올바른지 확인하세요.
  - **라이브러리 링크 확인**: `target_link_libraries`에서 링크하려는 라이브러리 이름이 정확한지 확인하세요.
  - **CMake 버전 확인**: `cmake_minimum_required`에서 설정한 CMake 버전이 시스템에 설치된 버전과 호환되는지 확인하세요.
- **동적 라이브러리 사용 시**:
  - **윈도우즈**: `.dll` 파일을 실행 파일과 동일한 디렉토리에 두거나, 시스템 PATH에 포함시켜야 합니다.
  - **Unix/Linux**: `.so` 파일을 적절한 라이브러리 디렉토리에 두거나, `LD_LIBRARY_PATH` 환경 변수를 설정해야 합니다.

---

이 예제를 통해 CMake를 사용하여 라이브러리를 생성하고, 이를 다른 타겟에서 사용하는 방법을 익히셨기를 바랍니다. 모듈화된 프로젝트는 코드의 재사용성과 유지보수성을 높이는 데 큰 도움이 됩니다. 추가적인 질문이나 도움이 필요하시면 언제든지 문의해 주세요!
