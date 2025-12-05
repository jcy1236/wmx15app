// HomeBroker.h
// home namespace - WMX 1.5 API to WMX3 API Broker
// Homing and position setting functions

#ifndef HOMEBROKER_H
#define HOMEBROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace home {

    class WMXBROKER_API Home {
    private:
        WMXLIB* wmxlib;

    public:
        Home(WMXLIB* lib);
        ~Home();

        // Homing
        WMXAPIFUNC StartHome(short axis);
        WMXAPIFUNC StartHome(short firstAxis, short lastAxis);

        // Continue/Cancel
        WMXAPIFUNC Continue(short axis);
        WMXAPIFUNC Cancel(short axis);

        // Position setting
        WMXAPIFUNC SetFeedbackPosition(short axis, double position);
        WMXAPIFUNC SetCommandPosition(short axis, double position);
        WMXAPIFUNC SetCmdPosToFbPos(short axis);
        WMXAPIFUNC SetCmdPosToFbPos(short axis, double posChangePerCycle);

        // Home done
        WMXAPIFUNC SetHomeDone(short axis, unsigned char value);
        WMXAPIFUNC GetHomeDone(short axis, unsigned char* pValue);

        // Home data
        WMXAPIFUNC GetHomeData(WMX_HOME_DATA* pHomeData);
    };

} // namespace home
} // namespace wmxAPI

#endif // HOMEBROKER_H
