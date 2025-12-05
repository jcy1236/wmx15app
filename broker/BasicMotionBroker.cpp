// BasicMotionBroker.cpp
// basicMotion namespace - WMX 1.5 API to WMX3 API Broker Implementation

#include "BasicMotionBroker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace BasicMotion {

    BasicMotion::BasicMotion(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    BasicMotion::~BasicMotion()
    {
    }

    WMXAPIFUNC BasicMotion::StartPos(short axis, double target, double velocity, double acc, double dec)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 position command with trapezoidal profile
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;
        posCmd.profile = wmx3Api::Profile::SetupTrapezoidal(velocity, acc, dec);

        return coreMotion->motion->StartPos(&posCmd);
    }

    WMXAPIFUNC BasicMotion::StartMov(short axis, double target, double velocity, double acc, double dec)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 move command with trapezoidal profile
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;
        posCmd.profile = wmx3Api::Profile::SetupTrapezoidal(velocity, acc, dec);

        return coreMotion->motion->StartMov(&posCmd);
    }

    WMXAPIFUNC BasicMotion::StartJog(short axis, double velocity, double acc)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 jog command
        wmx3Api::Motion::JogCommand jogCmd;
        jogCmd.axis = axis;
        jogCmd.profile = wmx3Api::Profile::SetupTrapezoidal(velocity, acc, acc);

        return coreMotion->motion->StartJog(&jogCmd);
    }

    WMXAPIFUNC BasicMotion::StopAxis(int axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->motion->Stop(axis);
    }

    WMXAPIFUNC BasicMotion::QStopAxis(int axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->motion->ExecQuickStop(axis);
    }

    WMXAPIFUNC BasicMotion::TimeStopAxis(int axis, double time)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->motion->ExecTimedStop(axis, time);
    }

    // Multi-axis Stop with WMX_AXIS_SELECTION
    WMXAPIFUNC BasicMotion::StopAxis(WMX_AXIS_SELECTION* axis_selection)
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

        return coreMotion->motion->Stop(&wmx3AxisSel);
    }

    WMXAPIFUNC BasicMotion::QStopAxis(WMX_AXIS_SELECTION* axis_selection)
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

        return coreMotion->motion->ExecQuickStop(&wmx3AxisSel);
    }

    WMXAPIFUNC BasicMotion::TimeStopAxis(WMX_AXIS_SELECTION* axis_selection, double time)
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

        return coreMotion->motion->ExecTimedStop(&wmx3AxisSel, time);
    }

    WMXAPIFUNC BasicMotion::StartPos(short axis, double target, double velocity, double acc, double dec,
        double startingVelocity, double endVelocity)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 position command with trapezoidal profile and custom start/end velocity
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;
        posCmd.profile = wmx3Api::Profile::SetupTrapezoidal(velocity, acc, dec);
        posCmd.profile.startingVelocity = startingVelocity;
        posCmd.profile.endVelocity = endVelocity;

        return coreMotion->motion->StartPos(&posCmd);
    }

    WMXAPIFUNC BasicMotion::StartMov(short axis, double target, double velocity, double acc, double dec,
        double startingVelocity, double endVelocity)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Setup WMX3 move command with trapezoidal profile and custom start/end velocity
        wmx3Api::Motion::PosCommand posCmd;
        posCmd.axis = axis;
        posCmd.target = target;
        posCmd.profile = wmx3Api::Profile::SetupTrapezoidal(velocity, acc, dec);
        posCmd.profile.startingVelocity = startingVelocity;
        posCmd.profile.endVelocity = endVelocity;

        return coreMotion->motion->StartMov(&posCmd);
    }

    WMXAPIFUNC BasicMotion::WaitAxis(int axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Poll until motion is complete
        wmx3Api::CoreMotionStatus status;
        while (true) {
            long ret = coreMotion->GetStatus(&status);
            if (ret != 0) return ret;

            // Check if motion is complete (Idle state)
            if (status.axesStatus[axis].opState == wmx3Api::OperationState::Idle) {
                break;
            }

            Sleep(1);  // 1ms polling interval
        }

        return 0;
    }

    WMXAPIFUNC BasicMotion::PauseAxis(int axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->motion->Pause(axis);
    }

    WMXAPIFUNC BasicMotion::ResumeAxis(int axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->motion->Resume(axis);
    }

} // namespace BasicMotion
} // namespace wmxAPI
