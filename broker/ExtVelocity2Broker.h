// ExtVelocity2Broker.h
// extVelocity2 namespace - WMX 1.5 API to WMX3 API Broker
// Extended velocity control with jerk ratio

#ifndef EXTVELOCITY2BROKER_H
#define EXTVELOCITY2BROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace extVelocity2 {

    class WMXBROKER_API ExtVelocity2 {
    private:
        WMXLIB* wmxlib;

    public:
        ExtVelocity2(WMXLIB* lib);
        ~ExtVelocity2();

        // Jerk ratio velocity commands
        WMXAPIFUNC StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity,
            double acc, double dec, double jerkAccRatio, double jerkDecRatio);

        // Extended velocity with starting velocity
        WMXAPIFUNC StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity,
            double acc, double dec, double jerkAccRatio, double jerkDecRatio,
            double startingVelocity);

        // Override velocity
        WMXAPIFUNC OverrideVel(short axis, double velocity, double acc, double dec);
    };

} // namespace extVelocity2
} // namespace wmxAPI

#endif // EXTVELOCITY2BROKER_H
