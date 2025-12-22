// CompensationApi_Sim.h
// WMX3 Compensation API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::Compensation interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef COMPENSATIONAPI_SIM_H
#define COMPENSATIONAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    class CompensationErrorCode : public ErrorCode
    {
    public:
        enum
        {
            PitchErrorCompensationIsEnabled = 0x00015000,
            PitchErrorCompensationIsDisabled,
            PitchErrorCompensationDataIsNotSet,
            BacklashCompensationIsEnabled,
            BacklashCompensationIsDisabled,
            PitchCountOutOfRange,
            PitchOriginIndexOutOfRange,
            PitchIntervalOutOfRange,
            EdgeDropoffDistanceOutOfRange,
            CompensationAxisNotPosMode,
            ReferenceAxisNotPosMode,
            NotUsingPitchIntervalMode,
            NotUsingFreePositionMode,
            PitchPositionRangeTooLarge,
            PitchPositionNotInAscendingOrder
        };
    };

    //=========================================================================
    // Compensation class
    //=========================================================================
    class Compensation
    {
    public:
        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_Compensation_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_Compensation_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // COMPENSATIONAPI_SIM_H
