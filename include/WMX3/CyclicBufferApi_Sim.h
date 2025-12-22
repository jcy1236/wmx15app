// CyclicBufferApi_Sim.h
// WMX3 CyclicBuffer API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::CyclicBuffer interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef CYCLICBUFFERAPI_SIM_H
#define CYCLICBUFFERAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    //=========================================================================
    // CyclicBuffer class
    //=========================================================================
    class CyclicBuffer
    {
    public:
        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_CyclicBuffer_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_CyclicBuffer_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // CYCLICBUFFERAPI_SIM_H
