// ExtMotion2Broker.cpp
// extMotion2 namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Jerk ratio-based motion

#include "ExtMotion2Broker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"
#include "AdvancedMotionApi.h"

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

    WMXAPIFUNC ExtMotion2::StopJerkJogAtPos(short axis, WMX_PROFILE_TYPE profile, double target,
        double dec, double jerkDecRatio)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 position command for stop at position
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;

        // Clamp ratio to valid range [0, 1]
        if (jerkDecRatio < 0) jerkDecRatio = 0;
        if (jerkDecRatio > 1) jerkDecRatio = 1;

        // Use jerk ratio profile with only deceleration
        posCmd.profile = wmx3Api::Profile::SetupJerkRatio(0, 0, dec, 0, jerkDecRatio, 0, 0);

        return coreMotion->motion->StopJogAtPos(&posCmd);
    }

    WMXAPIFUNC ExtMotion2::StartJerkCoordinatedPos(short axis, WMX_PROFILE_TYPE profile,
        double target, double velocity, double acc, double dec,
        double jerkAccRatio, double jerkDecRatio,
        double startingVelocity, double endVelocity,
        short axis2, double axis2target, double axis2smoothRatio)
    {
        if (!wmxlib) return -1;

        wmx3Api::AdvancedMotion* advMotion = wmxlib->GetAdvancedMotion();
        if (!advMotion) return -1;

        // Clamp ratio to valid range [0, 1]
        if (jerkAccRatio < 0) jerkAccRatio = 0;
        if (jerkAccRatio > 1) jerkAccRatio = 1;
        if (jerkDecRatio < 0) jerkDecRatio = 0;
        if (jerkDecRatio > 1) jerkDecRatio = 1;

        // Setup coordinated position command (AdvMotion class inside AdvancedMotion)
        wmx3Api::AdvMotion::CoordinatedPosCommand coordCmd;
        coordCmd.posCommand.axis = axis;
        coordCmd.posCommand.target = target;
        coordCmd.posCommand.profile = wmx3Api::Profile::SetupJerkRatio(velocity, acc, dec,
            jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
        coordCmd.axis2 = axis2;
        coordCmd.axis2Target = axis2target;
        coordCmd.axis2SmoothRatio = axis2smoothRatio;

        return advMotion->advMotion->StartCoordinatedPos(&coordCmd);
    }

} // namespace ExtMotion2
} // namespace wmxAPI
