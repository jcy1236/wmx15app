// HomeBroker.cpp
// home namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Homing and position setting functions

#include "HomeBroker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace home {

    Home::Home(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    Home::~Home()
    {
    }

    WMXAPIFUNC Home::StartHome(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->home->StartHome(axis);
    }

    WMXAPIFUNC Home::StartHome(short firstAxis, short lastAxis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Create axis selection for range
        wmx3Api::AxisSelection axisSelection;
        axisSelection.axisCount = 0;
        for (int i = firstAxis; i <= lastAxis; i++)
        {
            axisSelection.axis[axisSelection.axisCount++] = i;
        }

        return coreMotion->home->StartHome(&axisSelection);
    }

    WMXAPIFUNC Home::Continue(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->home->Continue(axis);
    }

    WMXAPIFUNC Home::Cancel(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->home->Cancel(axis);
    }

    WMXAPIFUNC Home::SetFeedbackPosition(short axis, double position)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->home->SetFeedbackPos(axis, position);
    }

    WMXAPIFUNC Home::SetCommandPosition(short axis, double position)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->home->SetCommandPos(axis, position);
    }

    WMXAPIFUNC Home::SetCmdPosToFbPos(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->home->SetCommandPosToFeedbackPos(axis);
    }

    WMXAPIFUNC Home::SetCmdPosToFbPos(short axis, double posChangePerCycle)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->home->SetCommandPosToFeedbackPos(axis, posChangePerCycle);
    }

    WMXAPIFUNC Home::SetHomeDone(short axis, unsigned char value)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->home->SetHomeDone(axis, value);
    }

    WMXAPIFUNC Home::GetHomeDone(short axis, unsigned char* pValue)
    {
        if (!wmxlib || !pValue) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Get status and extract home done from it
        wmx3Api::CoreMotionStatus status;
        long ret = coreMotion->GetStatus(&status);
        if (ret != 0) return ret;

        *pValue = status.axesStatus[axis].homeDone ? 1 : 0;
        return 0;
    }

    WMXAPIFUNC Home::GetHomeData(WMX_HOME_DATA* pHomeData)
    {
        if (!wmxlib || !pHomeData) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Get WMX3 home data
        wmx3Api::Home::HomeData wmx3HomeData;
        long ret = coreMotion->home->GetHomeData(&wmx3HomeData);
        if (ret != 0) return ret;

        // Map to WMX 1.5 format
        memset(pHomeData, 0, sizeof(WMX_HOME_DATA));
        for (int i = 0; i < MAX_AXIS; i++)
        {
            pHomeData->axesHomeData[i].distHStoZPulse = wmx3HomeData.axesHomeData[i].distHStoZPulse;
            pHomeData->axesHomeData[i].distLStoZPulse = wmx3HomeData.axesHomeData[i].distLStoZPulse;
        }

        return 0;
    }

    WMXAPIFUNC Home::StartHome(WMX_AXIS_SELECTION* axis_selection)
    {
        if (!wmxlib || !axis_selection) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Convert WMX 1.5 WMX_AXIS_SELECTION to WMX3 AxisSelection
        wmx3Api::AxisSelection wmx3AxisSel;
        wmx3AxisSel.axisCount = axis_selection->axisCount;
        for (int i = 0; i < axis_selection->axisCount && i < 64; i++) {
            wmx3AxisSel.axis[i] = axis_selection->axis[i];
        }

        return coreMotion->home->StartHome(&wmx3AxisSel);
    }

} // namespace home
} // namespace wmxAPI
