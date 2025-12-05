// BasicMotionBroker.h
// basicMotion namespace - WMX 1.5 API to WMX3 API Broker

#ifndef BASICMOTIONBROKER_H
#define BASICMOTIONBROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace BasicMotion {

    class WMXBROKER_API BasicMotion {
    private:
        WMXLIB* wmxlib;

    public:
        BasicMotion(WMXLIB* lib);
        ~BasicMotion();

        // Position commands (5 params)
        WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec);
        WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec);

        // Position commands with starting/end velocity (7 params)
        WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec,
            double startingVelocity, double endVelocity);
        WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec,
            double startingVelocity, double endVelocity);

        // Jog command
        WMXAPIFUNC StartJog(short axis, double velocity, double acc);

        // Stop commands
        WMXAPIFUNC StopAxis(int axis);
        WMXAPIFUNC QStopAxis(int axis);
        WMXAPIFUNC TimeStopAxis(int axis, double time);

        // Wait/Pause/Resume
        WMXAPIFUNC WaitAxis(int axis);
        WMXAPIFUNC PauseAxis(int axis);
        WMXAPIFUNC ResumeAxis(int axis);
    };

} // namespace BasicMotion
} // namespace wmxAPI

#endif // BASICMOTIONBROKER_H
