# 대화 기록: 다중 버전 빌드 시스템 구축

**날짜**: 2025-12-12

## 요청 사항

WMXBroker를 다양한 WMX 버전에 맞춰 빌드하고 배포할 수 있는 시스템 구축:
- WMX3.4u4 Windows
- WMX3.4u4 RTX
- WMX3.6u1 Windows
- WMX3.6u1 RTX

사용자 확인 사항:
- Windows/RTX는 동일 폴더에 설치됨 (인스톨러 선택으로 구분)
- WMX3.4u4와 WMX3.6u1 API 시그니처 차이 거의 없음
- SDK 파일을 git에 포함 (파일 크기 작음)

## 구현 내용

### 1. SDK 폴더 구조 생성

```
sdk/
├── README.md                 # 파일 복사 가이드
├── WMX15/Include/           # WMX 1.5 타입 정의 (공통)
├── WMX34u4_Win/Include,Lib/ # WMX 3.4u4 Windows
├── WMX34u4_RTX/Include,Lib/ # WMX 3.4u4 RTX
├── WMX36u1_Win/Include,Lib/ # WMX 3.6u1 Windows
└── WMX36u1_RTX/Include,Lib/ # WMX 3.6u1 RTX
```

### 2. MSBuild 속성 시트 파일 생성

```
broker/props/
├── WMX_Common.props     # 공통 설정 (WMX15 Include 경로)
├── WMX34u4_Win.props    # WMX3.4u4 Windows 설정
├── WMX34u4_RTX.props    # WMX3.4u4 RTX 설정
├── WMX36u1_Win.props    # WMX3.6u1 Windows 설정
└── WMX36u1_RTX.props    # WMX3.6u1 RTX 설정
```

각 속성 시트 내용:
- Include/Lib 경로 설정
- 출력 폴더 설정 (`x64\Release_<버전>\`)
- 버전별 전처리기 정의

### 3. WMXBroker.vcxproj 수정

- `WMXVersion` 속성 추가 (명령줄에서 지정)
- 조건부 속성 시트 Import
- 레거시 빌드를 위한 기본 경로 유지
- Include 경로 순서 변경 (WMX3 → WMX1.5, EcApi.h 충돌 방지)

### 4. 소스 코드 수정

하드코딩된 EcApi.h 경로를 상대 경로로 변경:
- `broker/EcDeviceManager.cpp`
- `broker/EcNetworkBroker.cpp`
- `broker/WMX3ContextManager.cpp`

```cpp
// 변경 전
#include "C:/Program Files/SoftServo/WMX3/Include/EcApi.h"

// 변경 후
#include "EcApi.h"
```

### 5. 빌드 스크립트 생성

`build_all.bat` - 전체 버전 빌드 스크립트

### 6. CLAUDE.md 업데이트

다중 버전 빌드 명령어 및 SDK 폴더 구조 문서화

## 빌드 방법

### 기본 빌드 (레거시)
```bash
msbuild wmx15app.sln -p:Configuration=Release -p:Platform=x64
```

### 특정 버전 빌드
```bash
msbuild broker\WMXBroker.vcxproj -p:Configuration=Release -p:Platform=x64 -p:WMXVersion=WMX34u4_Win
```

### 전체 버전 빌드
```bash
build_all.bat
```

## 출력 폴더

| 버전 | 출력 경로 |
|------|----------|
| 레거시 | `x64\Release\` |
| WMX3.4u4 Win | `x64\Release_WMX34u4_Win\` |
| WMX3.4u4 RTX | `x64\Release_WMX34u4_RTX\` |
| WMX3.6u1 Win | `x64\Release_WMX36u1_Win\` |
| WMX3.6u1 RTX | `x64\Release_WMX36u1_RTX\` |

## 사용자 작업 필요

SDK 파일을 각 버전별로 복사해야 합니다. 자세한 내용은 `sdk/README.md` 참조.

## 생성/수정된 파일

| 파일 | 작업 |
|------|------|
| `sdk/README.md` | 신규 생성 |
| `sdk/*/` | 폴더 구조 생성 |
| `broker/props/*.props` | 신규 생성 (5개 파일) |
| `broker/WMXBroker.vcxproj` | 수정 |
| `broker/EcDeviceManager.cpp` | 수정 |
| `broker/EcNetworkBroker.cpp` | 수정 |
| `broker/WMX3ContextManager.cpp` | 수정 |
| `build_all.bat` | 신규 생성 |
| `CLAUDE.md` | 수정 |
