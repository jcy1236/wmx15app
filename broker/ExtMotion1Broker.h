// ExtMotion1Broker.h
// extMotion1 namespace - WMX 1.5 API to WMX3 API Broker
// Jerk-based motion (pulse/s^3)

#ifndef EXTMOTION1BROKER_H
#define EXTMOTION1BROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace ExtMotion1 {

    class WMXBROKER_API ExtMotion1 {
    private:
        WMXLIB* wmxlib;

    public:
        ExtMotion1(WMXLIB* lib);
        ~ExtMotion1();

        // Jerk position commands
        WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target,
            double velocity, double acc, double dec, double jerkAcc, double jerkDec,
            double startingVelocity, double endVelocity);

        WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target,
            double velocity, double acc, double dec, double jerkAcc, double jerkDec,
            double startingVelocity, double endVelocity);

        // Jerk jog command
        WMXAPIFUNC StartJerkJog(short axis, WMX_PROFILE_TYPE profile,
            double velocity, double acc, double jerkAcc);
    };

} // namespace ExtMotion1
} // namespace wmxAPI

#endif // EXTMOTION1BROKER_H
