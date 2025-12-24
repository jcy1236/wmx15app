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
    class PosCommand
    {
    public:
        PosCommand();

        int axis;
        double target;
        Profile profile;
    };

    class CoordinatedPosCommand
    {
    public:
        CoordinatedPosCommand();

        PosCommand posCommand;
        int axis2;
        double axis2Target;
        double axis2SmoothRatio;
    };

    //=========================================================================
    // AdvSync class (Advanced Synchronization)
    //=========================================================================
    class AdvancedMotion;

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

        AdvancedMotion() : advSync(new AdvSync(this)) {}
        ~AdvancedMotion() { delete advSync; }

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
