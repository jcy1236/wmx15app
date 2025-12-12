# 대화 기록: build_all.bat MSBuild 경로 자동 탐지

## 날짜: 2025-12-12

## 문제
다른 PC에서 `build_all.bat` 실행 시 "지정된 경로를 찾을 수 없습니다" 에러 발생

## 원인
MSBuild 경로가 하드코딩되어 있어 Visual Studio가 다른 위치에 설치된 PC에서 실패

```batch
:: 기존 (하드코딩된 경로)
set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
```

## 해결책
`vswhere.exe`를 사용하여 MSBuild 경로를 자동 탐색하도록 수정

```batch
:: 수정 후 (자동 탐지)
set VSWHERE="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
for /f "usebackq tokens=*" %%i in (`%VSWHERE% -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
    set MSBUILD="%%i"
)
```

## 변경 내용
1. `vswhere.exe`를 사용하여 설치된 Visual Studio의 MSBuild 경로 자동 탐지
2. vswhere.exe 또는 MSBuild를 찾지 못할 경우 명확한 에러 메시지 표시
3. 사용 중인 MSBuild 경로를 출력하여 디버깅 용이하게 함

## 지원 환경
- Visual Studio 2017, 2019, 2022 (Community, Professional, Enterprise)
- vswhere.exe는 VS 2017+ 설치 시 자동으로 포함됨

## 테스트 결과
```
============================================
WMXBroker Multi-Version Build Script
============================================

Using MSBuild: "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"

[1/4] Building WMX3.4u4 Windows...
...
[OK] WMX3.4u4 Windows build completed.
```
