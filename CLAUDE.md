# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 프로젝트 개요

Movensys WMX 1.5를 사용하기 위한 C++ Application 프로젝트입니다.
WMX는 SoftServo의 모션 컨트롤러 라이브러리입니다.

## WMX 1.5 라이브러리 경로

- Header: `C:\Program Files\SoftServo\WMX1.5\Include`
- Library: `C:\Program Files\SoftServo\WMX1.5\Lib`

## 빌드 설정

Visual Studio 프로젝트 설정 시 필요한 구성:
- Include 디렉토리: `C:\Program Files\SoftServo\WMX1.5\Include` 추가
- Library 디렉토리: `C:\Program Files\SoftServo\WMX1.5\Lib` 추가
- 링커 입력: WMX 관련 .lib 파일 추가

## 빌드 명령어

```bash
# Visual Studio Developer Command Prompt에서 실행
msbuild wmx15app.sln /p:Configuration=Release /p:Platform=x64
```
