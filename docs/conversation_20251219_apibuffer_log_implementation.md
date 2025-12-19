# ApiBuffer 및 Log 클래스 구현 대화 기록

날짜: 2025-12-19

## 요청 사항

사용자가 API 인터페이스에 두 클래스 추가를 요청:
- `sdk/WMX34u4_Win/Include/ApiBufferApi.h`의 ApiBuffer 클래스
- `sdk/WMX34u4_Win/Include/LogApi.h`의 Log 클래스
- 새로 생성되는 헤더 파일은 원본과 동일하게 접미어 `_Sim`을 붙임
- 전체 Broker 구현 선택 (타입 정의만이 아닌)

## 구현 내용

### 1. WMX3BrokerC.h - C API 함수 선언 추가

#### ApiBuffer APIs (@530-553)
```cpp
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_GetLibVersion(...);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_GetVersion(...);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_CreateApiBuffer(...);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_FreeApiBuffer(...);
// ... 등 24개 함수
```

#### Log APIs (@560-594)
```cpp
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetLibVersion(...);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetVersion(...);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_StartLog(...);
// ... 등 35개 함수
```

### 2. WMX3BrokerC.cpp - C API 함수 구현 추가

- ApiBufferApi.h, LogApi.h 헤더 include 추가
- ApiBuffer 함수 구현 (1210-1401 라인)
- Log 함수 구현 (1403-1605 라인)
- WMX3ContextManager를 통해 shared context 사용

### 3. WMXBroker.def - DLL Export 추가

```def
; WMX3 ApiBuffer APIs
WMX3Broker_ApiBuffer_GetLibVersion               @530
WMX3Broker_ApiBuffer_GetVersion                  @531
...

; WMX3 Log APIs
WMX3Broker_Log_GetLibVersion                     @560
WMX3Broker_Log_GetVersion                        @561
...
```

### 4. WMX3ContextManager 업데이트

**WMX3ContextManager.h:**
- ApiBuffer, Log 클래스 forward declaration 추가
- `wmx3Api::ApiBuffer* m_apiBuffer` 멤버 추가
- `wmx3Api::Log* m_log` 멤버 추가
- `GetApiBuffer()`, `GetLog()` getter 추가

**WMX3ContextManager.cpp:**
- ApiBufferApi.h, LogApi.h include 추가
- 생성자에서 m_apiBuffer, m_log NULL 초기화
- CreateDeviceInternal()에서 ApiBuffer, Log 인스턴스 생성
- CloseDeviceInternal()에서 ApiBuffer, Log 인스턴스 삭제

### 5. 신규 Sim 헤더 파일 생성

#### include/ApiBufferApi_Sim.h
- 모든 타입 정의 (constants, enums, structs)
  - ApiBufferErrorCode
  - ApiBufferConditionType
  - ApiBufferState
  - SizeUnit
  - ApiBufferCondition
  - ApiBufferErrorLog
  - ApiBufferStatus
  - ApiBufferOptions
  - ApiBufferWatch
- ApiBuffer 클래스: WMX3Broker_ApiBuffer_* 함수 호출 래핑

#### include/LogApi_Sim.h
- 모든 타입 정의 (constants, enums, structs)
  - LogErrorCode
  - LogState, DetailLogState, ApiLogState
  - FormatType
  - LogStatus, LogOptions, LogChannelOptions
  - LogFilePathA, LogFilePathW
  - DetailLogBufferStatus, DetailLogStatus, DetailLogMemoryStatus
  - MemoryLogStatus, MemoryLogAxisData, MemoryLogIOData, MemoryLogMData
  - MemoryLogOptions, MemoryLogDatas, MemoryLogData
  - ApiLogInfo, ApiLogOptions, ApiLogStatus
- Log 클래스: WMX3Broker_Log_* 함수 호출 래핑

### 6. WMX3Api_Sim.h 업데이트

```cpp
#include "ApiBufferApi_Sim.h"
#include "LogApi_Sim.h"
```

### 7. 프로젝트 설정 업데이트

모든 props 파일과 vcxproj에 라이브러리 추가:
- `ApiBufferApi.lib`
- `LogApi.lib`

수정된 파일:
- broker/props/WMX34u4_Win.props
- broker/props/WMX34u4_RTX.props
- broker/props/WMX36u1_Win.props
- broker/props/WMX36u1_RTX.props
- broker/WMXBroker.vcxproj (Debug, Release 설정)

## 빌드 결과

WMX34u4_Win 버전 빌드 성공:
```
WMXBroker.vcxproj -> c:\Users\jcy1236\source\repos\wmx15app\x64\Release_WMX34u4_Win\WMXBroker.dll
```

## 파일 변경 요약

| 파일 | 변경 내용 |
|------|----------|
| broker/WMX3BrokerC.h | ApiBuffer/Log C API 선언 추가 |
| broker/WMX3BrokerC.cpp | ApiBuffer/Log C API 구현 추가 |
| broker/WMXBroker.def | ApiBuffer/Log export 추가 (@530-594) |
| broker/WMX3ContextManager.h | ApiBuffer/Log 멤버 및 getter 추가 |
| broker/WMX3ContextManager.cpp | ApiBuffer/Log 생성/삭제 로직 추가 |
| include/ApiBufferApi_Sim.h | 신규 생성 |
| include/LogApi_Sim.h | 신규 생성 |
| include/WMX3Api_Sim.h | ApiBuffer/Log Sim 헤더 include 추가 |
| broker/props/*.props | ApiBufferApi.lib, LogApi.lib 추가 |
| broker/WMXBroker.vcxproj | ApiBufferApi.lib, LogApi.lib 추가 |
