# g_wmxlib 초기화 문제 해결 - WMXBroker_Initialize/Uninitialize API 추가

날짜: 2025-12-08

## 문제 요약

사용자가 `new WMXLIB()`를 호출한 후 `GetActiveDeviceList()`를 호출하면 실패합니다.
- 사용자 코드의 `new WMXLIB()`는 **WMXBrokerClient.h의 WMXLIB** (헤더 온리 래퍼)
- DLL 내부의 `g_wmxlib`은 기존에는 `CreateDevice()`에서만 생성됨
- 따라서 `CreateDevice()` 전에 호출되는 API는 모두 실패

## 핵심 제약 조건

1. **사용자 코드 변경 불가**: `m_pWMXLIB = new WMXLIB(); m_pWMXLIB->CreateDevice();` 패턴 유지
2. **ABI 호환성**: DLL에서 WMXLIB 포인터를 직접 반환하면 안됨
3. **완전한 C API 래퍼**: WMXBrokerClient.h는 순수 C API 호출만 해야 함

## 이전 해결 시도 (불완전)

`WMXBroker_SetGlobalInstance` / `WMXBroker_ClearGlobalInstance` 내부 함수를 추가하여 WMXBroker.cpp의 생성자에서 호출하도록 했으나, 사용자의 `new WMXLIB()`는 WMXBrokerClient.h의 생성자를 호출하므로 의미가 없었음.

## 최종 해결 방법: WMXBroker_Initialize/Uninitialize C API 추가

### 1. WMXBrokerC.h 수정
```cpp
// System APIs에 추가
WMXBROKER_CAPI long __stdcall WMXBroker_Initialize(void);
WMXBROKER_CAPI long __stdcall WMXBroker_Uninitialize(void);
```

### 2. WMXBrokerC.cpp 수정
```cpp
// 참조 카운트 추가
static int g_refCount = 0;

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Initialize(void)
{
    if (g_wmxlib == nullptr) {
        g_wmxlib = new wmxAPI::WMXLIB();
    }
    g_refCount++;
    return 0;
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Uninitialize(void)
{
    if (g_refCount > 0) {
        g_refCount--;
    }
    // g_wmxlib는 CloseDevice에서 삭제
    return 0;
}
```

### 3. WMXBrokerClient.h 수정
```cpp
WMXLIB() {
    WMXBroker_Initialize();  // DLL 내부 g_wmxlib 생성
    // 래퍼 객체들 생성
}

~WMXLIB() {
    // 래퍼 객체들 정리
    WMXBroker_Uninitialize();
}
```

### 4. 기존 내부 함수 제거
- `WMXBroker_SetGlobalInstance` / `WMXBroker_ClearGlobalInstance` 제거
- WMXBroker.cpp의 생성자/소멸자에서 호출 제거

## 수정된 파일

| 파일 | 수정 내용 |
|------|----------|
| broker/WMXBrokerC.h | Initialize/Uninitialize 선언 추가, 내부 함수 제거 |
| broker/WMXBrokerC.cpp | Initialize/Uninitialize 구현, 내부 함수 제거 |
| broker/WMXBroker.cpp | 생성자/소멸자에서 내부 함수 호출 제거 |
| include/WMXBrokerClient.h | 생성자/소멸자에서 Initialize/Uninitialize 호출 |

## 예상 동작 흐름

```
사용자 코드:
1. new WMXLIB()          → WMXBroker_Initialize() 호출 → DLL 내부 g_wmxlib 생성
2. GetActiveDeviceList() → g_wmxlib 유효, 성공!
3. CreateDevice()        → g_wmxlib 이미 존재, CreateDevice 수행
4. CloseDevice()         → 정리
5. delete WMXLIB()       → WMXBroker_Uninitialize() 호출
```

## Git Commit

```
commit 8f3125b
Add Initialize/Uninitialize C APIs to fix g_wmxlib initialization

Replace internal WMXBroker_SetGlobalInstance/ClearGlobalInstance with
exported WMXBroker_Initialize/Uninitialize C APIs. This allows user code
using WMXBrokerClient.h (new WMXLIB()) to properly initialize the DLL's
internal g_wmxlib singleton before calling APIs like GetActiveDeviceList.
```
