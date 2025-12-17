# 코드 리뷰 Q&A (2025-12-05)

## 질문 1: WMX3ContextManager 이름 제안

### 현재 상황
현재 코드에는 `WMX3ContextManager`와 `EcDeviceManager` 두 개의 Manager 클래스가 있습니다.

| 현재 이름 | 역할 | 문제점 |
|-----------|------|--------|
| **WMX3ContextManager** | WMX3 인스턴스 공유 + Reference counting | "Context"가 모호함 |
| **EcDeviceManager** | ECDEV 핸들 매핑 관리 | 역할 명확함 |

### 제안 이름

| 제안 | 의미 | 추천도 |
|------|------|--------|
| `WMX3SharedResourceManager` | 공유 리소스 관리 강조 | ★★★ |
| `WMX3InstancePool` | 싱글톤 인스턴스 풀 의미 | ★★☆ |
| `WMX3ApiRegistry` | WMX3Api 레지스트리 | ★★☆ |
| `WMX3ConnectionManager` | 연결 관리자 | ★☆☆ |

### 추천
**`WMX3SharedResourceManager`** - 역할이 "공유 리소스(WMX3Api, CoreMotion, Io, Ecat) 관리"이므로 가장 직관적

---

## 질문 2: WMXBrokerC.h 배포 이유

### 헤더 파일 관계도
```
[Client Application]
        │
        ├── #include "WMXBrokerClient.h" (C++ wrapper, header-only)
        │           │
        │           └── #include "WMXBrokerC.h"  ← 필수 의존
        │                   │
        │                   └── #include "wmxapi_type.h"
        │
        └── Link: WMXBroker.lib → WMXBroker.dll
```

### WMXBrokerC.h가 필요한 이유

1. **C API 함수 선언** (L158-370)
   - `WMXBroker_CreateDevice()`, `WMXBroker_Io_SetOutBit()` 등 모든 C 함수 선언
   - WMXBrokerClient.h의 wrapper 클래스가 이 함수들을 호출함

2. **구조체 정의** (L21-142)
   - `WMX_HOME_DATA`, `PosBlockExt2`, `CoordinatedPosBlockExt2` 등
   - API 함수 파라미터에 사용되는 구조체

3. **Export/Import 매크로** (L148-153)
   ```cpp
   #ifdef WMXBROKER_EXPORTS
   #define WMXBROKER_CAPI __declspec(dllexport)
   #else
   #define WMXBROKER_CAPI __declspec(dllimport)  // 클라이언트용
   #endif
   ```

### 배포 구성
```
배포 패키지/
├── WMXBroker.dll          # 실행 DLL
├── WMXBroker.lib          # Import 라이브러리
├── include/
│   ├── WMXBrokerClient.h  # C++ wrapper (메인 헤더)
│   ├── WMXBrokerC.h       # C API 선언 + 구조체 (필수)
│   ├── wmxapi_type.h      # 타입 정의
│   ├── wmxapi_def.h       # 상수 정의
│   └── EC_Network_Api_Broker.h  # EC API (선택)
```

---

## 질문 3: 중복 코드 점검

### 발견된 중복: Motion Block 구조체

| 구조체 | WMXBrokerC.h | WMXBrokerClient.h |
|--------|--------------|-------------------|
| `PosBlockExt2Ind` | L44-55 | L99-116 |
| `IntBlockExt2Ind` | L62-75 | L81-96 |
| `CoordinatedPosBlockExt2Ind` | L122-140 | L28-49 |

### 현재 해결책
Include guard 사용:
```cpp
#ifndef POSBLOCKEXT2_DEFINED
#define POSBLOCKEXT2_DEFINED
// 구조체 정의...
#endif
```

### 문제점
- 동일 구조체가 두 파일에 복사되어 있음
- 수정 시 두 곳 모두 업데이트 필요 → 동기화 오류 위험

### 권장 개선안

**Option 1: 구조체 전용 헤더 분리**
```
include/
├── wmxapi_motion_blocks.h  # 모든 Motion Block 구조체
├── WMXBrokerC.h            # #include "wmxapi_motion_blocks.h"
└── WMXBrokerClient.h       # #include "wmxapi_motion_blocks.h"
```

**Option 2: WMXBrokerC.h에만 정의 유지** (선택됨)
- WMXBrokerClient.h는 WMXBrokerC.h를 include하므로
- WMXBrokerClient.h에서 중복 정의 제거

---

## 조치 사항

- [x] 문서 작성 완료
- [ ] Motion Block 구조체 중복 제거 (Option 2 적용)
