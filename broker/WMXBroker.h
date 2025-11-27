// WMXBroker.h
// WMX 1.5 API to WMX3 API Broker Layer
// Provides WMXLIB compatible interface to minimize code changes

#ifndef WMXBROKER_H
#define WMXBROKER_H

#include <windows.h>
#include <tchar.h>

// DLL Export/Import macros
#ifdef WMXBROKER_EXPORTS
#define WMXBROKER_API __declspec(dllexport)
#else
#define WMXBROKER_API __declspec(dllimport)
#endif

// WMX 1.5 type definitions (wmxapi_type.h includes wmxapi_def.h)
#include "wmxapi_type.h"

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

        // Io class - maintains WMX 1.5 interface
        class WMXBROKER_API Io {
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

            // Initial Output APIs (not available in WMX3 - stored internally)
            WMXAPIFUNC SetInitialOutBit(short byte, short bit, unsigned char data);
            WMXAPIFUNC SetInitialOutByte(short offsetByte, unsigned char data);
            WMXAPIFUNC SetInitialOutBytes(short offsetByte, short size, unsigned char* data);
            WMXAPIFUNC GetInitialOutBit(short byte, short bit, unsigned char* data);
            WMXAPIFUNC GetInitialOutByte(short offsetByte, unsigned char* data);
            WMXAPIFUNC GetInitialOutBytes(short offsetByte, short size, unsigned char* data);
        };

    } // namespace common

    // WMXLIB class - maintains WMX 1.5 interface, internally uses WMX3
    class WMXBROKER_API WMXLIB {
    private:
        wmx3Api::WMX3Api* wmx3;
        wmx3Api::CoreMotion* coreMotion;
        wmx3Api::Io* wmx3Io;
        bool isConnected;

        // Initial output buffer
        unsigned char initialOut[MAX_IOOUTSIZE];

    public:
        WMXLIB();
        ~WMXLIB();

        // WMX3 internal object access (for Broker internal use)
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

        // Io class instance
        common::Io* io;

        // Error code
        WMX_API_ERROR_CODE lastError;
    };

} // namespace wmxAPI

#endif // WMXBROKER_H
