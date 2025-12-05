// AxisControlBroker.cpp
// axisControl namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Axis control functions

#include "AxisControlBroker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace axisControl {

    AxisControl::AxisControl(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    AxisControl::~AxisControl()
    {
    }

    WMXAPIFUNC AxisControl::GetAxisMode(short axis, WMX_AXIS_MODE* pMode)
    {
        if (!wmxlib || !pMode) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::AxisCommandMode::T wmx3Mode;
        long ret = coreMotion->axisControl->GetAxisCommandMode(axis, &wmx3Mode);
        if (ret != 0) return ret;

        // Map WMX3 AxisCommandMode to WMX 1.5 WMX_AXIS_MODE
        switch (wmx3Mode)
        {
        case wmx3Api::AxisCommandMode::Position:
            *pMode = WMX_AXIS_MODE_POSITION;
            break;
        case wmx3Api::AxisCommandMode::Velocity:
            *pMode = WMX_AXIS_MODE_VELOCITY;
            break;
        case wmx3Api::AxisCommandMode::Torque:
            *pMode = WMX_AXIS_MODE_TORQUE;
            break;
        default:
            *pMode = WMX_AXIS_MODE_POSITION;
            break;
        }

        return 0;
    }

    WMXAPIFUNC AxisControl::SetAxisMode(short axis, WMX_AXIS_MODE mode)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Map WMX 1.5 WMX_AXIS_MODE to WMX3 AxisCommandMode
        wmx3Api::AxisCommandMode::T wmx3Mode;
        switch (mode)
        {
        case WMX_AXIS_MODE_POSITION:
            wmx3Mode = wmx3Api::AxisCommandMode::Position;
            break;
        case WMX_AXIS_MODE_VELOCITY:
            wmx3Mode = wmx3Api::AxisCommandMode::Velocity;
            break;
        case WMX_AXIS_MODE_TORQUE:
            wmx3Mode = wmx3Api::AxisCommandMode::Torque;
            break;
        default:
            wmx3Mode = wmx3Api::AxisCommandMode::Position;
            break;
        }

        return coreMotion->axisControl->SetAxisCommandMode(axis, wmx3Mode);
    }

    WMXAPIFUNC AxisControl::ServoOn(short axis, bool on)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->axisControl->SetServoOn(axis, on ? 1 : 0);
    }

    WMXAPIFUNC AxisControl::ServoOn(short firstAxis, short lastAxis, bool on)
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

        return coreMotion->axisControl->SetServoOn(&axisSelection, on ? 1 : 0);
    }

    WMXAPIFUNC AxisControl::AmpAlarmClear(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->axisControl->ClearAmpAlarm(axis);
    }

    WMXAPIFUNC AxisControl::AmpAlarmClear(short firstAxis, short lastAxis)
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

        return coreMotion->axisControl->ClearAmpAlarm(&axisSelection);
    }

    WMXAPIFUNC AxisControl::AxisAlarmClear(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->axisControl->ClearAxisAlarm(axis);
    }

    WMXAPIFUNC AxisControl::AxisAlarmClear(short firstAxis, short lastAxis)
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

        return coreMotion->axisControl->ClearAxisAlarm(&axisSelection);
    }

    WMXAPIFUNC AxisControl::GetPosCommand(short axis, double* pPosition)
    {
        if (!wmxlib || !pPosition) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->axisControl->GetPosCommand(axis, pPosition);
    }

    WMXAPIFUNC AxisControl::GetPosFeedback(short axis, double* pPosition)
    {
        if (!wmxlib || !pPosition) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->axisControl->GetPosFeedback(axis, pPosition);
    }

    WMXAPIFUNC AxisControl::GetVelCommand(short axis, double* pVelocity)
    {
        if (!wmxlib || !pVelocity) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->axisControl->GetVelCommand(axis, pVelocity);
    }

    WMXAPIFUNC AxisControl::GetVelFeedback(short axis, double* pVelocity)
    {
        if (!wmxlib || !pVelocity) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->axisControl->GetVelFeedback(axis, pVelocity);
    }

} // namespace axisControl
} // namespace wmxAPI
