// ConfigBroker.cpp
// config namespace - WMX 1.5 API to WMX3 API Broker Implementation
// Configuration functions for axis parameters

#include "ConfigBroker.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"

namespace wmxAPI {
namespace config {

    Config::Config(WMXLIB* lib)
        : wmxlib(lib)
    {
    }

    Config::~Config()
    {
    }

    WMXAPIFUNC Config::GetAxisHomeParam(short axis, WMX_HOME_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Config::HomeParam wmx3Param;
        long ret = coreMotion->config->GetHomeParam(axis, &wmx3Param);
        if (ret != 0) return ret;

        // Map WMX3 HomeParam to WMX 1.5 WMX_HOME_PARAM
        memset(pParam, 0, sizeof(WMX_HOME_PARAM));
        pParam->HomeType = (WMX_HOME_TYPE)wmx3Param.homeType;
        pParam->HomeDir = (WMX_HOME_DIR)wmx3Param.homeDirection;
        pParam->GridSearchVel = wmx3Param.homingVelocitySlow;
        pParam->GridSearchAcc = wmx3Param.homingVelocitySlowAcc;
        pParam->GridSearchDec = wmx3Param.homingVelocitySlowDec;
        pParam->HSSearchVel = wmx3Param.homingVelocityFast;
        pParam->HSSearchAcc = wmx3Param.homingVelocityFastAcc;
        pParam->HSSearchDec = wmx3Param.homingVelocityFastDec;
        pParam->HSReverseDistance = wmx3Param.homingReverseDistance;
        pParam->HomeShiftVel = wmx3Param.homeShiftVelocity;
        pParam->HomeShiftAcc = wmx3Param.homeShiftAcc;
        pParam->HomeShiftDec = wmx3Param.homeShiftDec;
        pParam->HomeShiftDistance = wmx3Param.homeShiftDistance;
        pParam->HSPol = wmx3Param.invertHSPolarity ? 1 : 0;
        pParam->MultipleZP = wmx3Param.multipleZPulse;

        return 0;
    }

    WMXAPIFUNC Config::SetAxisHomeParam(short axis, WMX_HOME_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Map WMX 1.5 WMX_HOME_PARAM to WMX3 HomeParam
        wmx3Api::Config::HomeParam wmx3Param;
        wmx3Param.homeType = (wmx3Api::Config::HomeType::T)pParam->HomeType;
        wmx3Param.homeDirection = (wmx3Api::Config::HomeDirection::T)pParam->HomeDir;
        wmx3Param.homingVelocitySlow = pParam->GridSearchVel;
        wmx3Param.homingVelocitySlowAcc = pParam->GridSearchAcc;
        wmx3Param.homingVelocitySlowDec = pParam->GridSearchDec;
        wmx3Param.homingVelocityFast = pParam->HSSearchVel;
        wmx3Param.homingVelocityFastAcc = pParam->HSSearchAcc;
        wmx3Param.homingVelocityFastDec = pParam->HSSearchDec;
        wmx3Param.homingReverseDistance = pParam->HSReverseDistance;
        wmx3Param.homeShiftVelocity = pParam->HomeShiftVel;
        wmx3Param.homeShiftAcc = pParam->HomeShiftAcc;
        wmx3Param.homeShiftDec = pParam->HomeShiftDec;
        wmx3Param.homeShiftDistance = pParam->HomeShiftDistance;
        wmx3Param.invertHSPolarity = pParam->HSPol != 0;
        wmx3Param.multipleZPulse = pParam->MultipleZP;

        return coreMotion->config->SetHomeParam(axis, &wmx3Param);
    }

    WMXAPIFUNC Config::GetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Config::FeedbackParam wmx3Param;
        long ret = coreMotion->config->GetFeedbackParam(axis, &wmx3Param);
        if (ret != 0) return ret;

        // Map WMX3 FeedbackParam to WMX 1.5 WMX_FEEDBACK_PARAM
        memset(pParam, 0, sizeof(WMX_FEEDBACK_PARAM));
        pParam->InPosWidth = (long)wmx3Param.inPosWidth;
        pParam->InPos2Width = (long)wmx3Param.inPosWidth2;
        pParam->InPos3Width = (long)wmx3Param.inPosWidth3;
        pParam->InPos4Width = (long)wmx3Param.inPosWidth4;
        pParam->InPos5Width = (long)wmx3Param.inPosWidth5;
        pParam->PosCompWidth = (long)wmx3Param.posSetWidth;

        return 0;
    }

    WMXAPIFUNC Config::SetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Map WMX 1.5 WMX_FEEDBACK_PARAM to WMX3 FeedbackParam
        wmx3Api::Config::FeedbackParam wmx3Param;
        wmx3Param.inPosWidth = pParam->InPosWidth;
        wmx3Param.inPosWidth2 = pParam->InPos2Width;
        wmx3Param.inPosWidth3 = pParam->InPos3Width;
        wmx3Param.inPosWidth4 = pParam->InPos4Width;
        wmx3Param.inPosWidth5 = pParam->InPos5Width;
        wmx3Param.posSetWidth = pParam->PosCompWidth;

        return coreMotion->config->SetFeedbackParam(axis, &wmx3Param);
    }

    WMXAPIFUNC Config::GetAxisLimitParam(short axis, WMX_LIMIT_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Config::LimitParam wmx3Param;
        long ret = coreMotion->config->GetLimitParam(axis, &wmx3Param);
        if (ret != 0) return ret;

        // Map WMX3 LimitParam to WMX 1.5 WMX_LIMIT_PARAM
        memset(pParam, 0, sizeof(WMX_LIMIT_PARAM));
        pParam->LSType = (WMX_LIMITSWITCH_TYPE)wmx3Param.lsType;
        pParam->PLSType = (WMX_LIMITSWITCH_TYPE)wmx3Param.positiveLSType;
        pParam->NLSType = (WMX_LIMITSWITCH_TYPE)wmx3Param.negativeLSType;
        pParam->SoftLimitPPos = wmx3Param.softLimitPositivePos;
        pParam->SoftLimitNPos = wmx3Param.softLimitNegativePos;

        return 0;
    }

    WMXAPIFUNC Config::SetAxisLimitParam(short axis, WMX_LIMIT_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Map WMX 1.5 WMX_LIMIT_PARAM to WMX3 LimitParam
        wmx3Api::Config::LimitParam wmx3Param;
        wmx3Param.lsType = (wmx3Api::Config::LimitSwitchType::T)pParam->LSType;
        wmx3Param.positiveLSType = (wmx3Api::Config::LimitSwitchType::T)pParam->PLSType;
        wmx3Param.negativeLSType = (wmx3Api::Config::LimitSwitchType::T)pParam->NLSType;
        wmx3Param.softLimitPositivePos = pParam->SoftLimitPPos;
        wmx3Param.softLimitNegativePos = pParam->SoftLimitNPos;

        return coreMotion->config->SetLimitParam(axis, &wmx3Param);
    }

    WMXAPIFUNC Config::GetAxisSystemParam(short axis, WMX_SYSTEM_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Get WMX3 AxisParam to get AxisUnit
        wmx3Api::Config::AxisParam axisParam;
        long ret = coreMotion->config->GetAxisParam(axis, &axisParam);
        if (ret != 0) return ret;

        // Map to WMX 1.5 format
        memset(pParam, 0, sizeof(WMX_SYSTEM_PARAM));
        pParam->AxisUnit = axisParam.axisUnit[axis];
        pParam->OpenLoopMode = 0; // WMX3 does not have direct equivalent

        return 0;
    }

    WMXAPIFUNC Config::SetAxisSystemParam(short axis, WMX_SYSTEM_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Get current axis param
        wmx3Api::Config::AxisParam axisParam;
        long ret = coreMotion->config->GetAxisParam(&axisParam);
        if (ret != 0) return ret;

        // Update axis unit
        axisParam.axisUnit[axis] = pParam->AxisUnit;

        return coreMotion->config->SetAxisParam(axis, &axisParam);
    }

    WMXAPIFUNC Config::GetAxisAlarmParam(short axis, WMX_ALARM_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Config::AlarmParam wmx3Param;
        long ret = coreMotion->config->GetAlarmParam(axis, &wmx3Param);
        if (ret != 0) return ret;

        // Map WMX3 AlarmParam to WMX 1.5 WMX_ALARM_PARAM
        memset(pParam, 0, sizeof(WMX_ALARM_PARAM));
        pParam->FollowingErrorStopped = wmx3Param.followingErrorStopped;
        pParam->FollowingErrorMoving = wmx3Param.followingErrorMoving;
        pParam->FollowingErrorType = (WMX_ALARM_FOLLOWING_ERROR_TYPE)wmx3Param.followingErrorType;

        return 0;
    }

    WMXAPIFUNC Config::SetAxisAlarmParam(short axis, WMX_ALARM_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Map WMX 1.5 WMX_ALARM_PARAM to WMX3 AlarmParam
        wmx3Api::Config::AlarmParam wmx3Param;
        wmx3Param.followingErrorStopped = pParam->FollowingErrorStopped;
        wmx3Param.followingErrorMoving = pParam->FollowingErrorMoving;
        wmx3Param.followingErrorType = (wmx3Api::Config::FollowingErrorAlarmType::T)pParam->FollowingErrorType;

        return coreMotion->config->SetAlarmParam(axis, &wmx3Param);
    }

    WMXAPIFUNC Config::GetAxisSingleTurn(short axis, bool* pEnable, unsigned int* pEncoderCount)
    {
        if (!wmxlib || !pEnable || !pEncoderCount) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->config->GetSingleTurn(axis, pEnable, pEncoderCount);
    }

    WMXAPIFUNC Config::SetAxisSingleTurn(short axis, bool enable, unsigned int encoderCount)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->config->SetSingleTurn(axis, enable, encoderCount);
    }

    WMXAPIFUNC Config::GetAxisMultiplier(short axis, unsigned int* pMultiplier)
    {
        if (!wmxlib || !pMultiplier) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Get axis param which contains gear ratio
        // WMX 1.5 uses single multiplier (numerator with denominator=1)
        wmx3Api::Config::AxisParam axisParam;
        long ret = coreMotion->config->GetAxisParam(axis, &axisParam);
        if (ret != 0) return ret;

        *pMultiplier = static_cast<unsigned int>(axisParam.gearRatioNumerator[axis]);

        return 0;
    }

    WMXAPIFUNC Config::SetAxisMultiplier(short axis, unsigned int multiplier)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Get current axis param
        wmx3Api::Config::AxisParam axisParam;
        long ret = coreMotion->config->GetAxisParam(&axisParam);
        if (ret != 0) return ret;

        // Update gear ratio (WMX 1.5 uses multiplier as numerator with denominator=1)
        axisParam.gearRatioNumerator[axis] = static_cast<double>(multiplier);
        axisParam.gearRatioDenominator[axis] = 1.0;

        return coreMotion->config->SetAxisParam(axis, &axisParam);
    }

    WMXAPIFUNC Config::GetAxisVelocityFeedforwardGain(short axis, double* pGain)
    {
        if (!wmxlib || !pGain) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->config->GetVelocityFeedforwardGain(axis, pGain);
    }

    WMXAPIFUNC Config::SetAxisVelocityFeedforwardGain(short axis, double gain)
    {
        if (!wmxlib) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        return coreMotion->config->SetVelocityFeedforwardGain(axis, gain);
    }

    WMXAPIFUNC Config::GetAxisMotionParam(short axis, WMX_MOTION_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Config::MotionParam wmx3Param;
        long ret = coreMotion->config->GetMotionParam(axis, &wmx3Param);
        if (ret != 0) return ret;

        // Map WMX3 MotionParam to WMX 1.5 WMX_MOTION_PARAM
        memset(pParam, 0, sizeof(WMX_MOTION_PARAM));
        pParam->QStopDec = wmx3Param.quickStopDec;

        return 0;
    }

    WMXAPIFUNC Config::SetAxisMotionParam(short axis, WMX_MOTION_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Map WMX 1.5 WMX_MOTION_PARAM to WMX3 MotionParam
        wmx3Api::Config::MotionParam wmx3Param;
        wmx3Param.quickStopDec = pParam->QStopDec;

        return coreMotion->config->SetMotionParam(axis, &wmx3Param);
    }

    WMXAPIFUNC Config::GetAxisParam(short axis, WMX_AXIS_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        wmx3Api::Config::AxisParam wmx3Param;
        long ret = coreMotion->config->GetAxisParam(axis, &wmx3Param);
        if (ret != 0) return ret;

        // Map WMX3 AxisParam to WMX 1.5 WMX_AXIS_PARAM
        memset(pParam, 0, sizeof(WMX_AXIS_PARAM));
        pParam->axisCommandMode = (WMX_AXIS_MODE)wmx3Param.axisCommandMode[axis];
        pParam->gearRatioNumerator = wmx3Param.gearRatioNumerator[axis];
        pParam->gearRatioDenominator = wmx3Param.gearRatioDenominator[axis];
        pParam->singleTurnMode = wmx3Param.singleTurnMode[axis];
        pParam->singleTurnEncoderCount = wmx3Param.singleTurnEncoderCount[axis];
        pParam->maxTrqLimit = wmx3Param.maxTrqLimit[axis];
        pParam->positiveTrqLimit = wmx3Param.positiveTrqLimit[axis];
        pParam->negativeTrqLimit = wmx3Param.negativeTrqLimit[axis];
        pParam->axisUnit = wmx3Param.axisUnit[axis];
        pParam->velocityFeedforwardGain = wmx3Param.velocityFeedforwardGain[axis];
        pParam->axisPolarity = wmx3Param.axisPolarity[axis];
        pParam->maxMotorSpeed = wmx3Param.maxMotorSpeed[axis];

        return 0;
    }

    WMXAPIFUNC Config::SetAxisParam(short axis, WMX_AXIS_PARAM* pParam)
    {
        if (!wmxlib || !pParam) return -1;

        wmx3Api::CoreMotion* coreMotion = wmxlib->GetCoreMotion();
        if (!coreMotion) return -1;

        // Get current axis param
        wmx3Api::Config::AxisParam wmx3Param;
        long ret = coreMotion->config->GetAxisParam(&wmx3Param);
        if (ret != 0) return ret;

        // Map WMX 1.5 WMX_AXIS_PARAM to WMX3 AxisParam
        wmx3Param.axisCommandMode[axis] = (wmx3Api::AxisCommandMode::T)pParam->axisCommandMode;
        wmx3Param.gearRatioNumerator[axis] = pParam->gearRatioNumerator;
        wmx3Param.gearRatioDenominator[axis] = pParam->gearRatioDenominator;
        wmx3Param.singleTurnMode[axis] = pParam->singleTurnMode;
        wmx3Param.singleTurnEncoderCount[axis] = pParam->singleTurnEncoderCount;
        wmx3Param.maxTrqLimit[axis] = pParam->maxTrqLimit;
        wmx3Param.positiveTrqLimit[axis] = pParam->positiveTrqLimit;
        wmx3Param.negativeTrqLimit[axis] = pParam->negativeTrqLimit;
        wmx3Param.axisUnit[axis] = pParam->axisUnit;
        wmx3Param.velocityFeedforwardGain[axis] = pParam->velocityFeedforwardGain;
        wmx3Param.axisPolarity[axis] = pParam->axisPolarity;
        wmx3Param.maxMotorSpeed[axis] = pParam->maxMotorSpeed;

        return coreMotion->config->SetAxisParam(axis, &wmx3Param);
    }

} // namespace config
} // namespace wmxAPI
