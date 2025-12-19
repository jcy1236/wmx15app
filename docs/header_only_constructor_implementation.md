# Header-Only 라이브러리에서 생성자 구현 방법

날짜: 2025-12-19

## 문제 상황

사용자 앱에서 `CoreMotionApi_Sim.h`를 사용하여 빌드 시, 다음과 같은 링크 에러 발생:

```
확인할 수 없는 외부 참조입니다.
public: __cdecl wmx3Api::Config::FeedbackParam::FeedbackParam(void)
public: __cdecl wmx3Api::Config::HomeParam::HomeParam(void)
public: __cdecl wmx3Api::Config::LimitParam::LimitParam(void)
```

## 원인 분석

### 원본 SDK 구조
```cpp
// CoreMotionApi.h (원본 SDK)
class FeedbackParam
{
public:
    FeedbackParam();  // 선언만 존재
    double inPosWidth;
    // ...
};
```

원본 SDK에서는 생성자가 **선언만** 되어 있고, 실제 구현은 `CoreMotionApi.lib`에 포함되어 있습니다.

### Sim 헤더의 특성

`*_Sim.h` 파일들은 **Header-Only 라이브러리**입니다:
- `.lib` 파일 없이 헤더 파일만으로 동작
- 모든 함수/생성자는 헤더 내에서 **인라인 구현** 필요
- 구현이 없는 선언만 있으면 링크 에러 발생

## 해결 방법

### 잘못된 코드 (링크 에러 발생)
```cpp
class FeedbackParam
{
public:
    FeedbackParam();  // 선언만 - 링크 에러!
    double inPosWidth;
};
```

### 올바른 코드 (인라인 구현)
```cpp
class FeedbackParam
{
public:
    FeedbackParam()
    {
        memset(this, 0, sizeof(FeedbackParam));
        velocityMonitorSource = VelocityMonitorSource::Command;
    }
    double inPosWidth;
};
```

## 구현 패턴

### 기본 패턴: memset + enum 초기화

```cpp
class MyClass
{
public:
    MyClass()
    {
        // 1. 모든 멤버를 0으로 초기화
        memset(this, 0, sizeof(MyClass));

        // 2. enum 멤버는 명시적으로 기본값 설정
        myEnumMember = MyEnum::DefaultValue;
    }

    int numericMember;        // memset으로 0 초기화됨
    double floatMember;       // memset으로 0.0 초기화됨
    MyEnum::T myEnumMember;   // 명시적 초기화 필요
};
```

### 주의사항

1. **memset 사용 조건**: POD(Plain Old Data) 타입에만 사용
   - 가상 함수가 없는 클래스
   - 포인터나 참조 멤버 없음
   - 표준 레이아웃 보장

2. **enum 초기화 필수**: memset은 0으로 설정하지만, enum의 첫 번째 값이 0이 아닐 수 있음

3. **배열 멤버**: memset으로 자동 0 초기화됨

## 실제 수정 사례

### FeedbackParam (CoreMotionApi_Sim.h:851)
```cpp
FeedbackParam()
{
    memset(this, 0, sizeof(FeedbackParam));
    // velocityMonitorSource defaults to UseVelocityFeedback(0) via memset
}
```

### HomeParam (CoreMotionApi_Sim.h:910)
```cpp
HomeParam()
{
    memset(this, 0, sizeof(HomeParam));
    // homeType defaults to CurrentPos(0) via memset
    // homeDirection defaults to Positive(0) via memset
}
```

### LimitParam (CoreMotionApi_Sim.h:983)
```cpp
LimitParam()
{
    memset(this, 0, sizeof(LimitParam));
    // All LimitSwitchType members default to None(0) via memset
}
```

### MotionParam (CoreMotionApi_Sim.h:1069)
```cpp
MotionParam()
{
    memset(this, 0, sizeof(MotionParam));
    // All enum members default to first value (0) via memset:
    // ProhibitOvertravelType::Disabled, LinearIntplOverrideType::Smoothing,
    // CircularIntplOverrideType::Blending, LinearIntplProfileCalcMode::AxisLimit
}
```

### AxisParam (CoreMotionApi_Sim.h:1107)
```cpp
AxisParam()
{
    memset(this, 0, sizeof(AxisParam));
    // AxisCommandMode::Position(0) is default via memset
}
```

## 기존 코드베이스의 올바른 예시

```cpp
// CoreMotionApi_Sim.h - CoreMotionAxisStatus
CoreMotionAxisStatus()
{
    memset(this, 0, sizeof(CoreMotionAxisStatus));
    opState = OperationState::Idle;
    detailOpState = DetailOperationState::Idle;
}

// EcApi_Sim.h - EcMasterInfo
EcMasterInfo()
{
    memset(this, 0, sizeof(EcMasterInfo));
    state = EcStateMachine::None;
    mode = EcMasterMode::CyclicMode;
}
```

## 새 클래스 추가 시 체크리스트

1. [ ] 생성자가 선언만 있는지 확인
2. [ ] 인라인 구현으로 변경
3. [ ] `memset(this, 0, sizeof(ClassName))` 추가
4. [ ] enum 멤버들의 기본값 명시적 초기화
5. [ ] 빌드 테스트로 링크 에러 없음 확인

## 관련 파일

- `include/WMX3/CoreMotionApi_Sim.h` - CoreMotion 관련 타입 정의
- `include/WMX3/EcApi_Sim.h` - EtherCAT 관련 타입 정의
- `include/WMX3/EventApi_Sim.h` - Event 관련 타입 정의
- `include/WMX3/LogApi_Sim.h` - Log 관련 타입 정의
