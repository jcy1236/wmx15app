# 대화 기록: include/wmxapi_def.h 파일 제거

## 날짜: 2025-12-12

## 요청
`include/wmxapi_def.h` 파일을 제거하고 SDK 폴더의 파일을 참조하도록 수정

## 배경
- `wmxapi_def.h`는 WMX 1.5 SDK에서 제공되는 파일
- 프로젝트의 `sdk/WMX15/Include/wmxapi_def.h`에 이미 존재
- `include/` 폴더에 중복으로 존재하던 파일을 제거

## 수행 작업

### 1. props 파일에서 include 경로 제거
4개의 버전별 props 파일에서 `$(WMXBrokerRoot)\include;` 경로를 제거:
- `broker/props/WMX34u4_Win.props`
- `broker/props/WMX34u4_RTX.props`
- `broker/props/WMX36u1_Win.props`
- `broker/props/WMX36u1_RTX.props`

변경 전:
```xml
<AdditionalIncludeDirectories>$(WMXBrokerRoot)\include;$(WMX3_IncludeDir);$(WMX15_IncludeDir);%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
```

변경 후:
```xml
<AdditionalIncludeDirectories>$(WMX3_IncludeDir);$(WMX15_IncludeDir);%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
```

### 2. include/wmxapi_def.h 파일 삭제
```bash
rm include/wmxapi_def.h
```

### 3. 빌드 테스트
모든 4개 버전 빌드 성공:
- WMX34u4_Win: `x64/Release_WMX34u4_Win/WMXBroker.dll`
- WMX34u4_RTX: `x64/Release_WMX34u4_RTX/WMXBroker.dll`
- WMX36u1_Win: `x64/Release_WMX36u1_Win/WMXBroker.dll`
- WMX36u1_RTX: `x64/Release_WMX36u1_RTX/WMXBroker.dll`

## 결과
- `include/wmxapi_def.h` 파일 제거 완료
- SDK 폴더의 `sdk/WMX15/Include/wmxapi_def.h`를 통해 참조
- 모든 버전 빌드 정상 동작 확인
