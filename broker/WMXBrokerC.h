// WMXBrokerC.h
// C-style API for VS2012 compatibility
// These functions can be called from any compiler version

#ifndef WMXBROKER_C_H
#define WMXBROKER_C_H

#include <windows.h>
#include <tchar.h>
#include "wmxapi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

// DLL Export/Import macros
#ifdef WMXBROKER_EXPORTS
#define WMXBROKER_CAPI __declspec(dllexport)
#else
#define WMXBROKER_CAPI __declspec(dllimport)
#endif

//=============================================================================
// System APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_CreateDevice(TCHAR* path, int type);
WMXBROKER_CAPI long __stdcall WMXBroker_CloseDevice(void);
WMXBROKER_CAPI long __stdcall WMXBroker_StartCommunication(void);
WMXBROKER_CAPI long __stdcall WMXBroker_StopCommunication(void);
WMXBROKER_CAPI long __stdcall WMXBroker_GetStatus(WMX_STATUS* st);
WMXBROKER_CAPI long __stdcall WMXBroker_GetStatusAxis(WMX_STATUS* st, short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_GetStatusRange(WMX_STATUS* st, short firstAxis, short lastAxis);
WMXBROKER_CAPI long __stdcall WMXBroker_GetVersion(double* pCeVersion, double* pPeVersion);

//=============================================================================
// Extended System APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_GetLastError(void);
WMXBROKER_CAPI long __stdcall WMXBroker_SetDeviceName(TCHAR* name);
WMXBROKER_CAPI long __stdcall WMXBroker_GetActiveDeviceList(WMX_ACT_DEV_LIST* list);
WMXBROKER_CAPI long __stdcall WMXBroker_ForceCloseDevice(int id);

//=============================================================================
// I/O Output APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutBit(short byte, short bit, unsigned char data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutByte(short offsetByte, unsigned char data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutBytes(short offsetByte, short size, unsigned char* data);

//=============================================================================
// I/O Input APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInBit(short byte, short bit, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInByte(short offsetByte, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInBytes(short offsetByte, short size, unsigned char* data);

//=============================================================================
// I/O Output Read APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutBit(short byte, short bit, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutByte(short offsetByte, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutBytes(short offsetByte, short size, unsigned char* data);

//=============================================================================
// I/O Initial Output APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutBit(short byte, short bit, unsigned char data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutByte(short offsetByte, unsigned char data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutBytes(short offsetByte, short size, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutBit(short byte, short bit, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutByte(short offsetByte, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutBytes(short offsetByte, short size, unsigned char* data);

//=============================================================================
// basicMotion APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartPos(short axis, double target, double velocity, double acc, double dec);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartMov(short axis, double target, double velocity, double acc, double dec);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartJog(short axis, double velocity, double acc);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StopAxis(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_QStopAxis(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_WaitAxis(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_PauseAxis(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_ResumeAxis(int axis);

//=============================================================================
// extMotion1 APIs (Jerk - pulse/s^3)
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkPos(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
    double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkMov(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
    double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkJog(short axis, int profile,
    double velocity, double acc, double jerkAcc);

//=============================================================================
// extMotion2 APIs (Jerk Ratio)
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkPos(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkMov(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkJog(short axis, int profile,
    double velocity, double acc, double jerkAccRatio);

//=============================================================================
// extList2 APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_BeginList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_EndList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ExecuteList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_AbortList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ClearList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_GetListStatus(unsigned int channel, WMX_LIST_STATUS* pStatus);

#ifdef __cplusplus
}
#endif

#endif // WMXBROKER_C_H
