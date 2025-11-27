# 대화 이력 006: StartCommunication 수정

## 날짜
2025-11-27

## 문제
CreateDevice를 호출했는데 StartCommunication까지 진행되지 않음

## 원인 분석
- WMX3 API에서 CreateDevice()는 디바이스 인스턴스만 생성
- StartCommunication()을 명시적으로 호출해야 통신이 시작됨
- 기존 WMXBroker의 StartCommunication()은 빈 함수로 구현되어 있었음

## WMX3 엔진 상태
| 상태 | 설명 |
|------|------|
| Idle | 엔진 준비되지 않음 |
| Running | 엔진 실행 중 |
| Communicating | 통신 활성화 (목표 상태) |

## 수정 내용

### broker/WMXBroker.cpp

**변경 전:**
```cpp
WMXAPIFUNC WMXLIB::StartCommunication()
{
    if (!wmx3) return -1;
    // In WMX3, communication starts with CreateDevice
    // Return success for compatibility
    return 0;
}

WMXAPIFUNC WMXLIB::StopCommunication()
{
    // In WMX3, communication stops with CloseDevice
    // Return success for compatibility
    return 0;
}
```

**변경 후:**
```cpp
WMXAPIFUNC WMXLIB::StartCommunication()
{
    if (!wmx3) return -1;

    // Call WMX3 StartCommunication with 5 second timeout
    return wmx3->StartCommunication(5000);
}

WMXAPIFUNC WMXLIB::StopCommunication()
{
    if (!wmx3) return -1;

    return wmx3->StopCommunication();
}
```

## 빌드 결과
```
WMXBroker.vcxproj -> c:\Users\jcy1236\source\repos\wmx15app\x64\Release\WMXBroker.dll
wmx15app.vcxproj -> c:\Users\jcy1236\source\repos\wmx15app\x64\Release\wmx15app.exe
경고 8개
오류 0개
```

## 결론
WMX3의 StartCommunication() API를 실제로 호출하도록 수정 완료
