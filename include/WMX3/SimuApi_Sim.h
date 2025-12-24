// SimuApi_Sim.h
// WMX3 SimuApi Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::simuApi::Simu interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef SIMUAPI_SIM_H
#define SIMUAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    namespace simuApi
    {
        //=====================================================================
        // SimuErrorCode - Error codes for simulation module
        //=====================================================================
        class SimuErrorCode : public ErrorCode
        {
        public:
            enum
            {
                SimuError = 0x00001000
            };
        };

        //=====================================================================
        // Simu class - Simulation control and monitoring
        //=====================================================================
        class Simu
        {
        public:
            // Static error handling methods
            static long ErrorToString(int errCode, char *pString, unsigned int size)
            {
                return WMX3Broker_Simu_ErrorToString(errCode, pString, size);
            }

            static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
            {
                return WMX3Broker_Simu_ErrorToStringW(errCode, pString, size);
            }
        };

    } // namespace simuApi
} // namespace wmx3Api

#endif // SIMUAPI_SIM_H
