// BasicMotionBroker.h
// basicMotion namespace - WMX 1.5 API to WMX3 API Broker

#ifndef BASICMOTIONBROKER_H
#define BASICMOTIONBROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace basicMotion {

    class WMXBROKER_API BasicMotion {
    private:
        WMXLIB* wmxlib;

    public:
        BasicMotion(WMXLIB* lib);
        ~BasicMotion();

        // Position commands
        WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec);
        WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec);

        // Jog command
        WMXAPIFUNC StartJog(short axis, double velocity, double acc);

        // Stop commands
        WMXAPIFUNC StopAxis(int axis);
        WMXAPIFUNC QStopAxis(int axis);

        // Wait/Pause/Resume
        WMXAPIFUNC WaitAxis(int axis);
        WMXAPIFUNC PauseAxis(int axis);
        WMXAPIFUNC ResumeAxis(int axis);
    };

} // namespace basicMotion
} // namespace wmxAPI

#endif // BASICMOTIONBROKER_H
