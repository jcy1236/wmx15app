// WMXBrokerC.cpp
// C-style API implementation for VS2012 compatibility

#include "WMXBrokerC.h"
#include "WMXBroker.h"
#include "BasicMotionBroker.h"
#include "ExtMotion1Broker.h"
#include "ExtMotion2Broker.h"
#include "ExtList2Broker.h"

// Global singleton instance
static wmxAPI::WMXLIB* g_wmxlib = nullptr;

//=============================================================================
// System APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_CreateDevice(TCHAR* path, int type)
{
    if (g_wmxlib != nullptr) {
        // Device already created - close first
        return -1;
    }

    g_wmxlib = new wmxAPI::WMXLIB();
    long result = g_wmxlib->CreateDevice(path, static_cast<PLTFRM_TYPE>(type));

    if (result != 0) {
        delete g_wmxlib;
        g_wmxlib = nullptr;
    }

    return result;
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_CloseDevice(void)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }

    long result = g_wmxlib->CloseDevice();
    delete g_wmxlib;
    g_wmxlib = nullptr;

    return result;
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_StartCommunication(void)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->StartCommunication();
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_StopCommunication(void)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->StopCommunication();
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_GetStatus(WMX_STATUS* st)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->GetStatus(st);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_GetStatusAxis(WMX_STATUS* st, short axis)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->GetStatus(st, axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_GetStatusRange(WMX_STATUS* st, short firstAxis, short lastAxis)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->GetStatus(st, firstAxis, lastAxis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_GetVersion(double* pCeVersion, double* pPeVersion)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->GetVersion(pCeVersion, pPeVersion);
}

//=============================================================================
// Extended System APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_GetLastError(void)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->GetLastError();
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_SetDeviceName(TCHAR* name)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->SetDeviceName(name);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_GetActiveDeviceList(WMX_ACT_DEV_LIST* list)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    return g_wmxlib->GetActiveDeviceList(list);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ForceCloseDevice(int id)
{
    if (g_wmxlib == nullptr) {
        return -1;
    }
    long result = g_wmxlib->ForceCloseDevice(id);
    delete g_wmxlib;
    g_wmxlib = nullptr;
    return result;
}

//=============================================================================
// I/O Output APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutBit(short byte, short bit, unsigned char data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->SetOutBit(byte, bit, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutByte(short offsetByte, unsigned char data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->SetOutByte(offsetByte, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutBytes(short offsetByte, short size, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->SetOutBytes(offsetByte, size, data);
}

//=============================================================================
// I/O Input APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInBit(short byte, short bit, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetInBit(byte, bit, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInByte(short offsetByte, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetInByte(offsetByte, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInBytes(short offsetByte, short size, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetInBytes(offsetByte, size, data);
}

//=============================================================================
// I/O Output Read APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutBit(short byte, short bit, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetOutBit(byte, bit, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutByte(short offsetByte, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetOutByte(offsetByte, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutBytes(short offsetByte, short size, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetOutBytes(offsetByte, size, data);
}

//=============================================================================
// I/O Initial Output APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutBit(short byte, short bit, unsigned char data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->SetInitialOutBit(byte, bit, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutByte(short offsetByte, unsigned char data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->SetInitialOutByte(offsetByte, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutBytes(short offsetByte, short size, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->SetInitialOutBytes(offsetByte, size, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutBit(short byte, short bit, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetInitialOutBit(byte, bit, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutByte(short offsetByte, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetInitialOutByte(offsetByte, data);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutBytes(short offsetByte, short size, unsigned char* data)
{
    if (g_wmxlib == nullptr || g_wmxlib->io == nullptr) {
        return -1;
    }
    return g_wmxlib->io->GetInitialOutBytes(offsetByte, size, data);
}

//=============================================================================
// basicMotion APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartPos(short axis, double target, double velocity, double acc, double dec)
{
    if (g_wmxlib == nullptr || g_wmxlib->basicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->basicMotion->StartPos(axis, target, velocity, acc, dec);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartMov(short axis, double target, double velocity, double acc, double dec)
{
    if (g_wmxlib == nullptr || g_wmxlib->basicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->basicMotion->StartMov(axis, target, velocity, acc, dec);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartJog(short axis, double velocity, double acc)
{
    if (g_wmxlib == nullptr || g_wmxlib->basicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->basicMotion->StartJog(axis, velocity, acc);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StopAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->basicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->basicMotion->StopAxis(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_QStopAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->basicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->basicMotion->QStopAxis(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_WaitAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->basicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->basicMotion->WaitAxis(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_PauseAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->basicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->basicMotion->PauseAxis(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_ResumeAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->basicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->basicMotion->ResumeAxis(axis);
}

//=============================================================================
// extMotion1 APIs (Jerk - pulse/s^3)
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkPos(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
    double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->extMotion1 == nullptr) {
        return -1;
    }
    return g_wmxlib->extMotion1->StartJerkPos(axis, static_cast<WMX_PROFILE_TYPE>(profile), target,
        velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkMov(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
    double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->extMotion1 == nullptr) {
        return -1;
    }
    return g_wmxlib->extMotion1->StartJerkMov(axis, static_cast<WMX_PROFILE_TYPE>(profile), target,
        velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkJog(short axis, int profile,
    double velocity, double acc, double jerkAcc)
{
    if (g_wmxlib == nullptr || g_wmxlib->extMotion1 == nullptr) {
        return -1;
    }
    return g_wmxlib->extMotion1->StartJerkJog(axis, static_cast<WMX_PROFILE_TYPE>(profile),
        velocity, acc, jerkAcc);
}

//=============================================================================
// extMotion2 APIs (Jerk Ratio)
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkPos(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->extMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extMotion2->StartJerkPos(axis, static_cast<WMX_PROFILE_TYPE>(profile), target,
        velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkMov(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->extMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extMotion2->StartJerkMov(axis, static_cast<WMX_PROFILE_TYPE>(profile), target,
        velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkJog(short axis, int profile,
    double velocity, double acc, double jerkAccRatio)
{
    if (g_wmxlib == nullptr || g_wmxlib->extMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extMotion2->StartJerkJog(axis, static_cast<WMX_PROFILE_TYPE>(profile),
        velocity, acc, jerkAccRatio);
}

//=============================================================================
// extList2 APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_BeginList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->extList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extList2->BeginList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_EndList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->extList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extList2->EndList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ExecuteList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->extList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extList2->ExecuteList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_AbortList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->extList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extList2->AbortList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ClearList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->extList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extList2->ClearList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_GetListStatus(unsigned int channel, WMX_LIST_STATUS* pStatus)
{
    if (g_wmxlib == nullptr || g_wmxlib->extList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->extList2->GetListStatus(channel, pStatus);
}
