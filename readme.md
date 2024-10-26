# LC-3 학습 프로그램 개발 일지

- 서울대학교 컴퓨터공학부 24-2 컴퓨터프로그래밍 강의
- C++ 프로젝트 과제
- 1차 결과물: https://github.com/woojeans1204/LC-3Emulator

## 목표

LC-3 어셈블리어의 어셈블러와 시뮬레이터를 구현하고, 이를 활용해 어셈블리어 학습 프로그램을 개발하는 것.

## 코드

### CMakeTutorial

- **설명**: 기본적인 CMake 사용법을 익히기 위한 프로젝트
- **기능**: `hello, world` 출력 프로그램 빌드
- **주요 학습 내용**:
  - CMake 파일의 기본 구조 및 사용법
  - 간단한 실행 파일 빌드 프로세스

### CMakeTestModule

- **설명**: 모듈화된 프로그램을 구축하고 테스트하는 프로젝트
- **기능**: 소스코드를 모듈화하고, 테스트 모듈을 통해 다른 모듈 검증
- **주요 학습 내용**:
  - 프로그램을 라이브러리 형태로 분할
  - 테스트 모듈을 통한 코드 검증 방법

### CMakeLibrary

- **설명**: Visual Studio .NET에서 프로젝트를 이식하기 위한 라이브러리 형태로 빌드
- **기능**: 프로젝트를 라이브러리 형태로 빌드하여 이식성 확보
- **주요 학습 내용**:
  - 정적 라이브러리 빌드
  - .NET 환경에서의 호환성 확보

## 개발 일지

### 2024-10-22

- **진행 사항**:

  - CMake를 사용해 프로젝트 빌드 시스템 설정 방법 학습
  - CMake 다운로드 후 Chat-GPT를 이용해 튜토리얼을 진행
  - CMAKE을 이용한 프로젝트 모듈화, 라이브러리화 튜토리얼 진행중
  - CMakeTutorial, CMakeTestModule 완성

- **주요 학습 내용**:

  - CMake의 작동 방법 및 기본 문법
  - 큰 프로젝트의 파일 분할 및 빌드
  - lib(정적 라이브러리)의 생성 및 사용 방법(링킹)

### 2024-10-23

- **진행 사항**:

  - CMakeLibrary 완성
  - 어셈블러 구현을 위한 개념 학습
  - 어셈블러 구현 시 obj파일 형식을 모르는 문제 발생
  - obj 파일을 생성하는 대신 어셈블러와 시뮬레이터를 합치는 방식으로 프로그램 구현 방향 설정
  - 1차 목표 진행 시작

- **개발 방향**:

  - **1차 목표**: CLI의 형태로 어셈블, 시뮬레이션 기능을 통합한 LC-3 에뮬레이터 구현 (라이브러리의 형태로 빌드)
  - **2차 목표**: VS, 윈도우 폼을 이용해 GUI를 완성
  - **3차 목표**: 그 외 학습을 위한 툴이나 튜토리얼 등을 구현해 학습 프로그램을 최종 완성

- **예상 프로젝트 구조**

```
LC3Emulator/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── Assembler.h
│   ├── Assembler.cpp
│   ├── Simulator.h
│   ├── Simulator.cpp
└── tests/
    ├── CMakeLists.txt
    ├── AssemblerTests.cpp
    └── SimulatorTests.cpp
```

### 2024-10-24

- **진행 사항**:

  - 프로젝트 생성 (https://github.com/woojeans1204/LC-3Emulator)
  - 코드를 Token 단위로 쪼개 저장하는 Parser 일부 구현
  - 다중 레이블 (한 라인에 레이블이 여러개 존재) 처리
  - 1차 패싱에서 각 label의 이름과 주소를 저장하는 SymbolTable을 일부 구현
  - 명령어 Encoding을 담당하는 InstructionSet 일부 구현

- **세부 구현 방향**:
  - Parser, SymbolTable, InstructionSet의 주요 기능들 먼저 구현 후 Assembler를 부분적으로 먼저 구현
  - 그 후, 각 클래스의 남은 부분들을 차례대로 구현
  - **Assembler**: Parser, SymbolTable, InstructionSet
  - **Simulator**: Memory, RegisterFile, Decoder, InstructionClasses

### 2024-10-26

- **진행 사항**:

  - Parser, SymbolTable, InstructionSet를 활용하여 2-Pass 어셈블러를 구현
  - Assembler 클래스를 부분적으로 구현함

- **특이 사항**:
  - LC-3은 기본적으로 Big Endian 인코딩 방식을 사용하지만 현대 아키텍쳐들은 Little Endian을 사용
  - 이 프로젝트에서는 구현의 편의를 위해 Little Endian 인코딩을 사용함
  - 현재 Assembler 작동 확인 하였지만, 다른 명령어 구현 등 미완성된 부분이 존재
  - Simulator 클래스도 불완전하게라도 먼저 구현 후 미완성된 부분들을 구현
