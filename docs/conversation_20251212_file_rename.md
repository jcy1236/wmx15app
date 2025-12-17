# 대화 기록: 헤더 파일명 변경

**날짜**: 2025-12-12

## 요청 사항

파일명 변경:
- `WMXBrokerClient.h` → `WMXLIB_Sim.h`
- `EC_Network_Api_Broker.h` → `EC_Network_Api_Sim.h`

## 수행 작업

### 1. 파일명 변경 (git mv)
```bash
git mv include/WMXBrokerClient.h include/WMXLIB_Sim.h
git mv include/EC_Network_Api_Broker.h include/EC_Network_Api_Sim.h
```

### 2. 헤더 가드 및 주석 업데이트

**WMXLIB_Sim.h:**
```cpp
// 변경 전
// WMXBrokerClient.h
#ifndef WMXBROKER_CLIENT_H
#define WMXBROKER_CLIENT_H
...
#endif // WMXBROKER_CLIENT_H

// 변경 후
// WMXLIB_Sim.h
#ifndef WMXLIB_SIM_H
#define WMXLIB_SIM_H
...
#endif // WMXLIB_SIM_H
```

**EC_Network_Api_Sim.h:**
```cpp
// 변경 전
// EC_Network_Api_Broker.h
#ifndef EC_NETWORK_API_BROKER_H
#define EC_NETWORK_API_BROKER_H
...
#endif // EC_NETWORK_API_BROKER_H

// 변경 후
// EC_Network_Api_Sim.h
#ifndef EC_NETWORK_API_SIM_H
#define EC_NETWORK_API_SIM_H
...
#endif // EC_NETWORK_API_SIM_H
```

### 3. 참조 파일 업데이트

**main.cpp:**
```cpp
// 변경 전
#include "WMXBrokerClient.h"  // for vs2012 compatibility

// 변경 후
#include "WMXLIB_Sim.h"  // for vs2012 compatibility
```

### 4. 빌드 확인

솔루션 Rebuild 성공:
- `WMXBroker.dll` 빌드 완료
- `wmx15app.exe` 빌드 완료

## 변경된 파일 목록

| 변경 유형 | 파일 |
|-----------|------|
| 이름 변경 | `include/WMXBrokerClient.h` → `include/WMXLIB_Sim.h` |
| 이름 변경 | `include/EC_Network_Api_Broker.h` → `include/EC_Network_Api_Sim.h` |
| 수정 | `main.cpp` (include 경로 변경) |

## 사용 방법

VS2012 호환 애플리케이션에서:
```cpp
// WMX 1.5 호환 API 사용
#include "WMXLIB_Sim.h"

// EtherCAT Network API 사용
#include "EC_Network_Api_Sim.h"
```
