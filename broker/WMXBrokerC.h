// WMXBrokerC.h
// C-style API for VS2012 compatibility
// These functions can be called from any compiler version

#ifndef WMXBROKER_C_H
#define WMXBROKER_C_H

#include <windows.h>
#include <tchar.h>
#include "wmxapi_type.h"

// Forward declare types from WMXBroker.h for C API
// These are defined in WMXBroker.h for DLL internal use
#ifndef WMX_HOME_DATA_DEFINED
#define WMX_HOME_DATA_DEFINED

#ifndef MAX_AXIS
#define MAX_AXIS 64
#endif

typedef struct {
    double distHStoZPulse;
    double distLStoZPulse;
} WMX_AXIS_HOME_DATA;

typedef struct {
    WMX_AXIS_HOME_DATA axesHomeData[MAX_AXIS];
} WMX_HOME_DATA;

#endif // WMX_HOME_DATA_DEFINED

//////////////////////////////////////////////////////////////////////////
// Motion Block Structures for ExtMotion2 and ExtList2
//////////////////////////////////////////////////////////////////////////

#ifndef MAX_ALLAXES
#define MAX_ALLAXES 64
#endif

#ifndef POSBLOCKEXT2_DEFINED
#define POSBLOCKEXT2_DEFINED

// PosBlockExt2 - extMotion2 any profile positioning
typedef struct {
    short axis;
    WMX_PROFILE_TYPE profile;
    double target;
    double velocity;
    double acc;
    double dec;
    double jerkAccRatio;
    double jerkDecRatio;
    double startingVelocity;
    double endVelocity;
} PosBlockExt2Ind, *PPosBlockExt2Ind;
typedef struct {
    short axisCount;
    PosBlockExt2Ind pos_block[MAX_ALLAXES];
} PosBlockExt2, *PPosBlockExt2;

// IntBlockExt2 - extMotion2 any profile simple interpolation
typedef struct {
    short axis;
    double target;
    double velocity;
    double acc;
    double dec;
} IntBlockExt2Ind, *PIntBlockExt2Ind;
typedef struct {
    short axisCount;
    WMX_PROFILE_TYPE profile;
    double compJerkAccRatio;
    double compJerkDecRatio;
    IntBlockExt2Ind pos_block[MAX_ALLAXES];
} IntBlockExt2, *PIntBlockExt2;

// PosBlockListExt2 - extList2 positioning
typedef struct {
    WMX_PROFILE_TYPE profile;
    short axis;
    double target;
    double velocity;
    double acc;
    double dec;
    double jerkAccRatio;
    double jerkDecRatio;
    double startingVelocity;
    double endVelocity;
} PosBlockListExt2Ind, *PPosBlockListExt2Ind;
typedef struct {
    short axisCount;
    PosBlockListExt2Ind pos_block[MAX_ALLAXES];
} PosBlockListExt2, *PPosBlockListExt2;

// CoordinatedPosBlockListExt2 - extList2 coordinated positioning
typedef struct {
    short axis;
    WMX_PROFILE_TYPE profile;
    double target;
    double velocity;
    double acc;
    double dec;
    double jerkAccRatio;
    double jerkDecRatio;
    double startingVelocity;
    double endVelocity;
    short axis2;
    double axis2target;
    double axis2smoothRatio;
} CoordinatedPosBlockListExt2Ind, *PCoordinatedPosBlockListExt2Ind;
typedef struct {
    short axisCount;
    CoordinatedPosBlockListExt2Ind pos_block[MAX_ALLAXES];
} CoordinatedPosBlockListExt2, *PCoordinatedPosBlockListExt2;

#endif // POSBLOCKEXT2_DEFINED

#ifndef COORDINATED_POSBLOCK_EXT2_DEFINED
#define COORDINATED_POSBLOCK_EXT2_DEFINED

// CoordinatedPosBlockExt2 - extMotion2 coordinated positioning
typedef struct {
    short axis;
    WMX_PROFILE_TYPE profile;
    double target;
    double velocity;
    double acc;
    double dec;
    double jerkAccRatio;
    double jerkDecRatio;
    double startingVelocity;
    double endVelocity;
    short axis2;
    double axis2target;
    double axis2smoothRatio;
} CoordinatedPosBlockExt2Ind, *PCoordinatedPosBlockExt2Ind;
typedef struct {
    short axisCount;
    CoordinatedPosBlockExt2Ind pos_block[MAX_ALLAXES];
} CoordinatedPosBlockExt2, *PCoordinatedPosBlockExt2;

#endif // COORDINATED_POSBLOCK_EXT2_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

// DLL Export/Import macros
#ifdef WMXBROKER_EXPORTS
#define WMXBROKER_CAPI __declspec(dllexport)
#else
#define WMXBROKER_CAPI __declspec(dllimport)
#endif

//=============================================================================
// System APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Initialize(void);
WMXBROKER_CAPI long __stdcall WMXBroker_Uninitialize(void);
WMXBROKER_CAPI long __stdcall WMXBroker_CreateDevice(TCHAR* path, int type);
WMXBROKER_CAPI long __stdcall WMXBroker_CloseDevice(void);
WMXBROKER_CAPI long __stdcall WMXBroker_StartCommunication(void);
WMXBROKER_CAPI long __stdcall WMXBroker_StopCommunication(void);
WMXBROKER_CAPI long __stdcall WMXBroker_GetStatus(WMX_STATUS* st);
WMXBROKER_CAPI long __stdcall WMXBroker_GetStatusAxis(WMX_STATUS* st, short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_GetStatusRange(WMX_STATUS* st, short firstAxis, short lastAxis);
WMXBROKER_CAPI long __stdcall WMXBroker_GetVersion(double* pCeVersion, double* pPeVersion);

//=============================================================================
// Extended System APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_GetLastError(void);
WMXBROKER_CAPI long __stdcall WMXBroker_SetDeviceName(const TCHAR* name);
WMXBROKER_CAPI long __stdcall WMXBroker_GetActiveDeviceList(WMX_ACT_DEV_LIST* list);
WMXBROKER_CAPI long __stdcall WMXBroker_ForceCloseDevice(int id);

//=============================================================================
// I/O Output APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutBit(short byte, short bit, unsigned char data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutByte(short offsetByte, unsigned char data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetOutBytes(short offsetByte, short size, unsigned char* data);

//=============================================================================
// I/O Input APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInBit(short byte, short bit, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInByte(short offsetByte, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInBytes(short offsetByte, short size, unsigned char* data);

//=============================================================================
// I/O Output Read APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutBit(short byte, short bit, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutByte(short offsetByte, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetOutBytes(short offsetByte, short size, unsigned char* data);

//=============================================================================
// I/O Initial Output APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutBit(short byte, short bit, unsigned char data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutByte(short offsetByte, unsigned char data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_SetInitialOutBytes(short offsetByte, short size, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutBit(short byte, short bit, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutByte(short offsetByte, unsigned char* data);
WMXBROKER_CAPI long __stdcall WMXBroker_Io_GetInitialOutBytes(short offsetByte, short size, unsigned char* data);

//=============================================================================
// basicMotion APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartPos(short axis, double target, double velocity, double acc, double dec);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartMov(short axis, double target, double velocity, double acc, double dec);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartJog(short axis, double velocity, double acc);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartPosEx(short axis, double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StartMovEx(short axis, double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StopAxis(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_StopAxisSelection(WMX_AXIS_SELECTION* axis_selection);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_QStopAxis(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_QStopAxisSelection(WMX_AXIS_SELECTION* axis_selection);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_TimeStopAxis(int axis, double time);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_TimeStopAxisSelection(WMX_AXIS_SELECTION* axis_selection, double time);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_WaitAxis(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_PauseAxis(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicMotion_ResumeAxis(int axis);

//=============================================================================
// extMotion1 APIs (Jerk - pulse/s^3)
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkPos(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
    double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkMov(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAcc, double jerkDec,
    double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion1_StartJerkJog(short axis, int profile,
    double velocity, double acc, double jerkAcc);

//=============================================================================
// extMotion2 APIs (Jerk Ratio)
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkPos(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkMov(short axis, int profile, double target,
    double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkJog(short axis, int profile,
    double velocity, double acc, double jerkAccRatio);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StopJerkJogAtPos(short axis, int profile, double target,
    double dec, double jerkDecRatio);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkCoordinatedPos(short axis, int profile,
    double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio);

//=============================================================================
// extList2 APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_BeginList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_EndList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ExecuteList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_AbortList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ClearList(unsigned int channel);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_GetListStatus(unsigned int channel, WMX_LIST_STATUS* pStatus);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkCoordinatedPos(unsigned int channel, short axis, int profile,
    double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
    double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio);

//=============================================================================
// AxisControl APIs (common namespace)
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetAxisMode(short axis, int* pMode);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_SetAxisMode(short axis, int mode);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_ServoOn(short axis, int on);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_ServoOnRange(short firstAxis, short lastAxis, int on);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_AmpAlarmClear(short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_AmpAlarmClearRange(short firstAxis, short lastAxis);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_AxisAlarmClear(short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_AxisAlarmClearRange(short firstAxis, short lastAxis);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetPosCommand(short axis, double* pPosition);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetPosFeedback(short axis, double* pPosition);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetVelCommand(short axis, double* pVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_AxisControl_GetVelFeedback(short axis, double* pVelocity);

//=============================================================================
// Home APIs (common namespace)
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Home_StartHome(int axis);
WMXBROKER_CAPI long __stdcall WMXBroker_Home_StartHomeRange(int firstAxis, int lastAxis);
WMXBROKER_CAPI long __stdcall WMXBroker_Home_Continue(short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_Home_Cancel(short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_Home_SetFeedbackPosition(short axis, double position);
WMXBROKER_CAPI long __stdcall WMXBroker_Home_SetCommandPosition(short axis, double position);
WMXBROKER_CAPI long __stdcall WMXBroker_Home_SetCmdPosToFbPos(short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_Home_GetHomeData(WMX_HOME_DATA* pData);

//=============================================================================
// Config APIs (common namespace)
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisHomeParam(short axis, WMX_HOME_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisHomeParam(short axis, WMX_HOME_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisLimitParam(short axis, WMX_LIMIT_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisLimitParam(short axis, WMX_LIMIT_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisSystemParam(short axis, WMX_SYSTEM_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisSystemParam(short axis, WMX_SYSTEM_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisAlarmParam(short axis, WMX_ALARM_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisAlarmParam(short axis, WMX_ALARM_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisMotionParam(short axis, WMX_MOTION_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisMotionParam(short axis, WMX_MOTION_PARAM* pParam);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisSingleTurn(short axis, int* pEnable, unsigned int* pEncoderCount);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisSingleTurn(short axis, int enable, unsigned int encoderCount);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisMultiplier(short axis, unsigned int* pMultiplier);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisMultiplier(short axis, unsigned int multiplier);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_GetAxisVelocityFeedforwardGain(short axis, double* pGain);
WMXBROKER_CAPI long __stdcall WMXBroker_Config_SetAxisVelocityFeedforwardGain(short axis, double gain);

//=============================================================================
// BasicVelocity APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_StopVel(short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_StopVelRange(short firstAxis, short lastAxis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_QStopVel(short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_QStopVelRange(short firstAxis, short lastAxis);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_TimedStopVel(short axis, double timeMilliseconds);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_TimedStopVelRange(short firstAxis, short lastAxis, double timeMilliseconds);
WMXBROKER_CAPI long __stdcall WMXBroker_BasicVelocity_StartVel(short axis, int profile, double velocity, double acc, double dec);

//=============================================================================
// ExtVelocity2 APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtVelocity2_StartJerkVel(short axis, int profile, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtVelocity2_StartJerkVelWithStarting(short axis, int profile, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtVelocity2_OverrideVel(short axis, double velocity, double acc, double dec);

//=============================================================================
// TorqueControl APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_GetMaxTrqLimit(short axis, double* pTorque);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_SetMaxTrqLimit(short axis, double torque);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_GetPositiveTrqLimit(short axis, double* pTorque);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_SetPositiveTrqLimit(short axis, double torque);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_GetNegativeTrqLimit(short axis, double* pTorque);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_SetNegativeTrqLimit(short axis, double torque);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StartTrq(short axis, double torque);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StartTrqWithMaxSpeed(short axis, double torque, double maxMotorSpeed);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StopTrq(short axis);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StopTrqRange(short firstAxis, short lastAxis);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StartRampTimeTrq(short axis, double torque, unsigned int rampCycleTime);
WMXBROKER_CAPI long __stdcall WMXBroker_TorqueControl_StartRampRateTrq(short axis, double torque, double rampRate);

//=============================================================================
// ExtMotion2 Block APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkPosBlock(PosBlockExt2* mpos_block);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkCoordinatedPosBlock(CoordinatedPosBlockExt2* mpos_block);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtMotion2_StartJerkLinIntPos(IntBlockExt2* mpos_block);

//=============================================================================
// ExtList2 ListJerkPos APIs
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkPos(unsigned int channel, short axis, int profile,
    double target, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkPosBlock(unsigned int channel, PosBlockListExt2* mpos_block);
WMXBROKER_CAPI long __stdcall WMXBroker_ExtList2_ListJerkCoordinatedPosBlock(unsigned int channel, CoordinatedPosBlockListExt2* mpos_block);

//=============================================================================
// Home AxisSelection API
//=============================================================================
WMXBROKER_CAPI long __stdcall WMXBroker_Home_StartHomeAxisSelection(WMX_AXIS_SELECTION* axis_selection);

#ifdef __cplusplus
}
#endif

#endif // WMXBROKER_C_H
