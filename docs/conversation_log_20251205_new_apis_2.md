# 대화 이력: 4개 새 API 추가 (2025-12-05) - Part 2

## 사용자 요청

이전 세션에서 계획 승인 후 구현 요청:

1. **StopAxis(WMX_AXIS_SELECTION*)** - basicMotion namespace (WMXLIB.h L656)
2. **QStopAxis(WMX_AXIS_SELECTION*)** - basicMotion namespace (WMXLIB.h L658)
3. **TimeStopAxis(WMX_AXIS_SELECTION*, double)** - basicMotion namespace (WMXLIB.h L660)
4. **ListJerkCoordinatedPos** - extList2 namespace (WMXLIB.h L1824)

## 수정된 파일

### 1. BasicMotionBroker.h
AxisSelection 기반 Stop API 선언 추가:
```cpp
WMXAPIFUNC StopAxis(WMX_AXIS_SELECTION* axis_selection);
WMXAPIFUNC QStopAxis(WMX_AXIS_SELECTION* axis_selection);
WMXAPIFUNC TimeStopAxis(WMX_AXIS_SELECTION* axis_selection, double time);
```

### 2. BasicMotionBroker.cpp
WMX 1.5 WMX_AXIS_SELECTION을 WMX3 AxisSelection으로 변환하는 구현 추가:
```cpp
WMXAPIFUNC BasicMotion::StopAxis(WMX_AXIS_SELECTION* axis_selection)
{
    // Convert WMX 1.5 WMX_AXIS_SELECTION to WMX3 AxisSelection
    wmx3Api::AxisSelection wmx3AxisSel;
    wmx3AxisSel.axisCount = axis_selection->axisCount;
    for (int i = 0; i < axis_selection->axisCount && i < 64; i++) {
        wmx3AxisSel.axis[i] = axis_selection->axis[i];
    }
    return coreMotion->motion->Stop(&wmx3AxisSel);
}
```

### 3. ExtList2Broker.h/cpp
ListJerkCoordinatedPos 스텁 추가 (WMX3에 List API 없음):
```cpp
WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile,
    double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio);
// Returns NOT_IMPLEMENTED (-100)
```

### 4. WMXBrokerC.h
C API 선언 추가:
```cpp
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StopAxisSelection(WMX_AXIS_SELECTION* axis_selection);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_QStopAxisSelection(WMX_AXIS_SELECTION* axis_selection);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_TimeStopAxisSelection(WMX_AXIS_SELECTION* axis_selection, double time);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkCoordinatedPos(...);
```

### 5. WMXBrokerC.cpp
C API 구현 추가

### 6. WMXBrokerClient.h
- WMX_AXIS_SELECTION 별도 정의 제거 (wmxapi_type.h에서 이미 정의됨)
- basicMotion::BasicMotion 클래스에 오버로드 추가:
  - `StopAxis(WMX_AXIS_SELECTION*)`
  - `QStopAxis(WMX_AXIS_SELECTION*)`
  - `TimeStopAxis(WMX_AXIS_SELECTION*, double)`
- extList2::ExtList2 클래스에 추가:
  - `ListJerkCoordinatedPos(...)`

## WMX3 API 매핑

### AxisSelection 기반 Stop APIs
| WMX 1.5 | WMX3 |
|---------|------|
| `StopAxis(WMX_AXIS_SELECTION*)` | `motion->Stop(AxisSelection*)` |
| `QStopAxis(WMX_AXIS_SELECTION*)` | `motion->ExecQuickStop(AxisSelection*)` |
| `TimeStopAxis(WMX_AXIS_SELECTION*, time)` | `motion->ExecTimedStop(AxisSelection*, time)` |

### 구조체 변환
```
WMX 1.5 WMX_AXIS_SELECTION:
  short axisCount;
  short axis[MAX_ALLAXES];  // MAX_ALLAXES = 64

WMX3 AxisSelection:
  int axisCount;
  int axis[constants::maxAxes];  // maxAxes = 64
```

## 빌드 결과

✅ 빌드 성공 (Release x64)
- WMXBroker.dll 생성
- wmx15app.exe 생성

## 주의사항

1. WMX_AXIS_SELECTION은 wmxapi_type.h에서 정의됨 (WMXBrokerC.h가 include)
2. WMXBrokerClient.h에서 별도 정의하면 타입 충돌 발생
3. ListJerkCoordinatedPos는 NOT_IMPLEMENTED 반환 (WMX3에 List API 없음)
