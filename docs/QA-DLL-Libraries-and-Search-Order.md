# Q&A: DLL 라이브러리와 검색 순서

## Q1: legacy_stdio_definitions.lib와 ucrt.lib의 역할

### 질문
WMXBroker.vcxproj에서 사용하는 다음 라이브러리들의 역할은?
- `legacy_stdio_definitions.lib`
- `ucrt.lib`

### 답변

#### legacy_stdio_definitions.lib

**역할**: Visual Studio 2015 이상에서 이전 버전(VS2012, VS2013 등)의 C 런타임 라이브러리와의 호환성을 제공합니다.

**필요한 이유**:
- WMX3 라이브러리가 이전 버전의 Visual Studio로 빌드되었을 가능성이 높습니다
- `printf`, `scanf`, `sprintf` 등 구형 stdio 함수들의 심볼을 제공합니다
- VS2015부터 Universal CRT(UCRT)로 변경되면서 일부 함수들이 인라인화되어 링크 오류가 발생할 수 있는데, 이 라이브러리가 해결합니다

**일반적인 링크 오류 예시** (이 라이브러리 없을 때):
```
unresolved external symbol __iob_func
unresolved external symbol _vsnprintf
unresolved external symbol _sprintf
```

#### ucrt.lib

**역할**: Universal C Runtime Library - Windows 10 이상에서 사용되는 표준 C 런타임 라이브러리입니다.

**필요한 이유**:
- `LIBCMT`를 무시하고 있기 때문에 (`IgnoreSpecificDefaultLibraries>LIBCMT`) 명시적으로 ucrt.lib를 링크해야 합니다
- 기본 C 런타임 함수들(`memcpy`, `strlen`, `malloc` 등)을 제공합니다

#### 두 라이브러리의 조합

vcxproj 설정:
```xml
<AdditionalDependencies>...legacy_stdio_definitions.lib;ucrt.lib;...</AdditionalDependencies>
<IgnoreSpecificDefaultLibraries>LIBCMT</IgnoreSpecificDefaultLibraries>
```

이 설정은 WMX3 라이브러리(VS2015 이전 빌드)와 현재 프로젝트(VS2022/v143)의 CRT 충돌을 해결하기 위한 것입니다. WMX3 라이브러리가 다른 버전의 CRT로 링크되어 있어서 이러한 호환성 라이브러리가 필요합니다.

---

## Q2: SetDllDirectory와 DLL 검색 순서

### 질문
WMX3가 설치된 위치의 DLL을 로드해야 하는데, 런타임 중 프로젝트의 출력 파일(실행 파일) 위치에 있는 DLL을 대신 로딩합니다. 실행 파일이 위치한 폴더를 우선으로 찾나요?

### 답변

네, 맞습니다. Windows의 DLL 검색 순서 때문에 그렇습니다.

#### Windows DLL 검색 순서 (기본)

1. **실행 파일이 있는 디렉토리** ← 가장 먼저 검색
2. 시스템 디렉토리 (`C:\Windows\System32`)
3. 16비트 시스템 디렉토리 (`C:\Windows\System`)
4. Windows 디렉토리 (`C:\Windows`)
5. 현재 작업 디렉토리
6. `PATH` 환경 변수에 지정된 디렉토리들

#### SetDllDirectory의 역할

`WMXBroker.cpp`의 `SetDllDirectory(dllPath)`는 DLL 검색 경로를 **추가**하는 것이지, 실행 파일 디렉토리보다 **우선순위를 높이는 것이 아닙니다**.

```
SetDllDirectory 호출 후 검색 순서:
1. 실행 파일이 있는 디렉토리  ← 여전히 1순위
2. SetDllDirectory로 지정한 경로
3. 시스템 디렉토리
...
```

#### 문제 상황

실행 파일 폴더(`x64\Release\`)에 WMX3 DLL 복사본이 있으면:
- `SetDllDirectory`로 WMX3 설치 경로를 지정해도
- 실행 파일 폴더의 DLL이 **먼저** 로드됩니다

#### 해결 방법

WMX3 설치 경로의 DLL을 강제로 먼저 로드하려면 `LoadLibraryEx`를 사용해야 합니다:

```cpp
// 절대 경로로 직접 로드
LoadLibraryEx(L"C:\\Program Files\\SoftServo\\WMX3\\Bin\\WMX3Api.dll",
              NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
```

또는 실행 파일 폴더에서 WMX3 관련 DLL들을 제거하면 `SetDllDirectory`가 의도대로 동작합니다.

---

*작성일: 2025-12-02*
