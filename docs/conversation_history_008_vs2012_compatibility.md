# 대화 이력 008: VS2012 호환성 개선

## 날짜
2025-11-28

## 요청
wmx15app에서 WMXBroker를 호출할 때 VS2012 호환성 문제 검토 및 해결

## 문제 분석

### 핵심 이슈
- **사용자 앱**: VS2012 (v110 toolset)로 빌드
- **WMXBroker DLL**: VS2022 (v143 toolset)로 빌드
- C++ ABI 불일치로 직접 클래스 호출 불가

### 발견된 문제점
1. C++ 런타임 ABI 불일치 (MSVCRT110 vs UCRT)
2. Name mangling 차이
3. vtable/RTTI 레이아웃 차이

## 해결 방안

### 아키텍처
```
[사용자 앱 VS2012]                    [WMXBroker.dll VS2022]
        │                                      │
        ▼                                      ▼
┌─────────────────┐                 ┌─────────────────────┐
│ WMXBrokerClient.h│                │ WMXBrokerC.cpp      │
│ (헤더 전용 래퍼) │───C API 호출──▶│ (C API 구현)        │
│                 │                 │         │           │
│ wmxAPI::WMXLIB  │                 │         ▼           │
│ wmxAPI::common::Io                │ wmxAPI::WMXLIB      │
└─────────────────┘                 │ (C++ 구현체)        │
                                    └─────────────────────┘
```

### 사용자 앱 변경 사항
```cpp
// 변경 전
#include "WMXLIB.h"

// 변경 후
#include "WMXBrokerClient.h"
```

나머지 코드는 변경 불필요 - 동일한 wmxAPI::WMXLIB 인터페이스 제공

## 구현 내용

### 추가된 파일

1. **broker/WMXBrokerC.h** - C API 선언
   - extern "C"로 선언된 함수들
   - __stdcall 호출 규약
   - __declspec(dllexport/dllimport)

2. **broker/WMXBrokerC.cpp** - C API 구현
   - 전역 싱글톤 wmxAPI::WMXLIB 인스턴스 관리
   - 각 C 함수에서 해당 C++ 메서드 호출

3. **broker/WMXBroker.def** - Export 정의
   - Undecorated 함수명 export
   - 순서 번호 지정

4. **include/WMXBrokerClient.h** - 헤더 전용 래퍼 클래스
   - wmxAPI::WMXLIB 동일 인터페이스
   - 내부적으로 C API 호출

### 수정된 파일

1. **broker/WMXBroker.vcxproj**
   - WMXBrokerC.h, WMXBrokerC.cpp 추가
   - WMXBroker.def 추가
   - ModuleDefinitionFile 설정

## C API 함수 목록

| 함수명 | Ordinal |
|--------|---------|
| WMXBroker_CreateDevice | @1 |
| WMXBroker_CloseDevice | @2 |
| WMXBroker_StartCommunication | @3 |
| WMXBroker_StopCommunication | @4 |
| WMXBroker_GetStatus | @5 |
| WMXBroker_GetStatusAxis | @6 |
| WMXBroker_GetStatusRange | @7 |
| WMXBroker_GetVersion | @8 |
| WMXBroker_Io_SetOutBit | @10 |
| WMXBroker_Io_SetOutByte | @11 |
| WMXBroker_Io_SetOutBytes | @12 |
| WMXBroker_Io_GetInBit | @13 |
| WMXBroker_Io_GetInByte | @14 |
| WMXBroker_Io_GetInBytes | @15 |
| WMXBroker_Io_GetOutBit | @16 |
| WMXBroker_Io_GetOutByte | @17 |
| WMXBroker_Io_GetOutBytes | @18 |
| WMXBroker_Io_SetInitialOutBit | @19 |
| WMXBroker_Io_SetInitialOutByte | @20 |
| WMXBroker_Io_SetInitialOutBytes | @21 |
| WMXBroker_Io_GetInitialOutBit | @22 |
| WMXBroker_Io_GetInitialOutByte | @23 |
| WMXBroker_Io_GetInitialOutBytes | @24 |

## 배포 파일

VS2012 사용자 앱에 배포해야 할 파일:
- `include/WMXBrokerClient.h` - 래퍼 클래스 헤더
- `include/WMXBrokerC.h` - C API 선언 (broker/ 폴더에서 복사)
- `lib/WMXBroker.lib` - Import Library
- `bin/WMXBroker.dll` - DLL 바이너리

## 빌드 결과
- 빌드 성공
- WMXBroker.dll, WMXBroker.lib 생성
- 경고 8개 (WMX3 라이브러리 PDB 관련 - 무시 가능)

## 주의사항
1. 사용자 앱도 MultiByte 문자셋 설정 필요
2. x64 플랫폼 전용
3. DLL 내부 싱글톤이므로 여러 WMXLIB 인스턴스 생성해도 동일한 DLL 인스턴스 사용
