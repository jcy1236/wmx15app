// PMMotionApi_Sim.h
// WMX3 PMMotion API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::PMMotion interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef PMMOTIONAPI_SIM_H
#define PMMOTIONAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    class PMMotionErrorCode : public ErrorCode
    {
    public:
        enum
        {
            PMErrorCode = 0x00019000,
            AxisIsOffline,
            AxisIsNotServoOn,
            AxisIsInUse,
            PPModeNotSupported,
            PVModeNotSupported,
            TQModeNotSupported,
            HMModeNotSupported,
            InvalidProfileSetting,
        };

        static int ConvertPMMotionErrorCode(int errCode);
    };

    //=========================================================================
    // PMMotion class
    //=========================================================================
    class PMMotion
    {
    public:
        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_PMMotion_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_PMMotion_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // PMMOTIONAPI_SIM_H
