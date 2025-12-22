# ErrorToString API 추가 작업 기록

날짜: 2025-12-22

## 요청
WMX3 SDK의 여러 API 클래스에 `ErrorToString` 정적 메서드를 브로커에 추가

## 대상 클래스 (10개)

| # | 클래스 | SDK 파일 |
|---|--------|----------|
| 1 | ApiBuffer | ApiBufferApi.h |
| 2 | Log | LogApi.h |
| 3 | CoreMotion | CoreMotionApi.h |
| 4 | EventControl | EventApi.h |
| 5 | CyclicBuffer | CyclicBufferApi.h |
| 6 | Compensation | CompensationApi.h |
| 7 | WMX3Api | WMX3Api.h |
| 8 | UserMemory | UserMemoryApi.h |
| 9 | PMMotion | PMMotionApi.h |
| 10 | AdvancedMotion | AdvancedMotionApi.h |

## 변경 파일

### C API 레이어
- **broker/include/WMX3/WMX3BrokerC.h** - 20개 함수 선언 추가 (10개 클래스 × 2개 함수)
- **broker/WMX3BrokerC.cpp** - 20개 함수 구현 추가

### 기존 Sim 헤더 수정
- include/WMX3/WMX3Api_Sim.h - ErrorToString 2개 추가
- include/WMX3/CoreMotionApi_Sim.h - ErrorToString 2개 추가
- include/WMX3/EventApi_Sim.h - ErrorToString 2개 추가
- include/WMX3/ApiBufferApi_Sim.h - ErrorToString 2개 추가
- include/WMX3/LogApi_Sim.h - ErrorToString 2개 추가

### 새로 생성한 Sim 헤더
- include/WMX3/CyclicBufferApi_Sim.h
- include/WMX3/CompensationApi_Sim.h
- include/WMX3/UserMemoryApi_Sim.h
- include/WMX3/PMMotionApi_Sim.h
- include/WMX3/AdvancedMotionApi_Sim.h

### 프로젝트 파일 수정
- **broker/WMXBroker.vcxproj** - 추가 라이브러리 링크 (CyclicBufferApi.lib, CompensationApi.lib, UserMemoryApi.lib, PMMotionApi.lib)

## API 패턴

### C API 함수
```cpp
WMX3BROKER_CAPI long __stdcall WMX3Broker_{ClassName}_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_{ClassName}_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);
```

### C++ 래퍼 (Sim 헤더)
```cpp
static long ErrorToString(int errCode, char *pString, unsigned int size)
{
    return WMX3Broker_{ClassName}_ErrorToString(errCode, pString, size);
}

static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
{
    return WMX3Broker_{ClassName}_ErrorToStringW(errCode, pString, size);
}
```

## 빌드 결과
- 빌드 성공: WMX36u1_Win 구성
- 출력: x64\Release_WMX36u1_Win\WMXBroker.dll
