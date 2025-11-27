// WMXBroker.h
// WMX 1.5 API를 WMX3 API로 변환하는 Broker 레이어
// WMXLIB과 동일한 인터페이스를 제공하여 기존 코드 수정 최소화

#ifndef WMXBROKER_H
#define WMXBROKER_H

#include <windows.h>
#include <tchar.h>

// WMX 1.5 타입 정의 포함
#include "wmxapi_type.h"
#include "wmxapi_def.h"

// Forward declarations for WMX3
namespace wmx3Api {
    class WMX3Api;
    class CoreMotion;
    class Io;
}

namespace wmxAPI {

    // Forward declaration
    class WMXLIB;

    namespace common {

        // Io 클래스 - WMX 1.5 인터페이스 유지
        class Io {
        public:
            WMXLIB* wmxlib;
            Io(WMXLIB* f) : wmxlib(f) {}

            // I/O APIs
            WMXAPIFUNC SetOutBit(short byte, short bit, unsigned char data);
            WMXAPIFUNC SetOutByte(short offsetByte, unsigned char data);
            WMXAPIFUNC SetOutBytes(short offsetByte, short size, unsigned char* data);
            WMXAPIFUNC GetInBit(short byte, short bit, unsigned char* data);
            WMXAPIFUNC GetInByte(short offsetByte, unsigned char* data);
            WMXAPIFUNC GetInBytes(short offsetByte, short size, unsigned char* data);
            WMXAPIFUNC GetOutBit(short byte, short bit, unsigned char* data);
            WMXAPIFUNC GetOutByte(short offsetByte, unsigned char* data);
            WMXAPIFUNC GetOutBytes(short offsetByte, short size, unsigned char* data);

            // Initial Output APIs (WMX3에는 해당 기능 없음 - 내부 저장)
            WMXAPIFUNC SetInitialOutBit(short byte, short bit, unsigned char data);
            WMXAPIFUNC SetInitialOutByte(short offsetByte, unsigned char data);
            WMXAPIFUNC SetInitialOutBytes(short offsetByte, short size, unsigned char* data);
            WMXAPIFUNC GetInitialOutBit(short byte, short bit, unsigned char* data);
            WMXAPIFUNC GetInitialOutByte(short offsetByte, unsigned char* data);
            WMXAPIFUNC GetInitialOutBytes(short offsetByte, short size, unsigned char* data);
        };

    } // namespace common

    // WMXLIB 클래스 - WMX 1.5 인터페이스 유지, 내부적으로 WMX3 사용
    class WMXLIB {
    private:
        wmx3Api::WMX3Api* wmx3;
        wmx3Api::CoreMotion* coreMotion;
        wmx3Api::Io* wmx3Io;
        bool isConnected;

        // Initial output 저장용 버퍼
        unsigned char initialOut[MAX_IOOUTSIZE];

    public:
        WMXLIB();
        ~WMXLIB();

        // WMX3 내부 객체 접근 (Broker 내부용)
        wmx3Api::WMX3Api* GetWMX3Api() { return wmx3; }
        wmx3Api::CoreMotion* GetCoreMotion() { return coreMotion; }
        wmx3Api::Io* GetWMX3Io() { return wmx3Io; }
        unsigned char* GetInitialOutBuffer() { return initialOut; }

        // System APIs
        WMXAPIFUNC CreateDevice(TCHAR* path, PLTFRM_TYPE type);
        WMXAPIFUNC CloseDevice();
        WMXAPIFUNC StartCommunication();
        WMXAPIFUNC StopCommunication();
        WMXAPIFUNC GetStatus(WMX_STATUS* st);
        WMXAPIFUNC GetStatus(WMX_STATUS* st, short axis);
        WMXAPIFUNC GetStatus(WMX_STATUS* st, short firstAxis, short lastAxis);
        WMXAPIFUNC GetVersion(double* pCeVersion, double* pPeVersion);

        // Io 클래스 인스턴스
        common::Io* io;

        // 에러 코드
        WMX_API_ERROR_CODE lastError;
    };

} // namespace wmxAPI

#endif // WMXBROKER_H
