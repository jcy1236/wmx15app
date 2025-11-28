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

#ifdef __cplusplus
}
#endif

#endif // WMXBROKER_C_H
