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

namespace basicMotion {

// BasicMotion wrapper class - WMX 1.5 compatible interface
class BasicMotion {
public:
    BasicMotion() {}

    WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec) {
        return WMXBroker_BasicMotion_StartPos(axis, target, velocity, acc, dec);
    }
    WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec) {
        return WMXBroker_BasicMotion_StartMov(axis, target, velocity, acc, dec);
    }
    WMXAPIFUNC StartJog(short axis, double velocity, double acc) {
        return WMXBroker_BasicMotion_StartJog(axis, velocity, acc);
    }
    WMXAPIFUNC StopAxis(int axis) {
        return WMXBroker_BasicMotion_StopAxis(axis);
    }
    WMXAPIFUNC QStopAxis(int axis) {
        return WMXBroker_BasicMotion_QStopAxis(axis);
    }
    WMXAPIFUNC WaitAxis(int axis) {
        return WMXBroker_BasicMotion_WaitAxis(axis);
    }
    WMXAPIFUNC PauseAxis(int axis) {
        return WMXBroker_BasicMotion_PauseAxis(axis);
    }
    WMXAPIFUNC ResumeAxis(int axis) {
        return WMXBroker_BasicMotion_ResumeAxis(axis);
    }
};

} // namespace basicMotion

namespace extMotion1 {

// ExtMotion1 wrapper class - Jerk (pulse/s^3) based motion
class ExtMotion1 {
public:
    ExtMotion1() {}

    WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target,
        double velocity, double acc, double dec, double jerkAcc, double jerkDec,
        double startingVelocity, double endVelocity) {
        return WMXBroker_ExtMotion1_StartJerkPos(axis, static_cast<int>(profile), target,
            velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity);
    }
    WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target,
        double velocity, double acc, double dec, double jerkAcc, double jerkDec,
        double startingVelocity, double endVelocity) {
        return WMXBroker_ExtMotion1_StartJerkMov(axis, static_cast<int>(profile), target,
            velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity);
    }
    WMXAPIFUNC StartJerkJog(short axis, WMX_PROFILE_TYPE profile,
        double velocity, double acc, double jerkAcc) {
        return WMXBroker_ExtMotion1_StartJerkJog(axis, static_cast<int>(profile),
            velocity, acc, jerkAcc);
    }
};

} // namespace extMotion1

namespace extMotion2 {

// ExtMotion2 wrapper class - Jerk ratio based motion
class ExtMotion2 {
public:
    ExtMotion2() {}

    WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target,
        double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
        double startingVelocity, double endVelocity) {
        return WMXBroker_ExtMotion2_StartJerkPos(axis, static_cast<int>(profile), target,
            velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
    }
    WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target,
        double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
        double startingVelocity, double endVelocity) {
        return WMXBroker_ExtMotion2_StartJerkMov(axis, static_cast<int>(profile), target,
            velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
    }
    WMXAPIFUNC StartJerkJog(short axis, WMX_PROFILE_TYPE profile,
        double velocity, double acc, double jerkAccRatio) {
        return WMXBroker_ExtMotion2_StartJerkJog(axis, static_cast<int>(profile),
            velocity, acc, jerkAccRatio);
    }
};

} // namespace extMotion2

namespace extList2 {

// ExtList2 wrapper class - List based motion
class ExtList2 {
public:
    ExtList2() {}

    WMXAPIFUNC BeginList(unsigned int channel) {
        return WMXBroker_ExtList2_BeginList(channel);
    }
    WMXAPIFUNC EndList(unsigned int channel) {
        return WMXBroker_ExtList2_EndList(channel);
    }
    WMXAPIFUNC ExecuteList(unsigned int channel) {
        return WMXBroker_ExtList2_ExecuteList(channel);
    }
    WMXAPIFUNC AbortList(unsigned int channel) {
        return WMXBroker_ExtList2_AbortList(channel);
    }
    WMXAPIFUNC ClearList(unsigned int channel) {
        return WMXBroker_ExtList2_ClearList(channel);
    }
    WMXAPIFUNC GetListStatus(unsigned int channel, WMX_LIST_STATUS* pStatus) {
        return WMXBroker_ExtList2_GetListStatus(channel, pStatus);
    }
};

} // namespace extList2

// WMXLIB wrapper class - WMX 1.5 compatible interface
class WMXLIB {
public:
    common::Io* io;
    basicMotion::BasicMotion* basicMotion;
    extMotion1::ExtMotion1* extMotion1;
    extMotion2::ExtMotion2* extMotion2;
    extList2::ExtList2* extList2;

    WMXLIB() {
        io = new common::Io(this);
        basicMotion = new basicMotion::BasicMotion();
        extMotion1 = new extMotion1::ExtMotion1();
        extMotion2 = new extMotion2::ExtMotion2();
        extList2 = new extList2::ExtList2();
    }

    ~WMXLIB() {
        delete io;
        io = NULL;
        delete basicMotion;
        basicMotion = NULL;
        delete extMotion1;
        extMotion1 = NULL;
        delete extMotion2;
        extMotion2 = NULL;
        delete extList2;
        extList2 = NULL;
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

    // Extended System APIs
    WMXAPIFUNC GetLastError() {
        return WMXBroker_GetLastError();
    }

    WMXAPIFUNC SetDeviceName(TCHAR* name) {
        return WMXBroker_SetDeviceName(name);
    }

    WMXAPIFUNC GetActiveDeviceList(WMX_ACT_DEV_LIST* list) {
        return WMXBroker_GetActiveDeviceList(list);
    }

    WMXAPIFUNC ForceCloseDevice(int id) {
        return WMXBroker_ForceCloseDevice(id);
    }
};

} // namespace wmxAPI

#endif // WMXBROKER_CLIENT_H
