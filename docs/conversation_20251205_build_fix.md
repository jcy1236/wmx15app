# 대화 이력 - 빌드 오류 수정 (2025-12-05)

## 작업 요약
이전 세션에서 추가된 새 Broker 파일들의 빌드 오류를 수정하여 성공적으로 빌드 완료.

## 수정된 파일

### 1. TorqueControlBroker.cpp
**문제**: `axisSelection.axisSelection[i]` - WMX3 AxisSelection 구조체에 `axisSelection` 멤버가 없음

**해결**: WMX3 AxisSelection은 `axis[]` 배열과 `axisCount`를 사용
```cpp
// Before (오류)
wmx3Api::AxisSelection axisSelection;
for (int i = firstAxis; i <= lastAxis; i++)
{
    axisSelection.axisSelection[i] = 1;
}

// After (수정)
wmx3Api::AxisSelection axisSelection;
axisSelection.axisCount = 0;
for (int i = firstAxis; i <= lastAxis; i++)
{
    axisSelection.axis[axisSelection.axisCount++] = i;
}
```

### 2. ExtVelocity2Broker.cpp
**문제 1**: `SetupSCurve`에 jerkRatio 파라미터 전달 - WMX3 SetupSCurve는 jerkRatio를 받지 않음

**해결**: `SetupJerkRatio` 사용
```cpp
// Before (오류)
velCmd.profile = wmx3Api::Profile::SetupSCurve(velocity, acc, dec, jerkAccRatio, jerkDecRatio, 0, 0);

// After (수정)
velCmd.profile = wmx3Api::Profile::SetupJerkRatio(velocity, acc, dec, jerkAccRatio, jerkDecRatio, 0, 0);
```

**문제 2**: `SetupTrapezoid` - 존재하지 않는 메서드명

**해결**: `SetupTrapezoidal` 사용
```cpp
// Before (오류)
velCmd.profile = wmx3Api::Profile::SetupTrapezoid(velocity, acc, dec, 0, 0);

// After (수정)
velCmd.profile = wmx3Api::Profile::SetupTrapezoidal(velocity, acc, dec, 0, 0);
```

### 3. ConfigBroker.cpp
**문제**: `SoftPLSPos`/`SoftNLSPos` - WMX 1.5 WMX_LIMIT_PARAM 구조체에 해당 멤버가 없음

**해결**: 실제 WMX 1.5 필드명 `SoftLimitPPos`/`SoftLimitNPos` 사용
```cpp
// Before (오류)
pParam->SoftPLSPos = wmx3Param.softLimitPositivePos;
pParam->SoftNLSPos = wmx3Param.softLimitNegativePos;

// After (수정)
pParam->SoftLimitPPos = wmx3Param.softLimitPositivePos;
pParam->SoftLimitNPos = wmx3Param.softLimitNegativePos;
```

## WMX3 Profile 메서드 정리
WMX3Api.h에서 확인한 Profile 클래스 Setup 메서드들:
- `SetupTrapezoidal(velocity, acc, dec, startingVelocity, endVelocity)`
- `SetupSCurve(velocity, acc, dec, startingVelocity, endVelocity)` - jerkRatio 없음
- `SetupJerkRatio(velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity)` - jerkRatio 포함
- `SetupJerkLimited(velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity)` - jerk 값 직접 지정

## WMX 1.5 WMX_LIMIT_PARAM 구조체 필드 (wmxapi_type.h)
```c
typedef struct{
    WMX_LIMITSWITCH_TYPE LSType;
    WMX_LIMITSWITCH_TYPE PLSType;
    WMX_LIMITSWITCH_TYPE NLSType;
    unsigned char LSPol;
    WMX_LIMITSWITCH_TYPE NearLSType;
    WMX_LIMITSWITCH_TYPE NearPLSType;
    WMX_LIMITSWITCH_TYPE NearNLSType;
    // ... 다른 Near/Ext 필드들 ...
    WMX_LIMITSWITCH_TYPE SoftLimitType;
    WMX_LIMITSWITCH_TYPE PSoftLimitType;
    WMX_LIMITSWITCH_TYPE NSoftLimitType;
    double SoftLimitPPos;    // 실제 필드명
    double SoftLimitNPos;    // 실제 필드명
    double LSDec;
    double LSSlowDec;
    unsigned char AllLSDuringHoming;
}WMX_LIMIT_PARAM;
```

## 빌드 결과
```
WMXBroker.vcxproj -> c:\Users\jcy1236\source\repos\wmx15app\x64\Release\WMXBroker.dll
wmx15app.vcxproj -> c:\Users\jcy1236\source\repos\wmx15app\x64\Release\wmx15app.exe
```

빌드 성공! (PDB 경고만 발생 - WMX3 라이브러리의 디버그 심볼 없음으로 인한 것으로 기능에는 영향 없음)

## 완료된 작업 목록
1. ✅ 기존 네임스페이스 PascalCase 변경 (BasicMotion, ExtMotion1, ExtMotion2, ExtList2)
2. ✅ AxisControlBroker 구현
3. ✅ HomeBroker 구현
4. ✅ BasicVelocityBroker 구현
5. ✅ TorqueControlBroker 구현
6. ✅ ExtVelocity2Broker 구현
7. ✅ ConfigBroker 구현
8. ✅ WMXBroker.h 타입 정의 추가 및 vcxproj 업데이트
9. ✅ 빌드 및 테스트
