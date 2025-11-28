// WMXBrokerClient.h
// Header-only wrapper class for VS2012 compatibility
// Provides wmxAPI::WMXLIB interface that internally calls C API
//
// Usage:
//   Replace #include "WMXLIB.h" with #include "WMXBrokerClient.h"
//   Link with WMXBroker.lib

#ifndef WMXBROKER_CLIENT_H
#define WMXBROKER_CLIENT_H

#include "WMXBrokerC.h"
#include "wmxapi_def.h"

namespace wmxAPI {

class WMXLIB;  // Forward declaration

namespace common {

// Io wrapper class - WMX 1.5 compatible interface
class Io {
public:
    WMXLIB* wmxlib;
    Io(WMXLIB* f) : wmxlib(f) {}

    // I/O Output APIs
    WMXAPIFUNC SetOutBit(short byte, short bit, unsigned char data) {
        return WMXBroker_Io_SetOutBit(byte, bit, data);
    }
    WMXAPIFUNC SetOutByte(short offsetByte, unsigned char data) {
        return WMXBroker_Io_SetOutByte(offsetByte, data);
    }
    WMXAPIFUNC SetOutBytes(short offsetByte, short size, unsigned char* data) {
        return WMXBroker_Io_SetOutBytes(offsetByte, size, data);
    }

    // I/O Input APIs
    WMXAPIFUNC GetInBit(short byte, short bit, unsigned char* data) {
        return WMXBroker_Io_GetInBit(byte, bit, data);
    }
    WMXAPIFUNC GetInByte(short offsetByte, unsigned char* data) {
        return WMXBroker_Io_GetInByte(offsetByte, data);
    }
    WMXAPIFUNC GetInBytes(short offsetByte, short size, unsigned char* data) {
        return WMXBroker_Io_GetInBytes(offsetByte, size, data);
    }

    // I/O Output Read APIs
    WMXAPIFUNC GetOutBit(short byte, short bit, unsigned char* data) {
        return WMXBroker_Io_GetOutBit(byte, bit, data);
    }
    WMXAPIFUNC GetOutByte(short offsetByte, unsigned char* data) {
        return WMXBroker_Io_GetOutByte(offsetByte, data);
    }
    WMXAPIFUNC GetOutBytes(short offsetByte, short size, unsigned char* data) {
        return WMXBroker_Io_GetOutBytes(offsetByte, size, data);
    }

    // I/O Initial Output APIs
    WMXAPIFUNC SetInitialOutBit(short byte, short bit, unsigned char data) {
        return WMXBroker_Io_SetInitialOutBit(byte, bit, data);
    }
    WMXAPIFUNC SetInitialOutByte(short offsetByte, unsigned char data) {
        return WMXBroker_Io_SetInitialOutByte(offsetByte, data);
    }
    WMXAPIFUNC SetInitialOutBytes(short offsetByte, short size, unsigned char* data) {
        return WMXBroker_Io_SetInitialOutBytes(offsetByte, size, data);
    }
    WMXAPIFUNC GetInitialOutBit(short byte, short bit, unsigned char* data) {
        return WMXBroker_Io_GetInitialOutBit(byte, bit, data);
    }
    WMXAPIFUNC GetInitialOutByte(short offsetByte, unsigned char* data) {
        return WMXBroker_Io_GetInitialOutByte(offsetByte, data);
    }
    WMXAPIFUNC GetInitialOutBytes(short offsetByte, short size, unsigned char* data) {
        return WMXBroker_Io_GetInitialOutBytes(offsetByte, size, data);
    }
};

} // namespace common

// WMXLIB wrapper class - WMX 1.5 compatible interface
class WMXLIB {
public:
    common::Io* io;

    WMXLIB() {
        io = new common::Io(this);
    }

    ~WMXLIB() {
        delete io;
        io = NULL;
    }

    // System APIs
    WMXAPIFUNC CreateDevice(TCHAR* path, PLTFRM_TYPE type) {
        return WMXBroker_CreateDevice(path, static_cast<int>(type));
    }

    WMXAPIFUNC CloseDevice() {
        return WMXBroker_CloseDevice();
    }

    WMXAPIFUNC StartCommunication() {
        return WMXBroker_StartCommunication();
    }

    WMXAPIFUNC StopCommunication() {
        return WMXBroker_StopCommunication();
    }

    WMXAPIFUNC GetStatus(WMX_STATUS* st) {
        return WMXBroker_GetStatus(st);
    }

    WMXAPIFUNC GetStatus(WMX_STATUS* st, short axis) {
        return WMXBroker_GetStatusAxis(st, axis);
    }

    WMXAPIFUNC GetStatus(WMX_STATUS* st, short firstAxis, short lastAxis) {
        return WMXBroker_GetStatusRange(st, firstAxis, lastAxis);
    }

    WMXAPIFUNC GetVersion(double* pCeVersion, double* pPeVersion) {
        return WMXBroker_GetVersion(pCeVersion, pPeVersion);
    }
};

} // namespace wmxAPI

#endif // WMXBROKER_CLIENT_H
