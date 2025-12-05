# 대화 이력: 4개 새 API 추가 (2025-12-05)

## 사용자 요청

4개의 새 API를 WMX 1.5 Broker에 추가 요청:

1. **TimeStopAxis** (basicMotion namespace) - WMXLIB.h line 659
2. **StartPos** (7 params, basicMotion namespace) - WMXLIB.h lines 526-527
3. **StopJerkJogAtPos** (extMotion2 namespace) - WMXLIB.h lines 1362-1363
4. **StartJerkCoordinatedPos** (extMotion2 namespace) - WMXLIB.h line 1357

## 수정된 파일

### 1. BasicMotionBroker.h/cpp
- `TimeStopAxis(int axis, double time)` 추가 - WMX3 `ExecTimedStop` 매핑
- `StartPos(short axis, double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity)` 추가 - 7 params 버전
- `StartMov()` 7 params 버전도 함께 추가

### 2. ExtMotion2Broker.h/cpp
- `StopJerkJogAtPos(short axis, WMX_PROFILE_TYPE profile, double target, double dec, double jerkDecRatio)` 추가
- `StartJerkCoordinatedPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio)` 추가

### 3. WMXBrokerC.h/cpp
C API 추가:
- `WMXBroker_BasicMotion_TimeStopAxis(int axis, double time)`
- `WMXBroker_BasicMotion_StartPosEx(short axis, double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity)`
- `WMXBroker_BasicMotion_StartMovEx(short axis, double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity)`
- `WMXBroker_ExtMotion2_StopJerkJogAtPos(short axis, int profile, double target, double dec, double jerkDecRatio)`
- `WMXBroker_ExtMotion2_StartJerkCoordinatedPos(short axis, int profile, double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio)`

### 4. WMXBrokerClient.h
VS2012 호환 wrapper 함수 추가 (BasicMotion, ExtMotion2 클래스)

### 5. WMXBroker.h/cpp
- `wmx3Api::AdvancedMotion* advancedMotion` 멤버 추가
- `GetAdvancedMotion()` 접근자 추가
- CreateDevice에서 AdvancedMotion 초기화
- CloseDevice에서 정리

### 6. WMX3ContextManager.h/cpp
- `wmx3Api::AdvancedMotion* m_advancedMotion` 멤버 추가
- `GetAdvancedMotion()` 접근자 추가
- CreateDeviceInternal()에서 AdvancedMotion 생성
- CloseDeviceInternal()에서 정리

### 7. WMXBroker.vcxproj
- Debug/Release 모두 `AdvancedMotionApi.lib` 링커 의존성 추가

## WMX3 API 구조

### AdvancedMotion 클래스 구조
```cpp
namespace wmx3Api {
    class AdvMotion {
    public:
        class CoordinatedPosCommand {
            PosCommand posCommand;
            int axis2;
            double axis2Target;
            double axis2SmoothRatio;
        };

        WMX3APIFUNC StartCoordinatedPos(CoordinatedPosCommand *pPosCommand);
    };

    class AdvancedMotion {
    public:
        AdvMotion *advMotion;  // 주의: motion이 아닌 advMotion
        AdvVelocity *advVelocity;
        AdvSync *advSync;
    };
}
```

접근 패턴: `advancedMotion->advMotion->StartCoordinatedPos(&coordCmd)`

## 빌드 결과

✅ 빌드 성공 (Release x64)
- WMXBroker.dll 생성
- wmx15app.exe 생성

## 주의사항

1. `CoordinatedPosCommand`는 `wmx3Api::AdvMotion::CoordinatedPosCommand`에 있음 (Motion 아님)
2. AdvancedMotion 클래스의 motion 멤버는 `advMotion`임 (`motion` 아님)
3. AdvancedMotionApi.lib를 링커에 추가해야 함
