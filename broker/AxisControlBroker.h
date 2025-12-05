// AxisControlBroker.h
// axisControl namespace - WMX 1.5 API to WMX3 API Broker
// Axis control functions

#ifndef AXISCONTROLBROKER_H
#define AXISCONTROLBROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace axisControl {

    class WMXBROKER_API AxisControl {
    private:
        WMXLIB* wmxlib;

    public:
        AxisControl(WMXLIB* lib);
        ~AxisControl();

        // Axis mode
        WMXAPIFUNC GetAxisMode(short axis, WMX_AXIS_MODE* pMode);
        WMXAPIFUNC SetAxisMode(short axis, WMX_AXIS_MODE mode);

        // Servo control
        WMXAPIFUNC ServoOn(short axis, bool on);
        WMXAPIFUNC ServoOn(short firstAxis, short lastAxis, bool on);

        // Alarm clear
        WMXAPIFUNC AmpAlarmClear(short axis);
        WMXAPIFUNC AmpAlarmClear(short firstAxis, short lastAxis);
        WMXAPIFUNC AxisAlarmClear(short axis);
        WMXAPIFUNC AxisAlarmClear(short firstAxis, short lastAxis);

        // Position control
        WMXAPIFUNC GetPosCommand(short axis, double* pPosition);
        WMXAPIFUNC GetPosFeedback(short axis, double* pPosition);
        WMXAPIFUNC GetVelCommand(short axis, double* pVelocity);
        WMXAPIFUNC GetVelFeedback(short axis, double* pVelocity);
    };

} // namespace axisControl
} // namespace wmxAPI

#endif // AXISCONTROLBROKER_H
