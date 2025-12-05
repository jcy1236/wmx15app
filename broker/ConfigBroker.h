// ConfigBroker.h
// config namespace - WMX 1.5 API to WMX3 API Broker
// Configuration functions for axis parameters

#ifndef CONFIGBROKER_H
#define CONFIGBROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace config {

    class WMXBROKER_API Config {
    private:
        WMXLIB* wmxlib;

    public:
        Config(WMXLIB* lib);
        ~Config();

        // Home parameters
        WMXAPIFUNC GetAxisHomeParam(short axis, WMX_HOME_PARAM* pParam);
        WMXAPIFUNC SetAxisHomeParam(short axis, WMX_HOME_PARAM* pParam);

        // Feedback parameters
        WMXAPIFUNC GetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM* pParam);
        WMXAPIFUNC SetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM* pParam);

        // Limit parameters
        WMXAPIFUNC GetAxisLimitParam(short axis, WMX_LIMIT_PARAM* pParam);
        WMXAPIFUNC SetAxisLimitParam(short axis, WMX_LIMIT_PARAM* pParam);

        // System parameters
        WMXAPIFUNC GetAxisSystemParam(short axis, WMX_SYSTEM_PARAM* pParam);
        WMXAPIFUNC SetAxisSystemParam(short axis, WMX_SYSTEM_PARAM* pParam);

        // Alarm parameters
        WMXAPIFUNC GetAxisAlarmParam(short axis, WMX_ALARM_PARAM* pParam);
        WMXAPIFUNC SetAxisAlarmParam(short axis, WMX_ALARM_PARAM* pParam);

        // Single turn
        WMXAPIFUNC GetAxisSingleTurn(short axis, bool* pEnable, unsigned int* pEncoderCount);
        WMXAPIFUNC SetAxisSingleTurn(short axis, bool enable, unsigned int encoderCount);

        // Multiplier (gear ratio) - WMX 1.5 uses single unsigned int multiplier
        WMXAPIFUNC GetAxisMultiplier(short axis, unsigned int* pMultiplier);
        WMXAPIFUNC SetAxisMultiplier(short axis, unsigned int multiplier);

        // Velocity feedforward
        WMXAPIFUNC GetAxisVelocityFeedforwardGain(short axis, double* pGain);
        WMXAPIFUNC SetAxisVelocityFeedforwardGain(short axis, double gain);

        // Motion parameters
        WMXAPIFUNC GetAxisMotionParam(short axis, WMX_MOTION_PARAM* pParam);
        WMXAPIFUNC SetAxisMotionParam(short axis, WMX_MOTION_PARAM* pParam);

        // Full axis param access
        WMXAPIFUNC GetAxisParam(short axis, WMX_AXIS_PARAM* pParam);
        WMXAPIFUNC SetAxisParam(short axis, WMX_AXIS_PARAM* pParam);
    };

} // namespace config
} // namespace wmxAPI

#endif // CONFIGBROKER_H
