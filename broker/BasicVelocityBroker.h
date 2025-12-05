// BasicVelocityBroker.h
// basicVelocity namespace - WMX 1.5 API to WMX3 API Broker
// Basic velocity control functions (Stop, QuickStop)

#ifndef BASICVELOCITYBROKER_H
#define BASICVELOCITYBROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace basicVelocity {

    class WMXBROKER_API BasicVelocity {
    private:
        WMXLIB* wmxlib;

    public:
        BasicVelocity(WMXLIB* lib);
        ~BasicVelocity();

        // Velocity stop
        WMXAPIFUNC StopVel(short axis);
        WMXAPIFUNC StopVel(short firstAxis, short lastAxis);

        // Quick stop
        WMXAPIFUNC QStopVel(short axis);
        WMXAPIFUNC QStopVel(short firstAxis, short lastAxis);

        // Timed stop
        WMXAPIFUNC TimedStopVel(short axis, double timeMilliseconds);
        WMXAPIFUNC TimedStopVel(short firstAxis, short lastAxis, double timeMilliseconds);

        // Basic velocity start
        WMXAPIFUNC StartVel(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, double dec);
    };

} // namespace basicVelocity
} // namespace wmxAPI

#endif // BASICVELOCITYBROKER_H
