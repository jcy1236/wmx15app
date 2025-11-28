// WMXBrokerC.cpp
// C-style API implementation for VS2012 compatibility

#include "WMXBrokerC.h"
#include "WMXBroker.h"

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
