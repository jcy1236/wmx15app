// TorqueControlBroker.cpp
// torque namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Torque control functions

#include "TorqueControlBroker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace torque {

    TorqueControl::TorqueControl(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    TorqueControl::~TorqueControl()
    {
    }

    WMXAPIFUNC TorqueControl::GetMaxTrqLimit(short axis, double* pTorque)
    {
        if (!wmxlib || !pTorque) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->torque->GetMaxTrqLimit(axis, pTorque);
    }

    WMXAPIFUNC TorqueControl::SetMaxTrqLimit(short axis, double torque)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->torque->SetMaxTrqLimit(axis, torque);
    }

    WMXAPIFUNC TorqueControl::GetPositiveTrqLimit(short axis, double* pTorque)
    {
        if (!wmxlib || !pTorque) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->torque->GetPositiveTrqLimit(axis, pTorque);
    }

    WMXAPIFUNC TorqueControl::SetPositiveTrqLimit(short axis, double torque)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->torque->SetPositiveTrqLimit(axis, torque);
    }

    WMXAPIFUNC TorqueControl::GetNegativeTrqLimit(short axis, double* pTorque)
    {
        if (!wmxlib || !pTorque) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->torque->GetNegativeTrqLimit(axis, pTorque);
    }

    WMXAPIFUNC TorqueControl::SetNegativeTrqLimit(short axis, double torque)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->torque->SetNegativeTrqLimit(axis, torque);
    }

    WMXAPIFUNC TorqueControl::StartTrq(short axis, double torque)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Torque::TrqCommand trqCmd;
        trqCmd.axis = axis;
        trqCmd.torque = torque;

        return coreMotion->torque->StartTrq(&trqCmd);
    }

    WMXAPIFUNC TorqueControl::StartTrq(short axis, double torque, double maxMotorSpeed)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Torque::TrqCommand trqCmd;
        trqCmd.axis = axis;
        trqCmd.torque = torque;

        return coreMotion->torque->StartTrq(&trqCmd, maxMotorSpeed);
    }

    WMXAPIFUNC TorqueControl::StopTrq(short axis)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->torque->StopTrq(axis);
    }

    WMXAPIFUNC TorqueControl::StopTrq(short firstAxis, short lastAxis)
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

        return coreMotion->torque->StopTrq(&axisSelection);
    }

    WMXAPIFUNC TorqueControl::StartRampTimeTrq(short axis, double torque, unsigned int rampCycleTime)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Torque::TrqCommand trqCmd;
        trqCmd.axis = axis;
        trqCmd.torque = torque;

        return coreMotion->torque->StartRampTimeTrq(&trqCmd, rampCycleTime);
    }

    WMXAPIFUNC TorqueControl::StartRampRateTrq(short axis, double torque, double rampRate)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Torque::TrqCommand trqCmd;
        trqCmd.axis = axis;
        trqCmd.torque = torque;

        return coreMotion->torque->StartRampRateTrq(&trqCmd, rampRate);
    }

} // namespace torque
} // namespace wmxAPI
