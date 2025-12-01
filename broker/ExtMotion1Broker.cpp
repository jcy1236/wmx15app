// ExtMotion1Broker.cpp
// extMotion1 namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Jerk-based motion (pulse/s^3)

#include "ExtMotion1Broker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace extMotion1 {

    ExtMotion1::ExtMotion1(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    ExtMotion1::~ExtMotion1()
    {
    }

    WMXAPIFUNC ExtMotion1::StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target,
        double velocity, double acc, double dec, double jerkAcc, double jerkDec,
        double startingVelocity, double endVelocity)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 position command with S-curve/jerk profile
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;

        // Use JerkLimited profile with absolute jerk values
        posCmd.profile = wmx3Api::Profile::SetupJerkLimited(velocity, acc, dec,
            jerkAcc, jerkDec, startingVelocity, endVelocity);

        return coreMotion->motion->StartPos(&posCmd);
    }

    WMXAPIFUNC ExtMotion1::StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target,
        double velocity, double acc, double dec, double jerkAcc, double jerkDec,
        double startingVelocity, double endVelocity)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 move command with S-curve/jerk profile
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;

        // Use JerkLimited profile with absolute jerk values
        posCmd.profile = wmx3Api::Profile::SetupJerkLimited(velocity, acc, dec,
            jerkAcc, jerkDec, startingVelocity, endVelocity);

        return coreMotion->motion->StartMov(&posCmd);
    }

    WMXAPIFUNC ExtMotion1::StartJerkJog(short axis, WMX_PROFILE_TYPE profile,
        double velocity, double acc, double jerkAcc)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 jog command with jerk
        wmx3Api::Motion::JogCommand jogCmd;
        jogCmd.axis = axis;

        // Use JerkLimited profile with absolute jerk values
        jogCmd.profile = wmx3Api::Profile::SetupJerkLimited(velocity, acc, acc,
            jerkAcc, jerkAcc, 0, 0);

        return coreMotion->motion->StartJog(&jogCmd);
    }

} // namespace extMotion1
} // namespace wmxAPI
