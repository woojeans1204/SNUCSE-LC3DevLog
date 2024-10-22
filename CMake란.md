CMake는 현대 C++ 프로젝트에서 널리 사용되는 **빌드 시스템 생성기(Build System Generator)**입니다. 다양한 플랫폼과 컴파일러를 지원하며, 프로젝트의 빌드 과정을 자동화하고 관리하기 쉽게 만들어줍니다. 이 설명에서는 CMake의 근본적인 작동 방식, **타겟(Target)**, **링크(Link)**의 개념을 포함하여 CMake의 핵심 요소들을 자세히 설명드리겠습니다.

---

## 목차

1. [CMake란 무엇인가?](#1-cmake란-무엇인가)
2. [CMake의 기본 구성 요소](#2-cmake의-기본-구성-요소)
3. [타겟(Target) 이해하기](#3-타겟target-이해하기)
   - [타겟의 종류](#타겟의-종류)
   - [타겟 생성](#타겟-생성)
4. [링크(Link) 이해하기](#4-링크link-이해하기)
   - [링크의 종류](#링크의-종류)
   - [타겟 간 링크 설정](#타겟-간-링크-설정)
5. [CMake의 작동 방식](#5-cmake의-작동-방식)
6. [실제 예제](#6-실제-예제)
7. [CMake의 접근 지정자](#7-cmake의-접근-지정자)
   - [PRIVATE, PUBLIC, INTERFACE의 의미](#private-public-interface의-의미)
8. [추가 리소스](#8-추가-리소스)

---

## 1. CMake란 무엇인가?

**CMake**는 플랫폼 독립적인 **빌드 자동화 도구**로, 소스 코드를 빌드하기 위한 다양한 플랫폼 및 컴파일러에서 사용될 수 있는 빌드 스크립트를 생성합니다. CMake를 사용하면 프로젝트의 빌드 설정을 일관되게 관리할 수 있으며, 복잡한 의존성 관리도 손쉽게 처리할 수 있습니다.

### CMake의 주요 특징

- **플랫폼 독립성**: Windows, macOS, Linux 등 다양한 운영체제에서 사용 가능.
- **다양한 컴파일러 지원**: GCC, Clang, MSVC 등 여러 컴파일러를 지원.
- **모듈화**: 대규모 프로젝트를 여러 서브디렉토리와 모듈로 나눌 수 있음.
- **의존성 관리**: 라이브러리 간의 의존성을 효과적으로 관리.
- **테스트 통합**: CTest와 통합되어 자동화된 테스트 실행 가능.

---

## 2. CMake의 기본 구성 요소

CMake를 사용하여 프로젝트를 빌드하려면, **CMakeLists.txt** 파일을 작성해야 합니다. 이 파일은 프로젝트의 빌드 설정을 정의하는 스크립트로, CMake는 이 파일을 읽고 플랫폼에 맞는 빌드 시스템 파일(예: Makefile, Visual Studio 솔루션 파일)을 생성합니다.

### 기본적인 CMakeLists.txt 구조

```cmake
cmake_minimum_required(VERSION 3.10)  # 최소 CMake 버전 설정
project(MyProject VERSION 1.0)        # 프로젝트 이름과 버전 설정

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 소스 파일 추가 및 타겟 생성
add_executable(MyExecutable main.cpp)
```

- **cmake_minimum_required**: 사용하려는 최소 CMake 버전을 지정.
- **project**: 프로젝트의 이름과 버전을 정의.
- **set**: CMake 변수 설정.
- **add_executable**: 실행 파일을 생성할 타겟을 정의.

---

## 3. 타겟(Target) 이해하기

### 타겟의 종류

CMake에서 **타겟(Target)**은 빌드할 수 있는 단위로, 주로 **실행 파일**이나 **라이브러리**를 의미합니다. 타겟은 소스 파일, 포함 디렉토리, 링크 라이브러리 등의 속성을 포함합니다.

- **실행 파일(Executable)**: 실행 가능한 프로그램.
- **라이브러리(Library)**:
  - **정적 라이브러리(Static Library)**: `.lib`(Windows), `.a`(Unix) 파일.
  - **동적 라이브러리(Dynamic Library)**: `.dll`(Windows), `.so`(Unix), `.dylib`(macOS) 파일.

### 타겟 생성

타겟을 생성하려면 `add_executable` 또는 `add_library` 명령어를 사용합니다.

- **실행 파일 타겟 생성**

  ```cmake
  add_executable(MyExecutable main.cpp)
  ```

- **정적 라이브러리 타겟 생성**

  ```cmake
  add_library(MyStaticLib STATIC MyLib.cpp)
  ```

- **동적 라이브러리 타겟 생성**

  ```cmake
  add_library(MySharedLib SHARED MyLib.cpp)
  ```

### 타겟의 속성

타겟은 다음과 같은 속성을 가질 수 있습니다:

- **소스 파일(Source Files)**: 타겟을 빌드하기 위한 소스 파일 목록.
- **포함 디렉토리(Include Directories)**: 헤더 파일이 있는 디렉토리.
- **링크 라이브러리(Link Libraries)**: 타겟이 링크해야 하는 라이브러리 목록.
- **컴파일 옵션(Compile Options)**: 특정 컴파일러 옵션.

---

## 4. 링크(Link) 이해하기

### 링크의 종류

링크는 타겟이 다른 라이브러리나 타겟과의 종속성을 정의하는 것을 의미합니다. 링크는 빌드 과정에서 하나의 타겟이 다른 타겟의 기능을 사용할 수 있도록 연결합니다.

- **정적 링크(Static Linking)**: 라이브러리의 코드를 실행 파일에 포함.
- **동적 링크(Dynamic Linking)**: 실행 시 라이브러리를 참조.

### 타겟 간 링크 설정

타겟 간의 링크를 설정하려면 `target_link_libraries` 명령어를 사용합니다. 이 명령어는 특정 타겟이 다른 타겟이나 외부 라이브러리를 링크하도록 지시합니다.

```cmake
target_link_libraries(MyExecutable PRIVATE MyStaticLib)
```

- **PRIVATE**: 링크된 라이브러리가 현재 타겟에만 영향을 미침.
- **PUBLIC**: 링크된 라이브러리가 현재 타겟과 이를 링크하는 다른 타겟에도 영향을 미침.
- **INTERFACE**: 현재 타겟은 링크하지 않지만, 이를 링크하는 다른 타겟에만 영향을 미침.

---

## 5. CMake의 작동 방식

CMake는 `CMakeLists.txt` 파일을 읽고, 지정된 규칙에 따라 플랫폼에 맞는 빌드 파일을 생성합니다. 예를 들어, Unix 시스템에서는 Makefile을, Windows에서는 Visual Studio 솔루션 파일을 생성합니다.

### CMake의 주요 단계

1. **설정 단계(Configuration Stage)**:

   - `cmake` 명령어를 실행하여 프로젝트의 빌드 설정을 구성.
   - `CMakeLists.txt` 파일을 읽고, 프로젝트의 타겟, 라이브러리, 의존성을 파악.
   - 플랫폼에 맞는 빌드 시스템 파일을 생성.

2. **빌드 단계(Build Stage)**:
   - 생성된 빌드 시스템 파일을 사용하여 실제로 소스 코드를 컴파일하고 링크.
   - 예를 들어, `make` 명령어를 사용하여 Makefile 기반 프로젝트를 빌드.

### CMake 명령어의 순서

CMake는 `CMakeLists.txt` 파일의 명령어를 순차적으로 처리합니다. 이는 프로젝트의 구조와 의존성을 정확하게 반영하기 위해 중요합니다.

---

## 6. 실제 예제

다음은 CMake를 사용하여 간단한 프로젝트를 설정하고, 라이브러리와 실행 파일을 링크하는 예제입니다.

### 프로젝트 구조

```
MyProject/
├── CMakeLists.txt
├── main.cpp
├── MathModule/
│   ├── CMakeLists.txt
│   ├── MathFunctions.h
│   └── MathFunctions.cpp
└── Utils/
    ├── CMakeLists.txt
    ├── Logger.h
    └── Logger.cpp
```

### 각 파일의 내용

#### 1. 최상위 `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 서브 디렉토리 포함
add_subdirectory(MathModule)
add_subdirectory(Utils)

# 메인 프로그램을 위한 실행 파일 생성
add_executable(MyExecutable main.cpp)

# 메인 프로그램이 MathModule과 Utils 라이브러리를 링크
target_link_libraries(MyExecutable PRIVATE MathModule Utils)
```

#### 2. `MathModule/CMakeLists.txt`

```cmake
# MathModule 라이브러리 생성
add_library(MathModule STATIC MathFunctions.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

#### 3. `Utils/CMakeLists.txt`

```cmake
# Utils 라이브러리 생성
add_library(Utils STATIC Logger.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

#### 4. `MathModule/MathFunctions.h`

```cpp
#pragma once

class MathFunctions {
public:
    static int add(int a, int b);
    static int subtract(int a, int b);
};
```

#### 5. `MathModule/MathFunctions.cpp`

```cpp
#include "MathFunctions.h"

int MathFunctions::add(int a, int b) {
    return a + b;
}

int MathFunctions::subtract(int a, int b) {
    return a - b;
}
```

#### 6. `Utils/Logger.h`

```cpp
#pragma once
#include <string>

class Logger {
public:
    static void log(const std::string& message);
};
```

#### 7. `Utils/Logger.cpp`

```cpp
#include "Logger.h"
#include <iostream>

void Logger::log(const std::string& message) {
    std::cout << "LOG: " << message << std::endl;
}
```

#### 8. `main.cpp`

```cpp
#include "MathFunctions.h"
#include "Logger.h"

int main() {
    int sum = MathFunctions::add(5, 3);
    Logger::log("Sum: " + std::to_string(sum));

    int difference = MathFunctions::subtract(10, 4);
    Logger::log("Difference: " + std::to_string(difference));

    return 0;
}
```

### 빌드 과정

1. **빌드 디렉토리 생성 및 CMake 실행**

   ```bash
   mkdir build
   cd build
   cmake ..
   ```

   - 이 단계에서 CMake는 최상위 `CMakeLists.txt` 파일을 읽고, 서브디렉토리의 `CMakeLists.txt`도 포함하여 빌드 시스템 파일을 생성합니다.

2. **빌드 실행**

   ```bash
   cmake --build .
   ```

   - 이 명령어는 생성된 빌드 시스템 파일(Makefile 등)을 사용하여 실제로 소스 코드를 컴파일하고 링크합니다.

3. **실행 파일 실행**

   ```bash
   ./MyExecutable    # Linux/macOS
   MyExecutable.exe  # Windows
   ```

   - 실행 결과:

     ```
     LOG: Sum: 8
     LOG: Difference: 6
     ```

---

## 7. CMake의 접근 지정자

`target_link_libraries` 명령어에서 사용되는 **접근 지정자(Access Specifiers)**는 라이브러리의 의존성이 타겟과 다른 타겟에 어떻게 전파되는지를 정의합니다. 주요 접근 지정자는 **PRIVATE**, **PUBLIC**, **INTERFACE**입니다.

### PRIVATE, PUBLIC, INTERFACE의 의미

- **PRIVATE**:

  - **의미**: 링크된 라이브러리가 현재 타겟에만 영향을 미침. 이 라이브러리를 링크하는 다른 타겟에는 영향을 미치지 않음.
  - **사용 예**: 타겟 내부에서만 사용하는 라이브러리.
  - **예시**:
    ```cmake
    target_link_libraries(MyExecutable PRIVATE MyLibrary)
    ```

- **PUBLIC**:

  - **의미**: 링크된 라이브러리가 현재 타겟과 이를 링크하는 모든 다른 타겟에 영향을 미침.
  - **사용 예**: 라이브러리의 인터페이스(헤더 파일)에서 사용하는 라이브러리.
  - **예시**:
    ```cmake
    target_link_libraries(MyLibrary PUBLIC AnotherLibrary)
    ```

- **INTERFACE**:
  - **의미**: 현재 타겟은 직접적으로 링크하지 않지만, 이를 링크하는 다른 타겟에만 영향을 미침.
  - **사용 예**: 헤더 전용 라이브러리나, 컴파일 옵션만 전파하고 싶은 경우.
  - **예시**:
    ```cmake
    target_link_libraries(MyInterfaceLibrary INTERFACE SomeLibrary)
    ```

### 예제 설명

최상위 `CMakeLists.txt`에서 테스트 타겟을 설정할 때 **PRIVATE**을 사용하는 이유는 테스트 타겟이 특정 모듈을 테스트하기 위해만 해당 라이브러리에 의존하고, 이 의존성이 다른 타겟에 전파될 필요가 없기 때문입니다.

```cmake
# Tests/CMakeLists.txt

add_executable(MathModuleTests MathModuleTests.cpp)
target_link_libraries(MathModuleTests PRIVATE MathModule)
```

- **PRIVATE**을 사용하면 `MathModuleTests`가 `MathModule`에 의존하지만, `MathModuleTests`를 다른 타겟이 링크할 때 `MathModule`의 의존성이 전파되지 않습니다. 이는 의존성의 불필요한 전파를 방지하여 빌드 시간을 최적화하고, 의존성 관리를 간소화합니다.

---

## 8. 추가 리소스

- **공식 CMake 문서**: [CMake Documentation](https://cmake.org/documentation/)
- **CMake Tutorials**:
  - [Official CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
  - [CMake Tutorial by Example](https://cliutils.gitlab.io/modern-cmake/)
- **CMake 예제 및 레퍼런스**: [CMake Examples](https://github.com/Kitware/CMake/tree/master/Help/examples)

---

## 요약

- **CMake**는 다양한 플랫폼과 컴파일러를 지원하는 빌드 시스템 생성기로, `CMakeLists.txt` 파일을 통해 프로젝트의 빌드 설정을 관리합니다.
- **타겟(Target)**은 빌드할 수 있는 실행 파일이나 라이브러리로, `add_executable` 또는 `add_library` 명령어로 생성합니다.
- **링크(Link)**는 타겟 간의 의존성을 정의하며, `target_link_libraries` 명령어를 통해 설정합니다.
- **접근 지정자(PRIVATE, PUBLIC, INTERFACE)**는 링크된 라이브러리의 의존성이 어떻게 전파되는지를 정의합니다.
- CMake는 설정 단계와 빌드 단계를 통해 소스 코드를 컴파일하고 링크하여 최종 실행 파일이나 라이브러리를 생성합니다.

CMake를 효과적으로 사용하면 대규모 프로젝트의 빌드 과정을 자동화하고, 의존성 관리를 용이하게 할 수 있습니다. 타겟과 링크 개념을 명확히 이해함으로써 프로젝트의 구조를 체계적으로 설계하고, 유지보수성을 높일 수 있습니다.

궁금한 점이나 추가적인 도움이 필요하시면 언제든지 문의해 주세요!

---

# 질문

물론입니다! 주신 CMake 코드의 두 줄에 대해 자세히 설명드리겠습니다. 이 두 줄은 CMake를 사용하여 **Utils**라는 라이브러리를 생성하고, 해당 라이브러리가 헤더 파일을 찾을 수 있는 경로를 설정하는 역할을 합니다.

### 코드 설명

```cmake
# Utils 라이브러리 생성
add_library(Utils STATIC Logger.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

#### 1. `add_library(Utils STATIC Logger.cpp)`

**`add_library`**는 CMake에서 라이브러리를 생성하기 위한 명령어입니다. 이 명령어는 두 가지 주요 역할을 합니다:

- **라이브러리 이름 지정**: 여기서는 **Utils**라는 이름의 라이브러리를 생성합니다.
- **라이브러리 타입 및 소스 파일 지정**: **STATIC** 라이브러리를 생성하며, `Logger.cpp` 파일을 포함합니다.

##### 세부 사항:

- **`Utils`**:
  - 생성할 라이브러리의 이름입니다. 이 이름은 나중에 다른 타겟(예: 실행 파일)에서 이 라이브러리를 링크할 때 사용됩니다.
- **`STATIC`**:

  - 라이브러리의 종류를 지정합니다. **STATIC** 라이브러리는 정적 라이브러리로, 컴파일 시점에 실행 파일에 포함됩니다.
  - 다른 옵션으로는 **SHARED** (동적 라이브러리)와 **MODULE** (플러그인 형식의 라이브러리)이 있습니다.
    - **STATIC** (`.lib` 또는 `.a` 파일): 실행 파일에 포함되어 배포 시 별도의 라이브러리 파일이 필요 없습니다.
    - **SHARED** (`.dll`, `.so`, `.dylib` 파일): 실행 시점에 로드되며, 배포 시 라이브러리 파일을 함께 제공해야 합니다.

- **`Logger.cpp`**:
  - **Utils** 라이브러리에 포함될 소스 파일입니다. 이 파일은 라이브러리의 구현을 담고 있습니다.
  - 만약 여러 소스 파일이 있다면, 쉼표로 구분하여 나열할 수 있습니다:
    ```cmake
    add_library(Utils STATIC Logger.cpp Helper.cpp)
    ```

##### 예시:

```cmake
# Utils라는 이름의 정적 라이브러리를 생성하고, Logger.cpp를 포함
add_library(Utils STATIC Logger.cpp)
```

#### 2. `target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})`

**`target_include_directories`**는 특정 타겟(여기서는 **Utils** 라이브러리)이 헤더 파일을 찾을 수 있는 디렉토리를 지정하는 명령어입니다. 이 명령어는 타겟의 컴파일러에게 추가적인 헤더 파일 경로를 알려줍니다.

##### 세부 사항:

- **`Utils`**:

  - 헤더 파일 포함 경로를 설정할 대상 타겟입니다. 여기서는 **Utils** 라이브러리에 대해 설정합니다.

- **`PUBLIC`**:

  - 접근 지정자(Access Specifier)로, 포함 경로가 **Utils** 라이브러리뿐만 아니라 **Utils**를 링크하는 다른 타겟(예: 실행 파일)에도 전파된다는 것을 의미합니다.
  - 다른 접근 지정자로는 **PRIVATE**과 **INTERFACE**가 있습니다:
    - **PRIVATE**: 포함 경로가 현재 타겟에만 적용되고, 이를 링크하는 다른 타겟에는 전파되지 않습니다.
    - **INTERFACE**: 포함 경로가 현재 타겟에는 적용되지 않지만, 이를 링크하는 다른 타겟에만 전파됩니다.

- **`${CMAKE_CURRENT_SOURCE_DIR}`**:
  - 현재 `CMakeLists.txt` 파일이 위치한 디렉토리의 절대 경로를 나타내는 변수입니다.
  - 즉, **Utils** 라이브러리의 소스 파일들이 위치한 디렉토리를 포함 경로로 지정하게 됩니다.

##### 예시:

```cmake
# Utils 라이브러리와 관련된 헤더 파일이 현재 소스 디렉토리에 있다고 가정
target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

이 설정을 통해 **Utils** 라이브러리를 사용하는 다른 타겟들은 자동으로 **Utils** 라이브러리의 헤더 파일 경로를 포함하게 됩니다. 따라서 다른 타겟에서 **Utils** 라이브러리의 헤더 파일을 쉽게 참조할 수 있습니다.

### 왜 `PUBLIC`을 사용할까?

`PUBLIC` 접근 지정자를 사용하면 **Utils** 라이브러리를 링크하는 모든 타겟이 **Utils**의 헤더 파일을 포함 경로로 사용할 수 있게 됩니다. 이는 라이브러리를 사용하는 코드가 라이브러리의 헤더 파일을 필요로 할 때 매우 유용합니다.

예를 들어, 메인 프로그램이 **Utils** 라이브러리를 사용한다고 할 때:

```cmake
# 메인 프로그램 타겟 생성
add_executable(MainProgram main.cpp)

# 메인 프로그램이 Utils 라이브러리를 링크하고, Utils의 PUBLIC 포함 경로를 사용
target_link_libraries(MainProgram PRIVATE Utils)
```

이 경우, **Utils** 라이브러리의 `target_include_directories`에서 `PUBLIC`으로 설정했기 때문에, **MainProgram**은 **Utils**의 헤더 파일을 포함 경로로 자동으로 인식할 수 있습니다. 따라서 `main.cpp`에서 **Utils**의 헤더 파일을 포함할 때 별도의 경로 지정이 필요 없습니다.

### 요약

- **`add_library(Utils STATIC Logger.cpp)`**:
  - **Utils**라는 이름의 정적 라이브러리를 생성하고, `Logger.cpp` 파일을 포함합니다.
- **`target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})`**:
  - **Utils** 라이브러리와 이를 사용하는 다른 타겟들이 **Utils**의 헤더 파일을 찾을 수 있도록 현재 소스 디렉토리를 포함 경로로 지정합니다.
  - `PUBLIC` 접근 지정자를 사용하여 **Utils**를 링크하는 모든 타겟이 이 포함 경로를 자동으로 사용할 수 있게 합니다.

### 추가 참고 자료

- **CMake 공식 문서 - add_library**:
  - [CMake Add Library](https://cmake.org/cmake/help/latest/command/add_library.html)
- **CMake 공식 문서 - target_include_directories**:

  - [CMake Target Include Directories](https://cmake.org/cmake/help/latest/command/target_include_directories.html)

- **CMake 접근 지정자 이해하기**:
  - [CMake Target Properties](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties)

CMake를 처음 접하셨다면, 공식 문서나 튜토리얼을 참고하여 다양한 예제를 통해 익히시는 것을 추천드립니다. 추가적으로 궁금한 점이나 더 알고 싶은 부분이 있으시면 언제든지 질문해 주세요!

---

물론입니다! CMake에서 `target_link_libraries` 명령어의 `PUBLIC`, `PRIVATE`, `INTERFACE` 접근 지정자가 최상위(CMake 프로젝트의 루트)에서 어떤 의미를 가지는지에 대해 자세히 설명드리겠습니다.

## CMake에서 `target_link_libraries`의 접근 지정자 이해하기

### 접근 지정자의 종류

1. **PRIVATE**
   - **의미**: 링크된 라이브러리가 **현재 타겟**에만 영향을 미칩니다.
   - **사용 시기**: 해당 라이브러리가 현재 타겟 내부에서만 필요하고, 이를 링크하는 다른 타겟에는 전파할 필요가 없을 때 사용합니다.
2. **PUBLIC**
   - **의미**: 링크된 라이브러리가 **현재 타겟**과 이를 링크하는 **모든 다른 타겟**에 영향을 미칩니다.
   - **사용 시기**: 현재 타겟이 사용하는 라이브러리가 이를 링크하는 다른 타겟에서도 필요할 때 사용합니다. 예를 들어, 라이브러리의 헤더 파일이 다른 타겟에서도 필요할 때 유용합니다.
3. **INTERFACE**
   - **의미**: 링크된 라이브러리가 **현재 타겟**에는 영향을 미치지 않지만, 이를 링크하는 **다른 타겟**에만 영향을 미칩니다.
   - **사용 시기**: 현재 타겟은 직접적으로 해당 라이브러리를 사용하지 않지만, 이를 사용하는 타겟들이 필요로 할 때 사용합니다. 주로 헤더 전용 라이브러리나 컴파일 옵션을 전파할 때 유용합니다.

### 최상위 CMakeLists.txt에서의 의미

최상위 `CMakeLists.txt` 파일은 보통 프로젝트의 **주 실행 파일**이나 **주 라이브러리**를 정의하고, 서브디렉토리의 모듈을 포함하는 역할을 합니다. 이때 `target_link_libraries`에서 사용하는 접근 지정자는 여전히 중요하며, 다음과 같은 방식으로 동작합니다:

1. **최상위 타겟이 실행 파일인 경우**

   - **PRIVATE 사용**: 주 실행 파일이 특정 라이브러리에만 의존하고, 이를 사용하는 다른 타겟이 없을 때 적합합니다.
   - **PUBLIC 사용**: 주 실행 파일이 라이브러리를 사용하며, 동시에 이 라이브러리를 사용하는 다른 타겟이 있을 때 적합합니다.

2. **최상위 타겟이 라이브러리인 경우**
   - **PUBLIC 사용**: 라이브러리가 의존하는 다른 라이브러리들이 이 라이브러리를 사용하는 모든 타겟에 전파되어야 할 때 사용합니다.
   - **PRIVATE 사용**: 라이브러리가 내부적으로만 사용하는 다른 라이브러리가 있을 때 사용합니다.
   - **INTERFACE 사용**: 라이브러리가 직접적으로는 다른 라이브러리에 의존하지 않지만, 이를 사용하는 타겟이 의존해야 할 경우 사용합니다.

### 구체적인 예시

#### 프로젝트 구조

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

# 메인 프로그램이 MathModule, UtilityModule, StringModule을 사용할 수 있도록 링크
target_link_libraries(MainProgram PRIVATE MathModule UtilityModule StringModule)
```

#### 2. 서브 디렉토리 `CMakeLists.txt`

**MathModule/CMakeLists.txt**

```cmake
# MathModule 라이브러리 생성
add_library(MathModule STATIC MathFunctions.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

**UtilityModule/CMakeLists.txt**

```cmake
# UtilityModule 라이브러리 생성
add_library(UtilityModule STATIC Logger.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(UtilityModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 스레드 라이브러리 링크 (Logger에 mutex 사용)
find_package(Threads REQUIRED)
target_link_libraries(UtilityModule PRIVATE Threads::Threads)
```

**StringModule/CMakeLists.txt**

```cmake
# StringModule 라이브러리 생성
add_library(StringModule STATIC StringFunctions.cpp)

# 헤더 파일 포함 경로 설정
target_include_directories(StringModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

**Tests/CMakeLists.txt**

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

### `PUBLIC`과 `PRIVATE`의 의미 적용 사례

1. **메인 프로그램에서 라이브러리를 링크할 때 (최상위 CMakeLists.txt)**

   - `target_link_libraries(MainProgram PRIVATE MathModule UtilityModule StringModule)`
   - **PRIVATE**을 사용한 이유:
     - **MainProgram**이 **MathModule**, **UtilityModule**, **StringModule**을 사용하지만, 다른 타겟이 이 라이브러리를 사용할 필요가 없기 때문입니다.
     - 이는 **MainProgram**이 최종 실행 파일이므로, 다른 타겟이 **MainProgram**을 링크할 일이 없기 때문에 **PRIVATE**을 사용해도 무방합니다.

2. **서브 모듈에서 다른 라이브러리를 링크할 때**

   - 예를 들어, **UtilityModule**이 스레드를 사용하기 위해 `Threads::Threads`를 링크할 때 **PRIVATE**을 사용했습니다.
   - 이는 **UtilityModule** 내부에서만 스레드 라이브러리가 필요하고, 이를 사용하는 다른 타겟에는 전파할 필요가 없기 때문입니다.

3. **서브 모듈의 헤더 파일 포함 경로 설정**
   - `target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})`
   - **PUBLIC**을 사용한 이유:
     - **MathModule**을 사용하는 다른 타겟(예: **MainProgram**)이 **MathModule**의 헤더 파일을 필요로 하기 때문입니다.
     - **PUBLIC**을 통해 **MathModule**을 링크하는 타겟에게 자동으로 헤더 파일 경로가 전달됩니다.

### 최상위에서 `PUBLIC` vs `PRIVATE`의 의미

최상위 `CMakeLists.txt`에서도 `PUBLIC`, `PRIVATE`, `INTERFACE`의 접근 지정자는 여전히 의미가 있습니다. 하지만, 사용되는 맥락에 따라 적절한 접근 지정자를 선택해야 합니다.

- **실행 파일을 최종 타겟으로 사용할 경우**:

  - **PRIVATE**을 사용하는 것이 일반적입니다. 이유는 실행 파일이 다른 타겟에 의해 링크될 일이 없기 때문입니다.
  - 예시:
    ```cmake
    target_link_libraries(MainProgram PRIVATE MathModule UtilityModule StringModule)
    ```

- **라이브러리를 최상위에서 정의하고, 이를 다른 서브디렉토리에서도 사용할 경우**:
  - **PUBLIC**을 사용할 수 있습니다. 이는 라이브러리를 사용하는 모든 타겟이 해당 라이브러리의 의존성을 알 수 있게 합니다.
  - 예시:

    ```cmake
    add_library(CommonLib STATIC Common.cpp)
    target_include_directories(CommonLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    # 다른 타겟에서 CommonLib를 사용할 때 PUBLIC 접근 지정자를 통해 의존성이 전파됨
    target_link_libraries(OtherLib PUBLIC CommonLib)
    ```

### 요약

- **PUBLIC**, **PRIVATE**, **INTERFACE**는 CMake에서 타겟 간의 의존성 전파 방식을 정의합니다.
- **최상위 `CMakeLists.txt`에서도 이 접근 지정자들은 의미가 있으며, 프로젝트의 구조와 의존성 관리 방식에 따라 적절히 사용해야 합니다.**
  - **최종 실행 파일을 링크할 경우**: **PRIVATE**을 사용하는 것이 적절합니다.
  - **라이브러리를 정의하고 이를 다른 타겟에서도 사용할 경우**: **PUBLIC**을 사용하여 의존성을 전파할 수 있습니다.
- **접근 지정자를 올바르게 사용하는 것이 의존성 관리와 빌드 효율성을 높이는 데 중요합니다.**

### 추가 예시

#### 최상위 `CMakeLists.txt`에서 라이브러리와 실행 파일을 링크하는 다양한 시나리오

1. **실행 파일이 라이브러리를 링크하는 경우**

   ```cmake
   # MainProgram이 MathModule, UtilityModule, StringModule을 사용
   target_link_libraries(MainProgram PRIVATE MathModule UtilityModule StringModule)
   ```

   - **PRIVATE**: MainProgram이 라이브러리를 사용하지만, 다른 타겟이 MainProgram을 링크할 일이 없기 때문에 **PRIVATE**을 사용합니다.

2. **라이브러리가 다른 라이브러리를 링크하고 이를 전파해야 하는 경우**

   예를 들어, **MathModule**이 **Utils** 라이브러리에 의존한다고 가정해보겠습니다.

   **MathModule/CMakeLists.txt**

   ```cmake
   add_library(MathModule STATIC MathFunctions.cpp)
   target_include_directories(MathModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

   # MathModule이 UtilityModule에 의존
   target_link_libraries(MathModule PUBLIC UtilityModule)
   ```

   - **PUBLIC**: **MathModule**을 사용하는 타겟도 자동으로 **UtilityModule**에 링크되도록 합니다.

3. **인터페이스 라이브러리 사용**

   **InterfaceLib/CMakeLists.txt**

   ```cmake
   add_library(InterfaceLib INTERFACE)
   target_include_directories(InterfaceLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
   ```

   - **INTERFACE**: **InterfaceLib** 자체는 컴파일되지 않지만, 이를 링크하는 타겟은 **InterfaceLib**의 포함 디렉토리를 사용하게 됩니다.

   **AnotherLib/CMakeLists.txt**

   ```cmake
   add_library(AnotherLib STATIC Another.cpp)
   target_link_libraries(AnotherLib PUBLIC InterfaceLib)
   ```

   - **PUBLIC**: **AnotherLib**를 사용하는 타겟도 **InterfaceLib**의 포함 디렉토리를 사용하게 됩니다.

### 결론

최상위 `CMakeLists.txt`에서도 `target_link_libraries`의 접근 지정자(`PUBLIC`, `PRIVATE`, `INTERFACE`)는 중요한 역할을 합니다. 프로젝트의 구조와 의존성 전파 방식을 고려하여 적절한 접근 지정자를 선택하는 것이 중요합니다. 이를 통해 의존성을 명확하게 관리하고, 빌드 프로세스를 효율적으로 유지할 수 있습니다.

추가적으로 궁금한 점이나 더 자세한 설명이 필요하시면 언제든지 질문해 주세요!
