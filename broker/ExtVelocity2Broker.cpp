// ExtVelocity2Broker.cpp
// extVelocity2 namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Extended velocity control with jerk ratio

#include "ExtVelocity2Broker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace extVelocity2 {

    ExtVelocity2::ExtVelocity2(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    ExtVelocity2::~ExtVelocity2()
    {
    }

    WMXAPIFUNC ExtVelocity2::StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity,
        double acc, double dec, double jerkAccRatio, double jerkDecRatio)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 velocity command with jerk ratio profile
        wmx3Api::Velocity::VelCommand velCmd;
        velCmd.axis = axis;
        velCmd.profile = wmx3Api::Profile::SetupJerkRatio(velocity, acc, dec, jerkAccRatio, jerkDecRatio, 0, 0);

        return coreMotion->velocity->StartVel(&velCmd);
    }

    WMXAPIFUNC ExtVelocity2::StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity,
        double acc, double dec, double jerkAccRatio, double jerkDecRatio,
        double startingVelocity)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 velocity command with jerk ratio profile and starting velocity
        wmx3Api::Velocity::VelCommand velCmd;
        velCmd.axis = axis;
        velCmd.profile = wmx3Api::Profile::SetupJerkRatio(velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, 0);

        return coreMotion->velocity->StartVel(&velCmd);
    }

    WMXAPIFUNC ExtVelocity2::OverrideVel(short axis, double velocity, double acc, double dec)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 velocity command for override
        wmx3Api::Velocity::VelCommand velCmd;
        velCmd.axis = axis;
        velCmd.profile = wmx3Api::Profile::SetupTrapezoidal(velocity, acc, dec, 0, 0);

        return coreMotion->velocity->OverrideVel(&velCmd);
    }

} // namespace extVelocity2
} // namespace wmxAPI
