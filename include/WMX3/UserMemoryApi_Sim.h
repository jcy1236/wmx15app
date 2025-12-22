// UserMemoryApi_Sim.h
// WMX3 UserMemory API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::UserMemory interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef USERMEMORYAPI_SIM_H
#define USERMEMORYAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    //=========================================================================
    // UserMemory class
    //=========================================================================
    class UserMemory
    {
    public:
        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_UserMemory_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_UserMemory_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // USERMEMORYAPI_SIM_H
