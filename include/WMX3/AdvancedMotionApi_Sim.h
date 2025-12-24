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
#include "CoreMotionApi_Sim.h"

namespace wmx3Api
{
    class PosCommand;
    class CoordinatedPosCommand;

    //=========================================================================
    // AdvMotion class (Advanced Motion Control)
    //=========================================================================
    class AdvancedMotion;

    class AdvMotion
    {
    private:
        AdvancedMotion *amApi;

    public:
        AdvMotion(AdvancedMotion *api) : amApi(api) {}

        bool IsDeviceValid()
        {
            return WMX3Broker_AdvancedMotion_AdvMotion_IsDeviceValid() != 0;
        }

        long StartCoordinatedPos(CoordinatedPosCommand *pPosCommand)
        {
            return WMX3Broker_AdvancedMotion_AdvMotion_StartCoordinatedPos(pPosCommand);
        }
    };

    //=========================================================================
    // AdvSync class (Advanced Synchronization)
    //=========================================================================

    class AdvSync
    {
    private:
        AdvancedMotion *amApi;

    public:
        AdvSync(AdvancedMotion *api) : amApi(api) {}

        bool IsDeviceValid()
        {
            return WMX3Broker_AdvancedMotion_AdvSync_IsDeviceValid() != 0;
        }
    };

    //=========================================================================
    // AdvancedMotion class
    //=========================================================================
    class AdvancedMotion
    {
    public:
        AdvSync *advSync;
        AdvMotion *advMotion;

        AdvancedMotion() : advSync(new AdvSync(this)), advMotion(new AdvMotion(this)) {}
        ~AdvancedMotion() { delete advSync; delete advMotion; }

        bool IsDeviceValid()
        {
            return WMX3Broker_AdvancedMotion_IsDeviceValid() != 0;
        }

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
