# 대화 이력 005: WMXBroker DLL 변환

## 날짜
2025-11-27

## 질문
WMXBroker 프로젝트에서만 WMX3 라이브러리를 참조하면 되는 것 아닌가요? wmx15app 프로젝트도 WMX3를 참조해야 합니까?

## 배경
- WMXBroker 정적 라이브러리가 생성되어 빌드 성공
- wmx15app이 WMXBroker.lib + WMX3 라이브러리 전부를 링크하는 상태

## 분석

### 정적 라이브러리 vs DLL 비교

| 항목 | 정적 라이브러리 (.lib) | DLL (.dll) |
|------|----------------------|------------|
| wmx15app 링크 | WMXBroker.lib + WMX3*.lib 전부 | WMXBroker.lib (import lib)만 |
| wmx15app Include 경로 | broker + WMX3 Include | broker만 |
| wmx15app Library 경로 | broker출력 + WMX3 Lib | broker출력만 |
| WMX3 종속성 노출 | 노출됨 | 숨겨짐 |
| 배포 | exe만 배포 | exe + WMXBroker.dll |

### 정적 라이브러리의 한계
- 정적 라이브러리는 종속성 정보를 전달하지 않음
- 최종 실행 파일(wmx15app)이 모든 종속성을 직접 링크해야 함
- WMX3 라이브러리 참조가 wmx15app에도 필요

### DLL의 장점
- wmx15app은 WMXBroker.lib(import library)만 링크
- WMX3 종속성이 DLL 내부에 캡슐화됨
- 원래 WMXDLL.dll과 동일한 패턴

## 결정
DLL 방식으로 변경 (사용자 코드 및 프로젝트 설정 변경 최소화)

## 수정 내용

### 1. broker/WMXBroker.vcxproj
- ConfigurationType: StaticLibrary → DynamicLibrary
- PreprocessorDefinitions에 WMXBROKER_EXPORTS 추가
- Link 섹션 추가 (WMX3 라이브러리 링크)

### 2. broker/WMXBroker.h
DLL export 매크로 추가:
```cpp
#ifdef WMXBROKER_EXPORTS
#define WMXBROKER_API __declspec(dllexport)
#else
#define WMXBROKER_API __declspec(dllimport)
#endif

class WMXBROKER_API Io { ... };
class WMXBROKER_API WMXLIB { ... };
```

### 3. wmx15app.vcxproj 단순화
- AdditionalDependencies: WMXBroker.lib만 유지
- WMX3 Include/Lib 경로 제거
- DelayLoadDLLs, IgnoreSpecificDefaultLibraries 제거

### 4. 인코딩 문제 해결
- C4819 경고: 한글 UTF-8 주석이 코드 페이지 949에서 문제 발생
- 해결: 모든 소스 파일의 한글 주석을 영문으로 변경

## 빌드 결과
```
WMXBroker.vcxproj -> c:\Users\jcy1236\source\repos\wmx15app\x64\Release\WMXBroker.dll
wmx15app.vcxproj -> c:\Users\jcy1236\source\repos\wmx15app\x64\Release\wmx15app.exe
경고 8개
오류 0개
```

## 생성된 파일
- x64\Release\WMXBroker.dll
- x64\Release\WMXBroker.lib (import library)
- x64\Release\wmx15app.exe

## 결론
DLL 변환 성공. wmx15app은 이제 WMXBroker.lib만 링크하면 되고, WMX3에 대한 직접 의존성이 제거됨.
