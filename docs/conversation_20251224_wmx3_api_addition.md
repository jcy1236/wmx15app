# 대화 이력: WMX3 API 추가 및 아키텍처 수정

**날짜**: 2025-12-24
**주제**: WMX3 SDK API 4개 추가 및 ConfigBroker 아키텍처 위반 수정

## 요약

WMX3 SDK의 4개 API를 WMXBroker에 추가하는 작업을 진행했습니다:
- `ApiBuffer::IsDeviceValid()`
- `AdvancedMotion::advSync::IsDeviceValid()`
- `CoreMotion::SetEmergencyStopParam()`
- `CoreMotion::GetEmergencyStopParam()`

초기 구현 후, 사용자 피드백을 통해 아키텍처 원칙을 명확히 이해하고 ConfigBroker(WMX 1.5 레이어)에 잘못 추가된 WMX3 전용 코드를 제거하여 올바른 아키텍처를 완성했습니다.

## 아키텍처 원칙 (사용자 설명)

### 두 가지 사용자 그룹

1. **WMX 1.5 사용자**
   - 경로: `WMX 1.5 App → ConfigBroker → WMX3 SDK`
   - ConfigBroker는 WMX 1.5 타입을 WMX3 타입으로 매핑
   - WMX3 전용 기능(EmergencyStopParam 등)은 접근 불가

2. **WMX3 사용자**
   - 경로: `WMX3 App → WMX3BrokerC → WMX3 SDK`
   - 또는: `WMX3 App → *_Sim.h → WMX3BrokerC → WMX3 SDK`
   - WMX3 타입을 그대로 사용, 매핑 없음
   - WMX3 모든 기능 접근 가능

### 핵심 원칙
- **"두 그룹의 기능이 섞이지 않도록 구현에 주의해야 해"**
- WMX3 전용 API는 WMX3BrokerC에만 추가
- ConfigBroker는 순수 WMX 1.5 호환 레이어로 유지

## 질문 1: 사용자가 요청한 API

```
API 추가
@sdk/WMX36u1_Win/Include/ApiBufferApi.h#L290
@sdk/WMX36u1_Win/Include/AdvancedMotionApi.h#L101
@sdk/WMX36u1_Win/Include/CoreMotionApi.h#L1657
@sdk/WMX36u1_Win/Include/CoreMotionApi.h#L1665
```

대상 API:
1. `bool ApiBuffer::IsDeviceValid()` (라인 290)
2. `bool AdvancedMotion::advSync::IsDeviceValid()` (라인 101)
3. `long CoreMotion::SetEmergencyStopParam(Config::EmergencyStopParam*, Config::EmergencyStopParam*)` (라인 1657)
4. `long CoreMotion::GetEmergencyStopParam(Config::EmergencyStopParam*)` (라인 1665)

## 답변 1: 구현 방식 선택 질문

사용자에게 3가지 질문을 통해 구현 방식 확인:

1. **IsDeviceValid 노출 방식**: "C API 스타일 (WMX3BrokerC.cpp 패턴)" 선택
2. **EmergencyStop 추가 위치**: "ConfigBroker에 추가 (추천)" 선택 → **나중에 잘못된 선택으로 판명**
3. **EmergencyStopParam 구조체**: "WMX3 구조체를 그대로 사용 (추천)" 선택

## 질문 2: Sim 래퍼 추가 요청

```
ApiBufferApi_Sim.h 와 CoreMotionApi_Sim.h 에도 인터페이스 추가해야 해
```

## 답변 2: 전체 구현 완료

### 구현한 파일들

#### 1. WMX3BrokerC.h/cpp (C API 레이어) ✅ 올바름
```cpp
// WMX3BrokerC.h
WMX3BROKER_CAPI int __stdcall WMX3Broker_ApiBuffer_IsDeviceValid(void);
WMX3BROKER_CAPI int __stdcall WMX3Broker_AdvancedMotion_AdvSync_IsDeviceValid(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetEmergencyStopParam(void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetEmergencyStopParam(void* pParam);

// WMX3BrokerC.cpp
int __stdcall WMX3Broker_ApiBuffer_IsDeviceValid(void)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ApiBuffer* apiBuffer = ctx->GetApiBuffer();
    if (!apiBuffer) return 0;
    return apiBuffer->IsDeviceValid() ? 1 : 0;
}
// ... 나머지 3개 함수 구현
```

#### 2. ConfigBroker.h/cpp ❌ 잘못된 구현 (나중에 제거)
```cpp
// ConfigBroker.h - INCORRECT (제거함)
#include "CoreMotionApi.h"  // 제거됨
WMXAPIFUNC GetEmergencyStopParam(wmx3Api::Config::EmergencyStopParam* pParam);  // 제거됨
WMXAPIFUNC SetEmergencyStopParam(wmx3Api::Config::EmergencyStopParam* pParam);  // 제거됨

// ConfigBroker.cpp - INCORRECT (제거함)
// GetEmergencyStopParam/SetEmergencyStopParam 구현 제거됨
```

#### 3. ApiBufferApi_Sim.h ✅ 올바름
```cpp
// ApiBuffer 클래스에 추가
bool IsDeviceValid()
{
    return WMX3Broker_ApiBuffer_IsDeviceValid() != 0;
}
```

#### 4. AdvancedMotionApi_Sim.h ✅ 올바름
```cpp
// AdvSync 클래스 전체 추가
class AdvancedMotion;

class AdvSync
{
private:
    AdvancedMotion *amApi;

public:
    AdvSync(AdvancedMotion *api) : amApi(api) {}

    bool IsDeviceValid()
    {
        return WMX3Broker_AdvancedMotion_AdvSync_IsDeviceValid() != 0;
    }
};

// AdvancedMotion 클래스 업데이트
class AdvancedMotion
{
public:
    AdvSync *advSync;

    AdvancedMotion() : advSync(new AdvSync(this)) {}
    ~AdvancedMotion() { delete advSync; }
    // ...
};
```

#### 5. CoreMotionApi_Sim.h ✅ 올바름
```cpp
// EmergencyStopParam 구조체 확장
class EmergencyStopParam
{
public:
    EmergencyStopParam() { memset(this, 0, sizeof(EmergencyStopParam)); }

    double eStopDec[constants::maxAxes];
    bool enableEStopSignal;
    int eStopSignalSource;
    int eStopSignalLevel;
    bool invertEStopSignalPolarity;
    unsigned int eStopSignalByteAddress;
    unsigned char eStopSignalBitAddress;
    bool enableEStopStatusSignal;
    int eStopStatusSignalDestination;
    bool invertEStopStatusSignalPolarity;
    unsigned int eStopStatusSignalByteAddress;
    unsigned char eStopStatusSignalBitAddress;
    int eStopLevel1Type;
};

// Config 클래스에 메서드 추가
long SetEmergencyStopParam(EmergencyStopParam *pParam, EmergencyStopParam *pParamError = NULL)
{
    return WMX3Broker_Config_SetEmergencyStopParam(pParam);
}

long GetEmergencyStopParam(EmergencyStopParam *pParam)
{
    return WMX3Broker_Config_GetEmergencyStopParam(pParam);
}
```

### 첫 번째 빌드 오류
```
error C2757: 'Config': 이름이 같은 기호가 이미 있으므로 이 이름을 네임스페이스 이름으로 사용할 수 없습니다.
```

**원인**: ConfigBroker.h에서 `wmx3Api::Config::EmergencyStopParam`를 forward declaration으로 선언하려 했으나 Config가 이미 네임스페이스로 존재

**해결**: Forward declaration 대신 `#include "CoreMotionApi.h"` 사용

### 빌드 성공
- 경고 42개 (외부 라이브러리 PDB 파일 누락 - 무해함)
- 오류 0개

## 질문 3: 아키텍처 위반 지적

```
WMX3 API 추가 시, WMX1.5 호환 API 를 만드는게 아니야, C API 호환 인터페이스를 만드는거지. 개념을 혼동하지 않았으면 해
```

```
현재 프로젝트에서는, 사용자 App 에서 사용하는 API를 Broking 하기 위한 Wrapper 클래스가 적용되고 있어
사용자 층은 구분되어 있어(WMX1.5 API 사용자, WMX3 API 사용자)

WMX3는 단순히 C API 호환 레이어 구성이야
WMX1.5는 WMX3로 매핑하기 위한 레이어가 추가되어 있어

중복 구현은 가능하면 줄여야 하지만, 두 그룹의 기능이 섞이지 않도록 구현에 주의해야 해
```

```
GetEmergencyStopParam과 SetEmergencyStopParam은 WMX3 에서 제공되는 API야. WMX1.5 사용자는 이 기능이 없어. 따라서 ConfigBroker에서 제거하고, WMX3BrokerC에만 남겨야 해
```

## 답변 3: 수정 계획 수립 및 실행

### 문제 인식
ConfigBroker(WMX 1.5 레이어)에 WMX3 전용 API인 EmergencyStopParam을 추가한 것은 아키텍처 원칙 위반

### 수정 작업

#### ConfigBroker.h 수정
제거 항목:
- `#include "CoreMotionApi.h"` (라인 10-11)
- EmergencyStopParam 메서드 선언 2줄 (라인 61-63)

#### ConfigBroker.cpp 수정
제거 항목:
- `GetEmergencyStopParam()` 구현 (라인 404-412)
- `SetEmergencyStopParam()` 구현 (라인 414-422)

#### 유지할 파일들 (올바른 구현)
- ✅ **broker/WMX3BrokerC.h/cpp**: WMX3 C API 레이어 - 4개 함수 유지
- ✅ **include/WMX3/ApiBufferApi_Sim.h**: WMX3 사용자용 C++ 래퍼
- ✅ **include/WMX3/AdvancedMotionApi_Sim.h**: WMX3 사용자용 AdvSync 클래스
- ✅ **include/WMX3/CoreMotionApi_Sim.h**: WMX3 사용자용 EmergencyStopParam 구조체 및 메서드

### 최종 빌드
```bash
msbuild broker\WMXBroker.vcxproj -p:Configuration=Release -p:Platform=x64 -p:WMXVersion=WMX36u1_Win
```

**결과**:
- ✅ 빌드 성공
- ⏱️ 경과 시간: 3.96초
- ⚠️ 경고 0개
- ❌ 오류 0개

## 최종 아키텍처

### WMX 1.5 사용자 경로
```
[WMX 1.5 App]
    → ConfigBroker (WMX 1.5 타입, WMX3로 매핑)
        → WMX3 SDK
```
- EmergencyStopParam 접근 불가 (WMX 1.5에 없는 기능)
- ConfigBroker는 순수 WMX 1.5 호환 레이어로 유지

### WMX3 사용자 경로
```
[WMX3 App]
    → WMX3BrokerC (C API, WMX3 타입 그대로, 매핑 없음)
        → WMX3 SDK

또는

[WMX3 App]
    → *_Sim.h (C++ 래퍼)
        → WMX3BrokerC
            → WMX3 SDK
```
- EmergencyStopParam 접근 가능
- IsDeviceValid 접근 가능
- 모든 WMX3 기능 사용 가능

## 수정된 파일 목록

### 최종 수정 파일 (올바른 구현)
1. **broker/WMX3BrokerC.h** - 4개 C API 함수 선언 추가 ✅
2. **broker/WMX3BrokerC.cpp** - 4개 C API 함수 구현 추가 ✅
3. **broker/ConfigBroker.h** - 잘못 추가된 EmergencyStopParam 제거 ✅
4. **broker/ConfigBroker.cpp** - 잘못 추가된 EmergencyStopParam 구현 제거 ✅
5. **include/WMX3/ApiBufferApi_Sim.h** - IsDeviceValid 메서드 추가 ✅
6. **include/WMX3/AdvancedMotionApi_Sim.h** - AdvSync 클래스 추가 ✅
7. **include/WMX3/CoreMotionApi_Sim.h** - EmergencyStopParam 구조체 확장 및 메서드 추가 ✅

## 학습한 내용

### 아키텍처 레이어 구분
1. **ConfigBroker** (WMX 1.5 레이어)
   - WMX 1.5에 존재하는 기능만 구현
   - WMX 1.5 타입 ↔ WMX3 타입 매핑 수행
   - WMX3 전용 기능은 추가하지 않음

2. **WMX3BrokerC** (WMX3 C API 레이어)
   - WMX3 SDK 함수를 C API로 노출
   - 타입 매핑 없음, WMX3 타입 그대로 사용
   - 모든 WMX3 기능 사용 가능

3. **Sim 래퍼** (*_Sim.h)
   - WMX3BrokerC의 C API를 C++ 래퍼로 제공
   - WMX3 사용자 편의성 향상
   - 헤더 전용 구현

### 사용자 그룹 분리의 중요성
- WMX 1.5 사용자와 WMX3 사용자는 서로 다른 기능 집합 사용
- 두 그룹의 API를 명확히 분리해야 함
- ConfigBroker에 WMX3 전용 기능 추가 시 WMX 1.5 사용자에게 혼란 발생 가능

## 결론

WMX3 SDK의 4개 API를 성공적으로 WMXBroker에 추가했습니다. 초기 구현 시 아키텍처 원칙을 완전히 이해하지 못해 ConfigBroker에 WMX3 전용 코드를 추가하는 실수를 했으나, 사용자의 명확한 피드백을 통해 올바른 아키텍처를 이해하고 수정을 완료했습니다.

최종적으로:
- ✅ WMX3BrokerC에만 4개 C API 함수 추가
- ✅ Sim 래퍼 파일들에 C++ 인터페이스 추가
- ✅ ConfigBroker에서 잘못 추가된 WMX3 코드 제거
- ✅ 빌드 성공 (오류 0개)
- ✅ 아키텍처 원칙 준수 (두 사용자 그룹 분리)
