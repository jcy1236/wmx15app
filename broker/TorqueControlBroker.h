// TorqueControlBroker.h
// torque namespace - WMX 1.5 API to WMX3 API Broker
// Torque control functions

#ifndef TORQUECONTROLBROKER_H
#define TORQUECONTROLBROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace torque {

    class WMXBROKER_API TorqueControl {
    private:
        WMXLIB* wmxlib;

    public:
        TorqueControl(WMXLIB* lib);
        ~TorqueControl();

        // Torque limits - Max
        WMXAPIFUNC GetMaxTrqLimit(short axis, double* pTorque);
        WMXAPIFUNC SetMaxTrqLimit(short axis, double torque);

        // Torque limits - Positive
        WMXAPIFUNC GetPositiveTrqLimit(short axis, double* pTorque);
        WMXAPIFUNC SetPositiveTrqLimit(short axis, double torque);

        // Torque limits - Negative
        WMXAPIFUNC GetNegativeTrqLimit(short axis, double* pTorque);
        WMXAPIFUNC SetNegativeTrqLimit(short axis, double torque);

        // Torque commands
        WMXAPIFUNC StartTrq(short axis, double torque);
        WMXAPIFUNC StartTrq(short axis, double torque, double maxMotorSpeed);
        WMXAPIFUNC StopTrq(short axis);
        WMXAPIFUNC StopTrq(short firstAxis, short lastAxis);

        // Ramp torque commands
        WMXAPIFUNC StartRampTimeTrq(short axis, double torque, unsigned int rampCycleTime);
        WMXAPIFUNC StartRampRateTrq(short axis, double torque, double rampRate);
    };

} // namespace torque
} // namespace wmxAPI

#endif // TORQUECONTROLBROKER_H
