# WMX SDK Files

이 폴더에는 WMXBroker 빌드에 필요한 WMX SDK 파일들이 포함됩니다.

## 폴더 구조

```
sdk/
├── WMX15/Include/           # WMX 1.5 타입 정의 (공통)
├── WMX34u4_Win/             # WMX 3.4u4 Windows
│   ├── Include/
│   └── Lib/
├── WMX34u4_RTX/             # WMX 3.4u4 RTX
│   ├── Include/
│   └── Lib/
├── WMX36u1_Win/             # WMX 3.6u1 Windows
│   ├── Include/
│   └── Lib/
└── WMX36u1_RTX/             # WMX 3.6u1 RTX
    ├── Include/
    └── Lib/
```

## 파일 복사 가이드

### WMX 1.5
소스: `C:\Program Files\SoftServo\WMX1.5\Include\`
대상: `sdk\WMX15\Include\`

복사할 파일:
- wmxapi_type.h

### WMX 3.x (각 버전별로 동일)
소스: `C:\Program Files\SoftServo\WMX3\`
대상: `sdk\WMX3x_xxx\`

**Include 폴더** - 복사할 헤더 파일:
- WMX3Api.h
- CoreMotionApi.h
- AdvancedMotionApi.h
- IOApi.h
- EcApi.h
- 기타 의존 헤더들

**Lib 폴더** - 복사할 라이브러리 파일:
- WMX3Api.lib
- CoreMotionApi.lib
- AdvancedMotionApi.lib
- IOApi.lib
- EcApi.lib
- IMDll.lib

## 버전별 설치 및 복사 절차

1. WMX 3.4u4 Windows 인스톨러로 설치
2. `C:\Program Files\SoftServo\WMX3\` 에서 `sdk\WMX34u4_Win\`으로 복사
3. WMX 3.4u4 RTX 인스톨러로 재설치
4. `C:\Program Files\SoftServo\WMX3\` 에서 `sdk\WMX34u4_RTX\`으로 복사
5. WMX 3.6u1 버전들도 동일하게 반복

## 빌드 명령

```bash
# 특정 버전 빌드
msbuild broker\WMXBroker.vcxproj /p:Configuration=Release /p:Platform=x64 /p:WMXVersion=WMX34u4_Win

# 전체 버전 빌드
build_all.bat
```
