// WMXBrokerClient.h
// Header-only wrapper class for VS2012 compatibility
// Provides wmxAPI::WMXLIB interface that internally calls C API
//
// Usage:
//   Replace #include "WMXLIB.h" with #include "WMXBrokerClient.h"
//   Link with WMXBroker.lib

#ifndef WMXBROKER_CLIENT_H
#define WMXBROKER_CLIENT_H

#include "WMXBrokerC.h"
#include "wmxapi_def.h"

//=============================================================================
// WMX 1.5 Motion Block Structures
// Note: All structures are defined in WMXBrokerC.h (included above)
// The following structures are available:
//   - PosBlockExt2, PosBlockExt2Ind
//   - IntBlockExt2, IntBlockExt2Ind
//   - PosBlockListExt2, PosBlockListExt2Ind
//   - CoordinatedPosBlockListExt2, CoordinatedPosBlockListExt2Ind
//   - CoordinatedPosBlockExt2, CoordinatedPosBlockExt2Ind
//   - WMX_HOME_DATA, WMX_AXIS_HOME_DATA
//=============================================================================

// IntBlock2 is NOT in WMXBrokerC.h, define it here if needed
#ifndef INTBLOCK2_DEFINED
#define INTBLOCK2_DEFINED

#ifndef MAX_ALLAXES
#define MAX_ALLAXES 64
#endif

// IntBlock2 - Trapezoidal profile composite vector interpolation
typedef struct
{
    short axis;
    double target;
    double velocity;
    double acc;
    double dec;
} IntBlock2Ind, *PIntBlock2Ind;

typedef struct
{
    short axisCount;
    double compVelocity;
    double compAcc;
    double compDec;
    double compStartingVelocity;
    double compEndVelocity;
    double compMinimumVelocity;
    IntBlock2Ind pos_block[MAX_ALLAXES];
} IntBlock2, *PIntBlock2;

#endif // INTBLOCK2_DEFINED

namespace wmxAPI
{

    class WMXLIB; // Forward declaration

    namespace common
    {

        // Io wrapper class - WMX 1.5 compatible interface
        class Io
        {
        public:
            WMXLIB *wmxlib;
            Io(WMXLIB *f) : wmxlib(f) {}

            // I/O Output APIs
            WMXAPIFUNC SetOutBit(short byte, short bit, unsigned char data)
            {
                return WMXBroker_Io_SetOutBit(byte, bit, data);
            }
            WMXAPIFUNC SetOutByte(short offsetByte, unsigned char data)
            {
                return WMXBroker_Io_SetOutByte(offsetByte, data);
            }
            WMXAPIFUNC SetOutBytes(short offsetByte, short size, unsigned char *data)
            {
                return WMXBroker_Io_SetOutBytes(offsetByte, size, data);
            }

            // I/O Input APIs
            WMXAPIFUNC GetInBit(short byte, short bit, unsigned char *data)
            {
                return WMXBroker_Io_GetInBit(byte, bit, data);
            }
            WMXAPIFUNC GetInByte(short offsetByte, unsigned char *data)
            {
                return WMXBroker_Io_GetInByte(offsetByte, data);
            }
            WMXAPIFUNC GetInBytes(short offsetByte, short size, unsigned char *data)
            {
                return WMXBroker_Io_GetInBytes(offsetByte, size, data);
            }

            // I/O Output Read APIs
            WMXAPIFUNC GetOutBit(short byte, short bit, unsigned char *data)
            {
                return WMXBroker_Io_GetOutBit(byte, bit, data);
            }
            WMXAPIFUNC GetOutByte(short offsetByte, unsigned char *data)
            {
                return WMXBroker_Io_GetOutByte(offsetByte, data);
            }
            WMXAPIFUNC GetOutBytes(short offsetByte, short size, unsigned char *data)
            {
                return WMXBroker_Io_GetOutBytes(offsetByte, size, data);
            }

            // I/O Initial Output APIs
            WMXAPIFUNC SetInitialOutBit(short byte, short bit, unsigned char data)
            {
                return WMXBroker_Io_SetInitialOutBit(byte, bit, data);
            }
            WMXAPIFUNC SetInitialOutByte(short offsetByte, unsigned char data)
            {
                return WMXBroker_Io_SetInitialOutByte(offsetByte, data);
            }
            WMXAPIFUNC SetInitialOutBytes(short offsetByte, short size, unsigned char *data)
            {
                return WMXBroker_Io_SetInitialOutBytes(offsetByte, size, data);
            }
            WMXAPIFUNC GetInitialOutBit(short byte, short bit, unsigned char *data)
            {
                return WMXBroker_Io_GetInitialOutBit(byte, bit, data);
            }
            WMXAPIFUNC GetInitialOutByte(short offsetByte, unsigned char *data)
            {
                return WMXBroker_Io_GetInitialOutByte(offsetByte, data);
            }
            WMXAPIFUNC GetInitialOutBytes(short offsetByte, short size, unsigned char *data)
            {
                return WMXBroker_Io_GetInitialOutBytes(offsetByte, size, data);
            }
        };

        // AxisControl wrapper class - WMX 1.5 compatible interface (common namespace)
        class AxisControl
        {
        public:
            AxisControl() {}

            WMXAPIFUNC GetAxisMode(short axis, WMX_AXIS_COMMAND_MODE *pMode)
            {
                int mode;
                long ret = WMXBroker_AxisControl_GetAxisMode(axis, &mode);
                if (ret == 0 && pMode)
                    *pMode = static_cast<WMX_AXIS_COMMAND_MODE>(mode);
                return ret;
            }
            WMXAPIFUNC SetAxisMode(short axis, WMX_AXIS_COMMAND_MODE mode)
            {
                return WMXBroker_AxisControl_SetAxisMode(axis, static_cast<int>(mode));
            }
            WMXAPIFUNC ServoOn(short axis, int on)
            {
                return WMXBroker_AxisControl_ServoOn(axis, on);
            }
            WMXAPIFUNC ServoOn(short firstAxis, short lastAxis, int on)
            {
                return WMXBroker_AxisControl_ServoOnRange(firstAxis, lastAxis, on);
            }
            WMXAPIFUNC AmpAlarmClear(short axis)
            {
                return WMXBroker_AxisControl_AmpAlarmClear(axis);
            }
            WMXAPIFUNC AmpAlarmClear(short firstAxis, short lastAxis)
            {
                return WMXBroker_AxisControl_AmpAlarmClearRange(firstAxis, lastAxis);
            }
            WMXAPIFUNC AxisAlarmClear(short axis)
            {
                return WMXBroker_AxisControl_AxisAlarmClear(axis);
            }
            WMXAPIFUNC AxisAlarmClear(short firstAxis, short lastAxis)
            {
                return WMXBroker_AxisControl_AxisAlarmClearRange(firstAxis, lastAxis);
            }
            WMXAPIFUNC GetPosCommand(short axis, double *pPosition)
            {
                return WMXBroker_AxisControl_GetPosCommand(axis, pPosition);
            }
            WMXAPIFUNC GetPosFeedback(short axis, double *pPosition)
            {
                return WMXBroker_AxisControl_GetPosFeedback(axis, pPosition);
            }
            WMXAPIFUNC GetVelCommand(short axis, double *pVelocity)
            {
                return WMXBroker_AxisControl_GetVelCommand(axis, pVelocity);
            }
            WMXAPIFUNC GetVelFeedback(short axis, double *pVelocity)
            {
                return WMXBroker_AxisControl_GetVelFeedback(axis, pVelocity);
            }
        };

        // Config wrapper class - WMX 1.5 compatible interface (common namespace)
        class Config
        {
        public:
            Config() {}

            WMXAPIFUNC GetAxisHomeParam(short axis, WMX_HOME_PARAM *pParam)
            {
                return WMXBroker_Config_GetAxisHomeParam(axis, pParam);
            }
            WMXAPIFUNC SetAxisHomeParam(short axis, WMX_HOME_PARAM *pParam)
            {
                return WMXBroker_Config_SetAxisHomeParam(axis, pParam);
            }
            WMXAPIFUNC GetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM *pParam)
            {
                return WMXBroker_Config_GetAxisFeedbackParam(axis, pParam);
            }
            WMXAPIFUNC SetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM *pParam)
            {
                return WMXBroker_Config_SetAxisFeedbackParam(axis, pParam);
            }
            WMXAPIFUNC GetAxisLimitParam(short axis, WMX_LIMIT_PARAM *pParam)
            {
                return WMXBroker_Config_GetAxisLimitParam(axis, pParam);
            }
            WMXAPIFUNC SetAxisLimitParam(short axis, WMX_LIMIT_PARAM *pParam)
            {
                return WMXBroker_Config_SetAxisLimitParam(axis, pParam);
            }
            WMXAPIFUNC GetAxisSystemParam(short axis, WMX_SYSTEM_PARAM *pParam)
            {
                return WMXBroker_Config_GetAxisSystemParam(axis, pParam);
            }
            WMXAPIFUNC SetAxisSystemParam(short axis, WMX_SYSTEM_PARAM *pParam)
            {
                return WMXBroker_Config_SetAxisSystemParam(axis, pParam);
            }
            WMXAPIFUNC GetAxisAlarmParam(short axis, WMX_ALARM_PARAM *pParam)
            {
                return WMXBroker_Config_GetAxisAlarmParam(axis, pParam);
            }
            WMXAPIFUNC SetAxisAlarmParam(short axis, WMX_ALARM_PARAM *pParam)
            {
                return WMXBroker_Config_SetAxisAlarmParam(axis, pParam);
            }
            WMXAPIFUNC GetAxisMotionParam(short axis, WMX_MOTION_PARAM *pParam)
            {
                return WMXBroker_Config_GetAxisMotionParam(axis, pParam);
            }
            WMXAPIFUNC SetAxisMotionParam(short axis, WMX_MOTION_PARAM *pParam)
            {
                return WMXBroker_Config_SetAxisMotionParam(axis, pParam);
            }
            WMXAPIFUNC GetAxisSingleTurn(short axis, unsigned char *pEnable, unsigned int *pEncoderCount)
            {
                int enable;
                long ret = WMXBroker_Config_GetAxisSingleTurn(axis, &enable, pEncoderCount);
                if (ret == 0 && pEnable)
                    *pEnable = static_cast<unsigned char>(enable);
                return ret;
            }
            WMXAPIFUNC SetAxisSingleTurn(short axis, unsigned char enable, unsigned int encoderCount)
            {
                return WMXBroker_Config_SetAxisSingleTurn(axis, static_cast<int>(enable), encoderCount);
            }
            WMXAPIFUNC GetAxisMultiplier(short axis, unsigned int *pMultiplier)
            {
                return WMXBroker_Config_GetAxisMultiplier(axis, pMultiplier);
            }
            WMXAPIFUNC SetAxisMultiplier(short axis, unsigned int multiplier)
            {
                return WMXBroker_Config_SetAxisMultiplier(axis, multiplier);
            }
            WMXAPIFUNC GetAxisVelocityFeedforwardGain(short axis, double *pGain)
            {
                return WMXBroker_Config_GetAxisVelocityFeedforwardGain(axis, pGain);
            }
            WMXAPIFUNC SetAxisVelocityFeedforwardGain(short axis, double gain)
            {
                return WMXBroker_Config_SetAxisVelocityFeedforwardGain(axis, gain);
            }
        };

        // Home wrapper class - WMX 1.5 compatible interface (common namespace)
        class Home
        {
        public:
            Home() {}

            WMXAPIFUNC StartHome(int axis)
            {
                return WMXBroker_Home_StartHome(axis);
            }
            WMXAPIFUNC StartHome(int firstAxis, int lastAxis)
            {
                return WMXBroker_Home_StartHomeRange(firstAxis, lastAxis);
            }
            WMXAPIFUNC Continue(short axis)
            {
                return WMXBroker_Home_Continue(axis);
            }
            WMXAPIFUNC Cancel(short axis)
            {
                return WMXBroker_Home_Cancel(axis);
            }
            WMXAPIFUNC SetFeedbackPosition(short axis, double position)
            {
                return WMXBroker_Home_SetFeedbackPosition(axis, position);
            }
            WMXAPIFUNC SetCommandPosition(short axis, double position)
            {
                return WMXBroker_Home_SetCommandPosition(axis, position);
            }
            WMXAPIFUNC SetCmdPosToFbPos(short axis)
            {
                return WMXBroker_Home_SetCmdPosToFbPos(axis);
            }
            WMXAPIFUNC GetHomeData(WMX_HOME_DATA *pHomeData)
            {
                return WMXBroker_Home_GetHomeData(pHomeData);
            }
            // AxisSelection based homing
            WMXAPIFUNC StartHome(WMX_AXIS_SELECTION* axis_selection)
            {
                return WMXBroker_Home_StartHomeAxisSelection(axis_selection);
            }
        };

    } // namespace common

    namespace basicMotion
    {

        // BasicMotion wrapper class - WMX 1.5 compatible interface
        class BasicMotion
        {
        public:
            BasicMotion() {}

            WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec)
            {
                return WMXBroker_BasicMotion_StartPos(axis, target, velocity, acc, dec);
            }
            WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec)
            {
                return WMXBroker_BasicMotion_StartMov(axis, target, velocity, acc, dec);
            }
            WMXAPIFUNC StartJog(short axis, double velocity, double acc)
            {
                return WMXBroker_BasicMotion_StartJog(axis, velocity, acc);
            }
            // Position commands with starting/end velocity (7 params)
            WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec,
                                double startingVelocity, double endVelocity)
            {
                return WMXBroker_BasicMotion_StartPosEx(axis, target, velocity, acc, dec, startingVelocity, endVelocity);
            }
            WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec,
                                double startingVelocity, double endVelocity)
            {
                return WMXBroker_BasicMotion_StartMovEx(axis, target, velocity, acc, dec, startingVelocity, endVelocity);
            }
            WMXAPIFUNC StopAxis(int axis)
            {
                return WMXBroker_BasicMotion_StopAxis(axis);
            }
            WMXAPIFUNC StopAxis(WMX_AXIS_SELECTION *axis_selection)
            {
                return WMXBroker_BasicMotion_StopAxisSelection(axis_selection);
            }
            WMXAPIFUNC QStopAxis(int axis)
            {
                return WMXBroker_BasicMotion_QStopAxis(axis);
            }
            WMXAPIFUNC QStopAxis(WMX_AXIS_SELECTION *axis_selection)
            {
                return WMXBroker_BasicMotion_QStopAxisSelection(axis_selection);
            }
            WMXAPIFUNC TimeStopAxis(int axis, double time)
            {
                return WMXBroker_BasicMotion_TimeStopAxis(axis, time);
            }
            WMXAPIFUNC TimeStopAxis(WMX_AXIS_SELECTION *axis_selection, double time)
            {
                return WMXBroker_BasicMotion_TimeStopAxisSelection(axis_selection, time);
            }
            WMXAPIFUNC WaitAxis(int axis)
            {
                return WMXBroker_BasicMotion_WaitAxis(axis);
            }
            WMXAPIFUNC PauseAxis(int axis)
            {
                return WMXBroker_BasicMotion_PauseAxis(axis);
            }
            WMXAPIFUNC ResumeAxis(int axis)
            {
                return WMXBroker_BasicMotion_ResumeAxis(axis);
            }
        };

    } // namespace basicMotion

    namespace extMotion1
    {

        // ExtMotion1 wrapper class - Jerk (pulse/s^3) based motion
        class ExtMotion1
        {
        public:
            ExtMotion1() {}

            WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target,
                                    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
                                    double startingVelocity, double endVelocity)
            {
                return WMXBroker_ExtMotion1_StartJerkPos(axis, static_cast<int>(profile), target,
                                                         velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity);
            }
            WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target,
                                    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
                                    double startingVelocity, double endVelocity)
            {
                return WMXBroker_ExtMotion1_StartJerkMov(axis, static_cast<int>(profile), target,
                                                         velocity, acc, dec, jerkAcc, jerkDec, startingVelocity, endVelocity);
            }
            WMXAPIFUNC StartJerkJog(short axis, WMX_PROFILE_TYPE profile,
                                    double velocity, double acc, double jerkAcc)
            {
                return WMXBroker_ExtMotion1_StartJerkJog(axis, static_cast<int>(profile),
                                                         velocity, acc, jerkAcc);
            }
        };

    } // namespace extMotion1

    namespace extMotion2
    {

        // ExtMotion2 wrapper class - Jerk ratio based motion
        class ExtMotion2
        {
        public:
            ExtMotion2() {}

            WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target,
                                    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
                                    double startingVelocity, double endVelocity)
            {
                return WMXBroker_ExtMotion2_StartJerkPos(axis, static_cast<int>(profile), target,
                                                         velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
            }
            WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target,
                                    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
                                    double startingVelocity, double endVelocity)
            {
                return WMXBroker_ExtMotion2_StartJerkMov(axis, static_cast<int>(profile), target,
                                                         velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity);
            }
            WMXAPIFUNC StartJerkJog(short axis, WMX_PROFILE_TYPE profile,
                                    double velocity, double acc, double jerkAccRatio)
            {
                return WMXBroker_ExtMotion2_StartJerkJog(axis, static_cast<int>(profile),
                                                         velocity, acc, jerkAccRatio);
            }
            // Stop jerk jog at position
            WMXAPIFUNC StopJerkJogAtPos(short axis, WMX_PROFILE_TYPE profile, double target,
                                        double dec, double jerkDecRatio)
            {
                return WMXBroker_ExtMotion2_StopJerkJogAtPos(axis, static_cast<int>(profile),
                                                             target, dec, jerkDecRatio);
            }
            // Coordinated position command
            WMXAPIFUNC StartJerkCoordinatedPos(short axis, WMX_PROFILE_TYPE profile,
                                               double target, double velocity, double acc, double dec,
                                               double jerkAccRatio, double jerkDecRatio,
                                               double startingVelocity, double endVelocity,
                                               short axis2, double axis2target, double axis2smoothRatio)
            {
                return WMXBroker_ExtMotion2_StartJerkCoordinatedPos(axis, static_cast<int>(profile),
                                                                    target, velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity, endVelocity,
                                                                    axis2, axis2target, axis2smoothRatio);
            }
            // Block-based StartJerkPos (multi-axis)
            WMXAPIFUNC StartJerkPos(PosBlockExt2* mpos_block)
            {
                return WMXBroker_ExtMotion2_StartJerkPosBlock(mpos_block);
            }
            // Block-based coordinated position command
            WMXAPIFUNC StartJerkCoordinatedPos(CoordinatedPosBlockExt2* mpos_block)
            {
                return WMXBroker_ExtMotion2_StartJerkCoordinatedPosBlock(mpos_block);
            }
            // Linear interpolation with jerk
            WMXAPIFUNC StartJerkLinIntPos(IntBlockExt2* mpos_block)
            {
                return WMXBroker_ExtMotion2_StartJerkLinIntPos(mpos_block);
            }
        };

    } // namespace extMotion2

    namespace extList2
    {

        // ExtList2 wrapper class - List based motion
        class ExtList2
        {
        public:
            ExtList2() {}

            WMXAPIFUNC BeginList(unsigned int channel)
            {
                return WMXBroker_ExtList2_BeginList(channel);
            }
            WMXAPIFUNC EndList(unsigned int channel)
            {
                return WMXBroker_ExtList2_EndList(channel);
            }
            WMXAPIFUNC ExecuteList(unsigned int channel)
            {
                return WMXBroker_ExtList2_ExecuteList(channel);
            }
            WMXAPIFUNC AbortList(unsigned int channel)
            {
                return WMXBroker_ExtList2_AbortList(channel);
            }
            WMXAPIFUNC ClearList(unsigned int channel)
            {
                return WMXBroker_ExtList2_ClearList(channel);
            }
            WMXAPIFUNC GetListStatus(unsigned int channel, WMX_LIST_STATUS *pStatus)
            {
                return WMXBroker_ExtList2_GetListStatus(channel, pStatus);
            }
            // List motion commands (individual parameters)
            WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile,
                                              double target, double velocity, double acc, double dec,
                                              double jerkAccRatio, double jerkDecRatio,
                                              double startingVelocity, double endVelocity,
                                              short axis2, double axis2target, double axis2smoothRatio)
            {
                return WMXBroker_ExtList2_ListJerkCoordinatedPos(channel, axis, static_cast<int>(profile),
                                                                  target, velocity, acc, dec, jerkAccRatio, jerkDecRatio,
                                                                  startingVelocity, endVelocity, axis2, axis2target, axis2smoothRatio);
            }
            // ListJerkPos - individual parameters
            WMXAPIFUNC ListJerkPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile,
                                   double target, double velocity, double acc, double dec,
                                   double jerkAccRatio, double jerkDecRatio,
                                   double startingVelocity, double endVelocity)
            {
                return WMXBroker_ExtList2_ListJerkPos(channel, axis, static_cast<int>(profile),
                                                      target, velocity, acc, dec, jerkAccRatio, jerkDecRatio,
                                                      startingVelocity, endVelocity);
            }
            // ListJerkPos - block version
            WMXAPIFUNC ListJerkPos(unsigned int channel, PosBlockListExt2* mpos_block)
            {
                return WMXBroker_ExtList2_ListJerkPosBlock(channel, mpos_block);
            }
            // ListJerkCoordinatedPos - block version
            WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, CoordinatedPosBlockListExt2* mpos_block)
            {
                return WMXBroker_ExtList2_ListJerkCoordinatedPosBlock(channel, mpos_block);
            }
        };

    } // namespace extList2

    namespace basicVelocity
    {

        // BasicVelocity wrapper class - WMX 1.5 compatible interface
        class BasicVelocity
        {
        public:
            BasicVelocity() {}

            WMXAPIFUNC StopVel(short axis)
            {
                return WMXBroker_BasicVelocity_StopVel(axis);
            }
            WMXAPIFUNC StopVel(short firstAxis, short lastAxis)
            {
                return WMXBroker_BasicVelocity_StopVelRange(firstAxis, lastAxis);
            }
            WMXAPIFUNC QStopVel(short axis)
            {
                return WMXBroker_BasicVelocity_QStopVel(axis);
            }
            WMXAPIFUNC QStopVel(short firstAxis, short lastAxis)
            {
                return WMXBroker_BasicVelocity_QStopVelRange(firstAxis, lastAxis);
            }
            WMXAPIFUNC TimedStopVel(short axis, double timeMilliseconds)
            {
                return WMXBroker_BasicVelocity_TimedStopVel(axis, timeMilliseconds);
            }
            WMXAPIFUNC TimedStopVel(short firstAxis, short lastAxis, double timeMilliseconds)
            {
                return WMXBroker_BasicVelocity_TimedStopVelRange(firstAxis, lastAxis, timeMilliseconds);
            }
            WMXAPIFUNC StartVel(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, double dec)
            {
                return WMXBroker_BasicVelocity_StartVel(axis, static_cast<int>(profile), velocity, acc, dec);
            }
        };

    } // namespace basicVelocity

    namespace extVelocity2
    {

        // ExtVelocity2 wrapper class - Jerk ratio based velocity
        class ExtVelocity2
        {
        public:
            ExtVelocity2() {}

            WMXAPIFUNC StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity,
                                    double acc, double dec, double jerkAccRatio, double jerkDecRatio)
            {
                return WMXBroker_ExtVelocity2_StartJerkVel(axis, static_cast<int>(profile),
                                                           velocity, acc, dec, jerkAccRatio, jerkDecRatio);
            }
            WMXAPIFUNC StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity,
                                    double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity)
            {
                return WMXBroker_ExtVelocity2_StartJerkVelWithStarting(axis, static_cast<int>(profile),
                                                                       velocity, acc, dec, jerkAccRatio, jerkDecRatio, startingVelocity);
            }
            WMXAPIFUNC OverrideVel(short axis, double velocity, double acc, double dec)
            {
                return WMXBroker_ExtVelocity2_OverrideVel(axis, velocity, acc, dec);
            }
        };

    } // namespace extVelocity2

    namespace torque
    {

        // TorqueControl wrapper class - WMX 1.5 compatible interface
        class TorqueControl
        {
        public:
            TorqueControl() {}

            WMXAPIFUNC GetMaxTrqLimit(short axis, double *pTorque)
            {
                return WMXBroker_TorqueControl_GetMaxTrqLimit(axis, pTorque);
            }
            WMXAPIFUNC SetMaxTrqLimit(short axis, double torque)
            {
                return WMXBroker_TorqueControl_SetMaxTrqLimit(axis, torque);
            }
            WMXAPIFUNC GetPositiveTrqLimit(short axis, double *pTorque)
            {
                return WMXBroker_TorqueControl_GetPositiveTrqLimit(axis, pTorque);
            }
            WMXAPIFUNC SetPositiveTrqLimit(short axis, double torque)
            {
                return WMXBroker_TorqueControl_SetPositiveTrqLimit(axis, torque);
            }
            WMXAPIFUNC GetNegativeTrqLimit(short axis, double *pTorque)
            {
                return WMXBroker_TorqueControl_GetNegativeTrqLimit(axis, pTorque);
            }
            WMXAPIFUNC SetNegativeTrqLimit(short axis, double torque)
            {
                return WMXBroker_TorqueControl_SetNegativeTrqLimit(axis, torque);
            }
            WMXAPIFUNC StartTrq(short axis, double torque)
            {
                return WMXBroker_TorqueControl_StartTrq(axis, torque);
            }
            WMXAPIFUNC StartTrq(short axis, double torque, double maxMotorSpeed)
            {
                return WMXBroker_TorqueControl_StartTrqWithMaxSpeed(axis, torque, maxMotorSpeed);
            }
            WMXAPIFUNC StopTrq(short axis)
            {
                return WMXBroker_TorqueControl_StopTrq(axis);
            }
            WMXAPIFUNC StopTrq(short firstAxis, short lastAxis)
            {
                return WMXBroker_TorqueControl_StopTrqRange(firstAxis, lastAxis);
            }
            WMXAPIFUNC StartRampTimeTrq(short axis, double torque, unsigned int rampCycleTime)
            {
                return WMXBroker_TorqueControl_StartRampTimeTrq(axis, torque, rampCycleTime);
            }
            WMXAPIFUNC StartRampRateTrq(short axis, double torque, double rampRate)
            {
                return WMXBroker_TorqueControl_StartRampRateTrq(axis, torque, rampRate);
            }
        };

    } // namespace torque

    // WMXLIB wrapper class - WMX 1.5 compatible interface
    class WMXLIB
    {
    public:
        common::Io *io;
        common::AxisControl *axisControl;
        common::Config *config;
        common::Home *home;
        basicMotion::BasicMotion *basicMotion;
        extMotion1::ExtMotion1 *extMotion1;
        extMotion2::ExtMotion2 *extMotion2;
        basicVelocity::BasicVelocity *basicVelocity;
        extVelocity2::ExtVelocity2 *extVelocity2;
        torque::TorqueControl *torqueControl;
        extList2::ExtList2 *extList2;

        WMXLIB()
        {
            // Initialize DLL internal g_wmxlib singleton
            WMXBroker_Initialize();

            io = new common::Io(this);
            axisControl = new common::AxisControl();
            config = new common::Config();
            home = new common::Home();
            basicMotion = new basicMotion::BasicMotion();
            extMotion1 = new extMotion1::ExtMotion1();
            extMotion2 = new extMotion2::ExtMotion2();
            basicVelocity = new basicVelocity::BasicVelocity();
            extVelocity2 = new extVelocity2::ExtVelocity2();
            torqueControl = new torque::TorqueControl();
            extList2 = new extList2::ExtList2();
        }

        ~WMXLIB()
        {
            delete io;
            io = NULL;
            delete axisControl;
            axisControl = NULL;
            delete config;
            config = NULL;
            delete home;
            home = NULL;
            delete basicMotion;
            basicMotion = NULL;
            delete extMotion1;
            extMotion1 = NULL;
            delete extMotion2;
            extMotion2 = NULL;
            delete basicVelocity;
            basicVelocity = NULL;
            delete extVelocity2;
            extVelocity2 = NULL;
            delete torqueControl;
            torqueControl = NULL;
            delete extList2;
            extList2 = NULL;

            // Uninitialize DLL internal g_wmxlib singleton
            WMXBroker_Uninitialize();
        }

        // System APIs
        WMXAPIFUNC CreateDevice(TCHAR *path, PLTFRM_TYPE type)
        {
            return WMXBroker_CreateDevice(path, static_cast<int>(type));
        }

        WMXAPIFUNC CloseDevice()
        {
            return WMXBroker_CloseDevice();
        }

        WMXAPIFUNC StartCommunication()
        {
            return WMXBroker_StartCommunication();
        }

        WMXAPIFUNC StopCommunication()
        {
            return WMXBroker_StopCommunication();
        }

        WMXAPIFUNC GetStatus(WMX_STATUS *st)
        {
            return WMXBroker_GetStatus(st);
        }

        WMXAPIFUNC GetStatus(WMX_STATUS *st, short axis)
        {
            return WMXBroker_GetStatusAxis(st, axis);
        }

        WMXAPIFUNC GetStatus(WMX_STATUS *st, short firstAxis, short lastAxis)
        {
            return WMXBroker_GetStatusRange(st, firstAxis, lastAxis);
        }

        WMXAPIFUNC GetVersion(double *pCeVersion, double *pPeVersion)
        {
            return WMXBroker_GetVersion(pCeVersion, pPeVersion);
        }

        // Extended System APIs
        WMXAPIFUNC GetLastError()
        {
            return WMXBroker_GetLastError();
        }

        WMXAPIFUNC SetDeviceName(const TCHAR *name)
        {
            return WMXBroker_SetDeviceName(name);
        }

        WMXAPIFUNC GetActiveDeviceList(WMX_ACT_DEV_LIST *list)
        {
            return WMXBroker_GetActiveDeviceList(list);
        }

        WMXAPIFUNC ForceCloseDevice(int id)
        {
            return WMXBroker_ForceCloseDevice(id);
        }
    };

} // namespace wmxAPI

#endif // WMXBROKER_CLIENT_H
