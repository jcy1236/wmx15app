# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 빌드 명령어

```bash
# Release 빌드
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" wmx15app.sln -p:Configuration=Release -p:Platform=x64

# Rebuild (전체 다시 빌드)
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" wmx15app.sln -p:Configuration=Release -p:Platform=x64 -t:Rebuild
```

빌드 결과물: `x64\Release\WMXBroker.dll`, `x64\Release\WMXBroker.lib`

## 프로젝트 개요

WMX 1.5 기반 Application을 WMX3 엔진 환경에서 실행하기 위한 프로젝트입니다.
WMX 1.5 API를 WMX3 API로 변환하는 Broker 레이어(DLL)를 구현합니다.

```
[App Code] --WMX 1.5 API--> [WMXBroker.dll] --WMX3 API--> [WMX3 Engine]
```

## 솔루션 구조

- **wmx15app**: 테스트용 애플리케이션 (WMXBroker에 의존)
- **WMXBroker**: Broker DLL 프로젝트 (broker/ 폴더)

### WMXBroker 핵심 파일
| 파일 | 역할 |
|------|------|
| WMXBroker.h/cpp | WMXLIB 클래스 - WMX 1.5 인터페이스를 WMX3로 위임 |
| IoBroker.h/cpp | wmxAPI::common::Io 클래스 - I/O API 구현 |
| StatusMapper.h/cpp | WMX3 CoreMotionStatus → WMX 1.5 WMX_STATUS 변환 |

### 클래스 구조
```
wmxAPI::WMXLIB (WMX 1.5 호환 인터페이스)
├── wmx3Api::WMX3Api* (내부 WMX3 API 인스턴스)
├── wmx3Api::CoreMotion* (축 제어/상태)
├── wmx3Api::Io* (I/O 제어)
└── wmxAPI::common::Io* io (WMX 1.5 호환 Io 클래스)
```

## 구현 범위

### 구현 완료
- WMXLIB: CreateDevice, CloseDevice, StartCommunication, StopCommunication, GetStatus, GetVersion
- Io 클래스: Set/Get OutBit/Byte/Bytes, Get InBit/Byte/Bytes
- SetInitialOut* API: 내부 버퍼에 저장 (WMX3에 해당 기능 없음)
- StatusMapper: 축 상태, 엔진 상태, I/O 상태 전체 매핑

### 미구현 (향후 확장)
- AuxIn/AuxOut API (사용하지 않음)
- Motion 명령 API (Pos, Jog, Home 등)

## 라이브러리 의존성

### 빌드 시 참조
- WMX 1.5 Header: `C:\Program Files\SoftServo\WMX1.5\Include` (타입 정의만 사용)
- WMX3 Header: `C:\Program Files\SoftServo\WMX3\Include`
- WMX3 Library: `C:\Program Files\SoftServo\WMX3\Lib`

### 링커 설정
- 필수 라이브러리: WMX3Api.lib, CoreMotionApi.lib, IOApi.lib, IMDll.lib
- DelayLoad: IMDll.dll
