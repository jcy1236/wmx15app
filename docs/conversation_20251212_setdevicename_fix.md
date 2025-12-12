# 대화 기록: SetDeviceName 타입 불일치 에러 수정

## 날짜: 2025-12-12

## 문제
다른 PC에서 빌드 시 에러 발생:
```
error C2664
WMX3Api::SetDeviceName(wchar_t *)
인수 1을 'const TCHAR*' 에서 'char *' 으로 변환할 수 없습니다.
```

## 원인
- WMX3 SDK의 `SetDeviceName`은 두 가지 오버로드 제공:
  - `SetDeviceName(const char* name)`
  - `SetDeviceName(const wchar_t* name)`
- 기존 코드에서 `TCHAR*`를 사용하여 프로젝트 문자셋 설정에 따라 다르게 해석됨
- MultiByte 설정에서는 `TCHAR` = `char`, Unicode 설정에서는 `TCHAR` = `wchar_t`
- 컴파일러가 어떤 오버로드를 선택할지 모호성 발생

## 해결책
WMX3 API 호출 시 명시적으로 `char*` 타입 사용

### 수정 파일
1. **broker/WMXBroker.cpp** - `WMXLIB::SetDeviceName()`
   ```cpp
   // 기존
   return wmx3->SetDeviceName(name);

   // 수정
   #ifdef UNICODE
       return wmx3->SetDeviceName(name);
   #else
       return wmx3->SetDeviceName(static_cast<const char*>(name));
   #endif
   ```

2. **broker/WMX3ContextManager.cpp** - `CreateDeviceInternal()`
   ```cpp
   // 기존
   m_wmx3->SetDeviceName(_T("WMXBroker"));

   // 수정
   m_wmx3->SetDeviceName("WMXBroker");
   ```

## 결론
- TCHAR 대신 명시적 타입 사용으로 오버로드 모호성 해결
- MultiByte/Unicode 빌드 모두 지원
