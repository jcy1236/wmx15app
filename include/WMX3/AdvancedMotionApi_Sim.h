// AdvancedMotionApi_Sim.h
// WMX3 AdvancedMotion API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::AdvancedMotion interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef ADVANCEDMOTIONAPI_SIM_H
#define ADVANCEDMOTIONAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    //=========================================================================
    // AdvancedMotion class
    //=========================================================================
    class AdvancedMotion
    {
    public:
        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_AdvancedMotion_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_AdvancedMotion_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // ADVANCEDMOTIONAPI_SIM_H
