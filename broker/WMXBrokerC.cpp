// WMXBrokerC.cpp
// C-style API implementation for VS2012 compatibility

#include "WMXBrokerC.h"
#include "WMXBroker.h"
#include "BasicMotionBroker.h"
#include "ExtMotion1Broker.h"
#include "ExtMotion2Broker.h"
#include "ExtList2Broker.h"
#include "AxisControlBroker.h"
#include "HomeBroker.h"
#include "ConfigBroker.h"
#include "BasicVelocityBroker.h"
#include "ExtVelocity2Broker.h"
#include "TorqueControlBroker.h"

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

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_SetDeviceName(const TCHAR* name)
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
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->StartPos(axis, target, velocity, acc, dec);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartMov(short axis, double target, double velocity, double acc, double dec)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->StartMov(axis, target, velocity, acc, dec);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartJog(short axis, double velocity, double acc)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->StartJog(axis, velocity, acc);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StopAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->StopAxis(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_QStopAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->QStopAxis(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_TimeStopAxis(int axis, double time)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->TimeStopAxis(axis, time);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StopAxisSelection(WMX_AXIS_SELECTION* axis_selection)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->StopAxis(axis_selection);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_QStopAxisSelection(WMX_AXIS_SELECTION* axis_selection)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->QStopAxis(axis_selection);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_TimeStopAxisSelection(WMX_AXIS_SELECTION* axis_selection, double time)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->TimeStopAxis(axis_selection, time);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartPosEx(short axis, double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->StartPos(axis, target, velocity, acc, dec, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartMovEx(short axis, double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->StartMov(axis, target, velocity, acc, dec, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_WaitAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->WaitAxis(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_PauseAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->PauseAxis(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_ResumeAxis(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicMotion == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicMotion->ResumeAxis(axis);
}

//=============================================================================
// extMotion1 APIs (Jerk - pulse/s^3)
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkPos(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
    double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion1 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion1->StartJerkPos(axis, static_cast<WMX_PROFILE_TYPE>(profile), target,
        velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkMov(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
    double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion1 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion1->StartJerkMov(axis, static_cast<WMX_PROFILE_TYPE>(profile), target,
        velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkJog(short axis, int profile,
    double velocity, double acc, double jerkAcc)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion1 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion1->StartJerkJog(axis, static_cast<WMX_PROFILE_TYPE>(profile),
        velocity, acc, jerkAcc);
}

//=============================================================================
// extMotion2 APIs (Jerk Ratio)
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkPos(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion2->StartJerkPos(axis, static_cast<WMX_PROFILE_TYPE>(profile), target,
        velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkMov(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion2->StartJerkMov(axis, static_cast<WMX_PROFILE_TYPE>(profile), target,
        velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkJog(short axis, int profile,
    double velocity, double acc, double jerkAccRatio)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion2->StartJerkJog(axis, static_cast<WMX_PROFILE_TYPE>(profile),
        velocity, acc, jerkAccRatio);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StopJerkJogAtPos(short axis, int profile, double target,
    double dec, double jerkDecRatio)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion2->StopJerkJogAtPos(axis, static_cast<WMX_PROFILE_TYPE>(profile),
        target, dec, jerkDecRatio);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkCoordinatedPos(short axis, int profile,
    double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion2->StartJerkCoordinatedPos(axis, static_cast<WMX_PROFILE_TYPE>(profile),
        target, velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity,
        axis2, axis2target, axis2smoothRatio);
}

//=============================================================================
// extList2 APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_BeginList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->BeginList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_EndList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->EndList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ExecuteList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->ExecuteList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_AbortList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->AbortList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ClearList(unsigned int channel)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->ClearList(channel);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_GetListStatus(unsigned int channel, WMX_LIST_STATUS* pStatus)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->GetListStatus(channel, pStatus);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkCoordinatedPos(unsigned int channel, short axis, int profile,
    double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->ListJerkCoordinatedPos(channel, axis, static_cast<WMX_PROFILE_TYPE>(profile),
        target, velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity,
        axis2, axis2target, axis2smoothRatio);
}

//=============================================================================
// AxisControl APIs (common namespace)
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetAxisMode(short axis, int* pMode)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    WMX_AXIS_MODE mode;
    long result = g_wmxlib->AxisControl->GetAxisMode(axis, &mode);
    if (result == 0 && pMode != nullptr) {
        *pMode = static_cast<int>(mode);
    }
    return result;
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_SetAxisMode(short axis, int mode)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->SetAxisMode(axis, static_cast<WMX_AXIS_MODE>(mode));
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_ServoOn(short axis, int on)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->ServoOn(axis, on);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_ServoOnRange(short firstAxis, short lastAxis, int on)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->ServoOn(firstAxis, lastAxis, on);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_AmpAlarmClear(short axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->AmpAlarmClear(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_AmpAlarmClearRange(short firstAxis, short lastAxis)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->AmpAlarmClear(firstAxis, lastAxis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_AxisAlarmClear(short axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->AxisAlarmClear(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_AxisAlarmClearRange(short firstAxis, short lastAxis)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->AxisAlarmClear(firstAxis, lastAxis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetPosCommand(short axis, double* pPosition)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->GetPosCommand(axis, pPosition);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetPosFeedback(short axis, double* pPosition)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->GetPosFeedback(axis, pPosition);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetVelCommand(short axis, double* pVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->GetVelCommand(axis, pVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetVelFeedback(short axis, double* pVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->AxisControl == nullptr) {
        return -1;
    }
    return g_wmxlib->AxisControl->GetVelFeedback(axis, pVelocity);
}

//=============================================================================
// Home APIs (common namespace)
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_StartHome(int axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->StartHome(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_StartHomeRange(int firstAxis, int lastAxis)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->StartHome(firstAxis, lastAxis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_Continue(short axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->Continue(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_Cancel(short axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->Cancel(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_SetFeedbackPosition(short axis, double position)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->SetFeedbackPosition(axis, position);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_SetCommandPosition(short axis, double position)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->SetCommandPosition(axis, position);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_SetCmdPosToFbPos(short axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->SetCmdPosToFbPos(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_GetHomeData(WMX_HOME_DATA* pHomeData)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->GetHomeData(pHomeData);
}

//=============================================================================
// Config APIs (common namespace)
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisHomeParam(short axis, WMX_HOME_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->GetAxisHomeParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisHomeParam(short axis, WMX_HOME_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisHomeParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->GetAxisFeedbackParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisFeedbackParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisLimitParam(short axis, WMX_LIMIT_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->GetAxisLimitParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisLimitParam(short axis, WMX_LIMIT_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisLimitParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisSystemParam(short axis, WMX_SYSTEM_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->GetAxisSystemParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisSystemParam(short axis, WMX_SYSTEM_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisSystemParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisAlarmParam(short axis, WMX_ALARM_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->GetAxisAlarmParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisAlarmParam(short axis, WMX_ALARM_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisAlarmParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisMotionParam(short axis, WMX_MOTION_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->GetAxisMotionParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisMotionParam(short axis, WMX_MOTION_PARAM* pParam)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisMotionParam(axis, pParam);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisSingleTurn(short axis, int* pEnable, unsigned int* pEncoderCount)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    bool enable = false;
    long result = g_wmxlib->Config->GetAxisSingleTurn(axis, &enable, pEncoderCount);
    if (result == 0 && pEnable != nullptr) {
        *pEnable = enable ? 1 : 0;
    }
    return result;
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisSingleTurn(short axis, int enable, unsigned int encoderCount)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisSingleTurn(axis, enable != 0, encoderCount);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisMultiplier(short axis, unsigned int* pMultiplier)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->GetAxisMultiplier(axis, pMultiplier);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisMultiplier(short axis, unsigned int multiplier)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisMultiplier(axis, multiplier);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisVelocityFeedforwardGain(short axis, double* pGain)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->GetAxisVelocityFeedforwardGain(axis, pGain);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisVelocityFeedforwardGain(short axis, double gain)
{
    if (g_wmxlib == nullptr || g_wmxlib->Config == nullptr) {
        return -1;
    }
    return g_wmxlib->Config->SetAxisVelocityFeedforwardGain(axis, gain);
}

//=============================================================================
// BasicVelocity APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_StopVel(short axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicVelocity == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicVelocity->StopVel(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_StopVelRange(short firstAxis, short lastAxis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicVelocity == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicVelocity->StopVel(firstAxis, lastAxis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_QStopVel(short axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicVelocity == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicVelocity->QStopVel(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_QStopVelRange(short firstAxis, short lastAxis)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicVelocity == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicVelocity->QStopVel(firstAxis, lastAxis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_TimedStopVel(short axis, double timeMilliseconds)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicVelocity == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicVelocity->TimedStopVel(axis, timeMilliseconds);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_TimedStopVelRange(short firstAxis, short lastAxis, double timeMilliseconds)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicVelocity == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicVelocity->TimedStopVel(firstAxis, lastAxis, timeMilliseconds);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_StartVel(short axis, int profile, double velocity, double acc, double dec)
{
    if (g_wmxlib == nullptr || g_wmxlib->BasicVelocity == nullptr) {
        return -1;
    }
    return g_wmxlib->BasicVelocity->StartVel(axis, static_cast<WMX_PROFILE_TYPE>(profile), velocity, acc, dec);
}

//=============================================================================
// ExtVelocity2 APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtVelocity2_StartJerkVel(short axis, int profile, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtVelocity2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtVelocity2->StartJerkVel(axis, static_cast<WMX_PROFILE_TYPE>(profile), velocity, acc, dec, jerkAccRatio, jerkDecRatio);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtVelocity2_StartJerkVelWithStarting(short axis, int profile, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtVelocity2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtVelocity2->StartJerkVel(axis, static_cast<WMX_PROFILE_TYPE>(profile), velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtVelocity2_OverrideVel(short axis, double velocity, double acc, double dec)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtVelocity2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtVelocity2->OverrideVel(axis, velocity, acc, dec);
}

//=============================================================================
// TorqueControl APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_GetMaxTrqLimit(short axis, double* pTorque)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->GetMaxTrqLimit(axis, pTorque);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_SetMaxTrqLimit(short axis, double torque)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->SetMaxTrqLimit(axis, torque);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_GetPositiveTrqLimit(short axis, double* pTorque)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->GetPositiveTrqLimit(axis, pTorque);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_SetPositiveTrqLimit(short axis, double torque)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->SetPositiveTrqLimit(axis, torque);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_GetNegativeTrqLimit(short axis, double* pTorque)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->GetNegativeTrqLimit(axis, pTorque);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_SetNegativeTrqLimit(short axis, double torque)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->SetNegativeTrqLimit(axis, torque);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StartTrq(short axis, double torque)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->StartTrq(axis, torque);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StartTrqWithMaxSpeed(short axis, double torque, double maxMotorSpeed)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->StartTrq(axis, torque, maxMotorSpeed);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StopTrq(short axis)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->StopTrq(axis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StopTrqRange(short firstAxis, short lastAxis)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->StopTrq(firstAxis, lastAxis);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StartRampTimeTrq(short axis, double torque, unsigned int rampCycleTime)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->StartRampTimeTrq(axis, torque, rampCycleTime);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StartRampRateTrq(short axis, double torque, double rampRate)
{
    if (g_wmxlib == nullptr || g_wmxlib->TorqueControl == nullptr) {
        return -1;
    }
    return g_wmxlib->TorqueControl->StartRampRateTrq(axis, torque, rampRate);
}

//=============================================================================
// ExtMotion2 Block APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkPosBlock(PosBlockExt2* mpos_block)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion2->StartJerkPos(mpos_block);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkCoordinatedPosBlock(CoordinatedPosBlockExt2* mpos_block)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion2->StartJerkCoordinatedPos(mpos_block);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkLinIntPos(IntBlockExt2* mpos_block)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtMotion2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtMotion2->StartJerkLinIntPos(mpos_block);
}

//=============================================================================
// ExtList2 ListJerkPos APIs
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkPos(unsigned int channel, short axis, int profile,
    double target, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->ListJerkPos(channel, axis, static_cast<WMX_PROFILE_TYPE>(profile),
        target, velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkPosBlock(unsigned int channel, PosBlockListExt2* mpos_block)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->ListJerkPos(channel, mpos_block);
}

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkCoordinatedPosBlock(unsigned int channel, CoordinatedPosBlockListExt2* mpos_block)
{
    if (g_wmxlib == nullptr || g_wmxlib->ExtList2 == nullptr) {
        return -1;
    }
    return g_wmxlib->ExtList2->ListJerkCoordinatedPos(channel, mpos_block);
}

//=============================================================================
// Home AxisSelection API
//=============================================================================

extern "C" WMXBROKER_CAPI long __stdcall WMXBroker_Home_StartHomeAxisSelection(WMX_AXIS_SELECTION* axis_selection)
{
    if (g_wmxlib == nullptr || g_wmxlib->Home == nullptr) {
        return -1;
    }
    return g_wmxlib->Home->StartHome(axis_selection);
}
