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

    WMXAPIFUNC ExtMotion2::StartJerkPos(PosBlockExt2* mpos_block)
    {
        if (!wmxlib || !mpos_block) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Multi-axis block: call StartPos for each axis in the block
        for (int i = 0; i < mpos_block->axisCount && i < 64; i++) {
            PosBlockExt2Ind& blk = mpos_block->pos_block[i];

            wmx3Api::Motion::PosCommand posCmd;
            posCmd.axis = blk.axis;
            posCmd.target = blk.target;

            // Clamp ratio to valid range [0, 1]
            double jerkAccRatio = blk.jerkAccRatio;
            double jerkDecRatio = blk.jerkDecRatio;
            if (jerkAccRatio < 0) jerkAccRatio = 0;
            if (jerkAccRatio > 1) jerkAccRatio = 1;
            if (jerkDecRatio < 0) jerkDecRatio = 0;
            if (jerkDecRatio > 1) jerkDecRatio = 1;

            posCmd.profile = wmx3Api::Profile::SetupJerkRatio(
                blk.velocity, blk.acc, blk.dec,
                jerkAccRatio, jerkDecRatio,
                blk.startingVelocity, blk.endVelocity);

            long ret = coreMotion->motion->StartPos(&posCmd);
            if (ret != 0) return ret;
        }
        return 0;
    }

    WMXAPIFUNC ExtMotion2::StartJerkLinIntPos(IntBlockExt2* mpos_block)
    {
        if (!wmxlib || !mpos_block) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Clamp ratio to valid range [0, 1]
        double compJerkAccRatio = mpos_block->compJerkAccRatio;
        double compJerkDecRatio = mpos_block->compJerkDecRatio;
        if (compJerkAccRatio < 0) compJerkAccRatio = 0;
        if (compJerkAccRatio > 1) compJerkAccRatio = 1;
        if (compJerkDecRatio < 0) compJerkDecRatio = 0;
        if (compJerkDecRatio > 1) compJerkDecRatio = 1;

        // Setup WMX3 LinearIntplCommand (CoreMotion::Motion API)
        wmx3Api::Motion::LinearIntplCommand linCmd;
        linCmd.axisCount = mpos_block->axisCount;

        // Find max velocity/acc/dec across all axes for profile
        double maxVel = 0, maxAcc = 0, maxDec = 0;
        for (int i = 0; i < mpos_block->axisCount && i < 64; i++) {
            IntBlockExt2Ind& blk = mpos_block->pos_block[i];
            linCmd.axis[i] = blk.axis;
            linCmd.target[i] = blk.target;
            linCmd.maxVelocity[i] = blk.velocity;
            linCmd.maxAcc[i] = blk.acc;
            linCmd.maxDec[i] = blk.dec;
            // WMX3 uses absolute jerk values, calculate from ratio
            linCmd.maxJerkAcc[i] = (compJerkAccRatio > 0) ? (blk.acc / compJerkAccRatio) : 0;
            linCmd.maxJerkDec[i] = (compJerkDecRatio > 0) ? (blk.dec / compJerkDecRatio) : 0;

            if (blk.velocity > maxVel) maxVel = blk.velocity;
            if (blk.acc > maxAcc) maxAcc = blk.acc;
            if (blk.dec > maxDec) maxDec = blk.dec;
        }

        // Set composite profile based on WMX 1.5 profile type
        linCmd.profile = wmx3Api::Profile::SetupJerkRatio(
            maxVel, maxAcc, maxDec,
            compJerkAccRatio, compJerkDecRatio, 0, 0);

        return coreMotion->motion->StartLinearIntplPos(&linCmd);
    }

} // namespace ExtMotion2
} // namespace wmxAPI
