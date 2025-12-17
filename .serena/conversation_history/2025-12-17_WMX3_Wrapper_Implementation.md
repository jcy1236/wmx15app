# WMX3 API Wrapper 구현 대화 이력

**날짜**: 2025-12-17
**주제**: WMX3 Native API Wrapper 구현

---

## 요약

WMX3.x 사용자가 WMXBroker DLL을 통해 WMX3 엔진에 접근할 수 있는 wrapper class를 구현했습니다.

### 구현 목표
- WMX3 네이티브 API와 **동일한 인터페이스** 제공
- 헤더 파일만 교체하면 기존 WMX3 코드가 그대로 동작
- **VS2012 + 최신 버전** 모두 컴파일 가능
- **기존 WMXBroker 기능 훼손 없이** 추가만 진행

### 핵심 설계 원칙: Adapter 패턴
WMXBroker는 단순한 pass-through가 아니라 **Adapter 레이어**입니다:
- 일부 API: WMX3 원본 API로 직접 연결
- 일부 API: 대체 시스템/커스텀 구현으로 연결 가능
- 예시: `WaitAxis`는 WMX3에 직접 대응 없음 → polling으로 자체 구현

---

## 생성된 파일

### 1. C API Layer (broker/ 폴더)

| 파일 | 설명 |
|------|------|
| `WMX3BrokerC.h` | WMX3 전용 C API 선언 (~90개 함수) |
| `WMX3BrokerC.cpp` | WMX3 전용 C API 구현 (Adapter 레이어) |

### 2. Header-only Wrapper (include/ 폴더)

| 파일 | 설명 |
|------|------|
| `WMX3Api_Sim.h` | 메인 wrapper - wmx3Api namespace, 기본 클래스/열거형 |
| `CoreMotion_Sim.h` | CoreMotion wrapper (AxisControl, Motion, Home, Velocity, Torque, Config) |
| `Io_Sim.h` | Io wrapper (Digital/Analog I/O) |
| `Ecat_Sim.h` | Ecat wrapper (SDO, PDO, Slave I/O, Master Info) |

### 3. 수정된 파일

| 파일 | 수정 내용 |
|------|---------|
| `WMXBroker.vcxproj` | WMX3BrokerC.h/cpp 추가 |
| `WMXBroker.def` | WMX3Broker_* 함수들 export 추가 (@300 ~ @465) |

---

## API 구조

### 아키텍처
```
[WMX3 App Code] --> [WMX3Api_Sim.h] --> [WMX3BrokerC API] --> [WMXBroker.dll] --> [WMX3 Engine]
                    (Header-only)       (C API)               (공유 Context)
                                                                    ↓
                                                          [대체 시스템] (향후)
```

### 주요 클래스 구조
```cpp
wmx3Api::WMX3Api          // 시스템 API (CreateDevice, StartCommunication 등)
wmx3Api::CoreMotion       // 축 제어
    ├── AxisControl*      // 서보 On/Off, 알람 클리어
    ├── Motion*           // 위치 명령 (StartPos, StartMov, StartJog)
    ├── Home*             // 원점 복귀
    ├── Velocity*         // 속도 제어
    ├── Torque*           // 토크 제어
    └── Config*           // 파라미터 설정
wmx3Api::Io               // I/O 제어
wmx3Api::ecApi::Ecat      // EtherCAT 제어
```

---

## 사용 예시

### Before (WMX3 네이티브)
```cpp
#include "WMX3Api.h"
#include "CoreMotionApi.h"

wmx3Api::WMX3Api wmx3;
wmx3.CreateDevice("C:\\WMX3");
wmx3.StartCommunication();

wmx3Api::CoreMotion cm(&wmx3);
cm.axisControl->SetServoOn(0, 1);
```

### After (WMXBroker Wrapper)
```cpp
#include "WMX3Api_Sim.h"  // 헤더만 교체!

wmx3Api::WMX3Api wmx3;
wmx3.CreateDevice("C:\\WMX3");  // 동일한 코드
wmx3.StartCommunication();

wmx3Api::CoreMotion cm(&wmx3);
cm.axisControl->SetServoOn(0, 1);  // 동일한 코드
```

---

## 빌드 결과

```
빌드했습니다.
    경고 0개
    오류 0개
경과 시간: 00:00:05.99
```

출력 파일: `x64\Release_WMX34u4_Win\WMXBroker.dll`

---

## VS2012 호환성 주의사항

코드에서 다음 사항을 준수했습니다:
- `nullptr` 대신 `NULL` 사용
- `auto` 키워드 사용 제한
- Range-based for loop 사용 제한
- `constexpr`, `override`, `final` 키워드 사용 불가
- `extern "C"` 로 C API name mangling 방지

---

## 향후 확장 포인트

1. **대체 시스템 연결**: Broker 클래스에서 WMX3 대신 대체 시스템으로 분기 가능
2. **추가 API**: 필요에 따라 WMX3BrokerC에 함수 추가 가능
3. **Callback 지원**: 현재 동기 API만 구현, 비동기 callback 추가 가능
