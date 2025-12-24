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
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetLibVersion(int* pMajorVersion, int* pMinorVersion, int* pRevisionVersion, int* pFixVersion);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetIMDllVersion(int* pVersion, int* pRevision);
WMX3BROKER_CAPI long __stdcall WMX3Broker_WMX3Api_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_WMX3Api_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetEngineStatus(void* pStatus);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CreateDevice(const char* path, int deviceType);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CreateDeviceW(const wchar_t* path, int deviceType);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CloseDevice(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_StartCommunication(unsigned int waitTimeMilliseconds);
WMX3BROKER_CAPI long __stdcall WMX3Broker_StopCommunication(unsigned int waitTimeMilliseconds);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetDeviceID(int* pId);
WMX3BROKER_CAPI long __stdcall WMX3Broker_SetDeviceName(const char* name);
WMX3BROKER_CAPI long __stdcall WMX3Broker_SetDeviceNameW(const wchar_t* name);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetDeviceName(char* nameBuf, unsigned int bufSize);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetDeviceNameW(wchar_t* nameBuf, unsigned int bufSize);
WMX3BROKER_CAPI long __stdcall WMX3Broker_SetWatchdog(unsigned int watchdog);
WMX3BROKER_CAPI long __stdcall WMX3Broker_SetWatchdogEx(int deviceId, unsigned int watchdog);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetAllDevices(void* pDevices);
WMX3BROKER_CAPI long __stdcall WMX3Broker_GetAllDevicesW(void* pDevices);
WMX3BROKER_CAPI int __stdcall WMX3Broker_WMX3Api_IsDeviceValid(void);

//=============================================================================
// CoreMotion Status APIs
//=============================================================================
// Note: pStatus should point to wmx3Api::CoreMotionStatus structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_CoreMotion_GetStatus(void* pStatus);
WMX3BROKER_CAPI int __stdcall WMX3Broker_CoreMotion_IsDeviceValid(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CoreMotion_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CoreMotion_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);

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

// StopJogAtPos
WMX3BROKER_CAPI long __stdcall WMX3Broker_Motion_StopJogAtPos(int axis, double target,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio);

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
WMX3BROKER_CAPI long __stdcall WMX3Broker_Home_SetHomeDone(int axis, unsigned char value);

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
// Note: pParam should point to wmx3Api::Config::AxisParam structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetAxisParam(int axis, void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetAxisParam(int axis, void* pParam, void* pParamError);
// Axis-independent AxisParam APIs (no axis parameter)
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetAxisParamNoAxis(void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetAxisParamNoAxis(void* pParam, void* pParamError);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetAxisUnit(int axis, double unit);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetAxisUnit(int axis, double* pUnit);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetAbsoluteEncoderHomeOffset(int axis, double offset);

// SystemParam/AxisParam APIs
// Note: pParam should point to wmx3Api::Config::SystemParam structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetParam(void* pParam, void* pParamError);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetDefaultParam(void* pParam);
// Note: pAxisParam should point to wmx3Api::Config::AxisParam structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetDefaultAxisParam(void* pAxisParam);
// Note: pParam should point to wmx3Api::Config::EmergencyStopParam structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_SetEmergencyStopParam(void* pParam);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Config_GetEmergencyStopParam(void* pParam);

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
WMX3BROKER_CAPI int __stdcall WMX3Broker_Io_IsDeviceValid(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_SetOutByteEx(int addr, unsigned char data);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_SetOutBytesEx(int addr, int size, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInBitEx(int addr, int bit, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInBytesEx(int addr, int size, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetOutBytesEx(int addr, int size, unsigned char* pData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_SetOutBitEx(int addr, int bit, unsigned char data);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Io_GetInByteEx(int addr, unsigned char* pData);

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
WMX3BROKER_CAPI int __stdcall WMX3Broker_Ecat_IsDeviceValid(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_ResetTransmitStatisticsInfo(void);

// SDO Communication
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SdoDownload(int slaveId, int index, int subindex,
    int sdoDataSize, unsigned char* sdoData, unsigned int* errCode, unsigned int waitTime);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SdoUpload(int slaveId, int index, int subindex,
    int sdoBuffSize, unsigned char* sdoBuff, unsigned int* actualSize, unsigned int* errCode, unsigned int waitTime);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SdoUploadWithType(int slaveId, int index, int subindex,
    int sdoType, int sdoBuffSize, unsigned char* sdoBuff, unsigned int* actualSize,
    unsigned int* errCode, unsigned int waitTime);

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

// SII (Slave Information Interface) Read/Write
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SIIWrite(int slaveId, int siiAddr, int len, unsigned char* data, int checkSum);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Ecat_SIIRead(int slaveId, int siiAddr, int len, unsigned char* buff);

//=============================================================================
// EventControl APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_EventControl_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_EventControl_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);
// SetEvent
// Note: pEventInput/pEventOutput should point to SDK EventInput/EventOutput derived classes
// Note: pOption should point to wmx3Api::EventOption structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_SetEvent(int* pId, void* pEventInput,
    void* pEventOutput, void* pOption);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_SetEventWithId(int* pId, void* pEventInput,
    void* pEventOutput, int id, void* pOption);

// Deprecated SetEvent (Event structure based)
// Note: pEventData should point to wmx3Api::EventControl::Event structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_SetEventDeprecated(int* pId, void* pEventData);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Event_SetEventDeprecatedWithId(int* pId, void* pEventData, int id);

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

//=============================================================================
// ApiBuffer APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_GetLibVersion(int* pMajorVersion, int* pMinorVersion, int* pRevisionVersion, int* pFixVersion);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_GetVersion(int* pMajorVersion, int* pMinorVersion, int* pRevisionVersion, int* pFixVersion);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_CreateApiBuffer(unsigned int channel, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_FreeApiBuffer(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_StartRecordBufferChannel(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_EndRecordBufferChannel(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_GetRecordingBufferChannel(int* pChannel, unsigned char* pEnable);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_Execute(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_Halt(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_Clear(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_Rewind(unsigned int channel);
// Note: pStatus should point to wmx3Api::ApiBufferStatus structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_GetStatus(unsigned int channel, void* pStatus);
// Note: pOptions should point to wmx3Api::ApiBufferOptions structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_SetOptions(unsigned int channel, void* pOptions);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_GetOptions(unsigned int channel, void* pOptions);
// Note: pWatch should point to wmx3Api::ApiBufferWatch structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_SetWatch(unsigned int channel, void* pWatch);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_GetWatch(unsigned int channel, void* pWatch);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_Sleep(unsigned int milliseconds);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_Wait(int axis);
// Note: pAxisSelection should point to wmx3Api::AxisSelection structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_WaitAxes(void* pAxisSelection);
// Note: pCondition should point to wmx3Api::ApiBufferCondition structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_WaitCondition(void* pCondition);
// Flow control
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_FlowIf(void* pCondition, void* pWait);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_FlowElseIf(void* pCondition);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_FlowElse(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_ApiBuffer_FlowEndIf(void);
WMX3BROKER_CAPI int __stdcall WMX3Broker_ApiBuffer_IsDeviceValid(void);

//=============================================================================
// Log APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetLibVersion(int* pMajorVersion, int* pMinorVersion, int* pRevisionVersion, int* pFixVersion);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetVersion(int* pMajorVersion, int* pMinorVersion, int* pRevisionVersion, int* pFixVersion);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_StartLog(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_StopLog(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_ResetLog(unsigned int channel);
// Note: pOption should point to wmx3Api::LogChannelOptions structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_SetLogOption(unsigned int channel, void* pOption);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetLogOption(unsigned int channel, void* pOption);
// Note: pPath should point to wmx3Api::LogFilePathA structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_SetLogFilePath(unsigned int channel, void* pPath);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetLogFilePath(unsigned int channel, void* pPath);
// Note: pPath should point to wmx3Api::LogFilePathW structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_SetLogFilePathW(unsigned int channel, void* pPath);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetLogFilePathW(unsigned int channel, void* pPath);
// Note: pStatus should point to wmx3Api::LogStatus structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetLogStatus(unsigned int channel, void* pStatus);
// Note: pStatus should point to wmx3Api::DetailLogStatus structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetDetailLogStatus(unsigned int channel, void* pStatus);

// Memory Log APIs
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_OpenMemoryLogBuffer(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_CloseMemoryLogBuffer(unsigned int channel);
// Note: pAxisSelection should point to wmx3Api::AxisSelection structure
// Note: pOption should point to wmx3Api::MemoryLogOptions structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_SetMemoryLog(unsigned int channel, void* pAxisSelection, void* pOption);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_StartMemoryLog(unsigned int channel);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_StopMemoryLog(unsigned int channel);
// Note: pStatus should point to wmx3Api::MemoryLogStatus structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetMemoryLogStatus(unsigned int channel, void* pStatus);
// Note: pData should point to wmx3Api::MemoryLogData structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetMemoryLogData(unsigned int channel, void* pData);

// Api Log APIs
// Note: pOptions should point to wmx3Api::ApiLogOptions structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_SetApiLog(const char* pPath, void* pOptions, unsigned int buffSize);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_SetApiLogW(const wchar_t* pPath, void* pOptions, unsigned int buffSize);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_StartApiLog(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_StopApiLog(void);
// Note: pStatus should point to wmx3Api::ApiLogStatus structure
WMX3BROKER_CAPI long __stdcall WMX3Broker_Log_GetApiLogStatus(void* pStatus);

//=============================================================================
// CyclicBuffer APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_CyclicBuffer_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_CyclicBuffer_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);

//=============================================================================
// Compensation APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_Compensation_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_Compensation_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);

//=============================================================================
// UserMemory APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_UserMemory_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_UserMemory_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);

//=============================================================================
// PMMotion APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_PMMotion_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_PMMotion_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);

//=============================================================================
// AdvancedMotion APIs
//=============================================================================
WMX3BROKER_CAPI long __stdcall WMX3Broker_AdvancedMotion_ErrorToString(int errCode, char* pString, unsigned int size);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AdvancedMotion_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size);
WMX3BROKER_CAPI int __stdcall WMX3Broker_AdvancedMotion_IsDeviceValid(void);
WMX3BROKER_CAPI int __stdcall WMX3Broker_AdvancedMotion_AdvSync_IsDeviceValid(void);
// Note: pPosCommand should point to wmx3Api::AdvMotion::CoordinatedPosCommand structure
WMX3BROKER_CAPI int __stdcall WMX3Broker_AdvancedMotion_AdvMotion_IsDeviceValid(void);
WMX3BROKER_CAPI long __stdcall WMX3Broker_AdvancedMotion_AdvMotion_StartCoordinatedPos(void* pPosCommand);

#ifdef __cplusplus
}
#endif

#endif // WMX3_BROKER_C_H
