// ExtMotion2Broker.h
// extMotion2 namespace - WMX 1.5 API to WMX3 API Broker
// Jerk ratio-based motion

#ifndef EXTMOTION2BROKER_H
#define EXTMOTION2BROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace ExtMotion2 {

    class WMXBROKER_API ExtMotion2 {
    private:
        WMXLIB* wmxlib;

    public:
        ExtMotion2(WMXLIB* lib);
        ~ExtMotion2();

        // Jerk ratio position commands
        WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target,
            double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
            double startingVelocity, double endVelocity);

        WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target,
            double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
            double startingVelocity, double endVelocity);

        // Jerk ratio jog command
        WMXAPIFUNC StartJerkJog(short axis, WMX_PROFILE_TYPE profile,
            double velocity, double acc, double jerkAccRatio);
    };

} // namespace ExtMotion2
} // namespace wmxAPI

#endif // EXTMOTION2BROKER_H
