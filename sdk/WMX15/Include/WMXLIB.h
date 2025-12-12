//WMX v0.987718

#ifndef WMXLIBH
#define WMXLIBH

#define WMX_MAJOR_VERSION 0
#define WMX_MINOR_VERSION 987718

#include "wmxapi_type.h"
#include "wmxapi_def.h"

namespace wmxAPI {

	class WMXLIB;//Main class

	namespace common {

		class EventControl {
		public:
			WMXLIB *wmxlib;//Reference to main class
			EventControl(WMXLIB *f) : wmxlib(f) {}

			//Event APIs
			WMXAPIFUNC SetEvent(unsigned int *pId, WMX_EVENT_DATA *pEventData);
			WMXAPIFUNC GetEvent(unsigned int id, WMX_EVENT_DATA *pEventData);
			WMXAPIFUNC EnableEvent(unsigned int id, unsigned char enable);
			WMXAPIFUNC RemoveEvent(unsigned int id);
			WMXAPIFUNC ClearAllEvent();
			WMXAPIFUNC GetAllEventId(WMX_ALL_EVENT_ID_DATA* pEvenIdData);
			WMXAPIFUNC SetMotionEvent1(unsigned int *pId, WMX_MOTION_EXT_EVENT1_DATA *pMotionEventData);
			WMXAPIFUNC SetMotionEvent2(unsigned int *pId, WMX_MOTION_EXT_EVENT2_DATA *pMotionEventData);
			WMXAPIFUNC GetMotionEvent(unsigned int id, WMX_MOTION_EVENT_DATA *pMotionEventData);
			WMXAPIFUNC EnableMotionEvent(unsigned int id, unsigned char enable);
			WMXAPIFUNC RemoveMotionEvent(unsigned int id);
			WMXAPIFUNC ClearAllMotionEvent();
			WMXAPIFUNC GetAllMotionEventId(WMX_ALL_MOTION_EVENT_ID_DATA* pMotionEvenIdData);

			//Touch Probe APIs
			WMXAPIFUNC SetTouchProbe(unsigned int channel, unsigned char enable, short axis, short byteAddrs,
				short bitOffset, unsigned char polarity, unsigned char mode);
			WMXAPIFUNC EnableTouchProbe(unsigned int channel, unsigned char enable);
			WMXAPIFUNC GetTouchProbe(unsigned int channel, unsigned char *pEnabled, short *pAxis,
				short *pByteAddrs, short *pBitOffset, unsigned char *pPolarity, unsigned char *pMode);
			WMXAPIFUNC IsTouchProbeLatched(unsigned int channel, unsigned char *pLatched);
			WMXAPIFUNC GetTouchProbeCounterValue(unsigned int channel, unsigned char *pLatched, 
				double *pCounterValue);
			WMXAPIFUNC SetHardwareTouchProbe(short axis, unsigned char enable, unsigned char mode,
				unsigned char triggerSource);
			WMXAPIFUNC GetHardwareTouchProbeStatus(short axis, WMX_HARDWARE_TOUCH_PROBE_STATUS *pStatus);
			WMXAPIFUNC EnableHardwareTouchProbe(short axis, unsigned char enable);

			//Position Synchronous Output APIs
			WMXAPIFUNC SetPSOConfig(unsigned int channel, WMX_COMP_TYPE type, WMX_COMP_SOURCE *pSource, 
				WMX_IO_ADDRESS *pIoAddrs, unsigned char polarity, int duration);
			WMXAPIFUNC GetPSOConfig(unsigned int channel, WMX_COMP_TYPE *pType, WMX_COMP_SOURCE *pSource,
				WMX_IO_ADDRESS *pIoAddrs, unsigned char *pPolarity, int *pDuration);
			WMXAPIFUNC SetPSOSData(unsigned int channel, double sData);
			WMXAPIFUNC SetPSOMData(unsigned int channel, int count, double *mData);
			WMXAPIFUNC GetPSOData(unsigned int channel, int *pCount, double *mData);
			WMXAPIFUNC GetPSODataCount(unsigned int channel, int *pCount);
			WMXAPIFUNC StartPSO(unsigned int channel);
			WMXAPIFUNC StopPSO(unsigned int channel);
			WMXAPIFUNC GetPSOStatus(unsigned int channel, WMX_PSO_STATUS *pStatus);

			//Planned Velocity Override APIs
			WMXAPIFUNC SetPVelOverrideConfig(unsigned int channel, WMX_COMP_TYPE type, 
				WMX_COMP_SOURCE *pSource, short axis);
			WMXAPIFUNC GetPVelOverrideConfig(unsigned int channel, WMX_COMP_TYPE *pType, 
				WMX_COMP_SOURCE *pSource, short *pAxis);
			WMXAPIFUNC SetPVelOverrideSData(unsigned int channel, WMX_PVELO_DATA sData);
			WMXAPIFUNC SetPVelOverrideMData(unsigned int channel, int count, WMX_PVELO_DATA *mData);
			WMXAPIFUNC GetPVelOverrideData(unsigned int channel, int *pCount, WMX_PVELO_DATA *mData);
			WMXAPIFUNC GetPVelOverrideDataCount(unsigned int channel, int *pCount);
			WMXAPIFUNC StartPVelOverride(unsigned int channel);
			WMXAPIFUNC StopPVelOverride(unsigned int channel);
			WMXAPIFUNC GetPVelOverrideStatus(unsigned int channel, WMX_PVELO_STATUS *pStatus);
		};

		class Log {
		public:
			WMXLIB *wmxlib;//Reference to main class
			Log(WMXLIB *f) : wmxlib(f) {}

			//Log APIs
			WMXAPIFUNC SetLog(unsigned int channel, TCHAR *path, unsigned int sampleTime,
				unsigned int samplePeriod, WMX_AXIS_SELECTION *axisSelection, WMX_LOG_OPTIONS* options,
				unsigned int mode, unsigned int burstWriteLines = 4, unsigned short scale = 9);
			WMXAPIFUNC SetLogHeader(unsigned int channel, char **line, unsigned int numLines);
			WMXAPIFUNC StartLog(unsigned int channel);
			WMXAPIFUNC StopLog(unsigned int channel);
			WMXAPIFUNC GetLogStatus(unsigned int channel, WMX_LOG_STATUS *pStatus);
			WMXAPIFUNC SetApiCallLog(TCHAR *path, unsigned char onlyLogErr = 0);
			WMXAPIFUNC StartApiCallLog();
			WMXAPIFUNC StopApiCallLog();
			WMXAPIFUNC GetApiCallLogStatus(WMX_API_CALL_LOG_STATUS *pStatus);
			WMXAPIFUNC SetIOLog(unsigned int channel, WMX_IO_ADDRESS* inputIOAddress, unsigned int inputSize,
				WMX_IO_ADDRESS* outputIOAddress, unsigned int outputSize);
			WMXAPIFUNC SetIOLogFormat(unsigned int channel, WMX_IO_LOG_FORMAT* inputIOLogFormat, unsigned int inputIOFormatCount, 
				WMX_IO_LOG_FORMAT* outputIOLogFormat, unsigned int outputIOFormatCount);

			WMXAPIFUNC SetMemLog(WMX_AXIS_SELECTION *axisSelection, WMX_MEM_LOG_OPTIONS *option);
			WMXAPIFUNC StartMemLog();
			WMXAPIFUNC StopMemLog();
			WMXAPIFUNC GetMemLogStatus(WMX_MEM_LOG_STATUS *pStatus);
			WMXAPIFUNC GetMemLogData(WMX_MEM_LOG_DATA *pData);

			WMXAPIFUNC SetFlightRecorderPath(TCHAR *path);
		};

		class Io {
		public:
			WMXLIB *wmxlib;//Reference to main class
			Io(WMXLIB *f) : wmxlib(f) {}

			//I/O APIs
			WMXAPIFUNC SetOutBit(short byte, short bit, unsigned char data);
			WMXAPIFUNC SetOutByte(short offsetByte, unsigned char data);
			WMXAPIFUNC SetOutBytes(short offsetByte, short size, unsigned char *data);
			WMXAPIFUNC GetInBit(short byte, short bit, unsigned char *data);
			WMXAPIFUNC GetInByte(short offsetByte, unsigned char *data);
			WMXAPIFUNC GetInBytes(short offsetByte, short size,unsigned char *data);
			WMXAPIFUNC GetOutBit(short byte, short bit, unsigned char *data);
			WMXAPIFUNC GetOutByte(short offsetByte, unsigned char *data);
			WMXAPIFUNC GetOutBytes(short offsetByte, short size, unsigned char *data);

			WMXAPIFUNC SetInitialOutBit(short byte, short bit, unsigned char data);
			WMXAPIFUNC SetInitialOutByte(short offsetByte, unsigned char data);
			WMXAPIFUNC SetInitialOutBytes(short offsetByte, short size, unsigned char *data);
			WMXAPIFUNC GetInitialOutBit(short byte, short bit, unsigned char *data);
			WMXAPIFUNC GetInitialOutByte(short offsetByte, unsigned char *data);
			WMXAPIFUNC GetInitialOutBytes(short offsetByte, short size, unsigned char *data);

			//Auxiliary command and feedback APIs
			WMXAPIFUNC SetAuxOutBit(short axis, short index, short byte, short bit, unsigned char data);
			WMXAPIFUNC SetAuxOutByte(short axis, short index, short byte, unsigned char data);
			WMXAPIFUNC SetAuxOutBytes(short axis, short index, short byte, short size, unsigned char *pData);

			WMXAPIFUNC GetAuxInBit(short axis, short index, short byte, short bit, unsigned char *pData);
			WMXAPIFUNC GetAuxInByte(short axis, short index, short byte, unsigned char *pData);
			WMXAPIFUNC GetAuxInBytes(short axis, short index, short byte, short size, unsigned char *pData);
			WMXAPIFUNC GetAuxInSize(short axis, short index, unsigned int *pSize);
			WMXAPIFUNC GetAuxInName(short axis, short index, short length, char *pName);

			WMXAPIFUNC GetAuxOutBit(short axis, short index, short byte, short bit, unsigned char *pData);
			WMXAPIFUNC GetAuxOutByte(short axis, short index, short byte, unsigned char *pData);
			WMXAPIFUNC GetAuxOutBytes(short axis, short index, short byte, short size, unsigned char *pData);
			WMXAPIFUNC GetAuxOutSize(short axis, short index, unsigned int *pSize);
			WMXAPIFUNC GetAuxOutName(short axis, short index, short length, char *pName);
		};

		class Config {
		public:
			WMXLIB *wmxlib;//Reference to main class
			Config(WMXLIB *f) : wmxlib(f) {}

			//Parameter APIs
			WMXAPIFUNC SetParam(WMX_PARAM *param, WMX_PARAM *paramError = NULL);
			WMXAPIFUNC GetParam(WMX_PARAM *param);
			WMXAPIFUNC SetAxisGearRatio(short axis, unsigned int numerator, unsigned int denominator);
			WMXAPIFUNC SetAxisSingleTurn(short axis, unsigned char enable, unsigned int encoderCount);
			WMXAPIFUNC SetAxisMultiplier(short axis, unsigned int multiplier);
			WMXAPIFUNC SetAxisStopParam(short axis, WMX_STOP_PARAM_MODE mode, double dec, double time,
				WMX_STOP_PARAM_MODE velMode, double velDec, double velTime);
			WMXAPIFUNC SetAxisSpecialParam(short axis, unsigned int fn, unsigned int val);
			WMXAPIFUNC SetAxisEncoderRange(short axis, unsigned char enable, int encoderRangeLow, int encoderRangeHigh);
			WMXAPIFUNC GetAxisGearRatio(short axis, unsigned int *pNumerator, unsigned int *pDenominator);
			WMXAPIFUNC GetAxisSingleTurn(short axis, unsigned char *pEnable, unsigned int *pEncoderCount);
			WMXAPIFUNC GetAxisMultiplier(short axis, unsigned int *pMultiplier);
			WMXAPIFUNC GetAxisStopParam(short axis, WMX_STOP_PARAM_MODE *pMode, double *pDec, double *pTime,
				WMX_STOP_PARAM_MODE *pVelMode, double *pVelDec, double *pVelTime);
			WMXAPIFUNC GetAxisSpecialParam(short axis, unsigned int fn, unsigned int *pVal);
			WMXAPIFUNC GetAxisEncoderRange(short axis, unsigned char *pEnable, int *pEncoderRangeLow, int *pEncoderRangeHigh);
			WMXAPIFUNC SetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM *param, WMX_FEEDBACK_PARAM *paramError = NULL);
			WMXAPIFUNC SetAxisHomeParam(short axis, WMX_HOME_PARAM *param, WMX_HOME_PARAM *paramError = NULL);
			WMXAPIFUNC SetAxisLimitParam(short axis, WMX_LIMIT_PARAM *param, WMX_LIMIT_PARAM *paramError = NULL);
			WMXAPIFUNC SetAxisMotionParam(short axis, WMX_MOTION_PARAM *param, WMX_MOTION_PARAM *paramError = NULL);
			WMXAPIFUNC SetAxisAlarmParam(short axis, WMX_ALARM_PARAM *param, WMX_ALARM_PARAM *paramError = NULL);
			WMXAPIFUNC SetAxisSystemParam(short axis, WMX_SYSTEM_PARAM *param, WMX_SYSTEM_PARAM *paramError = NULL);
			WMXAPIFUNC SetAxisSyncParam(short axis, WMX_SYNC_PARAM *param, WMX_SYNC_PARAM *paramError = NULL);
			WMXAPIFUNC SetSystemParam2(WMX_SYSTEM_PARAM_2 *param, WMX_SYSTEM_PARAM_2 *paramError = NULL);
			WMXAPIFUNC GetAxisFeedbackParam(short axis, WMX_FEEDBACK_PARAM *param);
			WMXAPIFUNC GetAxisHomeParam(short axis, WMX_HOME_PARAM *param);
			WMXAPIFUNC GetAxisLimitParam(short axis, WMX_LIMIT_PARAM *param);
			WMXAPIFUNC GetAxisMotionParam(short axis, WMX_MOTION_PARAM *param);
			WMXAPIFUNC GetAxisAlarmParam(short axis, WMX_ALARM_PARAM *param);
			WMXAPIFUNC GetAxisSystemParam(short axis, WMX_SYSTEM_PARAM *param);
			WMXAPIFUNC GetAxisSyncParam(short axis, WMX_SYNC_PARAM *param);
			WMXAPIFUNC GetSystemParam2(WMX_SYSTEM_PARAM_2 *param);
			WMXAPIFUNC GetDefaultParam(WMX_PARAM *param);
			WMXAPIFUNC GetDefaultOtherParam(WMX_OTHER_PARAM *otherParam);
			WMXAPIFUNC ExportParam(TCHAR *path, WMX_PARAM *param);
			WMXAPIFUNC ExportParam(TCHAR *path, WMX_PARAM *param, short axis);
			WMXAPIFUNC ExportParam(TCHAR *path, WMX_PARAM *param, WMX_OTHER_PARAM *otherParam);
			WMXAPIFUNC ExportParam(TCHAR *path, WMX_PARAM *param, WMX_OTHER_PARAM *otherParam, short axis);
			WMXAPIFUNC ImportParam(TCHAR *path, WMX_PARAM *param);
			WMXAPIFUNC ImportParam(TCHAR *path, WMX_OTHER_PARAM *otherParam);
			WMXAPIFUNC ImportParam(TCHAR *path, WMX_PARAM *param, WMX_OTHER_PARAM *otherParam);
			WMXAPIFUNC GetAndExportAllParam(TCHAR *path);
			WMXAPIFUNC ImportAndSetAllParam(TCHAR *path, WMX_PARAM *paramError = NULL, WMX_OTHER_PARAM *otherParamError = NULL,
				unsigned char startCommunication = 0);
		};

		class AxisControl {
		public:
			WMXLIB *wmxlib;//Reference to main class
			AxisControl(WMXLIB *f) : wmxlib(f) {}

			//Axis Control APIs
			WMXAPIFUNC ServoOn(int axis, int newStatus);
			WMXAPIFUNC AmpAlarmClear(short axis);
			WMXAPIFUNC AxisAlarmClear(short axis);
			WMXAPIFUNC SetAxisMode(short axis, WMX_AXIS_COMMAND_MODE mode);
			WMXAPIFUNC GetAxisMode(short axis, WMX_AXIS_COMMAND_MODE *pMode);
			WMXAPIFUNC GetAxisPosCmd(short axis, double *pPosition);
			WMXAPIFUNC GetAxisPosFb(short axis, double *pPosition);
			WMXAPIFUNC GetAxisVelCmd(short axis, double *pVelocity);
			WMXAPIFUNC GetAxisVelFb(short axis, double *pVelocity);

			//Direct Control APIs
			WMXAPIFUNC StartDirectControl(int axis);
			WMXAPIFUNC StartDirectControl(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC StopDirectControl(int axis);
			WMXAPIFUNC StopDirectControl(WMX_AXIS_SELECTION *axis_selection);
		};

		class Sync {
		public:
			WMXLIB *wmxlib;//Reference to main class
			Sync(WMXLIB *f) : wmxlib(f) {}

			//Sync APIs
			WMXAPIFUNC SetSyncMasterSlave(short masterAxis, short slaveAxis);
			WMXAPIFUNC ResolveSync(short axis);
			WMXAPIFUNC SetSyncGroup(int groupId, WMX_SYNC_GROUP syncGroup);
			WMXAPIFUNC GetSyncGroup(int groupId, WMX_SYNC_GROUP *pSyncGroup);
			WMXAPIFUNC AddAxisToSyncGroup(int groupId, int axis, unsigned char isMaster);
			WMXAPIFUNC RemoveAxisFromSyncGroup(int groupId, int axis);
			WMXAPIFUNC SetSyncGroupEnabled(int groupId, unsigned char enable);
			WMXAPIFUNC GetSyncGroupStatus(int groupId, WMX_SYNC_GROUP_STATUS *pStatus);
		};

		class Home {
		public:
			WMXLIB *wmxlib;//Reference to main class
			Home(WMXLIB *f) : wmxlib(f) {}
			
			//Homing APIs
			WMXAPIFUNC StartHome(int axis);
			WMXAPIFUNC StartHome(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC StartHome2(int axis);
			WMXAPIFUNC StartHome2(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC ContinueHome(int axis);
			WMXAPIFUNC ContinueHome(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC CancelHome(int axis);
			WMXAPIFUNC CancelHome(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC SetCommandPosition(short axis, double position);
			WMXAPIFUNC SetFeedbackPosition(short axis, double position);
			WMXAPIFUNC SetHomeDone(short axis, unsigned char value);
			WMXAPIFUNC SetCmdPosToFbPos(short axis);
		};
	
		class Compensation{
		public:
			WMXLIB *wmxlib;
			Compensation(WMXLIB* f):wmxlib(f){}

			WMXAPIFUNC SetPitchErrComp(short axis, WMX_PITCH_ERROR_COMPENSATION_DATA* pitchErrCompData);
			WMXAPIFUNC GetPitchErrComp(short axis, WMX_PITCH_ERROR_COMPENSATION_DATA* pitchErrCompData);
			WMXAPIFUNC EnablePitchErrComp(short axis);
			WMXAPIFUNC DisablePitchErrComp(short axis);

			WMXAPIFUNC Set2DPitchErrComp(unsigned int channel, WMX_2D_PITCH_ERROR_COMPENSATION_DATA* pitchErrCompData2D);
			WMXAPIFUNC Get2DPitchErrComp(unsigned int channel, WMX_2D_PITCH_ERROR_COMPENSATION_DATA* pitchErrCompData2D);
			WMXAPIFUNC Enable2DPitchErrComp(unsigned int channel);
			WMXAPIFUNC Disable2DPitchErrComp(unsigned int channel);

		};
	}

	namespace basicMotion {

		//MPos block for Trapezoidal profile positioning
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
		}PosBlockInd, *PPosBlockInd;
		typedef struct {
			short axisCount;
			PosBlockInd pos_block[MAX_ALLAXES];
		}PosBlock, *PPosBlock;

		//MPos block for Trapezoidal profile triggered positioning
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			WMX_TRIGGER_TYPE triggerType;
			short triggerAxis;
			double triggerValue;
		}TriggeredPosBlockInd, *PTriggeredPosBlockInd;
		typedef struct {
			short axisCount;
			TriggeredPosBlockInd pos_block[MAX_ALLAXES];
		}TriggeredPosBlock, *PTriggeredPosBlock;
			
		//MPos block for Trapezoidal profile acceleration time positioning
		typedef struct {
			short axis;
			double target;
			double velocity;
			double accTime;
			double decTime;
			double startingVelocity;
			double endVelocity;
		}TimedAccPosBlockInd, *PTimedAccPosBlockInd;
		typedef struct {
			short axisCount;
			TimedAccPosBlockInd pos_block[MAX_ALLAXES];
		}TimedAccPosBlock, *PTimedAccPosBlock;

		//MPos block for Trapezoidal profile simple interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlockInd, *PIntBlockInd;
		typedef struct {
			short axisCount;
			IntBlockInd pos_block[MAX_ALLAXES];
		}IntBlock, *PIntBlock;

		//MPos block for Trapezoidal profile composite vector interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlock2Ind, *PIntBlock2Ind;
		typedef struct {
			short axisCount;
			double compVelocity;
			double compAcc;
			double compDec;
			double compStartingVelocity;
			double compEndVelocity;
			double compMinimumVelocity;
			IntBlock2Ind pos_block[MAX_ALLAXES];
		}IntBlock2, *PIntBlock2;

		//MPos block for Trapezoidal profile arc abs circular interpolation
		typedef struct {
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcAbsCirIntBlock, *PArcAbsCirIntBlock;

		//MPos block for Trapezoidal profile arc offset circular interpolation
		typedef struct {
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcOffsetCirIntBlock, *PArcOffsetCirIntBlock;

		//MPos block for Trapezoidal profile abs pos abs circular interpolation
		typedef struct {
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}AbsPosAbsCirIntBlock, *PAbsPosAbsCirIntBlock;

		//MPos block for Trapezoidal profile rel pos offset circular interpolation
		typedef struct {
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}RelPosOffsetCirIntBlock, *PRelPosOffsetCirIntBlock;

		//MPos block for Trapezoidal profile two-velocity positioning
		typedef struct {
			short axis;
			double target;
			double velocity;
			double secondVelocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
		}TwoVPosBlockInd, *PTwoVPosBlockInd;
		typedef struct {
			short axisCount;
			TwoVPosBlockInd pos_block[MAX_ALLAXES];
		}TwoVPosBlock, *PTwoVPosBlock;

		//MPos block for Trapezoidal profile jog
		typedef struct {
			short axis;
			double velocity;
			double acc;
		}JogBlockInd, *PJogBlockInd;
		typedef struct {
			short axisCount;
			JogBlockInd pos_block[MAX_ALLAXES];
		}JogBlock, *PJogBlock;

		//MPos block for Time Stop
		typedef struct {
			short axis;
			double time;
		}TimeStopInd, *PTimeStopInd;
		typedef struct {
			short axisCount;
			TimeStopInd pos_block[MAX_ALLAXES];
		}TimeStopBlock, *PTimeStopBlock;
		
		//MPos block for Trapezoidal profile acceleration time jog
		typedef struct {
			short axis;
			double velocity;
			double accTime;
		}TimedAccJogBlockInd, *PTimedAccJogBlockInd;
		typedef struct {
			short axisCount;
			TimedAccJogBlockInd pos_block[MAX_ALLAXES];
		}TimedAccJogBlock, *PTimedAccJogBlock;

		//MPos block for Trapezoidal profile timed jog
		typedef struct {
			short axis;
			double velocity;
			double runTime;
			double accTime;
			double decTime;
		}TimedJogBlockInd, *PTimedJogBlockInd;
		typedef struct {
			short axisCount;
			TimedJogBlockInd pos_block[MAX_ALLAXES];
		}TimedJogBlock, *PTimedJogBlock;

		//MPos block for Trapezoidal profile positioning using parameter init/end vel
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}PosBlockParamVelInd, *PPosBlockParamVelInd;
		typedef struct {
			short axisCount;
			PosBlockParamVelInd pos_block[MAX_ALLAXES];
		}PosBlockParamVel, *PPosBlockParamVel;
			
		//MPos block for Trapezoidal profile acceleration time positioning using parameter init/end vel
		typedef struct {
			short axis;
			double target;
			double velocity;
			double accTime;
			double decTime;
		}TimedAccPosBlockParamVelInd, *PTimedAccPosBlockParamVelInd;
		typedef struct {
			short axisCount;
			TimedAccPosBlockParamVelInd pos_block[MAX_ALLAXES];
		}TimedAccPosBlockParamVel, *PTimedAccPosBlockParamVel;

		//MPos block for Trapezoidal profile constant deceleration positioning
		typedef struct {
			short axis;
			double target;
			double startingVelocity;
			double endVelocity;
		}ConstDecPosBlockInd, *PConstDecPosBlockInd;
		typedef struct {
			short axisCount;
			ConstDecPosBlockInd pos_block[MAX_ALLAXES];
		}ConstDecPosBlock, *PConstDecPosBlock;

		class BasicMotion {
		public:
			WMXLIB *wmxlib;//Reference to main class
			BasicMotion(WMXLIB *f) : wmxlib(f) {}

			WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec, 
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartPos(PosBlock *mpos_block);
			WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec,
				double startingVelocity, double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartPos(PosBlock *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec);
			WMXAPIFUNC StartPos(PosBlockParamVel *mpos_block);
			WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec, 
				unsigned int waitTime);
			WMXAPIFUNC StartPos(PosBlockParamVel *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec,
				double startingVelocity, double endVelocity, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue); 
			WMXAPIFUNC StartPos(TriggeredPosBlock *mpos_block);
			WMXAPIFUNC StartPos(short axis, double target, double velocity, double acc, double dec, 
				double startingVelocity, double endVelocity, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartPos(TriggeredPosBlock *mpos_block, unsigned int triggerWaitTime);
			WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartMov(PosBlock *mpos_block);
			WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec, 
				double startingVelocity, double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartMov(PosBlock *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec);
			WMXAPIFUNC StartMov(PosBlockParamVel *mpos_block);
			WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec,
				unsigned int waitTime);
			WMXAPIFUNC StartMov(PosBlockParamVel *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec,
				double startingVelocity, double endVelocity, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue); 
			WMXAPIFUNC StartMov(TriggeredPosBlock *mpos_block);
			WMXAPIFUNC StartMov(short axis, double target, double velocity, double acc, double dec, 
				double startingVelocity, double endVelocity, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartMov(TriggeredPosBlock *mpos_block, unsigned int triggerWaitTime);
			WMXAPIFUNC StartLinIntPos(IntBlock *mpos_block);
			WMXAPIFUNC StartLinIntPos(IntBlock2 *mpos_block);
			WMXAPIFUNC StartLinIntPos(IntBlock2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartLinIntPos(IntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartLinIntPos(IntBlock2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartLinIntPos(IntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartLinIntPos(IntBlock2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartLinIntMov(IntBlock *mpos_block);
			WMXAPIFUNC StartLinIntMov(IntBlock2 *mpos_block);
			WMXAPIFUNC StartLinIntMov(IntBlock2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartLinIntMov(IntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartLinIntMov(IntBlock2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartLinIntMov(IntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartLinIntMov(IntBlock2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartCircularInt(ArcAbsCirIntBlock *mpos_block);
			WMXAPIFUNC StartCircularInt(ArcOffsetCirIntBlock *mpos_block);
			WMXAPIFUNC StartCircularInt(AbsPosAbsCirIntBlock *mpos_block);
			WMXAPIFUNC StartCircularInt(RelPosOffsetCirIntBlock *mpos_block);
			WMXAPIFUNC StartCircularInt(ArcAbsCirIntBlock *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartCircularInt(ArcOffsetCirIntBlock *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartCircularInt(AbsPosAbsCirIntBlock *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartCircularInt(RelPosOffsetCirIntBlock *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartCircularInt(ArcAbsCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartCircularInt(ArcOffsetCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartCircularInt(AbsPosAbsCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartCircularInt(RelPosOffsetCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartCircularInt(ArcAbsCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartCircularInt(ArcOffsetCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartCircularInt(AbsPosAbsCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartCircularInt(RelPosOffsetCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC Start2VPos(short axis, double target, double velocity, double secondVelocity, 
				double acc, double dec, double startingVelocity, double endVelocity);
			WMXAPIFUNC Start2VPos(TwoVPosBlock *mpos_block);
			WMXAPIFUNC Start2VMov(short axis, double target, double velocity, double secondVelocity,
				double acc, double dec, double startingVelocity, double endVelocity);
			WMXAPIFUNC Start2VMov(TwoVPosBlock *mpos_block);
			WMXAPIFUNC StartConstDecPos(short axis, double target, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartConstDecPos(ConstDecPosBlock *mpos_block);
			WMXAPIFUNC StartConstDecPos(short axis, double target, double startingVelocity, double endVelocity,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJog(short axis, double velocity, double acc);
			WMXAPIFUNC StartJog(JogBlock *mpos_block);
			WMXAPIFUNC StartTimedAccJog(short axis, double velocity, double accTime);
			WMXAPIFUNC StartTimedAccJog(TimedAccJogBlock *mpos_block);
			WMXAPIFUNC SetPosOverride(short axis, double target);
			WMXAPIFUNC SetPosOverride(PosBlock *mpos_block);
			WMXAPIFUNC SetMovOverride(short axis, double target);
			WMXAPIFUNC SetMovOverride(PosBlock *mpos_block);
			WMXAPIFUNC StartTimedAccPos(short axis, double target, double velocity, double accTime, 
				double decTime, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartTimedAccPos(TimedAccPosBlock *mpos_block);
			WMXAPIFUNC StartTimedAccPos(short axis, double target, double velocity, double accTime, 
				double decTime, double startingVelocity, double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartTimedAccPos(TimedAccPosBlock *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartTimedAccPos(short axis, double target, double velocity, double accTime, 
				double decTime);
			WMXAPIFUNC StartTimedAccPos(TimedAccPosBlockParamVel *mpos_block);
			WMXAPIFUNC StartTimedAccPos(short axis, double target, double velocity, double accTime, 
				double decTime, unsigned int waitTime);
			WMXAPIFUNC StartTimedAccPos(TimedAccPosBlockParamVel *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartTimedAccMov(short axis, double target, double velocity, double accTime,
				double decTime, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartTimedAccMov(TimedAccPosBlock *mpos_block);
			WMXAPIFUNC StartTimedAccMov(short axis, double target, double velocity, double accTime, 
				double decTime, double startingVelocity, double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartTimedAccMov(TimedAccPosBlock *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartTimedAccMov(short axis, double target, double velocity, double accTime, 
				double decTime);
			WMXAPIFUNC StartTimedAccMov(TimedAccPosBlockParamVel *mpos_block);
			WMXAPIFUNC StartTimedAccMov(short axis, double target, double velocity, double accTime, 
				double decTime, unsigned int waitTime);
			WMXAPIFUNC StartTimedAccMov(TimedAccPosBlockParamVel *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartTimedJog(short axis, double velocity, double runTime, double accTime, 
				double decTime);
			WMXAPIFUNC StartTimedJog(TimedJogBlock *mpos_block);
			WMXAPIFUNC StopAxis(int axis);
			WMXAPIFUNC StopAxis(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC QStopAxis(int axis);
			WMXAPIFUNC QStopAxis(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC TimeStopAxis(int axis, double time);
			WMXAPIFUNC TimeStopAxis(WMX_AXIS_SELECTION *axis_selection, double time);
			WMXAPIFUNC TimeStopAxis(TimeStopBlock *mpos_block);
			WMXAPIFUNC WaitAxis(int axis);
			WMXAPIFUNC WaitAxis(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC PauseAxis(int axis);
			WMXAPIFUNC PauseAxis(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC ResumeAxis(int axis);
			WMXAPIFUNC ResumeAxis(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC SetVelOverride(short axis, double velocity);
			WMXAPIFUNC SetVelOverride(PosBlock *mpos_block);
			WMXAPIFUNC SetAccOverride(short axis, double acc);
			WMXAPIFUNC SetAccOverride(PosBlock *mpos_block);
			WMXAPIFUNC SetDecOverride(short axis, double dec);
			WMXAPIFUNC SetDecOverride(PosBlock *mpos_block);
			WMXAPIFUNC SetProfileOverride(short axis, double velocity, double acc, double dec,
				double startingVelocity, double endVelocity, unsigned char overtravelCancel = 0);
			WMXAPIFUNC SetProfileOverride(PosBlock *mpos_block, unsigned char overtravelCancel = 0);
			WMXAPIFUNC StartCSpline(PWMX_SPLINE_BLOCK spline_data);
			WMXAPIFUNC StartCBSpline(PWMX_SPLINE_BLOCK spline_data);
			WMXAPIFUNC StartPVT(PWMX_PVT_BLOCK pvt_data);
			WMXAPIFUNC StartPVT(PWMX_PVT_INTERPOLATE_BLOCK pvt_data);
		};
	}

	namespace extMotion1 { //Pulse/s^3 Jerk

		//MPos block for any profile positioning
		typedef struct {
			short axis;
			WMX_PROFILE_TYPE profile;
			double target;
			double velocity;
			double acc;
			double dec;
			double jerkAcc;
			double jerkDec;
			double startingVelocity;
			double endVelocity;
		}PosBlockExt1Ind, *PPosBlockExt1Ind;
		typedef struct {
			short axisCount;
			PosBlockExt1Ind pos_block[MAX_ALLAXES];
		}PosBlockExt1, *PPosBlockExt1;

		//MPos block for any profile acceleration time positioning
		typedef struct {
			short axis;
			WMX_PROFILE_TYPE profile;
			double target;
			double velocity;
			double accTime;
			double decTime;
			double startingVelocity;
			double endVelocity;
		}TimedAccPosBlockExt1Ind, *PTimedAccPosBlockExt1Ind;
		typedef struct {
			short axisCount;
			TimedAccPosBlockExt1Ind pos_block[MAX_ALLAXES];
		}TimedAccPosBlockExt1, *PTimedAccPosBlockExt1;

		//MPos block for any profile simple interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
			double jerkAcc;
			double jerkDec;
		}IntBlockExt1Ind, *PIntBlockExt1Ind;
		typedef struct {
			short axisCount;
			WMX_PROFILE_TYPE profile;
			IntBlockExt1Ind pos_block[MAX_ALLAXES];
		}IntBlockExt1, *PIntBlockExt1;

		//MPos block for any profile composite vector interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
			double jerkAcc;
			double jerkDec;
		}IntBlock2Ext1Ind, *PIntBlock2Ext1Ind;
		typedef struct {
			short axisCount;
			WMX_PROFILE_TYPE profile;
			double compVelocity;
			double compAcc;
			double compDec;
			double compJerkAcc;
			double compJerkDec;
			double compStartingVelocity;
			double compEndVelocity;
			double compMinimumVelocity;
			IntBlock2Ext1Ind pos_block[MAX_ALLAXES];
		}IntBlock2Ext1, *PIntBlock2Ext1;

		//MPos block for any profile arc abs circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double jerkAcc;
			double jerkDec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcAbsCirIntBlockExt1, *PArcAbsCirIntBlockExt1;

		//MPos block for any profile arc offset circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double jerkAcc;
			double jerkDec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcOffsetCirIntBlockExt1, *PArcOffsetCirIntBlockExt1;

		//MPos block for any profile abs pos abs circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double jerkAcc;
			double jerkDec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}AbsPosAbsCirIntBlockExt1, *PAbsPosAbsCirIntBlockExt1;

		//MPos block for any profile rel pos offset circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double jerkAcc;
			double jerkDec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}RelPosOffsetCirIntBlockExt1, *PRelPosOffsetCirIntBlockExt1;

		//MPos block for any profile jog
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double acc;
			double jerkAcc;
		}JogBlockExt1Ind, *PJogBlockExt1Ind;
		typedef struct {
			short axisCount;
			JogBlockExt1Ind pos_block[MAX_ALLAXES];
		}JogBlockExt1, *PJogBlockExt1;

		//MPos block for any profile acceleration time jog
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double accTime;
		}TimedAccJogBlockExt1Ind, *PTimedAccJogBlockExt1Ind;
		typedef struct {
			short axisCount;
			TimedAccJogBlockExt1Ind pos_block[MAX_ALLAXES];
		}TimedAccJogBlockExt1, *PTimedAccJogBlockExt1;

		//MPos block for any profile timed jog
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double runTime;
			double accTime;
			double decTime;
		}TimedJogBlockExt1Ind, *PTimedJogBlockExt1Ind;
		typedef struct {
			short axisCount;
			TimedJogBlockExt1Ind pos_block[MAX_ALLAXES];
		}TimedJogBlockExt1, *PTimedJogBlockExt1;

		class ExtMotion1 {
		public:
			WMXLIB *wmxlib;//Reference to main class
			ExtMotion1(WMXLIB *f) : wmxlib(f) {}

			WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity, 
				double acc, double dec, double jerkAcc, double jerkDec, double startingVelocity, 
				double endVelocity);
			WMXAPIFUNC StartJerkPos(PosBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity, 
				double acc, double dec, double jerkAcc, double jerkDec, double startingVelocity, 
				double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartJerkPos(PosBlockExt1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target, double velocity, 
				double acc, double dec, double jerkAcc, double jerkDec, double startingVelocity, 
				double endVelocity);
			WMXAPIFUNC StartJerkMov(PosBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAcc, double jerkDec, double startingVelocity, 
				double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartJerkMov(PosBlockExt1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkLinIntPos(IntBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkLinIntPos(IntBlock2Ext1 *mpos_block);
			WMXAPIFUNC StartJerkLinIntPos(IntBlock2Ext1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkLinIntMov(IntBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkLinIntMov(IntBlock2Ext1 *mpos_block);
			WMXAPIFUNC StartJerkLinIntMov(IntBlock2Ext1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkCircularInt(ArcAbsCirIntBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(ArcOffsetCirIntBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(AbsPosAbsCirIntBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(RelPosOffsetCirIntBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(ArcAbsCirIntBlockExt1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkCircularInt(ArcOffsetCirIntBlockExt1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkCircularInt(AbsPosAbsCirIntBlockExt1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkCircularInt(RelPosOffsetCirIntBlockExt1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkJog(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, 
				double jerkAcc);
			WMXAPIFUNC StartJerkJog(JogBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccJog(short axis, WMX_PROFILE_TYPE profile, double velocity, 
				double accTime);
			WMXAPIFUNC StartJerkTimedAccJog(TimedAccJogBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccPos(short axis, WMX_PROFILE_TYPE profile, double target,
				double velocity, double accTime, double decTime, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerkTimedAccPos(TimedAccPosBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccPos(short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double accTime, double decTime, double startingVelocity, double endVelocity,
				unsigned int waitTime);
			WMXAPIFUNC StartJerkTimedAccPos(TimedAccPosBlockExt1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkTimedAccMov(short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double accTime, double decTime, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerkTimedAccMov(TimedAccPosBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccMov(short axis, WMX_PROFILE_TYPE profile, double target,
				double velocity, double accTime, double decTime, double startingVelocity, double endVelocity,
				unsigned int waitTime);
			WMXAPIFUNC StartJerkTimedAccMov(TimedAccPosBlockExt1 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkTimedJog(short axis, WMX_PROFILE_TYPE profile, double velocity,
				double runTime, double accTime, double decTime);
			WMXAPIFUNC StartJerkTimedJog(TimedJogBlockExt1 *mpos_block);
			WMXAPIFUNC SetJerkAccOverride(short axis, double jerkAcc);
			WMXAPIFUNC SetJerkAccOverride(PosBlockExt1 *mpos_block);
			WMXAPIFUNC SetJerkDecOverride(short axis, double jerkDec);
			WMXAPIFUNC SetJerkDecOverride(PosBlockExt1 *mpos_block);
			WMXAPIFUNC SetJerkProfileOverride(short axis, WMX_PROFILE_TYPE profile, double velocity, 
				double acc, double dec, double jerkAcc, double jerkDec, double startingVelocity,
				double endVelocity, unsigned char overtravelCancel = 0);
			WMXAPIFUNC SetJerkProfileOverride(PosBlockExt1 *mpos_block, unsigned char overtravelCancel = 0);
		};
	}

	namespace extMotion2 { //Jerk Ratio

		//MPos block for any profile positioning
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
		}PosBlockExt2Ind, *PPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			PosBlockExt2Ind pos_block[MAX_ALLAXES];
		}PosBlockExt2, *PPosBlockExt2;

		//MPos block for any profile triggered positioning
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
			WMX_TRIGGER_TYPE triggerType;
			short triggerAxis;
			double triggerValue;
		}TriggeredPosBlockExt2Ind, *PTriggeredPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			TriggeredPosBlockExt2Ind pos_block[MAX_ALLAXES];
		}TriggeredPosBlockExt2, *PTriggeredPosBlockExt2;

		//MPos block for any profile simple interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlockExt2Ind, *PIntBlockExt2Ind;
		typedef struct {
			short axisCount;
			WMX_PROFILE_TYPE profile;
			double compJerkAccRatio;
			double compJerkDecRatio;
			IntBlockExt2Ind pos_block[MAX_ALLAXES];
		}IntBlockExt2, *PIntBlockExt2;

		//MPos block for any profile composite vector interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlock2Ext2Ind, *PIntBlock2Ext2Ind;
		typedef struct {
			short axisCount;
			WMX_PROFILE_TYPE profile;
			double compVelocity;
			double compAcc;
			double compDec;
			double compJerkAccRatio;
			double compJerkDecRatio;
			double compStartingVelocity;
			double compEndVelocity;
			double compMinimumVelocity;
			IntBlock2Ext2Ind pos_block[MAX_ALLAXES];
		}IntBlock2Ext2, *PIntBlock2Ext2;

		//MPos block for any profile arc abs circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcAbsCirIntBlockExt2, *PArcAbsCirIntBlockExt2;

		//MPos block for any profile arc offset circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcOffsetCirIntBlockExt2, *PArcOffsetCirIntBlockExt2;

		//MPos block for any profile abs pos abs circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}AbsPosAbsCirIntBlockExt2, *PAbsPosAbsCirIntBlockExt2;

		//MPos block for any profile rel pos offset circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}RelPosOffsetCirIntBlockExt2, *PRelPosOffsetCirIntBlockExt2;

		//MPos block for any profile two-velocity positioning
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double target;
			double velocity;
			double secondVelocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
		}TwoVPosBlockExt2Ind, *PTwoVPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			TwoVPosBlockExt2Ind pos_block[MAX_ALLAXES];
		}TwoVPosBlockExt2, *PTwoVPosBlockExt2;

		//MPos block for any profile acceleration time positioning
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double target;
			double velocity;
			double accTime;
			double decTime;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
		}TimedAccPosBlockExt2Ind, *PTimedAccPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			TimedAccPosBlockExt2Ind pos_block[MAX_ALLAXES];
		}TimedAccPosBlockExt2, *PTimedAccPosBlockExt2;

		//MPos block for any profile jog
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double acc;
			double jerkAccRatio;
		}JogBlockExt2Ind, *PJogBlockExt2Ind;
		typedef struct {
			short axisCount;
			JogBlockExt2Ind pos_block[MAX_ALLAXES];
		}JogBlockExt2, *PJogBlockExt2;

		//MPos block for any profile timed jog
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double runTime;
			double accTime;
			double decTime;
			double jerkAccRatio;
			double jerkDecRatio;
		}TimedJogBlockExt2Ind, *PTimedJogBlockExt2Ind;
		typedef struct {
			short axisCount;
			TimedJogBlockExt2Ind pos_block[MAX_ALLAXES];
		}TimedJogBlockExt2, *PTimedJogBlockExt2;

		//MPos block for any profile coordinated positioning
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
		}CoordinatedPosBlockExt2Ind, *PCoordinatedPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			CoordinatedPosBlockExt2Ind pos_block[MAX_ALLAXES];
		}CoordinatedPosBlockExt2, *PCoordinatedPosBlockExt2;
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
			short spindleAxis;
			double spindleTargetVelocity;
			double spindleAxisJerkRatio;
		}CoordinatedPosSpindleBlockExt2Ind, *PCoordinatedPosSpindleBlockExt2Ind;
		typedef struct {
			short axisCount;
			CoordinatedPosSpindleBlockExt2Ind pos_block[MAX_ALLAXES];
		}CoordinatedPosSpindleBlockExt2, *PCoordinatedPosSpindleBlockExt2;

		//MPos block for any profile three dimensional circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis[3];
			double target[3];
			double intermediateTarget[3];
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
		}ThreeDCirIntBlockExt2, *PThreeDCirIntBlockExt2;

		//MPos block for any profile path interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis[MAX_PATH_INTERPOLATE_DIMENSIONS];
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			unsigned int numPoints;
			WMX_PATH_INTERPOLATE_SEGMENT_TYPE type[MAX_PATH_INTERPOLATE_POINTS];
			char dir[MAX_PATH_INTERPOLATE_POINTS];
			double target[MAX_PATH_INTERPOLATE_DIMENSIONS][MAX_PATH_INTERPOLATE_POINTS];
			double centerPos[MAX_PATH_INTERPOLATE_DIMENSIONS][MAX_PATH_INTERPOLATE_POINTS];
		}PathIntBlockExt2, *PPathIntBlockExt2;

		class ExtMotion2 { 
		public:
			WMXLIB *wmxlib;//Reference to main class
			ExtMotion2(WMXLIB *f) : wmxlib(f) {}

			WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity);
			WMXAPIFUNC StartJerkPos(PosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartJerkPos(PosBlockExt2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue); 
			WMXAPIFUNC StartJerkPos(TriggeredPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue, 
				unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkPos(TriggeredPosBlockExt2 *mpos_block, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity, 
				double endVelocity);
			WMXAPIFUNC StartJerkMov(PosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target, double velocity, 
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartJerkMov(PosBlockExt2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue); 
			WMXAPIFUNC StartJerkMov(TriggeredPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkMov(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue,
				unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkMov(TriggeredPosBlockExt2 *mpos_block, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkLinIntPos(IntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntPos(IntBlock2Ext2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntPos(IntBlock2Ext2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkLinIntPos(IntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkLinIntPos(IntBlock2Ext2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkLinIntPos(IntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkLinIntPos(IntBlock2Ext2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkLinIntMov(IntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntMov(IntBlock2Ext2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntMov(IntBlock2Ext2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkLinIntMov(IntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkLinIntMov(IntBlock2Ext2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkLinIntMov(IntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkLinIntMov(IntBlock2Ext2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkCircularInt(ArcAbsCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(ArcOffsetCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(AbsPosAbsCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(RelPosOffsetCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(ThreeDCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(ArcAbsCirIntBlockExt2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkCircularInt(ArcOffsetCirIntBlockExt2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkCircularInt(AbsPosAbsCirIntBlockExt2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkCircularInt(RelPosOffsetCirIntBlockExt2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkCircularInt(ArcAbsCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkCircularInt(ArcOffsetCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkCircularInt(AbsPosAbsCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkCircularInt(RelPosOffsetCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkCircularInt(ArcAbsCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkCircularInt(ArcOffsetCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkCircularInt(AbsPosAbsCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerkCircularInt(RelPosOffsetCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue, unsigned int triggerWaitTime);
			WMXAPIFUNC StartJerk2VPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity, 
				double secondVelocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerk2VPos(TwoVPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerk2VMov(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double secondVelocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerk2VMov(TwoVPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccPos(short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerkTimedAccPos(TimedAccPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccPos(short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartJerkTimedAccPos(TimedAccPosBlockExt2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkTimedAccMov(short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerkTimedAccMov(TimedAccPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccMov(short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity, unsigned int waitTime);
			WMXAPIFUNC StartJerkTimedAccMov(TimedAccPosBlockExt2 *mpos_block, unsigned int waitTime);
			WMXAPIFUNC StartJerkJog(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc,
				double jerkAccRatio);
			WMXAPIFUNC StartJerkJog(JogBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkTimedJog(short axis, WMX_PROFILE_TYPE profile, double velocity,
				double runTime, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio);
			WMXAPIFUNC StartJerkTimedJog(TimedJogBlockExt2 *mpos_block);
			WMXAPIFUNC SetJerkProfileOverride(short axis, WMX_PROFILE_TYPE profile, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, unsigned char overtravelCancel = 0);
			WMXAPIFUNC SetJerkProfileOverride(PosBlockExt2 *mpos_block, unsigned char overtravelCancel = 0);
			WMXAPIFUNC StartJerkPathInt(PathIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCoordinatedPos(short axis, WMX_PROFILE_TYPE profile, 
				double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio);
			WMXAPIFUNC StartJerkCoordinatedPos(CoordinatedPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCoordinatedPos(short axis, WMX_PROFILE_TYPE profile, 
				double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio, short spindleAxis, double spindleAxisTargetVelocity, double spindleAxisJerkRatio);
			WMXAPIFUNC StartJerkCoordinatedPos(CoordinatedPosSpindleBlockExt2 *mpos_block);
			WMXAPIFUNC StopJerkJogAtPos(short axis, WMX_PROFILE_TYPE profile, double target, double dec,
				double jerkDecRatio);
			WMXAPIFUNC SimulateJerkPos(short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, double *pPeakVelocity, int *pTotalTime, 
				int *pAccelerationTime, int *pCruiseTime, int *pDecelerationTime);
			WMXAPIFUNC SimulateJerkLinIntPos(IntBlock2Ext2 *mpos_block, double *pPeakVelocity,
				int *pTotalTime, int *pAccelerationTime, int *pCruiseTime, int *pDecelerationTime);
		};
	}

	namespace basicVelocity {

		//MPos block for Trapezoidal profile vel
		typedef struct {
			short axis;
			double velocity;
			double acc;
		}VelBlockInd, *PVelBlockInd;
		typedef struct {
			short axisCount;
			VelBlockInd pos_block[MAX_ALLAXES];
		}VelBlock, *PVelBlock;

		//MPos block for Trapezoidal profile acceleration time vel
		typedef struct {
			short axis;
			double velocity;
			double accTime;
		}TimedAccVelBlockInd, *PTimedAccVelBlockInd;
		typedef struct {
			short axisCount;
			TimedAccVelBlockInd pos_block[MAX_ALLAXES];
		}TimedAccVelBlock, *PTimedAccVelBlock;

		//MPos block for Trapezoidal profile timed vel
		typedef struct {
			short axis;
			double velocity;
			double runTime;
			double accTime;
			double decTime;
		}TimedVelBlockInd, *PTimedVelBlockInd;
		typedef struct {
			short axisCount;
			TimedVelBlockInd pos_block[MAX_ALLAXES];
		}TimedVelBlock, *PTimedVelBlock;

		class BasicVelocity {
		public:
			WMXLIB *wmxlib;//Reference to main class
			BasicVelocity(WMXLIB *f) : wmxlib(f) {}

			//Velocity Control APIs
			WMXAPIFUNC StartVel(short axis, double velocity, double acc);
			WMXAPIFUNC StartVel(VelBlock *mpos_block);
			WMXAPIFUNC StartTimedAccVel(short axis, double velocity, double accTime);
			WMXAPIFUNC StartTimedAccVel(TimedAccVelBlock *mpos_block);
			WMXAPIFUNC StartTimedVel(short axis, double velocity, double runTime, double accTime, 
				double decTime);
			WMXAPIFUNC StartTimedVel(TimedVelBlock *mpos_block);
			WMXAPIFUNC StopVel(int axis);
			WMXAPIFUNC StopVel(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC QStopVel(int axis);
			WMXAPIFUNC QStopVel(WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC SetMaxVelLimit(short axis, double velocity);
			WMXAPIFUNC GetMaxVelLimit(short axis, double *pVelocity);
			WMXAPIFUNC SetVelOverride(short axis, double velocity);
			WMXAPIFUNC SetVelOverride(VelBlock *mpos_block);
			WMXAPIFUNC SetAxisConstantLinearVelocity(short masterAxis, short slaveAxis, 
				double centerPos, double minR, double positiveMaxR, double negativeMaxR,
				double constLinVel, double initVelVariance);
			WMXAPIFUNC ResolveAxisConstantLinearVelocity(short axis);
		};
	}

	namespace extVelocity1 {

		//MPos block for any profile vel
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double acc;
			double jerkAcc;
		}VelBlockExt1Ind, *PVelBlockExt1Ind;
		typedef struct {
			short axisCount;
			VelBlockExt1Ind pos_block[MAX_ALLAXES];
		}VelBlockExt1, *PVelBlockExt1;

		//MPos block for any profile acceleration time vel
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double accTime;
		}TimedAccVelBlockExt1Ind, *PTimedAccVelBlockExt1Ind;
		typedef struct {
			short axisCount;
			TimedAccVelBlockExt1Ind pos_block[MAX_ALLAXES];
		}TimedAccVelBlockExt1, *PTimedAccVelBlockExt1;

		//MPos block for any profile timed vel
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double runTime;
			double accTime;
			double decTime;
		}TimedVelBlockExt1Ind, *PTimedVelBlockExt1Ind;
		typedef struct {
			short axisCount;
			TimedVelBlockExt1Ind pos_block[MAX_ALLAXES];
		}TimedVelBlockExt1, *PTimedVelBlockExt1;

		class ExtVelocity1 {
		public:
			WMXLIB *wmxlib;//Reference to main class
			ExtVelocity1(WMXLIB *f) : wmxlib(f) {}

			WMXAPIFUNC StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, 
				double jerkAcc);
			WMXAPIFUNC StartJerkVel(VelBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccVel(short axis, WMX_PROFILE_TYPE profile, double velocity, 
				double accTime);
			WMXAPIFUNC StartJerkTimedAccVel(TimedAccVelBlockExt1 *mpos_block);
			WMXAPIFUNC StartJerkTimedVel(short axis, WMX_PROFILE_TYPE profile, double velocity, 
				double runTime, double accTime, double decTime);
			WMXAPIFUNC StartJerkTimedVel(TimedVelBlockExt1 *mpos_block);
		};
	}

	namespace extVelocity2 {

		//MPos block for any profile vel
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double acc;
			double jerkAccRatio;
		}VelBlockExt2Ind, *PVelBlockExt2Ind;
		typedef struct {
			short axisCount;
			VelBlockExt2Ind pos_block[MAX_ALLAXES];
		}VelBlockExt2, *PVelBlockExt2;

		//MPos block for any profile vel with dec and jerk dec ratio specified
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
		}VelBlock2Ext2Ind, *PVelBlock2Ext2Ind;
		typedef struct {
			short axisCount;
			VelBlock2Ext2Ind pos_block[MAX_ALLAXES];
		}VelBlock2Ext2, *PVelBlock2Ext2;

		//MPos block for any profile timed vel
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double runTime;
			double accTime;
			double decTime;
			double jerkAccRatio;
			double jerkDecRatio;
		}TimedVelBlockExt2Ind, *PTimedVelBlockExt2Ind;
		typedef struct {
			short axisCount;
			TimedVelBlockExt2Ind pos_block[MAX_ALLAXES];
		}TimedVelBlockExt2, *PTimedVelBlockExt2;

		class ExtVelocity2 {
		public:
			WMXLIB *wmxlib;//Reference to main class
			ExtVelocity2(WMXLIB *f) : wmxlib(f) {}

			WMXAPIFUNC StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, 
				double jerkAccRatio);
			WMXAPIFUNC StartJerkVel(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, 
				double dec, double jerkAccRatio, double jerkDecRatio);
			WMXAPIFUNC StartJerkVel(VelBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkVel(VelBlock2Ext2 *mpos_block);
			WMXAPIFUNC StartJerkTimedVel(short axis, WMX_PROFILE_TYPE profile, double velocity, 
				double runTime, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio);
			WMXAPIFUNC StartJerkTimedVel(TimedVelBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkPosToVel(short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, 
				double jerkAccRatio, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
		};
	}

	namespace torque {

		//MTrq block for torque command
		typedef struct {
			short axis;
			double torque;
		}TrqBlockInd, *PTrqBlockInd;
		typedef struct {
			short axisCount;
			TrqBlockInd trq_block[MAX_ALLAXES];
		}TrqBlock, *PTrqBlock;

		class TorqueControl { 
		public:
			WMXLIB *wmxlib;//Reference to main class
			TorqueControl(WMXLIB *f) : wmxlib(f) {}

			//Torque Control APIs
			WMXAPIFUNC SetMaxTrqLimit(short axis, double torque);
			WMXAPIFUNC GetMaxTrqLimit(short axis, double *pTorque);
			WMXAPIFUNC SetPositiveTrqLimit(short axis, double torque);
			WMXAPIFUNC GetPositiveTrqLimit(short axis, double *pTorque);
			WMXAPIFUNC SetNegativeTrqLimit(short axis, double torque);
			WMXAPIFUNC GetNegativeTrqLimit(short axis, double *pTorque);
			WMXAPIFUNC StartTrq(short axis, double torque);
			WMXAPIFUNC StartTrq(TrqBlock *mpos_block);
			WMXAPIFUNC StopTrq(int axis);
			WMXAPIFUNC StopTrq(WMX_AXIS_SELECTION *axis_selection);
		};
	}

	namespace extList2 {

		//MPos block for list motion positioning
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
		}PosBlockListExt2Ind, *PPosBlockListExt2Ind;
		typedef struct {
			short axisCount;
			PosBlockListExt2Ind pos_block[MAX_ALLAXES];
		}PosBlockListExt2, *PPosBlockListExt2;

		//MPos block for list motion composite vector interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlock2ListExt2Ind, *PIntBlock2ListExt2Ind;
		typedef struct {
			short axisCount;
			WMX_PROFILE_TYPE profile;
			double compVelocity;
			double compAcc;
			double compDec;
			double compJerkAccRatio;
			double compJerkDecRatio;
			double compStartingVelocity;
			double compEndVelocity;
			double compMinimumVelocity;
			IntBlock2ListExt2Ind pos_block[MAX_ALLAXES];
		}IntBlock2ListExt2, *PIntBlock2ListExt2;

		//MPos block for list motion arc abs circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcAbsCirIntBlockListExt2, *PArcAbsCirIntBlockListExt2;

		//MPos block for list motion arc offset circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcOffsetCirIntBlockListExt2, *PArcOffsetCirIntBlockListExt2;

		//MPos block for list motion abs pos abs circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}AbsPosAbsCirIntBlockListExt2, *PAbsPosAbsCirIntBlockListExt2;

		//MPos block for list motion rel pos offset circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}RelPosOffsetCirIntBlockListExt2, *PRelPosOffsetCirIntBlockListExt2;

		//MPos block for list motion profile two-velocity positioning
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double target;
			double velocity;
			double secondVelocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
		}TwoVPosBlockListExt2Ind, *PTwoVPosBlockListExt2Ind;
		typedef struct {
			short axisCount;
			TwoVPosBlockListExt2Ind pos_block[MAX_ALLAXES];
		}TwoVPosBlockListExt2, *PTwoVPosBlockListExt2;

		//MPos block for list motion coordinated positioning
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
		}CoordinatedPosBlockListExt2Ind, *PCoordinatedPosBlockListExt2Ind;
		typedef struct {
			short axisCount;
			CoordinatedPosBlockListExt2Ind pos_block[MAX_ALLAXES];
		}CoordinatedPosBlockListExt2, *PCoordinatedPosBlockListExt2;
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
			short spindleAxis;
			double spindleTargetVelocity;
			double spindleAxisJerkRatio;
		}CoordinatedPosSpindleBlockListExt2Ind, *PCoordinatedPosSpindleBlockListExt2Ind;
		typedef struct {
			short axisCount;
			CoordinatedPosSpindleBlockListExt2Ind pos_block[MAX_ALLAXES];
		}CoordinatedPosSpindleBlockListExt2, *PCoordinatedPosSpindleBlockListExt2;

		//MPos block for list motion trapezoidal profile constant deceleration positioning
		typedef struct {
			short axis;
			double target;
			double startingVelocity;
			double endVelocity;
		}ConstDecPosBlockListInd, *PConstDecPosBlockListInd;
		typedef struct {
			short axisCount;
			ConstDecPosBlockListInd pos_block[MAX_ALLAXES];
		}ConstDecPosBlockList;
		
		class ExtList2 {
		public:
			WMXLIB *wmxlib;//Reference to main class
			ExtList2(WMXLIB *f) : wmxlib(f) {}

			//List motion APIs
			WMXAPIFUNC BeginList(unsigned int channel);
			WMXAPIFUNC EndList(unsigned int channel);
			WMXAPIFUNC ExecuteList(unsigned int channel);
			WMXAPIFUNC AbortList(unsigned int channel);
			WMXAPIFUNC PauseList(unsigned int channel);
			WMXAPIFUNC ResumeList(unsigned int channel);
			WMXAPIFUNC ClearList(unsigned int channel);
			WMXAPIFUNC ClearAllList();
			WMXAPIFUNC GetListStatus(unsigned int channel, WMX_LIST_STATUS *pStatus);
			
			WMXAPIFUNC ListJerkPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio, 
				double startingVelocity, double endVelocity);
			WMXAPIFUNC ListJerkPos(unsigned int channel, PosBlockListExt2 *mpos_block);
			WMXAPIFUNC ListJerkMov(unsigned int channel, short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC ListJerkMov(unsigned int channel, PosBlockListExt2 *mpos_block);
			WMXAPIFUNC ListJerkLinIntPos(unsigned int channel, IntBlock2ListExt2 *mpos_block);
			WMXAPIFUNC ListJerkLinIntMov(unsigned int channel, IntBlock2ListExt2 *mpos_block);
			WMXAPIFUNC ListJerkCircularInt(unsigned int channel, ArcAbsCirIntBlockListExt2 *mpos_block);
			WMXAPIFUNC ListJerkCircularInt(unsigned int channel, ArcOffsetCirIntBlockListExt2 *mpos_block);
			WMXAPIFUNC ListJerkCircularInt(unsigned int channel, AbsPosAbsCirIntBlockListExt2 *mpos_block);
			WMXAPIFUNC ListJerkCircularInt(unsigned int channel, RelPosOffsetCirIntBlockListExt2 *mpos_block);
			WMXAPIFUNC ListJerk2VPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile, double target,
				double velocity, double secondVelocity, double acc, double dec, double jerkAccRatio, 
				double jerkDecRatio, double startingVelocity, double endVelocity);
			WMXAPIFUNC ListJerk2VPos(unsigned int channel, TwoVPosBlockListExt2 *mpos_block);
			WMXAPIFUNC ListJerk2VMov(unsigned int channel, short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double secondVelocity, double acc, double dec, double jerkAccRatio, 
				double jerkDecRatio, double startingVelocity, double endVelocity);
			WMXAPIFUNC ListJerk2VMov(unsigned int channel, TwoVPosBlockListExt2 *mpos_block);
			WMXAPIFUNC ListConstDecPos(unsigned int channel, short axis, double target, double startingVelocity,
				double endVelocity);
			WMXAPIFUNC ListConstDecPos(unsigned int channel, ConstDecPosBlockList *mpos_block);
			WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile, 
				double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio);
			WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, CoordinatedPosBlockListExt2 *mpos_block);
			WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, short axis, WMX_PROFILE_TYPE profile, 
				double target, double velocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity, short axis2, double axis2target, double axis2smoothRatio, short spindleAxis, double spindleAxisTargetVelocity, double spindleAxisJerkRatio);
			WMXAPIFUNC ListJerkCoordinatedPos(unsigned int channel, CoordinatedPosSpindleBlockListExt2 *mpos_block);
		};
	}

	namespace basicBuffer {
		//MPos block for Trapezoidal profile positioning
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
		}PosBlockInd, *PPosBlockInd;
		typedef struct {
			short axisCount;
			PosBlockInd pos_block[MAX_ALLAXES];
		}PosBlock, *PPosBlock;

		//MPos block for Trapezoidal profile triggered positioning
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			WMX_TRIGGER_TYPE triggerType;
			short triggerAxis;
			double triggerValue;
		}TriggeredPosBlockInd, *PTriggeredPosBlockInd;
		typedef struct {
			short axisCount;
			TriggeredPosBlockInd pos_block[MAX_ALLAXES];
		}TriggeredPosBlock, *PTriggeredPosBlock;
			
		//MPos block for Trapezoidal profile acceleration time positioning
		typedef struct {
			short axis;
			double target;
			double velocity;
			double accTime;
			double decTime;
			double startingVelocity;
			double endVelocity;
		}TimedAccPosBlockInd, *PTimedAccPosBlockInd;
		typedef struct {
			short axisCount;
			TimedAccPosBlockInd pos_block[MAX_ALLAXES];
		}TimedAccPosBlock, *PTimedAccPosBlock;

		//MPos block for Trapezoidal profile simple interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlockInd, *PIntBlockInd;
		typedef struct {
			short axisCount;
			IntBlockInd pos_block[MAX_ALLAXES];
		}IntBlock, *PIntBlock;

		//MPos block for Trapezoidal profile composite vector interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlock2Ind, *PIntBlock2Ind;
		typedef struct {
			short axisCount;
			double compVelocity;
			double compAcc;
			double compDec;
			double compStartingVelocity;
			double compEndVelocity;
			double compMinimumVelocity;
			IntBlock2Ind pos_block[MAX_ALLAXES];
		}IntBlock2, *PIntBlock2;

		//MPos block for Trapezoidal profile arc abs circular interpolation
		typedef struct {
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcAbsCirIntBlock, *PArcAbsCirIntBlock;

		//MPos block for Trapezoidal profile arc offset circular interpolation
		typedef struct {
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcOffsetCirIntBlock, *PArcOffsetCirIntBlock;

		//MPos block for Trapezoidal profile abs pos abs circular interpolation
		typedef struct {
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}AbsPosAbsCirIntBlock, *PAbsPosAbsCirIntBlock;

		//MPos block for Trapezoidal profile rel pos offset circular interpolation
		typedef struct {
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}RelPosOffsetCirIntBlock, *PRelPosOffsetCirIntBlock;

		//MPos block for Trapezoidal profile two-velocity positioning
		typedef struct {
			short axis;
			double target;
			double velocity;
			double secondVelocity;
			double acc;
			double dec;
			double startingVelocity;
			double endVelocity;
		}TwoVPosBlockInd, *PTwoVPosBlockInd;
		typedef struct {
			short axisCount;
			TwoVPosBlockInd pos_block[MAX_ALLAXES];
		}TwoVPosBlock, *PTwoVPosBlock;

		//MPos block for Trapezoidal profile jog
		typedef struct {
			short axis;
			double velocity;
			double acc;
		}JogBlockInd, *PJogBlockInd;
		typedef struct {
			short axisCount;
			JogBlockInd pos_block[MAX_ALLAXES];
		}JogBlock, *PJogBlock;

		//MPos block for Trapezoidal profile acceleration time jog
		typedef struct {
			short axis;
			double velocity;
			double accTime;
		}TimedAccJogBlockInd, *PTimedAccJogBlockInd;
		typedef struct {
			short axisCount;
			TimedAccJogBlockInd pos_block[MAX_ALLAXES];
		}TimedAccJogBlock, *PTimedAccJogBlock;

		//MPos block for Trapezoidal profile timed jog
		typedef struct {
			short axis;
			double velocity;
			double runTime;
			double accTime;
			double decTime;
		}TimedJogBlockInd, *PTimedJogBlockInd;
		typedef struct {
			short axisCount;
			TimedJogBlockInd pos_block[MAX_ALLAXES];
		}TimedJogBlock, *PTimedJogBlock;

		//MPos block for Trapezoidal profile positioning using parameter init/end vel
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}PosBlockParamVelInd, *PPosBlockParamVelInd;
		typedef struct {
			short axisCount;
			PosBlockParamVelInd pos_block[MAX_ALLAXES];
		}PosBlockParamVel, *PPosBlockParamVel;
			
		//MPos block for Trapezoidal profile acceleration time positioning using parameter init/end vel
		typedef struct {
			short axis;
			double target;
			double velocity;
			double accTime;
			double decTime;
		}TimedAccPosBlockParamVelInd, *PTimedAccPosBlockParamVelInd;
		typedef struct {
			short axisCount;
			TimedAccPosBlockParamVelInd pos_block[MAX_ALLAXES];
		}TimedAccPosBlockParamVel, *PTimedAccPosBlockParamVel;

		//MPos block for Trapezoidal profile constant deceleration positioning
		typedef struct {
			short axis;
			double target;
			double startingVelocity;
			double endVelocity;
		}ConstDecPosBlockInd, *PConstDecPosBlockInd;
		typedef struct {
			short axisCount;
			ConstDecPosBlockInd pos_block[MAX_ALLAXES];
		}ConstDecPosBlock;

		class BasicBuffer {
		public:
			WMXLIB *wmxlib;//Reference to main class
			BasicBuffer(WMXLIB *f) : wmxlib(f) {}

			WMXAPIFUNC StartAPIBuffer(unsigned int channel);
			WMXAPIFUNC StopAPIBuffer(unsigned int channel);
			WMXAPIFUNC ClearAPIBuffer(unsigned int channel);
			WMXAPIFUNC RewindAPIBuffer(unsigned int channel);
			WMXAPIFUNC GetAPIBufferStatus(unsigned int channel, WMX_BUF_STATUS *pStatus);

			WMXAPIFUNC SleepAPIBuffer(unsigned int channel, unsigned int milliseconds);
			WMXAPIFUNC WaitAPIBuffer(unsigned int channel, WMX_BUF_CONDITION condition);
			WMXAPIFUNC IfAPIBuffer(unsigned int channel, WMX_BUF_CONDITION condition);
			WMXAPIFUNC IfAPIBuffer(unsigned int channel, WMX_BUF_CONDITION condition, WMX_BUF_CONDITION wait);
			WMXAPIFUNC IfElseAPIBuffer(unsigned int channel, WMX_BUF_CONDITION condition);
			WMXAPIFUNC ElseAPIBuffer(unsigned int channel);
			WMXAPIFUNC EndIfAPIBuffer(unsigned int channel);

			WMXAPIFUNC StartPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlock *mpos_block);
			WMXAPIFUNC StartPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double acc, double dec);
			WMXAPIFUNC StartPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlockParamVel *mpos_block);
			WMXAPIFUNC StartPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue); 
			WMXAPIFUNC StartPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, TriggeredPosBlock *mpos_block);
			WMXAPIFUNC StartMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis, 
				double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlock *mpos_block);
			WMXAPIFUNC StartMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double acc, double dec);
			WMXAPIFUNC StartMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlockParamVel *mpos_block);
			WMXAPIFUNC StartMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis, 
				double target, double velocity, double acc, double dec, double startingVelocity, double endVelocity,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue); 
			WMXAPIFUNC StartMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, TriggeredPosBlock *mpos_block);
			WMXAPIFUNC StartLinIntPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, IntBlock *mpos_block);
			WMXAPIFUNC StartLinIntPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, IntBlock2 *mpos_block);
			WMXAPIFUNC StartLinIntPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, IntBlock *mpos_block,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartLinIntPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, IntBlock2 *mpos_block,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartLinIntMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, IntBlock *mpos_block);
			WMXAPIFUNC StartLinIntMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, IntBlock2 *mpos_block);
			WMXAPIFUNC StartLinIntMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, IntBlock *mpos_block,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartLinIntMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, IntBlock2 *mpos_block,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				ArcAbsCirIntBlock *mpos_block);
			WMXAPIFUNC StartCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				ArcOffsetCirIntBlock *mpos_block);
			WMXAPIFUNC StartCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				AbsPosAbsCirIntBlock *mpos_block);
			WMXAPIFUNC StartCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				RelPosOffsetCirIntBlock *mpos_block);
			WMXAPIFUNC StartCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				ArcAbsCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				ArcOffsetCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				AbsPosAbsCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				RelPosOffsetCirIntBlock *mpos_block, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC Start2VPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double secondVelocity, double acc, double dec, double startingVelocity,
				double endVelocity);
			WMXAPIFUNC Start2VPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, TwoVPosBlock *mpos_block);
			WMXAPIFUNC Start2VMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double secondVelocity, double acc, double dec, double startingVelocity,
				double endVelocity);
			WMXAPIFUNC Start2VMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, TwoVPosBlock *mpos_block);
			WMXAPIFUNC StartConstDecPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis, double target, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartConstDecPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, ConstDecPosBlock *mpos_block);
			WMXAPIFUNC StartConstDecPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis, double target, double startingVelocity, double endVelocity,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJog(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis, 
				double velocity, double acc);
			WMXAPIFUNC StartJog(unsigned int channel, WMX_BUF_FINISH_TYPE type, JogBlock *mpos_block);
			WMXAPIFUNC StartTimedAccJog(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double velocity, double accTime);
			WMXAPIFUNC StartTimedAccJog(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				TimedAccJogBlock *mpos_block);
			WMXAPIFUNC SetPosOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target);
			WMXAPIFUNC SetPosOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlock *mpos_block);
			WMXAPIFUNC SetMovOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target);
			WMXAPIFUNC SetMovOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlock *mpos_block);
			WMXAPIFUNC StartTimedAccPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double accTime, double decTime, double startingVelocity, 
				double endVelocity);
			WMXAPIFUNC StartTimedAccPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				TimedAccPosBlock *mpos_block);
			WMXAPIFUNC StartTimedAccPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double accTime, double decTime);
			WMXAPIFUNC StartTimedAccPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				TimedAccPosBlockParamVel *mpos_block);
			WMXAPIFUNC StartTimedAccMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double accTime, double decTime, double startingVelocity,
				double endVelocity);
			WMXAPIFUNC StartTimedAccMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				TimedAccPosBlock *mpos_block);
			WMXAPIFUNC StartTimedAccMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double target, double velocity, double accTime, double decTime);
			WMXAPIFUNC StartTimedAccMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				TimedAccPosBlockParamVel *mpos_block);
			WMXAPIFUNC StartTimedJog(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double velocity, double runTime, double accTime, double decTime);
			WMXAPIFUNC StartTimedJog(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				TimedJogBlock *mpos_block);
			WMXAPIFUNC StopAxis(unsigned int channel, WMX_BUF_FINISH_TYPE type, int axis);
			WMXAPIFUNC StopAxis(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC QStopAxis(unsigned int channel, WMX_BUF_FINISH_TYPE type, int axis);
			WMXAPIFUNC QStopAxis(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				WMX_AXIS_SELECTION *axis_selection);
			WMXAPIFUNC SetVelOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double velocity);
			WMXAPIFUNC SetVelOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlock *mpos_block);
			WMXAPIFUNC SetAccOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double acc);
			WMXAPIFUNC SetAccOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlock *mpos_block);
			WMXAPIFUNC SetDecOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				double dec);
			WMXAPIFUNC SetDecOverride(unsigned int channel, WMX_BUF_FINISH_TYPE type, PosBlock *mpos_block);

			WMXAPIFUNC SetMaxTrqLimit(unsigned int channel, short axis, double torque);
			WMXAPIFUNC SetPositiveTrqLimit(unsigned int channel, short axis, double torque);
			WMXAPIFUNC SetNegativeTrqLimit(unsigned int channel, short axis, double torque);
			
			WMXAPIFUNC SetMaxVelLimit(unsigned int channel, short axis, double velocity);
			WMXAPIFUNC SetAxisMode(unsigned int channel, short axis, WMX_AXIS_COMMAND_MODE mode);
			WMXAPIFUNC StartTrq(unsigned int channel, short axis, double torque);
			WMXAPIFUNC StopVel(unsigned int channel, WMX_BUF_FINISH_TYPE type, int axis);
			
			WMXAPIFUNC SetOutBit(unsigned int channel, short byte, short bit, unsigned char data);
			WMXAPIFUNC SetOutByte(unsigned int channel, short offsetByte, unsigned char data);
			WMXAPIFUNC SetOutBytes(unsigned int channel, short offsetByte, short size, unsigned char *data);
		};
	}

	namespace extBuffer2 {

		//MPos block for any profile positioning
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
		}PosBlockExt2Ind, *PPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			PosBlockExt2Ind pos_block[MAX_ALLAXES];
		}PosBlockExt2, *PPosBlockExt2;

		//MPos block for any profile triggered positioning
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
			WMX_TRIGGER_TYPE triggerType;
			short triggerAxis;
			double triggerValue;
		}TriggeredPosBlockExt2Ind, *PTriggeredPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			TriggeredPosBlockExt2Ind pos_block[MAX_ALLAXES];
		}TriggeredPosBlockExt2, *PTriggeredPosBlockExt2;

		//MPos block for any profile simple interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlockExt2Ind, *PIntBlockExt2Ind;
		typedef struct {
			short axisCount;
			WMX_PROFILE_TYPE profile;
			double compJerkAccRatio;
			double compJerkDecRatio;
			IntBlockExt2Ind pos_block[MAX_ALLAXES];
		}IntBlockExt2, *PIntBlockExt2;

		//MPos block for any profile composite vector interpolation
		typedef struct {
			short axis;
			double target;
			double velocity;
			double acc;
			double dec;
		}IntBlock2Ext2Ind, *PIntBlock2Ext2Ind;
		typedef struct {
			short axisCount;
			WMX_PROFILE_TYPE profile;
			double compVelocity;
			double compAcc;
			double compDec;
			double compJerkAccRatio;
			double compJerkDecRatio;
			double compStartingVelocity;
			double compEndVelocity;
			double compMinimumVelocity;
			IntBlock2Ext2Ind pos_block[MAX_ALLAXES];
		}IntBlock2Ext2, *PIntBlock2Ext2;

		//MPos block for any profile arc abs circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcAbsCirIntBlockExt2, *PArcAbsCirIntBlockExt2;

		//MPos block for any profile arc offset circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double degreeDistance;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}ArcOffsetCirIntBlockExt2, *PArcOffsetCirIntBlockExt2;

		//MPos block for any profile abs pos abs circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}AbsPosAbsCirIntBlockExt2, *PAbsPosAbsCirIntBlockExt2;

		//MPos block for any profile rel pos offset circular interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis1;
			short axis2;
			double target1;
			double target2;
			double direction;
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			double centerFirstAxis;
			double centerSecondAxis;
		}RelPosOffsetCirIntBlockExt2, *PRelPosOffsetCirIntBlockExt2;

		//MPos block for any profile two-velocity positioning
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double target;
			double velocity;
			double secondVelocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
		}TwoVPosBlockExt2Ind, *PTwoVPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			TwoVPosBlockExt2Ind pos_block[MAX_ALLAXES];
		}TwoVPosBlockExt2, *PTwoVPosBlockExt2;

		//MPos block for any profile acceleration time positioning
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double target;
			double velocity;
			double accTime;
			double decTime;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
		}TimedAccPosBlockExt2Ind, *PTimedAccPosBlockExt2Ind;
		typedef struct {
			short axisCount;
			TimedAccPosBlockExt2Ind pos_block[MAX_ALLAXES];
		}TimedAccPosBlockExt2, *PTimedAccPosBlockExt2;

		//MPos block for any profile jog
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double acc;
			double jerkAccRatio;
		}JogBlockExt2Ind, *PJogBlockExt2Ind;
		typedef struct {
			short axisCount;
			JogBlockExt2Ind pos_block[MAX_ALLAXES];
		}JogBlockExt2, *PJogBlockExt2;

		//MPos block for any profile timed jog
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis;
			double velocity;
			double runTime;
			double accTime;
			double decTime;
			double jerkAccRatio;
			double jerkDecRatio;
		}TimedJogBlockExt2Ind, *PTimedJogBlockExt2Ind;
		typedef struct {
			short axisCount;
			TimedJogBlockExt2Ind pos_block[MAX_ALLAXES];
		}TimedJogBlockExt2, *PTimedJogBlockExt2;

		//MPos block for any profile path interpolation
		typedef struct {
			WMX_PROFILE_TYPE profile;
			short axis[MAX_PATH_INTERPOLATE_DIMENSIONS];
			double velocity;
			double acc;
			double dec;
			double jerkAccRatio;
			double jerkDecRatio;
			double startingVelocity;
			double endVelocity;
			unsigned int numPoints;
			WMX_PATH_INTERPOLATE_SEGMENT_TYPE type[MAX_PATH_INTERPOLATE_POINTS];
			char dir[MAX_PATH_INTERPOLATE_POINTS];
			double target[MAX_PATH_INTERPOLATE_DIMENSIONS][MAX_PATH_INTERPOLATE_POINTS];
			double centerPos[MAX_PATH_INTERPOLATE_DIMENSIONS][MAX_PATH_INTERPOLATE_POINTS];
		}PathIntBlockExt2, *PPathIntBlockExt2;

		class ExtBuffer2 {
		public:
			WMXLIB *wmxlib;//Reference to main class
			ExtBuffer2(WMXLIB *f) : wmxlib(f) {}

			//API Buffer APIs
			WMXAPIFUNC StartJerkPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, short axis,
				WMX_PROFILE_TYPE profile, double target, double velocity, double acc, double dec, double jerkAccRatio,
				double jerkDecRatio, double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerkPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				PosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkPos(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue); 
			WMXAPIFUNC StartJerkPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				TriggeredPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity, 
				double endVelocity);
			WMXAPIFUNC StartJerkMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				PosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double acc, double dec, double jerkAccRatio, double jerkDecRatio, double startingVelocity,
				double endVelocity, WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue); 
			WMXAPIFUNC StartJerkMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				TriggeredPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				IntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				IntBlock2Ext2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				IntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkLinIntPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				IntBlock2Ext2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkLinIntMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				IntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				IntBlock2Ext2 *mpos_block);
			WMXAPIFUNC StartJerkLinIntMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				IntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkLinIntMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				IntBlock2Ext2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				ArcAbsCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				ArcOffsetCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				AbsPosAbsCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				RelPosOffsetCirIntBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				ArcAbsCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				ArcOffsetCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				AbsPosAbsCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerkCircularInt(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				RelPosOffsetCirIntBlockExt2 *mpos_block, WMX_TRIGGER_TYPE triggerType, 
				short triggerAxis, double triggerValue);
			WMXAPIFUNC StartJerk2VPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double target, double velocity, 
				double secondVelocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerk2VPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				TwoVPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerk2VMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double target, double velocity,
				double secondVelocity, double acc, double dec, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerk2VMov(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				TwoVPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerkTimedAccPos(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				TimedAccPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkTimedAccMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double target, 
				double velocity, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio,
				double startingVelocity, double endVelocity);
			WMXAPIFUNC StartJerkTimedAccMov(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				TimedAccPosBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkJog(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				short axis, WMX_PROFILE_TYPE profile, double velocity, double acc,
				double jerkAccRatio);
			WMXAPIFUNC StartJerkJog(unsigned int channel, WMX_BUF_FINISH_TYPE type, 
				JogBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkTimedJog(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double velocity,
				double runTime, double accTime, double decTime, double jerkAccRatio, double jerkDecRatio);
			WMXAPIFUNC StartJerkTimedJog(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				TimedJogBlockExt2 *mpos_block);
			WMXAPIFUNC StartJerkPathInt(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				PathIntBlockExt2 *mpos_block);

			WMXAPIFUNC StartJerkVel(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, double jerkAccRatio);
			WMXAPIFUNC StartJerkPosToVel(unsigned int channel, WMX_BUF_FINISH_TYPE type,
				short axis, WMX_PROFILE_TYPE profile, double velocity, double acc, double jerkAccRatio,
				WMX_TRIGGER_TYPE triggerType, short triggerAxis, double triggerValue);
		};
	}

	class WMXLIB {
	public:
		HSSDEV dev;

		WMXLIB();
		~WMXLIB();

		//System APIs
		WMXAPIFUNC CreateDevice(TCHAR *path, PLTFRM_TYPE type);
		WMXAPIFUNC CreateDevice(TCHAR *path, PLTFRM_TYPE type, short core);
		WMXAPIFUNC CreateDevice(TCHAR *path, PLTFRM_TYPE type, short ceCore, short peCore);
		
		WMXAPIFUNC CreateDevice(TCHAR *path, PLTFRM_TYPE type, WMX_AXIS_COUNT axisCount);
		WMXAPIFUNC CreateDevice(TCHAR *path, PLTFRM_TYPE type, short core, WMX_AXIS_COUNT axisCount);
		WMXAPIFUNC CreateDevice(TCHAR *path, PLTFRM_TYPE type, short ceCore, short peCore,
			WMX_AXIS_COUNT axisCount);
		
		WMXAPIFUNC CreateDeviceEx(TCHAR *path, PLTFRM_TYPE type);
		WMXAPIFUNC CreateDeviceEx(TCHAR *path, PLTFRM_TYPE type, short core);
		WMXAPIFUNC CreateDeviceEx(TCHAR *path, PLTFRM_TYPE type, short ceCore, short peCore);
		
		WMXAPIFUNC CreateDeviceEx(TCHAR *path, PLTFRM_TYPE type, WMX_AXIS_COUNT axisCount);
		WMXAPIFUNC CreateDeviceEx(TCHAR *path, PLTFRM_TYPE type, short core, WMX_AXIS_COUNT axisCount);
		WMXAPIFUNC CreateDeviceEx(TCHAR *path, PLTFRM_TYPE type, short ceCore, short peCore,
			WMX_AXIS_COUNT axisCount);

		WMXAPIFUNC CloseDevice();
		WMXAPIFUNC CloseDeviceEx();
		WMXAPIFUNC GetDeviceType(WMX_DEV_TYPE *type);
		WMXAPIFUNC GetDeviceID(int *id);
		WMXAPIFUNC GetDeviceCount(int *pCount);
		WMXAPIFUNC GetDeviceName(TCHAR *name);
		WMXAPIFUNC SetDeviceName(TCHAR *name);
		WMXAPIFUNC StartCommunication();
		WMXAPIFUNC StopCommunication();
		WMXAPIFUNC GetStatus(WMX_STATUS *st);
		WMXAPIFUNC GetStatus(WMX_STATUS *st, short axis);
		WMXAPIFUNC GetStatus(WMX_STATUS *st, short firstAxis, short lastAxis);
		WMXAPIFUNC GetVersion(double *pCeVersion, double *pPeVersion);
		WMXAPIFUNC EStop(WMX_ESTOP_LEVEL level);
		WMXAPIFUNC GetLastError();
		WMXAPIFUNC GetErrorCode(unsigned long cmdID);
		WMXAPIFUNC GetErrorCodeLog(WMX_API_ERROR_LOG_DATA* errLog);
		WMXAPIFUNC ForceExit();
		WMXAPIFUNC SetAPITimeOut(unsigned int sec);
		WMXAPIFUNC ForceCloseDevice(int id);
		WMXAPIFUNC GetActiveDeviceList(WMX_ACT_DEV_LIST* list);
		WMXAPIFUNC GetQueueCount(int *pCount);

		common::EventControl *eventControl;
		common::Log *log;
		common::Io *io;
		common::Config *config;
		common::AxisControl *axisControl;
		common::Sync *sync;
		common::Home *home;
		common::Compensation *compensation;
		basicMotion::BasicMotion *basicMotion;
		extMotion1::ExtMotion1 *extMotion1;
		extMotion2::ExtMotion2 *extMotion2;
		basicVelocity::BasicVelocity *basicVelocity;
		extVelocity1::ExtVelocity1 *extVelocity1;
		extVelocity2::ExtVelocity2 *extVelocity2;
		torque::TorqueControl *torqueControl;	
		extList2::ExtList2 *extList2;
		basicBuffer::BasicBuffer *basicBuffer;
		extBuffer2::ExtBuffer2 *extBuffer2;
		
		WMX_API_ERROR_CODE lastError;
	};
}

#endif
