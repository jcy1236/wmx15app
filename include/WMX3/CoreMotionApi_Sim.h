// CoreMotionApi_Sim.h
// CoreMotion Header-only wrapper for VS2012 compatibility
// Provides wmx3Api::CoreMotion interface that internally calls WMX3Broker C API

#ifndef COREMOTIONAPI_SIM_H
#define COREMOTIONAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    namespace constants
    {
        static const int maxFlightRecorderBufferSize = 5000;
        static const int maxInPosChannel = 5;
        static const int maxSyncGroup = 64;
        static const int maxTriggerEvents = 8;
        static const unsigned long long int maxProfileUnsignedInput = 274877906943ULL;
    }

    class CoreMotion;

    //=========================================================================
    // CoreMotion Enums
    //=========================================================================
    class DetailOperationState
    {
    public:
        enum T
        {
            Idle = 0,
            Pos = 200,
            Pos_OverrideSetup,
            Pos_WaitingForTrigger,
            Jog = 300,
            Jog_OverrideSetup,
            Home = 400,
            Sync = 500,
            Sync_PhaseShift,
            Sync_GearShift,
            GantryHome = 600,
            Stop = 700,
            Stop_QStop,
            Stop_EStop,
            Intpl = 800,
            Intpl_Linear,
            Intpl_Circular,
            Intpl_Helical,
            Intpl_Spline,
            Intpl_Path,
            Intpl_PathWithRotation,
            Intpl_PathLookahead,
            Intpl_OverrideSetup,
            Intpl_OverrideSmoothing,
            Velocity = 900,
            Velocity_OverrideSetup,
            ConstLinearVelocity = 1100,
            Trq = 1200
        };
    };

    class HomeError
    {
    public:
        enum T
        {
            NoError,
            LSTriggered,
            MaxLSRevDistanceTraveled,
            MaxHSOnAtStartRevDistanceTraveled,
            ZPulseDistanceCheckError
        };
    };

    class AxisSyncMode
    {
    public:
        enum T
        {
            NoSync,
            NoOffset,
            VelocityOffset,
            SymmetricVelocityOffset
        };
    };

    class EStopLevel
    {
    public:
        enum T
        {
            Final,
            Level1
        };
    };

    //=========================================================================
    // CoreMotion Data Classes
    //=========================================================================
    class AxisCompensation
    {
    public:
        AxisCompensation() : pitchErrorCompensation(0), pitchErrorCompensation2D(0),
                             backlashCompensation(0), totalPosCompensation(0) {}

        double pitchErrorCompensation;
        double pitchErrorCompensation2D;
        double backlashCompensation;
        double totalPosCompensation;
    };

    class AxisSupportedFunction
    {
    public:
        AxisSupportedFunction() : posFeedbackSupport(false), posCommandSupport(false),
                                  velocityFeedbackSupport(false), velocityCommandSupport(false),
                                  velocityOffsetSupport(false), trqFeedbackSupport(false),
                                  trqCommandSupport(false), maxTrqLimitSupport(false),
                                  positiveTrqLimitSupport(false), negativeTrqLimitSupport(false),
                                  maxMotorSpeedSupport(false) {}

        bool posFeedbackSupport;
        bool posCommandSupport;
        bool velocityFeedbackSupport;
        bool velocityCommandSupport;
        bool velocityOffsetSupport;
        bool trqFeedbackSupport;
        bool trqCommandSupport;
        bool maxTrqLimitSupport;
        bool positiveTrqLimitSupport;
        bool negativeTrqLimitSupport;
        bool maxMotorSpeedSupport;
    };

    //=========================================================================
    // CoreMotionAxisStatus class
    //=========================================================================
    class CoreMotionAxisStatus
    {
    public:
        CoreMotionAxisStatus()
        {
            memset(this, 0, sizeof(CoreMotionAxisStatus));
            opState = OperationState::Idle;
            detailOpState = DetailOperationState::Idle;
            axisCommandMode = AxisCommandMode::Position;
            axisSyncMode = AxisSyncMode::NoSync;
            homeState = HomeState::Idle;
            homeError = HomeError::NoError;
        }

        bool servoOn;
        bool servoOffline;
        bool ampAlarm;
        int ampAlarmCode;
        int masterAxis;
        int secondMasterAxis;
        double posCmd;
        double actualPos;
        double compPosCmd;
        double compActualPos;
        double syncPosCmd;
        double syncActualPos;
        int encoderCommand;
        int encoderFeedback;
        long long accumulatedEncoderFeedback;
        double velocityCmd;
        double actualVelocity;
        double velocityLag;
        double torqueCmd;
        double actualTorque;
        double actualFollowingError;
        AxisCompensation compensation;
        AxisSupportedFunction axisSupportedFunction;
        OperationState::T opState;
        DetailOperationState::T detailOpState;
        AxisCommandMode::T axisCommandMode;
        AxisSyncMode::T axisSyncMode;
        double syncOffset;
        double syncPhaseOffset;
        double syncGearRatio;
        double profileTotalMilliseconds;
        double profileAccMilliseconds;
        double profileCruiseMilliseconds;
        double profileDecMilliseconds;
        double profileRemainingMilliseconds;
        double profileCompletedMilliseconds;
        double profileTargetPos;
        double profileTotalDistance;
        double profileRemainingDistance;
        double profileCompletedDistance;
        double intplVelocity;
        int intplSegment;
        bool followingErrorAlarm;
        bool commandReady;
        bool waitingForTrigger;
        bool motionPaused;
        bool motionComplete;
        bool execSuperimposedMotion;
        double cmdAcc;
        bool accFlag;
        bool decFlag;
        bool inPos;
        bool inPos2;
        bool inPos3;
        bool inPos4;
        bool inPos5;
        bool cmdDistributionEnd;
        bool posSet;
        bool delayedPosSet;
        unsigned int cmdDistributionEndDelayedPosSetDiff;
        bool positiveLS;
        bool negativeLS;
        bool nearPositiveLS;
        bool nearNegativeLS;
        bool externalPositiveLS;
        bool externalNegativeLS;
        bool positiveSoftLimit;
        bool negativeSoftLimit;
        HomeState::T homeState;
        HomeError::T homeError;
        double homeOffset;
        bool homeSwitch;
        bool homeDone;
        bool homePaused;
        bool cmdPosToFbPosFlag;
        unsigned int singleTurnCounter;
        double userOffset;
        double userOffsetPosCmd;
        double userOffsetActualPos;
    };

    //=========================================================================
    // CoreMotionStatus class
    //=========================================================================
    class CoreMotionStatus
    {
    public:
        CoreMotionStatus()
        {
            invalidLicenseError = false;
            engineState = EngineState::Idle;
            numOfInterrupts = 0;
            emergencyStop = false;
            emergencyStopLevel = EStopLevel::Final;
            for (int i = 0; i < constants::maxInterrupts; i++)
            {
                cycleTimeMilliseconds[i] = 0;
                cycleCounter[i] = 0;
            }
        }

        bool invalidLicenseError;
        EngineState::T engineState;
        int numOfInterrupts;
        double cycleTimeMilliseconds[constants::maxInterrupts];
        long long cycleCounter[constants::maxInterrupts];
        bool emergencyStop;
        EStopLevel::T emergencyStopLevel;
        CoreMotionAxisStatus axesStatus[constants::maxAxes];
    };

    //=========================================================================
    // AxisControl sub-class
    //=========================================================================
    class AxisControl
    {
    public:
        CoreMotion *cmApi;
        AxisControl(CoreMotion *f) : cmApi(f) {}

        long SetServoOn(int axis, int newStatus)
        {
            return WMX3Broker_AxisControl_SetServoOn(axis, newStatus);
        }

        long SetServoOn(AxisSelection *pAxisSelection, int newStatus)
        {
            if (!pAxisSelection)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < pAxisSelection->axisCount; i++)
            {
                ret = WMX3Broker_AxisControl_SetServoOn(pAxisSelection->axis[i], newStatus);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long ClearAmpAlarm(int axis)
        {
            return WMX3Broker_AxisControl_ClearAmpAlarm(axis);
        }

        long ClearAmpAlarm(AxisSelection *pAxisSelection)
        {
            if (!pAxisSelection)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < pAxisSelection->axisCount; i++)
            {
                ret = WMX3Broker_AxisControl_ClearAmpAlarm(pAxisSelection->axis[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long ClearAxisAlarm(int axis)
        {
            return WMX3Broker_AxisControl_ClearAxisAlarm(axis);
        }

        long SetAxisCommandMode(int axis, AxisCommandMode::T mode)
        {
            return WMX3Broker_AxisControl_SetAxisCommandMode(axis, static_cast<int>(mode));
        }

        long GetAxisCommandMode(int axis, AxisCommandMode::T *pMode)
        {
            if (!pMode)
                return -1;
            int mode;
            long ret = WMX3Broker_AxisControl_GetAxisCommandMode(axis, &mode);
            if (ret == 0)
                *pMode = static_cast<AxisCommandMode::T>(mode);
            return ret;
        }

        long GetPosCommand(int axis, double *pPosition)
        {
            return WMX3Broker_AxisControl_GetPosCommand(axis, pPosition);
        }

        long GetPosFeedback(int axis, double *pPosition)
        {
            return WMX3Broker_AxisControl_GetPosFeedback(axis, pPosition);
        }

        long GetVelCommand(int axis, double *pVelocity)
        {
            return WMX3Broker_AxisControl_GetVelCommand(axis, pVelocity);
        }

        long GetVelFeedback(int axis, double *pVelocity)
        {
            return WMX3Broker_AxisControl_GetVelFeedback(axis, pVelocity);
        }
    };

    //=========================================================================
    // Motion sub-class
    //=========================================================================
    class Motion
    {
    public:
        CoreMotion *cmApi;
        Motion(CoreMotion *f) : cmApi(f) {}

        // PosCommand struct (WMX3 compatible)
        class PosCommand
        {
        public:
            PosCommand() : axis(0), target(0) {}
            PosCommand(int _axis, double _target, Profile _profile)
                : axis(_axis), target(_target), profile(_profile) {}
            int axis;
            double target;
            Profile profile;
        };

        // JogCommand struct
        class JogCommand
        {
        public:
            JogCommand() : axis(0) {}
            JogCommand(int _axis, Profile _profile) : axis(_axis), profile(_profile) {}
            int axis;
            Profile profile;
        };

        // LinearIntplCommand struct
        class LinearIntplCommand
        {
        public:
            LinearIntplCommand() : axisCount(0)
            {
                for (int i = 0; i < constants::maxAxes; i++)
                {
                    axis[i] = 0;
                    target[i] = 0;
                    maxVelocity[i] = 0;
                    maxAcc[i] = 0;
                    maxDec[i] = 0;
                    maxJerkAcc[i] = 0;
                    maxJerkDec[i] = 0;
                }
            }
            unsigned int axisCount;
            int axis[constants::maxAxes];
            double target[constants::maxAxes];
            double maxVelocity[constants::maxAxes];
            double maxAcc[constants::maxAxes];
            double maxDec[constants::maxAxes];
            double maxJerkAcc[constants::maxAxes];
            double maxJerkDec[constants::maxAxes];
            Profile profile;
        };

        long StartPos(PosCommand *pPosCommand)
        {
            if (!pPosCommand)
                return -1;
            return WMX3Broker_Motion_StartPos(
                pPosCommand->axis, pPosCommand->target,
                static_cast<int>(pPosCommand->profile.type),
                pPosCommand->profile.velocity,
                pPosCommand->profile.acc,
                pPosCommand->profile.dec,
                pPosCommand->profile.jerkAccRatio,
                pPosCommand->profile.jerkDecRatio,
                pPosCommand->profile.startingVelocity,
                pPosCommand->profile.endVelocity);
        }

        long StartPos(unsigned int numCommands, PosCommand *pPosCommand)
        {
            if (!pPosCommand)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < numCommands; i++)
            {
                ret = StartPos(&pPosCommand[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long StartMov(PosCommand *pPosCommand)
        {
            if (!pPosCommand)
                return -1;
            return WMX3Broker_Motion_StartMov(
                pPosCommand->axis, pPosCommand->target,
                static_cast<int>(pPosCommand->profile.type),
                pPosCommand->profile.velocity,
                pPosCommand->profile.acc,
                pPosCommand->profile.dec,
                pPosCommand->profile.jerkAccRatio,
                pPosCommand->profile.jerkDecRatio,
                pPosCommand->profile.startingVelocity,
                pPosCommand->profile.endVelocity);
        }

        long StartMov(unsigned int numCommands, PosCommand *pPosCommand)
        {
            if (!pPosCommand)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < numCommands; i++)
            {
                ret = StartMov(&pPosCommand[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long StartJog(JogCommand *pJogCommand)
        {
            if (!pJogCommand)
                return -1;
            return WMX3Broker_Motion_StartJog(
                pJogCommand->axis,
                static_cast<int>(pJogCommand->profile.type),
                pJogCommand->profile.velocity,
                pJogCommand->profile.acc,
                pJogCommand->profile.jerkAccRatio);
        }

        long StartLinearIntplPos(LinearIntplCommand *pLinearIntplCommand)
        {
            if (!pLinearIntplCommand)
                return -1;
            return WMX3Broker_Motion_StartLinearIntplPos(
                pLinearIntplCommand->axisCount,
                pLinearIntplCommand->axis,
                pLinearIntplCommand->target,
                pLinearIntplCommand->maxVelocity,
                pLinearIntplCommand->maxAcc,
                pLinearIntplCommand->maxDec,
                static_cast<int>(pLinearIntplCommand->profile.type),
                pLinearIntplCommand->profile.velocity,
                pLinearIntplCommand->profile.acc,
                pLinearIntplCommand->profile.dec,
                pLinearIntplCommand->profile.jerkAccRatio,
                pLinearIntplCommand->profile.jerkDecRatio,
                pLinearIntplCommand->profile.startingVelocity,
                pLinearIntplCommand->profile.endVelocity);
        }

        long StopJogAtPos(PosCommand *pPosCommand)
        {
            if (!pPosCommand)
                return -1;
            return WMX3Broker_Motion_StopJogAtPos(
                pPosCommand->axis,
                pPosCommand->target,
                static_cast<int>(pPosCommand->profile.type),
                pPosCommand->profile.velocity,
                pPosCommand->profile.acc,
                pPosCommand->profile.dec,
                pPosCommand->profile.jerkAccRatio,
                pPosCommand->profile.jerkDecRatio);
        }

        long StopJogAtPos(unsigned int numCommands, PosCommand *pPosCommand)
        {
            if (!pPosCommand)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < numCommands; i++)
            {
                ret = StopJogAtPos(&pPosCommand[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long Stop(int axis)
        {
            return WMX3Broker_Motion_Stop(axis);
        }

        long Stop(AxisSelection *pAxisSelection)
        {
            if (!pAxisSelection)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < pAxisSelection->axisCount; i++)
            {
                ret = WMX3Broker_Motion_Stop(pAxisSelection->axis[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long ExecQuickStop(int axis)
        {
            return WMX3Broker_Motion_ExecQuickStop(axis);
        }

        long ExecQuickStop(AxisSelection *pAxisSelection)
        {
            if (!pAxisSelection)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < pAxisSelection->axisCount; i++)
            {
                ret = WMX3Broker_Motion_ExecQuickStop(pAxisSelection->axis[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long ExecTimedStop(int axis, double timeMilliseconds)
        {
            return WMX3Broker_Motion_ExecTimedStop(axis, timeMilliseconds);
        }

        long Wait(int axis)
        {
            return WMX3Broker_Motion_Wait(axis);
        }

        long Pause(int axis)
        {
            return WMX3Broker_Motion_Pause(axis);
        }

        long Resume(int axis)
        {
            return WMX3Broker_Motion_Resume(axis);
        }
    };

    //=========================================================================
    // Home sub-class
    //=========================================================================
    class Home
    {
    public:
        CoreMotion *cmApi;
        Home(CoreMotion *f) : cmApi(f) {}

        class AxisHomeData
        {
        public:
            AxisHomeData() : distHStoZPulse(0), distLStoZPulse(0) {}
            double distHStoZPulse;
            double distLStoZPulse;
        };

        class HomeData
        {
        public:
            HomeData() {}
            AxisHomeData axesHomeData[constants::maxAxes];
        };

        long StartHome(int axis)
        {
            return WMX3Broker_Home_StartHome(axis);
        }

        long StartHome(AxisSelection *pAxisSelection)
        {
            if (!pAxisSelection)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < pAxisSelection->axisCount; i++)
            {
                ret = WMX3Broker_Home_StartHome(pAxisSelection->axis[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long Continue(int axis)
        {
            return WMX3Broker_Home_Continue(axis);
        }

        long Cancel(int axis)
        {
            return WMX3Broker_Home_Cancel(axis);
        }

        long SetCommandPos(int axis, double position)
        {
            return WMX3Broker_Home_SetCommandPos(axis, position);
        }

        long SetFeedbackPos(int axis, double position)
        {
            return WMX3Broker_Home_SetFeedbackPos(axis, position);
        }

        long SetCommandPosToFeedbackPos(int axis, double posChangePerCycle = 0)
        {
            return WMX3Broker_Home_SetCommandPosToFeedbackPos(axis, posChangePerCycle);
        }

        long GetHomeData(HomeData *pHomeData)
        {
            return WMX3Broker_Home_GetHomeData(pHomeData);
        }

        long SetHomeDone(int axis, unsigned char value)
        {
            return WMX3Broker_Home_SetHomeDone(axis, value);
        }
    };

    //=========================================================================
    // Velocity sub-class
    //=========================================================================
    class Velocity
    {
    public:
        CoreMotion *cmApi;
        Velocity(CoreMotion *f) : cmApi(f) {}

        class VelCommand
        {
        public:
            VelCommand() : axis(0) {}
            VelCommand(int _axis, Profile _profile) : axis(_axis), profile(_profile) {}
            int axis;
            Profile profile;
        };

        long StartVel(VelCommand *pVelCommand)
        {
            if (!pVelCommand)
                return -1;
            return WMX3Broker_Velocity_StartVel(
                pVelCommand->axis,
                static_cast<int>(pVelCommand->profile.type),
                pVelCommand->profile.velocity,
                pVelCommand->profile.acc,
                pVelCommand->profile.dec,
                pVelCommand->profile.jerkAccRatio,
                pVelCommand->profile.jerkDecRatio);
        }

        long StartVel(unsigned int numCommands, VelCommand *pVelCommand)
        {
            if (!pVelCommand)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < numCommands; i++)
            {
                ret = StartVel(&pVelCommand[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long Stop(int axis)
        {
            return WMX3Broker_Velocity_Stop(axis);
        }

        long Stop(AxisSelection *pAxisSelection)
        {
            if (!pAxisSelection)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < pAxisSelection->axisCount; i++)
            {
                ret = WMX3Broker_Velocity_Stop(pAxisSelection->axis[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long ExecQuickStop(int axis)
        {
            return WMX3Broker_Velocity_ExecQuickStop(axis);
        }

        long ExecTimedStop(int axis, double timeMilliseconds)
        {
            return WMX3Broker_Velocity_ExecTimedStop(axis, timeMilliseconds);
        }

        long OverrideVel(VelCommand *pVelCommand)
        {
            if (!pVelCommand)
                return -1;
            return WMX3Broker_Velocity_OverrideVel(
                pVelCommand->axis,
                static_cast<int>(pVelCommand->profile.type),
                pVelCommand->profile.velocity,
                pVelCommand->profile.acc,
                pVelCommand->profile.dec,
                pVelCommand->profile.jerkAccRatio,
                pVelCommand->profile.jerkDecRatio);
        }
    };

    //=========================================================================
    // Torque sub-class
    //=========================================================================
    class Torque
    {
    public:
        CoreMotion *cmApi;
        Torque(CoreMotion *f) : cmApi(f) {}

        class TrqCommand
        {
        public:
            TrqCommand() : axis(0), torque(0) {}
            TrqCommand(int _axis, double _torque) : axis(_axis), torque(_torque) {}
            int axis;
            double torque;
        };

        long SetMaxTrqLimit(int axis, double torque)
        {
            return WMX3Broker_Torque_SetMaxTrqLimit(axis, torque);
        }

        long GetMaxTrqLimit(int axis, double *pTorque)
        {
            return WMX3Broker_Torque_GetMaxTrqLimit(axis, pTorque);
        }

        long SetPositiveTrqLimit(int axis, double torque)
        {
            return WMX3Broker_Torque_SetPositiveTrqLimit(axis, torque);
        }

        long GetPositiveTrqLimit(int axis, double *pTorque)
        {
            return WMX3Broker_Torque_GetPositiveTrqLimit(axis, pTorque);
        }

        long SetNegativeTrqLimit(int axis, double torque)
        {
            return WMX3Broker_Torque_SetNegativeTrqLimit(axis, torque);
        }

        long GetNegativeTrqLimit(int axis, double *pTorque)
        {
            return WMX3Broker_Torque_GetNegativeTrqLimit(axis, pTorque);
        }

        long StartTrq(TrqCommand *pTrqCommand)
        {
            if (!pTrqCommand)
                return -1;
            return WMX3Broker_Torque_StartTrq(pTrqCommand->axis, pTrqCommand->torque);
        }

        long StartTrq(unsigned int numCommands, TrqCommand *pTrqCommand)
        {
            if (!pTrqCommand)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < numCommands; i++)
            {
                ret = StartTrq(&pTrqCommand[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }

        long StartTrq(TrqCommand *pTrqCommand, double maxMotorSpeed)
        {
            if (!pTrqCommand)
                return -1;
            return WMX3Broker_Torque_StartTrqWithMaxSpeed(pTrqCommand->axis, pTrqCommand->torque, maxMotorSpeed);
        }

        long StopTrq(int axis)
        {
            return WMX3Broker_Torque_StopTrq(axis);
        }

        long StopTrq(AxisSelection *pAxisSelection)
        {
            if (!pAxisSelection)
                return -1;
            long ret = 0;
            for (unsigned int i = 0; i < pAxisSelection->axisCount; i++)
            {
                ret = WMX3Broker_Torque_StopTrq(pAxisSelection->axis[i]);
                if (ret != 0)
                    return ret;
            }
            return ret;
        }
    };

    //=========================================================================
    // Config sub-class
    //=========================================================================
    class Config
    {
    public:
        CoreMotion *cmApi;
        Config(CoreMotion *f) : cmApi(f) {}

        class VelocityMonitorSource
        {
        public:
            enum T
            {
                UseVelocityFeedback,
                CalculateFromPositionFeedback
            };
        };

        // FeedbackParam class
        class FeedbackParam
        {
        public:
            FeedbackParam()
            {
                memset(this, 0, sizeof(FeedbackParam));
                // velocityMonitorSource defaults to UseVelocityFeedback(0) via memset
            }
            double inPosWidth;
            double inPosWidth2;
            double inPosWidth3;
            double inPosWidth4;
            double inPosWidth5;
            VelocityMonitorSource::T velocityMonitorSource;
            double posSetWidth;
            double delayedPosSetWidth;
            double delayedPosSetMilliseconds;
        };

        class HomeDirection
        {
        public:
            enum T
            {
                Positive,
                Negative
            };
        };

        class HomeType
        {
        public:
            enum T
            {
                CurrentPos,
                ZPulse,
                HS,
                HSHS,
                HSZPulse,
                HSReverseZPulse,
                HSOff,
                HSOffZPulse,
                HSOffReverseZPulse,
                LSReverseZPulse,
                NearLSReverseZPulse,
                ExternalLSReverseZPulse,
                TouchProbe,
                HSTouchProbe,
                LS,
                NearLS,
                ExternalLS,
                MechanicalEndDetection,
                MechanicalEndDetectionHS,
                MechanicalEndDetectionLS,
                MechanicalEndDetectionReverseZPulse
            };
        };

        // HomeParam class (from CoreMotionApi.h)
        class HomeParam
        {
        public:
            HomeParam()
            {
                memset(this, 0, sizeof(HomeParam));
                // homeType defaults to CurrentPos(0) via memset
                // homeDirection defaults to Positive(0) via memset
            }
            HomeType::T homeType;
            HomeDirection::T homeDirection;
            double homingVelocitySlow;
            double homingVelocitySlowAcc;
            double homingVelocitySlowDec;
            double homingVelocityFast;
            double homingVelocityFastAcc;
            double homingVelocityFastDec;
            double homingReverseDistance;
            double homeShiftVelocity;
            double homeShiftAcc;
            double homeShiftDec;
            double homeShiftDistance;
            bool invertHSPolarity;
            unsigned int multipleZPulse;
            bool roundPosCmdAfterHoming;
            bool pauseMode;
            double maxHSOnAtStartReverseDistance;
            double maxLSReverseDistance;
            unsigned int zPulseDistanceCheck;
            double homePosition;
            bool gantryHomingUseSlaveHS;
            bool gantryHomingUseSlaveLS;
            bool gantryHomingUseSlaveZPulse;
            bool gantryHomingUseSlaveTouchProbe;
            bool gantryHomingUseSlaveMechanicalEnd;
            bool gantryHomingRetainSyncOffset;
            bool immediateStopAtLS;
            double mechanicalEndDetectionPosDiff;
            double mechanicalEndDetectionTimeMilliseconds;
            bool mechanicalEndDetectionIgnoreLS;
            double mechanicalEndDetectionFirstTorqueLimit;
            double mechanicalEndDetectionSecondTorqueLimit;
            bool openLoopHoming;
            bool clearHomeDoneOnServoOff;
            bool clearHomeDoneOnCommStop;
        };

        class LimitSwitchType
        {
        public:
            enum T
            {
                None,
                ServoOff,
                DecServoOff,
                Dec,
                SlowDecServoOff,
                SlowDec,
                SeparatePositiveLSNegativeLS
            };
        };

        class LimitSwitchDirection
        {
        public:
            enum T
            {
                Normal,
                Reverse
            };
        };

        // LimitParam class
        class LimitParam
        {
        public:
            LimitParam()
            {
                memset(this, 0, sizeof(LimitParam));
                // All LimitSwitchType members default to None(0) via memset
            }
            LimitSwitchType::T lsType;
            LimitSwitchType::T positiveLSType;
            LimitSwitchType::T negativeLSType;
            bool invertPositiveLSPolarity;
            bool invertNegativeLSPolarity;
            LimitSwitchType::T nearLSType;
            LimitSwitchType::T nearPositiveLSType;
            LimitSwitchType::T nearNegativeLSType;
            int nearPositiveLSByte;
            int nearPositiveLSBit;
            bool invertNearPositiveLSPolarity;
            int nearNegativeLSByte;
            int nearNegativeLSBit;
            bool invertNearNegativeLSPolarity;
            LimitSwitchType::T externalLSType;
            LimitSwitchType::T externalPositiveLSType;
            LimitSwitchType::T externalNegativeLSType;
            int externalPositiveLSByte;
            int externalPositiveLSBit;
            bool invertExternalPositiveLSPolarity;
            int externalNegativeLSByte;
            int externalNegativeLSBit;
            bool invertExternalNegativeLSPolarity;
            LimitSwitchType::T softLimitType;
            LimitSwitchType::T positiveSoftLimitType;
            LimitSwitchType::T negativeSoftLimitType;
            double softLimitPositivePos;
            double softLimitNegativePos;
            double lsDec;
            double lsSlowDec;
            bool allLSDuringHoming;
            LimitSwitchDirection::T lsDirection;
        };

        class ProhibitOvertravelType
        {
        public:
            enum T
            {
                Disabled,
                ChangeDeceleration,
                ChangeInitialVelocity
            };
        };

        class LinearIntplOverrideType
        {
        public:
            enum T
            {
                Smoothing,
                Blending,
                FastBlending
            };
        };

        class LinearIntplProfileCalcMode
        {
        public:
            enum T
            {
                AxisLimit,
                MatchSlowestAxis,
                MatchFarthestAxis
            };
        };

        class CircularIntplOverrideType
        {
        public:
            enum T
            {
                Blending,
                FastBlending
            };
        };

        // MotionParam class
        class MotionParam
        {
        public:
            MotionParam()
            {
                memset(this, 0, sizeof(MotionParam));
                // All enum members default to first value (0) via memset:
                // ProhibitOvertravelType::Disabled, LinearIntplOverrideType::Smoothing,
                // CircularIntplOverrideType::Blending, LinearIntplProfileCalcMode::AxisLimit
            }
            double quickStopDec;
            ProhibitOvertravelType::T prohibitOvertravel;
            LinearIntplOverrideType::T linearIntplOverrideType;
            unsigned int linearIntplOverrideSmoothPercent;
            CircularIntplOverrideType::T circularIntplOverrideType;
            bool interruptedIntplUseQuickStop;
            bool singleTurnReduceToHalfTurn;
            bool enableGlobalStartingVelocity;
            double globalStartingVelocity;
            bool enableGlobalEndVelocity;
            double globalEndVelocity;
            bool enableGlobalMinVelocity;
            double globalMinVelocity;
            bool enableGlobalMovingAverageProfileTimeMilliseconds;
            double globalMovingAverageProfileTimeMilliseconds;
            bool apiWaitUntilMotionStart;
            LinearIntplProfileCalcMode::T linearIntplProfileCalcMode;
        };

        // AlarmParam class
        class AlarmParam
        {
        public:
            AlarmParam() : followingErrorLimit(0), enableFollowingError(false) {}
            double followingErrorLimit;
            bool enableFollowingError;
        };

        class AxisParam
        {
        public:
            AxisParam()
            {
                memset(this, 0, sizeof(AxisParam));
                // AxisCommandMode::Position(0) is default via memset
            }
            AxisCommandMode::T axisCommandMode[constants::maxAxes];
            double gearRatioNumerator[constants::maxAxes];
            double gearRatioDenominator[constants::maxAxes];
            bool singleTurnMode[constants::maxAxes];
            unsigned int singleTurnEncoderCount[constants::maxAxes];
            double maxTrqLimit[constants::maxAxes];
            double negativeTrqLimit[constants::maxAxes];
            double positiveTrqLimit[constants::maxAxes];
            double axisUnit[constants::maxAxes];
            double velocityFeedforwardGain[constants::maxAxes];
            char axisPolarity[constants::maxAxes];
            double maxMotorSpeed[constants::maxAxes];
            bool absoluteEncoderMode[constants::maxAxes];
            double absoluteEncoderHomeOffset[constants::maxAxes];
        };

        // SyncParam class (placeholder for SystemParam)
        class SyncParam
        {
        public:
            SyncParam() { memset(this, 0, sizeof(SyncParam)); }
            int masterAxis;
            double ratio;
        };

        // FlightRecorderParam class (placeholder for SystemParam)
        class FlightRecorderParam
        {
        public:
            FlightRecorderParam() { memset(this, 0, sizeof(FlightRecorderParam)); }
            bool enabled;
            unsigned int bufferSize;
        };

        // EmergencyStopParam class (placeholder for SystemParam)
        class EmergencyStopParam
        {
        public:
            EmergencyStopParam() { memset(this, 0, sizeof(EmergencyStopParam)); }
            double eStopDec;
        };

        // SystemParam class
        class SystemParam
        {
        public:
            SystemParam() { memset(this, 0, sizeof(SystemParam)); }
            FeedbackParam feedbackParam[constants::maxAxes];
            HomeParam homeParam[constants::maxAxes];
            LimitParam limitParam[constants::maxAxes];
            MotionParam motionParam[constants::maxAxes];
            AlarmParam alarmParam[constants::maxAxes];
            SyncParam syncParam[constants::maxAxes];
            FlightRecorderParam flightRecorderParam;
            EmergencyStopParam emergencyStopParam;
        };

        long SetParam(SystemParam *pParam, SystemParam *pParamError = NULL)
        {
            return WMX3Broker_Config_SetParam(pParam, pParamError);
        }

        long GetDefaultParam(SystemParam *pParam)
        {
            return WMX3Broker_Config_GetDefaultParam(pParam);
        }

        long GetDefaultAxisParam(AxisParam *pAxisParam)
        {
            return WMX3Broker_Config_GetDefaultAxisParam(pAxisParam);
        }

        long SetHomeParam(int axis, HomeParam *pParam, HomeParam *pParamError = NULL)
        {
            return WMX3Broker_Config_SetHomeParam(axis, pParam);
        }

        long GetHomeParam(int axis, HomeParam *pParam)
        {
            return WMX3Broker_Config_GetHomeParam(axis, pParam);
        }

        long SetFeedbackParam(int axis, FeedbackParam *pParam, FeedbackParam *pParamError = NULL)
        {
            return WMX3Broker_Config_SetFeedbackParam(axis, pParam);
        }

        long GetFeedbackParam(int axis, FeedbackParam *pParam)
        {
            return WMX3Broker_Config_GetFeedbackParam(axis, pParam);
        }

        long SetLimitParam(int axis, LimitParam *pParam, LimitParam *pParamError = NULL)
        {
            return WMX3Broker_Config_SetLimitParam(axis, pParam);
        }

        long GetLimitParam(int axis, LimitParam *pParam)
        {
            return WMX3Broker_Config_GetLimitParam(axis, pParam);
        }

        long SetMotionParam(int axis, MotionParam *pParam, MotionParam *pParamError = NULL)
        {
            return WMX3Broker_Config_SetMotionParam(axis, pParam);
        }

        long GetMotionParam(int axis, MotionParam *pParam)
        {
            return WMX3Broker_Config_GetMotionParam(axis, pParam);
        }

        long SetAlarmParam(int axis, AlarmParam *pParam, AlarmParam *pParamError = NULL)
        {
            return WMX3Broker_Config_SetAlarmParam(axis, pParam);
        }

        long GetAlarmParam(int axis, AlarmParam *pParam)
        {
            return WMX3Broker_Config_GetAlarmParam(axis, pParam);
        }

        long SetGearRatio(int axis, double numerator, double denominator)
        {
            return WMX3Broker_Config_SetGearRatio(axis, numerator, denominator);
        }

        long GetGearRatio(int axis, double *pNumerator, double *pDenominator)
        {
            return WMX3Broker_Config_GetGearRatio(axis, pNumerator, pDenominator);
        }

        long SetSingleTurn(int axis, bool enable, unsigned int encoderCount)
        {
            return WMX3Broker_Config_SetSingleTurn(axis, enable ? 1 : 0, encoderCount);
        }

        long GetSingleTurn(int axis, bool *pEnable, unsigned int *pEncoderCount)
        {
            if (!pEnable || !pEncoderCount)
                return -1;
            int enable;
            long ret = WMX3Broker_Config_GetSingleTurn(axis, &enable, pEncoderCount);
            if (ret == 0)
                *pEnable = (enable != 0);
            return ret;
        }

        long SetVelocityFeedforwardGain(int axis, double gain)
        {
            return WMX3Broker_Config_SetVelocityFeedforwardGain(axis, gain);
        }

        long GetVelocityFeedforwardGain(int axis, double *pGain)
        {
            return WMX3Broker_Config_GetVelocityFeedforwardGain(axis, pGain);
        }

        long GetAxisParam(int axis, AxisParam *pParam)
        {
            return WMX3Broker_Config_GetAxisParam(axis, pParam);
        }

        long SetAxisUnit(int axis, double unit)
        {
            return WMX3Broker_Config_SetAxisUnit(axis, unit);
        }

        long GetAxisUnit(int axis, double *pUnit)
        {
            return WMX3Broker_Config_GetAxisUnit(axis, pUnit);
        }

        long SetAbsoluteEncoderHomeOffset(int axis, double offset)
        {
            return WMX3Broker_Config_SetAbsoluteEncoderHomeOffset(axis, offset);
        }
    };

    //=========================================================================
    // CoreMotion main class
    //=========================================================================
    class CoreMotion
    {
    public:
        AxisControl *axisControl;
        Motion *motion;
        Home *home;
        Velocity *velocity;
        Torque *torque;
        Config *config;

        CoreMotion(WMX3Api *f)
        {
            axisControl = new AxisControl(this);
            motion = new Motion(this);
            home = new Home(this);
            velocity = new Velocity(this);
            torque = new Torque(this);
            config = new Config(this);
        }

        CoreMotion()
        {
            axisControl = new AxisControl(this);
            motion = new Motion(this);
            home = new Home(this);
            velocity = new Velocity(this);
            torque = new Torque(this);
            config = new Config(this);
        }

        ~CoreMotion()
        {
            delete axisControl;
            axisControl = NULL;
            delete motion;
            motion = NULL;
            delete home;
            home = NULL;
            delete velocity;
            velocity = NULL;
            delete torque;
            torque = NULL;
            delete config;
            config = NULL;
        }

        long GetStatus(CoreMotionStatus *pStatus)
        {
            return WMX3Broker_CoreMotion_GetStatus(pStatus);
        }

        bool IsDeviceValid()
        {
            return WMX3Broker_CoreMotion_IsDeviceValid() != 0;
        }

        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_CoreMotion_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_CoreMotion_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // COREMOTION_SIM_H
