// WMX3BrokerC.h
// WMX3 Native API C-style interface for VS2012 compatibility
// These functions provide WMX3 API through WMXBroker DLL
//
// Usage:
//   Link with WMXBroker.lib
//   Include WMX3Api_Sim.h for C++ wrapper

#ifndef WMX3_BROKER_C_H
#define WMX3_BROKER_C_H

#include <windows.h>
#include <tchar.h>

#ifdef __cplusplus
extern "C" {
#endif

// DLL Export/Import macros
#ifdef WMXBROKER_EXPORTS
#define WMX3BROKER_CAPI __declspec(dllexport)
#else
#define WMX3BROKER_CAPI __declspec(dllimport)
#endif

//=============================================================================
// Constants
//=============================================================================
#ifndef WMX3_MAX_AXES
#define WMX3_MAX_AXES 128
#endif

//=============================================================================
// Initialization APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_Initialize(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Uninitialize(void);

//=============================================================================
// WMX3Api System APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetIMDllVersion(int* pVersion, int* pRevision);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetEngineStatus(void* pStatus);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CreateDevice(const char* path, int deviceType);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CreateDeviceW(const wchar_t* path, int deviceType);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CloseDevice(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_StartCommunication(unsigned int waitTimeMilliseconds);
WMX3BROKER_CAPI long __stdcall WMX3Broker_StopCommunication(unsigned int waitTimeMilliseconds);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetDeviceID(int* pId);
WMX3BROKER_CAPI long __stdcall WMX3Broker_SetDeviceName(const char* name);
WMX3BROKER_CAPI long __stdcall WMX3Broker_SetDeviceNameW(const wchar_t* name);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetAllDevices(void* pDevices);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetAllDevicesW(void* pDevices);

//=============================================================================
// CoreMotion Status APIs
//=============================================================================
// Note: pStatus should point to wmx3Api::CoreMotionStatus structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_CoreMotion_GetStatus(void* pStatus);

//=============================================================================
// CoreMotion::AxisControl APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_SetServoOn(int axis, int newStatus);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_ClearAmpAlarm(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_ClearAxisAlarm(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_SetAxisCommandMode(int axis, int mode);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_GetAxisCommandMode(int axis, int* pMode);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_GetPosCommand(int axis, double* pPosition);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_GetPosFeedback(int axis, double* pPosition);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_GetVelCommand(int axis, double* pVelocity);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AxisControl_GetVelFeedback(int axis, double* pVelocity);

//=============================================================================
// CoreMotion::Motion APIs
//=============================================================================
// StartPos - absolute position command
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_StartPos(int axis, double target,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity);

// StartMov - relative position command
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_StartMov(int axis, double target,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity);

// StartJog - continuous motion
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_StartJog(int axis,
    int profileType, double velocity, double acc, double jerkAccRatio);

// Stop commands
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_Stop(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_ExecQuickStop(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_ExecTimedStop(int axis, double timeMilliseconds);

// Wait/Pause/Resume
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_Wait(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_Pause(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_Resume(int axis);

// Linear Interpolation
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_StartLinearIntplPos(
    int axisCount, int* axes, double* targets,
    double* maxVelocities, double* maxAccs, double* maxDecs,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity);

//=============================================================================
// CoreMotion::Home APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_Home_StartHome(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Home_Continue(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Home_Cancel(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Home_SetCommandPos(int axis, double position);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Home_SetFeedbackPos(int axis, double position);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Home_SetCommandPosToFeedbackPos(int axis, double posChangePerCycle);
// Note: pHomeData should point to wmx3Api::Home::HomeData structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Home_GetHomeData(void* pHomeData);

//=============================================================================
// CoreMotion::Velocity APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_Velocity_StartVel(int axis,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Velocity_Stop(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Velocity_ExecQuickStop(int axis);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Velocity_ExecTimedStop(int axis, double timeMilliseconds);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Velocity_OverrideVel(int axis,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio);

//=============================================================================
// CoreMotion::Torque APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_SetMaxTrqLimit(int axis, double torque);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_GetMaxTrqLimit(int axis, double* pTorque);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_SetPositiveTrqLimit(int axis, double torque);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_GetPositiveTrqLimit(int axis, double* pTorque);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_SetNegativeTrqLimit(int axis, double torque);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_GetNegativeTrqLimit(int axis, double* pTorque);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_StartTrq(int axis, double torque);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_StartTrqWithMaxSpeed(int axis, double torque, double maxMotorSpeed);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Torque_StopTrq(int axis);

//=============================================================================
// CoreMotion::Config APIs
//=============================================================================
// Note: pParam should point to appropriate wmx3Api::Config::XXXParam structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetHomeParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetHomeParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetFeedbackParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetFeedbackParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetLimitParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetLimitParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetMotionParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetMotionParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetAlarmParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetAlarmParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetGearRatio(int axis, double numerator, double denominator);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetGearRatio(int axis, double* pNumerator, double* pDenominator);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetSingleTurn(int axis, int enable, unsigned int encoderCount);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetSingleTurn(int axis, int* pEnable, unsigned int* pEncoderCount);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetVelocityFeedforwardGain(int axis, double gain);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetVelocityFeedforwardGain(int axis, double* pGain);

//=============================================================================
// Io APIs
//=============================================================================
// Digital Output
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_SetOutBit(int addr, int bit, unsigned char data);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_SetOutByte(int addr, unsigned char data);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_SetOutBytes(int addr, int size, unsigned char* pData);

// Digital Input
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInBit(int addr, int bit, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInByte(int addr, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInBytes(int addr, int size, unsigned char* pData);

// Digital Output Read
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetOutBit(int addr, int bit, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetOutByte(int addr, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetOutBytes(int addr, int size, unsigned char* pData);

// Analog I/O
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_SetOutAnalogDataShort(int addr, short analogData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInAnalogDataShort(int addr, short* pAnalogData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_SetOutAnalogDataInt(int addr, int analogData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInAnalogDataInt(int addr, int* pAnalogData);

// Ex APIs (Extended)
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInBytesEx(int addr, int size, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetOutBytesEx(int addr, int size, unsigned char* pData);

//=============================================================================
// Ecat APIs
//=============================================================================
// ErrorToString
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);
// Note: pMaster should point to wmx3Api::ecApi::EcMasterInfo structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_GetMasterInfo(void* pMaster);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_ScanNetwork(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_StartHotconnect(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_ChangeSlaveState(int slaveId, int state, int* pErrorCode);

// SDO Communication
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SdoDownload(int slaveId, int index, int subindex,
    int sdoDataSize, unsigned char* sdoData, unsigned int* errCode, unsigned int waitTime);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SdoUpload(int slaveId, int index, int subindex,
    int sdoBuffSize, unsigned char* sdoBuff, unsigned int* actualSize, unsigned int* errCode, unsigned int waitTime);

// Register Read/Write
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_RegisterWrite(int slaveId, int regAddr, int len, unsigned char* data);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_RegisterRead(int slaveId, int regAddr, int len, unsigned char* buff);

// PDO Read/Write
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_TxPdoWrite(int slaveId, int index, int subindex,
    int pdoDataSize, unsigned char* pdoData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_PdoRead(int slaveId, int index, int subindex,
    int pdoBuffSize, unsigned char* pdoBuff, unsigned int* actualSize);

// Slave I/O
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SetOutputBit(int slaveId, int byte, int bit, unsigned char data);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SetOutputByte(int slaveId, int byte, unsigned char data);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SetOutputBytes(int slaveId, int byte, int size, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_GetInputBit(int slaveId, int byte, int bit, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_GetInputByte(int slaveId, int byte, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_GetInputBytes(int slaveId, int byte, int size, unsigned char* pData);

//=============================================================================
// EventControl APIs
//=============================================================================
// Event Management
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_EnableEvent(int id, unsigned char enable);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_RemoveEvent(int id);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_ClearAllEvent(void);
// Note: pEventIdData should point to wmx3Api::AllEventID structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_GetAllEventID(void* pEventIdData,
    int filterInputModuleId, int filterOutputModuleId);

// Software Touch Probe
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_SetSoftwareTouchProbe(unsigned int channel,
    unsigned char enable, int axis, int byteAddrs, int bitOffset, unsigned char logic, int mode);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_EnableSoftwareTouchProbe(unsigned int channel,
    unsigned char enable);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_GetSoftwareTouchProbe(unsigned int channel,
    unsigned char* pEnabled, int* pAxis, int* pByteAddrs, int* pBitOffset,
    unsigned char* pLogic, int* pMode);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_IsSoftwareTouchProbeLatched(unsigned int channel,
    unsigned char* pLatched);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_GetSoftwareTouchProbeCounterValue(unsigned int channel,
    unsigned char* pLatched, double* pCounterValue);

// Hardware Touch Probe
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_SetHardwareTouchProbe(int axis, unsigned char enable,
    int mode, int triggerSource, unsigned int channel);
// Note: pStatus should point to wmx3Api::EventControl::HardwareTouchProbeStatus structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_GetHardwareTouchProbeStatus(int axis, void* pStatus);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_EnableHardwareTouchProbe(int axis, unsigned char enable);

#ifdef __cplusplus
}
#endif

#endif // WMX3_BROKER_C_H
