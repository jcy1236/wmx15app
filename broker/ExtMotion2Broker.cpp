// ExtMotion2Broker.cpp
// extMotion2 namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Jerk ratio-based motion

#include "ExtMotion2Broker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace ExtMotion2 {

    ExtMotion2::ExtMotion2(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    ExtMotion2::~ExtMotion2()
    {
    }

    WMXAPIFUNC ExtMotion2::StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target,
        double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
        double startingVelocity, double endVelocity)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 position command with jerk ratio profile
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;

        // Clamp ratio to valid range [0, 1]
        if (jerkAccRatio < 0) jerkAccRatio = 0;
        if (jerkAccRatio > 1) jerkAccRatio = 1;
        if (jerkDecRatio < 0) jerkDecRatio = 0;
        if (jerkDecRatio > 1) jerkDecRatio = 1;

        posCmd.profile = wmx3Api::Profile::SetupJerkRatio(velocity, acc, dec,
            jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);

        return coreMotion->motion->StartPos(&posCmd);
    }

    WMXAPIFUNC ExtMotion2::StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target,
        double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
        double startingVelocity, double endVelocity)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 move command with jerk ratio profile
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;

        // Clamp ratio to valid range [0, 1]
        if (jerkAccRatio < 0) jerkAccRatio = 0;
        if (jerkAccRatio > 1) jerkAccRatio = 1;
        if (jerkDecRatio < 0) jerkDecRatio = 0;
        if (jerkDecRatio > 1) jerkDecRatio = 1;

        posCmd.profile = wmx3Api::Profile::SetupJerkRatio(velocity, acc, dec,
            jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);

        return coreMotion->motion->StartMov(&posCmd);
    }

    WMXAPIFUNC ExtMotion2::StartJerkJog(short axis, WMX_PROFILE_TYPE profile,
        double velocity, double acc, double jerkAccRatio)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 jog command with jerk ratio
        wmx3Api::Motion::JogCommand jogCmd;
        jogCmd.axis = axis;

        // Clamp ratio to valid range [0, 1]
        if (jerkAccRatio < 0) jerkAccRatio = 0;
        if (jerkAccRatio > 1) jerkAccRatio = 1;

        jogCmd.profile = wmx3Api::Profile::SetupJerkRatio(velocity, acc, acc,
            jerkAccRatio, jerkAccRatio, 0, 0);

        return coreMotion->motion->StartJog(&jogCmd);
    }

} // namespace ExtMotion2
} // namespace wmxAPI
