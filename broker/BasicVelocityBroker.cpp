// BasicVelocityBroker.cpp
// basicVelocity namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Basic velocity control functions (Stop, QuickStop)

#include "BasicVelocityBroker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace basicVelocity {

    BasicVelocity::BasicVelocity(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    BasicVelocity::~BasicVelocity()
    {
    }

    WMXAPIFUNC BasicVelocity::StopVel(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->velocity->Stop(axis);
    }

    WMXAPIFUNC BasicVelocity::StopVel(short firstAxis, short lastAxis)
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

        return coreMotion->velocity->Stop(&axisSelection);
    }

    WMXAPIFUNC BasicVelocity::QStopVel(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->velocity->ExecQuickStop(axis);
    }

    WMXAPIFUNC BasicVelocity::QStopVel(short firstAxis, short lastAxis)
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

        return coreMotion->velocity->ExecQuickStop(&axisSelection);
    }

    WMXAPIFUNC BasicVelocity::TimedStopVel(short axis, double timeMilliseconds)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->velocity->ExecTimedStop(axis, timeMilliseconds);
    }

    WMXAPIFUNC BasicVelocity::TimedStopVel(short firstAxis, short lastAxis, double timeMilliseconds)
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

        return coreMotion->velocity->ExecTimedStop(&axisSelection, timeMilliseconds);
    }

    WMXAPIFUNC BasicVelocity::StartVel(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, double dec)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 velocity command
        wmx3Api::Velocity::VelCommand velCmd;
        velCmd.axis = axis;
        velCmd.profile = wmx3Api::Profile::SetupTrapezoidal(velocity, acc, dec, 0, 0);

        return coreMotion->velocity->StartVel(&velCmd);
    }

} // namespace basicVelocity
} // namespace wmxAPI
