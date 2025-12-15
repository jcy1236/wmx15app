# WMX3.4/3.6 API 호환성 수정

**날짜**: 2025-12-15

## 요약
WMX3.4와 WMX3.6 SDK 간의 API 시그니처 차이로 인한 빌드 오류를 해결했습니다.

## 문제점

### 1. API 시그니처 차이
| 함수 | WMX3.4u4 | WMX3.6u1 |
|------|----------|----------|
| `SetDeviceName` | `char*`, `wchar_t*` (non-const) | `const char*`, `const wchar_t*` |
| `CreateDevice` | `char*`, `wchar_t*` (non-const) | `const char*`, `const wchar_t*` |

### 2. WMX3.6 전용 API
- `ResetTransmitStatisticsInfo()` - WMX3.4에 없음
- `GetEniFilePath()` - WMX3.4에 없음

### 3. SDK 파일 혼동
초기에 WMX3.4 폴더에 WMX3.6 lib 파일이 복사되어 있어 헤더/라이브러리 불일치로 링크 오류 발생

## 해결책

### 1. const_cast 적용 (WMX3.4 호환)

**broker/WMX3ContextManager.cpp:**
```cpp
// WMX3.4 SDK uses char*/wchar_t* (non-const)
// WMX3.6 SDK uses const char*/const wchar_t*
// Use const_cast for WMX3.4 compatibility
#ifdef UNICODE
    long ret = m_wmx3->CreateDevice(const_cast<wchar_t*>(WMX3_PATH), wmx3Api::DeviceType::DeviceTypeNormal);
#else
    long ret = m_wmx3->CreateDevice(const_cast<char*>(WMX3_PATH), wmx3Api::DeviceType::DeviceTypeNormal);
#endif
```

**broker/WMXBroker.cpp:**
```cpp
#ifdef UNICODE
    return wmx3->SetDeviceName(const_cast<wchar_t*>(name));
#else
    return wmx3->SetDeviceName(const_cast<char*>(name));
#endif
```

### 2. 조건부 컴파일 (WMX3.4 미지원 API)

**broker/EcNetworkBroker.cpp:**
```cpp
extern "C" ECBROKER_API long __stdcall ecClearMasterStatistics(ECDEV dev)
{
#if defined(WMX_VERSION_34U4_WIN) || defined(WMX_VERSION_34U4_RTX)
    // ResetTransmitStatisticsInfo is not available in WMX3.4
    (void)dev;
    return EC_API_ERROR_CODE_NOT_SUPPORTED;
#else
    // WMX3.6 구현
    ...
#endif
}

extern "C" ECBROKER_API long __stdcall ecGetMasterConfigFilename(ECDEV dev, TCHAR* filename, int bufferSize)
{
#if defined(WMX_VERSION_34U4_WIN) || defined(WMX_VERSION_34U4_RTX)
    // GetEniFilePath is not available in WMX3.4
    (void)dev;
    filename[0] = '\0';
    return EC_API_ERROR_CODE_NOT_SUPPORTED;
#else
    // WMX3.6 구현
    ...
#endif
}
```

### 3. 에러 코드 추가

**broker/EcDeviceManager.h:**
```cpp
#define EC_API_ERROR_CODE_NOT_SUPPORTED             0x20000002
```

## 빌드 결과
4개 버전 모두 빌드 성공:
- `x64/Release_WMX34u4_Win/WMXBroker.dll`
- `x64/Release_WMX34u4_RTX/WMXBroker.dll`
- `x64/Release_WMX36u1_Win/WMXBroker.dll`
- `x64/Release_WMX36u1_RTX/WMXBroker.dll`

## 수정된 파일
- `broker/WMX3ContextManager.cpp` - const_cast 적용
- `broker/WMXBroker.cpp` - const_cast 적용
- `broker/EcNetworkBroker.cpp` - 조건부 컴파일 추가
- `broker/EcDeviceManager.h` - NOT_SUPPORTED 에러 코드 추가
- `sdk/WMX34u4_Win/*` - 올바른 WMX3.4 SDK 파일로 교체
- `sdk/WMX34u4_RTX/*` - 올바른 WMX3.4 SDK 파일로 교체

## 커밋
- `9831d45` - Fix WMX3.4/3.6 API compatibility and update SDK files

---

## 추가 수정: SdoDownload/SdoUpload 시그니처 차이

### 문제점
WMX3.4 빌드 시 링크 에러 발생:
```
EcNetworkBroker.obj : error LNK2001
SdoUpload(int,int,int,enum wmx3Api::ecApi::EcSdoType::T,int,unsigned char*, unsigned int*, unsigned int*, unsigned int, int)
```

### 원인
| 함수 | WMX3.4u4 | WMX3.6u1 |
|------|----------|----------|
| `SdoDownload` | 8개 파라미터 | 9개 파라미터 (`BOOL complete` 추가) |
| `SdoUpload` | 8개 파라미터 | 9개 파라미터 (`BOOL complete` 추가) |

C++ 기본값이 헤더에 있어도, **라이브러리(.lib)에 export된 함수 시그니처**는 다릅니다.

### 해결책: 조건부 컴파일

**broker/EcNetworkBroker.cpp:**
```cpp
// ecDownloadSDO
#if defined(WMX_VERSION_34U4_WIN) || defined(WMX_VERSION_34U4_RTX)
    // WMX3.4: 8 parameters (no 'complete' parameter)
    long ret = ecat->SdoDownload(configuredId, index, subIndex,
        wmx3SdoType, length, data, &errCode, 0);
#else
    // WMX3.6: 9 parameters (with 'complete' parameter)
    long ret = ecat->SdoDownload(configuredId, index, subIndex,
        wmx3SdoType, length, data, &errCode, 0, FALSE);
#endif

// ecUploadSDO
#if defined(WMX_VERSION_34U4_WIN) || defined(WMX_VERSION_34U4_RTX)
    // WMX3.4: 8 parameters (no 'complete' parameter)
    long ret = ecat->SdoUpload(configuredId, index, subIndex,
        wmx3SdoType, length, data, &actualSize, &errCode, 0);
#else
    // WMX3.6: 9 parameters (with 'complete' parameter)
    long ret = ecat->SdoUpload(configuredId, index, subIndex,
        wmx3SdoType, length, data, &actualSize, &errCode, 0, FALSE);
#endif
```

### 빌드 결과
4개 버전 모두 빌드 성공

---

## 추가 수정: Visual Studio Batch Build 구성 추가

### 문제점
Visual Studio Batch Build에서 WMX3.4 빌드가 실패했습니다.

### 원인
- 기존 빌드 시스템은 MSBuild 명령줄에서 `/p:WMXVersion=WMX34u4_Win`을 전달하는 방식
- Visual Studio Batch Build는 이 property를 전달할 수 없음
- 솔루션에 `Release_WMX34u4_Win|x64` 같은 별도 구성이 없었음

### 해결책
솔루션(.sln)과 프로젝트(.vcxproj)에 4개의 새 구성 추가:
- `Release_WMX34u4_Win|x64`
- `Release_WMX34u4_RTX|x64`
- `Release_WMX36u1_Win|x64`
- `Release_WMX36u1_RTX|x64`

### 수정된 파일

#### 1. wmx15app.sln
```
GlobalSection(SolutionConfigurationPlatforms) = preSolution
    ...
    Release_WMX34u4_RTX|x64 = Release_WMX34u4_RTX|x64
    Release_WMX34u4_Win|x64 = Release_WMX34u4_Win|x64
    Release_WMX36u1_RTX|x64 = Release_WMX36u1_RTX|x64
    Release_WMX36u1_Win|x64 = Release_WMX36u1_Win|x64
EndGlobalSection
```

#### 2. broker/WMXBroker.vcxproj
- ProjectConfiguration 항목 4개 추가
- Configuration PropertyGroup 4개 추가 (Unicode CharacterSet)
- PropertySheets ImportGroup 4개 추가 (각 .props 파일 import)
- ItemDefinitionGroup 4개 추가 (Release 설정 기반)

### 빌드 방법

#### 명령줄 빌드 (기존 방식 계속 지원)
```batch
MSBuild broker\WMXBroker.vcxproj /p:Configuration=Release /p:Platform=x64 /p:WMXVersion=WMX34u4_Win
```

#### Visual Studio Batch Build (새로 추가)
1. Build → Batch Build 메뉴
2. 원하는 구성 선택:
   - `Release_WMX34u4_Win|x64`
   - `Release_WMX34u4_RTX|x64`
   - `Release_WMX36u1_Win|x64`
   - `Release_WMX36u1_RTX|x64`
3. Build 또는 Rebuild 클릭

### 빌드 결과
4개 버전 모두 빌드 성공:
- `x64/Release_WMX34u4_Win/WMXBroker.dll` (139,264 bytes)
- `x64/Release_WMX34u4_RTX/WMXBroker.dll` (139,264 bytes)
- `x64/Release_WMX36u1_Win/WMXBroker.dll` (144,896 bytes)
- `x64/Release_WMX36u1_RTX/WMXBroker.dll` (144,896 bytes)
