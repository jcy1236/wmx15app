# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 프로젝트 개요

WMX 1.5 기반 Application을 WMX3 엔진 환경에서 실행하기 위한 프로젝트입니다.
WMX3에만 있는 추가 기능을 활용하기 위해, WMX 1.5 API를 WMX3 API로 변환하는 Broker 레이어를 구현합니다.

### 배경
- WMX는 SoftServo의 모션 컨트롤러 라이브러리
- 이 PC에는 WMX 1.5와 WMX3 엔진이 모두 설치됨
- 기존 WMX 1.5 App 코드를 WMX3 환경에서 동작하도록 변환

## Broker 아키텍처

WMX 1.5 API 호출을 WMX3 API로 중계하는 레이어입니다.

```
[App Code] --WMX 1.5 API--> [Broker] --WMX3 API--> [WMX3 Engine]
```

### 구현 범위
- **Io 클래스**: SetOutBit/Byte/Bytes, GetInBit/Byte/Bytes, GetOutBit/Byte/Bytes
- **GetStatus()**: WMX_STATUS를 CoreMotionStatus + Io로 조합하여 반환
- **제외**: AuxIn/AuxOut API는 사용하지 않음
- **확장**: 다른 API들은 점진적으로 추가 예정

### API 매핑

#### Io 클래스 (wmxAPI::common::Io → wmx3Api::Io)
| WMX 1.5 | WMX3 | 비고 |
|---------|------|------|
| SetOutBit(short, short, uchar) | SetOutBit(int, int, uchar) | 타입만 변경 |
| SetOutByte(short, uchar) | SetOutByte(int, uchar) | 타입만 변경 |
| SetOutBytes(short, short, uchar*) | SetOutBytes(int, int, uchar*) | 타입만 변경 |
| GetInBit(short, short, uchar*) | GetInBit(int, int, uchar*) | 타입만 변경 |
| GetInByte(short, uchar*) | GetInByte(int, uchar*) | 타입만 변경 |
| GetInBytes(short, short, uchar*) | GetInBytes(int, int, uchar*) | 타입만 변경 |
| GetOutBit(short, short, uchar*) | GetOutBit(int, int, uchar*) | 타입만 변경 |
| GetOutByte(short, uchar*) | GetOutByte(int, uchar*) | 타입만 변경 |
| GetOutBytes(short, short, uchar*) | GetOutBytes(int, int, uchar*) | 타입만 변경 |
| SetInitialOutBit/Byte/Bytes | 해당 없음 | 별도 처리 필요 |

#### GetStatus 매핑 (WMX_STATUS → CoreMotionStatus)
| WMX 1.5 (WMX_STATUS) | WMX3 (CoreMotionStatus) |
|----------------------|-------------------------|
| ServoOn[axis] | axesStatus[axis].servoOn |
| AmpAlarm[axis] | axesStatus[axis].ampAlarm |
| ActualPosition[axis] | axesStatus[axis].actualPos |
| PositionCommand[axis] | axesStatus[axis].posCmd |
| VelocityCommand[axis] | axesStatus[axis].velocityCmd |
| InPosition[axis] | axesStatus[axis].inPos |
| HomeDone[axis] | axesStatus[axis].homeDone |
| OpState[axis] | axesStatus[axis].opState |
| GenIn[] | Io::GetInBytes()로 획득 |
| GenOut[] | Io::GetOutBytes()로 획득 |

## 라이브러리 경로

### WMX 1.5
- Header: `C:\Program Files\SoftServo\WMX1.5\Include`
- Library: `C:\Program Files\SoftServo\WMX1.5\Lib`

### WMX 3
- Header: `C:\Program Files\SoftServo\WMX3\Include`
- Library: `C:\Program Files\SoftServo\WMX3\Lib`
- 주요 모듈: WMX3Api, CoreMotionApi, IOApi

## 빌드 설정

Visual Studio 프로젝트 설정:
- Include 디렉토리: WMX 1.5 및 WMX3 Include 경로 추가
- Library 디렉토리: WMX 1.5 및 WMX3 Lib 경로 추가
- 링커 입력: WMXLIB.lib, WMXDLL.lib, WMX3Api.lib, CoreMotionApi.lib, IOApi.lib
- DelayLoad: WMXDLL.dll (SetDllDirectory로 경로 지정)

## 빌드 명령어

```bash
# Visual Studio Developer Command Prompt에서 실행
msbuild wmx15app.sln /p:Configuration=Release /p:Platform=x64
```
