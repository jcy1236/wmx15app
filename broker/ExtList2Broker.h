// ExtList2Broker.h
// extList2 namespace - WMX 1.5 API to WMX3 API Broker
// List-based motion control

#ifndef EXTLIST2BROKER_H
#define EXTLIST2BROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace ExtList2 {

    class WMXBROKER_API ExtList2 {
    private:
        WMXLIB* wmxlib;

    public:
        ExtList2(WMXLIB* lib);
        ~ExtList2();

        // List management
        WMXAPIFUNC BeginList(unsigned int channel);
        WMXAPIFUNC EndList(unsigned int channel);
        WMXAPIFUNC ExecuteList(unsigned int channel);
        WMXAPIFUNC AbortList(unsigned int channel);
        WMXAPIFUNC ClearList(unsigned int channel);
        WMXAPIFUNC GetListStatus(unsigned int channel, WMX_LIST_STATUS* pStatus);

        // List motion commands (individual parameters)
        WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile,
            double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
            double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio);

        // ListJerkPos - individual parameters
        WMXAPIFUNC ListJerkPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile,
            double target, double velocity, double acc, double dec,
            double jerkAccRatio, double jerkDecRatio,
            double startingVelocity, double endVelocity);

        // ListJerkPos - block version
        WMXAPIFUNC ListJerkPos(unsigned int channel, PosBlockListExt2* mpos_block);

        // ListJerkCoordinatedPos - block version
        WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, CoordinatedPosBlockListExt2* mpos_block);
    };

} // namespace ExtList2
} // namespace wmxAPI

#endif // EXTLIST2BROKER_H
