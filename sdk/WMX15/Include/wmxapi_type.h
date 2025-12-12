//WMX v0.987718

#ifndef WMXAPI_TYPE
#define WMXAPI_TYPE
#include "wmxapi_def.h"

typedef HANDLE HSSDEV, *PHSSDEV;

typedef struct{
	long InPosWidth;             //In position width
	long InPos2Width;             //In position width 2
	long InPos3Width;             //In position width 3
	long InPos4Width;             //In position width 4
	long InPos5Width;             //In position width 5
	short VelocityMonitorSource; //0: Calculate from feedback, 1: Use Actual Velocity Feedback from the drive if available
	long PosCompWidth;           //Position completed width for PSET
	long DPsetPosCompWidth;     //Position completed width for DPSET
	unsigned int DPsetDelay;    //Cycles within position completed width for DPSET to be 1
}WMX_FEEDBACK_PARAM, *PWMX_FEEDBACK_PARAM;

typedef struct{
	WMX_HOME_TYPE HomeType;
	WMX_HOME_DIR HomeDir;
	double GridSearchVel;
	double GridSearchAcc;
	double GridSearchDec;
	double HSSearchVel;
	double HSSearchAcc;
	double HSSearchDec;
	double HSReverseDistance;
	double HomeShiftVel;
	double HomeShiftAcc;
	double HomeShiftDec;
	double HomeShiftDistance;
	unsigned char HSPol;
	unsigned int MultipleZP;
	unsigned char MultiplierCompensation;
	unsigned char PauseMode;
	double MaxHSOnAtStartReverseDistance;
	double MaxLSReverseDistance;
	unsigned int ZPDistanceCheck;
	unsigned char GantryHoming;
	unsigned char GantryHomingSingleHS;
	unsigned char GantryHomingSingleLS;
	unsigned char GantryHomingSingleZP;
	unsigned char GantryHomingSingleHSTP;
	unsigned char LimitSwitchReverseType;
}WMX_HOME_PARAM, *PWMX_HOME_PARAM;

typedef struct{
	WMX_LIMITSWITCH_TYPE LSType;        //Limit switch type
	WMX_LIMITSWITCH_TYPE PLSType;		//Positive limit switch type
	WMX_LIMITSWITCH_TYPE NLSType;		//Negative limit switch type
	unsigned char LSPol;                //Limit switch polarity
	WMX_LIMITSWITCH_TYPE NearLSType;    //Near limit switch type
	WMX_LIMITSWITCH_TYPE NearPLSType;	//Positive near limit switch type
	WMX_LIMITSWITCH_TYPE NearNLSType;	//Negative near limit switch type
	int NearPLSByte;                    //Near positive limit switch byte address
	short NearPLSBit;                   //Near positive limit switch bit offset
	unsigned char NearPLSPol;           //Near positive limit switch polarity
	int NearNLSByte;                    //Near negative limit switch byte address
	short NearNLSBit;                   //Near negative limit switch bit offset
	unsigned char NearNLSPol;           //Near negative limit switch polarity
	WMX_LIMITSWITCH_TYPE ExtLSType;     //External limit switch type
	WMX_LIMITSWITCH_TYPE ExtPLSType;	//Positive External limit switch type
	WMX_LIMITSWITCH_TYPE ExtNLSType;	//Negative External limit switch type
	int ExtPLSByte;                     //External positive limit switch byte address
	short ExtPLSBit;                    //External positive limit switch bit offset
	unsigned char ExtPLSPol;            //External positive limit switch polarity
	int ExtNLSByte;                     //External negative limit switch byte address
	short ExtNLSBit;                    //External negative limit switch bit offset
	unsigned char ExtNLSPol;            //External negative limit switch polarity
	WMX_LIMITSWITCH_TYPE SoftLimitType; //Software limit type
	WMX_LIMITSWITCH_TYPE PSoftLimitType; //Positive software limit type
	WMX_LIMITSWITCH_TYPE NSoftLimitType; //Negative software limit type
	double SoftLimitPPos;               //Positive software limit position
	double SoftLimitNPos;               //Negative software limit position
	double LSDec;                       //Limit switch deceleration
	double LSSlowDec;                   //Limit switch slow deceleration
	unsigned char AllLSDuringHoming;    //Enable all limit switches during homing
}WMX_LIMIT_PARAM, *PWMX_LIMIT_PARAM;

typedef struct{
	double QStopDec;             //Quick stop deceleration
	double EStopDec;             //E-Stop deceleration
	double StartingVelocity;     //Starting velocity for functions that use the parameter-specified starting velocity
	double EndVelocity;          //End velocity for functions that use the parameter-specified end velocity
	double MinimumVelocity;      //Minimum velocity for functions that use the parameter-specified end deceleration
	unsigned char ProhibitOvertravel; //Prohibit overtravel mode
	unsigned int LinIntOvrdSmoothPercent; //Linear interpolation override smoothing percent
	unsigned char InterruptedIntplUseQuickStop; //Interrupted interpolation use quick stop
}WMX_MOTION_PARAM, *PWMX_MOTION_PARAM;

typedef struct{
	double FollowingErrorStopped;        //Maximum tolerable following error while axis is not moving
	double FollowingErrorMoving;         //Maximum tolerable following error while axis is moving
	WMX_ALARM_FOLLOWING_ERROR_TYPE FollowingErrorType; //Following error action type
	double VelFollowingErrorStopped;     //Maximum tolerable velocity following error for stopped velocity axes
	double VelFollowingErrorStoppedTime; //Maximum tolerable time that the velocity following error stopped is exceeded
	double VelFollowingErrorMoving;      //Maximum tolerable velocity following error for moving velocity axes
	double VelFollowingErrorMovingTime;  //Maximum tolerable time that the velocity following error moving is exceeded
	WMX_ALARM_VELOCITY_FOLLOWING_ERROR_TYPE VelFollowingErrorType; //Following error action type for velocity following error
	unsigned char ServoOffDuringAmpAlarm; //Turn servo off during amp alarm
}WMX_ALARM_PARAM, *PWMX_ALARM_PARAM;

typedef struct{
	double AxisUnit;                  //Machine unit
	unsigned char OpenLoopMode;       //Open loop mode
	unsigned char SaveFlightRecorder; //Save flight recorder data
}WMX_SYSTEM_PARAM, *PWMX_SYSTEM_PARAM;

typedef struct{
	long InSyncWidth;                        //Minimum sync offset to apply compensation
	double SyncGain;                         //Compensation gain
	unsigned char UseVelocityOffset;         //Send velocity offset signal to servo instead of position offset
	WMX_MASTER_DESYNC_TYPE MasterDesyncType; //Master behavior when slave desyncs
	double MasterDesyncDec;                  //Deceleration used for certain master desync types
	WMX_SLAVE_DESYNC_TYPE SlaveDesyncType;   //Slave behavior when master desyncs
	double SlaveDesyncDec;                   //Deceleration used for certain slave desync types
	unsigned char MatchPosition;             //Match the slave and master positions
}WMX_SYNC_PARAM, *PWMX_SYNC_PARAM;

typedef struct{
	unsigned char EnableFlightRecorder;    //Use flight recorder
	unsigned char FlightRecorderTimeStamp; //Add time stamp to flight recorder files
}WMX_SYSTEM_PARAM_2, *PWMX_SYSTEM_PARAM_2;

typedef struct{
	WMX_FEEDBACK_PARAM FeedbackParam[MAX_ALLAXES]; //Feedback parameters
	WMX_HOME_PARAM HomeParam[MAX_ALLAXES];         //Home parameters
	WMX_LIMIT_PARAM LimitParam[MAX_ALLAXES];       //Limit parameters
	WMX_MOTION_PARAM MotionParam[MAX_ALLAXES];     //Motion parameters
	WMX_ALARM_PARAM AlarmParam[MAX_ALLAXES];       //Alarm parameters
	WMX_SYSTEM_PARAM SystemParam[MAX_ALLAXES];     //System parameters
	WMX_SYNC_PARAM SyncParam[MAX_ALLAXES];         //Sync parameters
	WMX_SYSTEM_PARAM_2 SystemParam2;               //Axis independent system parameters
}WMX_PARAM, *PWMX_PARAM;

typedef struct{
	short masterAxis;
	short slaveAxisCount;
	short slaveAxis[MAX_ALLAXES-1];
	double slaveAxisSyncOffset[MAX_ALLAXES-1];
	unsigned char servoOffSynchronization;
	unsigned char servoOnSynchronization;
	WMX_SYNC_GROUP_STARTUP_TYPE startupType;
	
	WMX_HOME_TYPE homeType;
	WMX_HOME_DIR homeDir;
	double gridSearchVel;
	double gridSearchAcc;
	double gridSearchDec;
	double hSSearchVel;
	double hSSearchAcc;
	double hSSearchDec;
	double hSReverseDistance;
	double homeShiftVel;
	double homeShiftAcc;
	double homeShiftDec;
	double homeShiftDistance;
	unsigned char hSPol;
	unsigned int multipleZP;
	unsigned char multiplierCompensation;
	unsigned char pauseMode;
	double maxHSOnAtStartReverseDistance;
	double maxLSReverseDistance;
	unsigned int zPDistanceCheck;
	unsigned char gantryHomingSingleHS;
	unsigned char gantryHomingSingleLS;
	unsigned char gantryHomingSingleZP;
	unsigned char gantryHomingSingleHSTP;
	unsigned char limitSwitchReverseType;
}WMX_SYNC_GROUP, *PWMX_SYNC_GROUP;

typedef struct{
	WMX_AXIS_COMMAND_MODE axisCommandMode[MAX_ALLAXES];
	unsigned int axisGearRatioNumerator[MAX_ALLAXES];
	unsigned int axisGearRatioDenominator[MAX_ALLAXES];
	unsigned char singleTurnMode[MAX_ALLAXES];
	unsigned int singleTurnEncoderCount[MAX_ALLAXES];
	WMX_STOP_PARAM_MODE stopParamMode[MAX_ALLAXES];
	double stopParamDec[MAX_ALLAXES];
	double stopParamTime[MAX_ALLAXES];
	WMX_STOP_PARAM_MODE stopParamVelMode[MAX_ALLAXES];
	double stopParamVelDec[MAX_ALLAXES];
	double stopParamVelTime[MAX_ALLAXES];
	double maxTrqLimit[MAX_ALLAXES];
	double negativeTrqLimit[MAX_ALLAXES];
	double positiveTrqLimit[MAX_ALLAXES];
	unsigned int axisMultiplier[MAX_ALLAXES];
	unsigned char encoderRangeMode[MAX_ALLAXES];
	int encoderRangeLow[MAX_ALLAXES];
	int encoderRangeHigh[MAX_ALLAXES];
}WMX_OTHER_PARAM, *PWMX_OTHER_PARAM;

typedef struct{
	unsigned char VelocityFeedbackSupport;
	unsigned char VelocityCommandSupport;
	unsigned char VelocityOffsetSupport;
}WMX_AXIS_SUPPORTED_FUNCTION, *PWMX_AXIS_SUPPORTED_FUNCTION;

typedef struct {
	double PitchErrorCompensation;
	double PitchErrorCompensation2D;
}WMX_AXIS_COMPENSATION, *PWMX_AXIS_COMPENSATION;

typedef struct{
	int reserved;
	double version;
	unsigned char InvalidLicenseError;
	int NumLicensedAxes;
	WMX_PE_STATE EngineStatus;
	short ServoOn[MAX_ALLAXES];					// 0: Servo off, 1: Servo on for each axis
	short AmpAlarm[MAX_ALLAXES];				// Alarm reset command for each axis
	long AmpAlarmCode[MAX_ALLAXES];
	short MasterAxis[MAX_ALLAXES];
	long EncoderValue[MAX_ALLAXES];				// pulse: 32 bit counter in Device Driver
	double ActualPosition[MAX_ALLAXES];			// Feedback position based on machine coordinate system
	double PositionCommand[MAX_ALLAXES];		// Position command based on machine coordinate system
	double ActualAxisVelocity[MAX_ALLAXES];		// Calculated or feedback velocity
	double RawPositionCommand[MAX_ALLAXES];		// Position command with compensation
	double RawFeedback[MAX_ALLAXES];			// Feedback position with compensation
	WMX_AXIS_COMPENSATION Compensation[MAX_ALLAXES]; // Various kinds of compensation amount 
	double VelocityCommand[MAX_ALLAXES];		// Velocity command
	double VelocityLag[MAX_ALLAXES];			// Difference between cyclic velocity calculated from position commands and feedback velocity
	double ActualTorque[MAX_ALLAXES];			// Feedback torque
	int ProfileTotalCycleTime[MAX_ALLAXES];
	int ProfileAccCycleTime[MAX_ALLAXES];
	int ProfileCruiseCycleTime[MAX_ALLAXES];
	int ProfileDecCycleTime[MAX_ALLAXES];
	unsigned char HomeSwitch[MAX_ALLAXES];
	unsigned char HardPLS[MAX_ALLAXES];
	unsigned char HardNLS[MAX_ALLAXES];
	unsigned char NearPLS[MAX_ALLAXES];
	unsigned char NearNLS[MAX_ALLAXES];
	unsigned char ExtPLS[MAX_ALLAXES];
	unsigned char ExtNLS[MAX_ALLAXES];
	unsigned char PositiveLimitSwitch[MAX_ALLAXES];
	unsigned char NegativeLimitSwitch[MAX_ALLAXES];
	unsigned char PositiveSoftLimit[MAX_ALLAXES];
	unsigned char NegativeSoftLimit[MAX_ALLAXES];
	unsigned char InPosition[MAX_ALLAXES];
	unsigned char InPosition2[MAX_ALLAXES];
	unsigned char InPosition3[MAX_ALLAXES];
	unsigned char InPosition4[MAX_ALLAXES];
	unsigned char InPosition5[MAX_ALLAXES];
	unsigned char DenFlag[MAX_ALLAXES];
	unsigned char PsetFlag[MAX_ALLAXES];
	unsigned char DPsetFlag[MAX_ALLAXES];
	unsigned long DenDPsetDiff[MAX_ALLAXES];
	unsigned char HomeDone[MAX_ALLAXES];
	unsigned char AxisAccFlag[MAX_ALLAXES];
	unsigned char AxisDecFlag[MAX_ALLAXES];
	unsigned char IntplAccFlag[MAX_ALLAXES];
	unsigned char IntplDecFlag[MAX_ALLAXES];
	WMX_OPSTATE OpState[MAX_ALLAXES]; //Operation state
	WMX_AXIS_COMMAND_MODE AxisCommandMode[MAX_ALLAXES]; //Axis command mode
	double DistanceHStoZP[MAX_ALLAXES];
	double DistanceLStoZP[MAX_ALLAXES];
	unsigned char FollowingErrorAlarm[MAX_ALLAXES];
	unsigned char HomePaused[MAX_ALLAXES];
	WMX_HOME_STATE HomeState[MAX_ALLAXES];
	WMX_HOME_ERROR HomeError[MAX_ALLAXES];
	WMX_AXIS_SYNC_MODE AxisSyncMode[MAX_ALLAXES];
	WMX_AXIS_SUPPORTED_FUNCTION AxisSupportedFunction[MAX_ALLAXES];
	unsigned char CmdReadyFlag[MAX_ALLAXES];
	long LatchedEncoderHSRisingEdge[MAX_ALLAXES];
	long LatchedEncoderHSFallingEdge[MAX_ALLAXES];
	unsigned char GenIn[MAX_IOINSIZE];
	unsigned char GenOut[MAX_IOOUTSIZE_TOTAL];
	char AuxiliaryCmdName[MAX_ALLAXES][MAX_AUXILIARY_DATA_COUNT][MAX_AUXILIARY_DATA_NAME_SIZE];
	int AuxiliaryCmdSize[MAX_ALLAXES][MAX_AUXILIARY_DATA_COUNT];
	unsigned char AuxiliaryCmdData[MAX_ALLAXES][MAX_AUXILIARY_DATA_COUNT][MAX_AUXILIARY_DATA_SIZE];
	char AuxiliaryFbName[MAX_ALLAXES][MAX_AUXILIARY_DATA_COUNT][MAX_AUXILIARY_DATA_NAME_SIZE];
	int AuxiliaryFbSize[MAX_ALLAXES][MAX_AUXILIARY_DATA_COUNT];
	unsigned char AuxiliaryFbData[MAX_ALLAXES][MAX_AUXILIARY_DATA_COUNT][MAX_AUXILIARY_DATA_SIZE];
}WMX_STATUS, *PWMX_STATUS;

typedef struct{
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
	double minimumVelocity;
	double jerkAccRatio;
	double jerkDecRatio;
	double runTime;
	double secondVelocity;
}WMX_POS_BLOCK, *PWMX_POS_BLOCK;

typedef struct{
	short axisCount;
	WMX_POS_BLOCK pos_block[MAX_ALLAXES];
}WMX_MPOS_BLOCK, *PWMX_MPOS_BLOCK;

typedef struct{
	double pos[MAX_SPLINE_DIMENSIONS];
	double time;
}WMX_SPLINE_POINTS, *PWMX_SPLINE_POINTS;

typedef struct{
	unsigned int num_dimensions;
	unsigned int num_points;
	short axis[MAX_SPLINE_DIMENSIONS];
	WMX_SPLINE_POINTS points[MAX_SPLINE_POINTS];
}WMX_SPLINE_BLOCK, *PWMX_SPLINE_BLOCK;

typedef struct{
	double pos;
	double vel;
	double time;
}WMX_PVT_POINTS, *PWMX_PVT_POINTS;

typedef struct{
	short axis;
	unsigned int num_points;
	WMX_PVT_POINTS points[MAX_PVT_POINTS];
}WMX_PVT_BLOCK, *PWMX_PVT_BLOCK;

typedef struct{
	unsigned int num_axes;
	WMX_PVT_BLOCK block[MAX_PVT_INTERPOLATE_AXES];
}WMX_PVT_INTERPOLATE_BLOCK, *PWMX_PVT_INTERPOLATE_BLOCK;

typedef struct{
	short axisCount;
	short axis[MAX_ALLAXES];
}WMX_AXIS_SELECTION, *PWMX_AXIS_SELECTION;

typedef struct{
	int byteAddress;
	short bitOffset;
	int size;
}WMX_IO_ADDRESS, *PWMX_IO_ADDRESS;

typedef struct{
	unsigned char enabled;
	unsigned char active;
	int activeDataIndex;
	WMX_IO_ADDRESS ioAddrs;
}WMX_PSO_STATUS, *PWMX_PSO_STATUS;

typedef struct{
	WMX_COMP_SOURCE_TYPE sType;
	union{
		WMX_IO_ADDRESS ioAddrs;
		unsigned short axis;
	};
}WMX_COMP_SOURCE, *PWMX_COMP_SOURCE;

typedef struct{
	double position;
	double velocity;
}WMX_PVELO_DATA, *PWMX_PVELO_DATA;

typedef struct{
	unsigned char enabled;
	unsigned char active;
	int activeDataIndex;
	double activeVelocityCmd;
	short axis;
}WMX_PVELO_STATUS, *PWMX_PVELO_STATUS;

typedef struct{
	unsigned char active;
	int blockIndex;
	int endBlockIndex;
	int blockCount;
	unsigned int motionCounter;
	unsigned int errorCount;
	unsigned int errorLogIndex[MAX_BUFFER_ERROR_LOG];
	WMX_API_ERROR_CODE errorLogCode[MAX_BUFFER_ERROR_LOG];
}WMX_BUF_STATUS, *PWMX_BUF_STATUS;

typedef struct{
	WMX_BUF_FINISH_TYPE type;
}WMX_BUF_FINISH, *PWMX_BUF_FINISH;

typedef struct{
	WMX_BUF_CONDITION_TYPE type;
	unsigned char polarity;
	WMX_IO_ADDRESS ioAddrs;
	unsigned int eventId;
	short axis;
	double torque;
}WMX_BUF_CONDITION, *PWMX_BUF_CONDITION;

typedef struct{
	unsigned int steps;
	unsigned int currentStep;
	WMX_LIST_STATE state;
	unsigned char recordingState;
}WMX_LIST_STATUS, *PWMX_LIST_STATUS;

typedef struct{
	unsigned char enabled;
	unsigned char homeDone;
}WMX_SYNC_GROUP_STATUS, *PWMX_SYNC_GROUP_STATUS;

typedef struct{
	WMX_LOG_STATE state;
	unsigned int samplesToCollect;
	unsigned int samplesCollected;
	unsigned int samplesWritten;
	double timeToCollect;
	double timeCollected;
	double timeWritten;
}WMX_LOG_STATUS, *PWMX_LOG_STATUS;

typedef struct{
	unsigned char logCmdPos;
	unsigned char logFbPos;
	unsigned char logPeCmdPos;
	unsigned char logPeFbPos;
	unsigned char logCmdVel;
	unsigned char logFbVel;
	unsigned char logPeCmdVel;
	unsigned char logCmdTorque;
	unsigned char logFbTorque;
	unsigned char logHomeOffset;
	unsigned char logInposFlag;
	unsigned char logInpos2Flag;
	unsigned char logInpos3Flag;
	unsigned char logInpos4Flag;
	unsigned char logInpos5Flag;
	unsigned char logDenFlag;
	unsigned char logPsetFlag;
	unsigned char logDPsetFlag;
	unsigned char triggerOnCmdPos;
	unsigned char triggerOnEvent;
	unsigned int triggerEventId;
}WMX_LOG_OPTIONS, *PWMX_LOG_OPTIONS;

typedef struct{
	int byteAddress;
	short bitOffset;
	WMX_IO_FORMAT_TYPE formatType;
}WMX_IO_LOG_FORMAT, *PWMX_IO_LOG_FORMAT;

typedef struct{
	WMX_LOG_STATE state;
	unsigned int samplesWritten;
	unsigned int samplesToWrite;
}WMX_API_CALL_LOG_STATUS, *PWMX_API_CALL_LOG_STATUS;

typedef struct{
	WMX_LOG_STATE state;
	unsigned int samplesToCollect;
	unsigned int samplesCollected;
	double usageRate;
	unsigned short overflowFlag;
}WMX_MEM_LOG_STATUS, *PWMX_MEM_LOG_STATUS;

typedef struct{
	double fbVel;
	double fbTorque;
}WMX_MEM_LOG_AXIS_DATA, *PWMX_MEM_LOG_AXIS_DATA;

typedef struct{
	unsigned char triggerEventCount;
	unsigned int triggerEventId[MAX_MEM_LOG_TRIGGER_EVENT_SIZE];
}WMX_MEM_LOG_OPTIONS, *PWMX_MEM_LOG_OPTIONS;

typedef struct{
	long cycleCounter;
	WMX_MEM_LOG_AXIS_DATA axisData[MAX_MEM_LOG_AXES_SIZE];
}WMX_MEM_LOG_DATAS, *PWMX_MEM_LOG_DATAS;

typedef struct{
	unsigned int count;
	unsigned char overflowFlag;
	WMX_MEM_LOG_DATAS logDatas[MAX_MEM_LOG_DATA_SIZE];
}WMX_MEM_LOG_DATA, *PWMX_MEM_LOG_DATA;

typedef struct{
	short axis;
	unsigned char enabled;
	unsigned char mode;
	unsigned char latched;
	unsigned int numLatchedValue;
	unsigned int latchedValue[MAX_HARDWARE_TOUCH_PROBE_LATCHED_VALUES];
}WMX_HARDWARE_TOUCH_PROBE_STATUS, *PWMX_HARDWARE_TOUCH_PROBE_STATUS;

typedef enum {
	WMX_EVENT_DATA_INPUT_FUNC_NOT_IO_BIT,
	WMX_EVENT_DATA_INPUT_FUNC_OR_IO_BIT,
	WMX_EVENT_DATA_INPUT_FUNC_AND_IO_BIT,
	WMX_EVENT_DATA_INPUT_FUNC_NOT_EVENT,
	WMX_EVENT_DATA_INPUT_FUNC_DELAY_IO_BIT,
	WMX_EVENT_DATA_INPUT_FUNC_DELAY_EVENT,
	WMX_EVENT_DATA_INPUT_FUNC_EQUAL_POS,
	WMX_EVENT_DATA_INPUT_FUNC_GREATER_POS,
	WMX_EVENT_DATA_INPUT_FUNC_LESS_POS,
	WMX_EVENT_DATA_INPUT_FUNC_EQUAL_VEL,
	WMX_EVENT_DATA_INPUT_FUNC_GREATER_VEL,
	WMX_EVENT_DATA_INPUT_FUNC_LESS_VEL,
	WMX_EVENT_DATA_INPUT_FUNC_OP_STATE,
	WMX_EVENT_DATA_INPUT_FUNC_PSET,
	WMX_EVENT_DATA_INPUT_FUNC_DPSET,
	WMX_EVENT_DATA_INPUT_FUNC_DEN
}WMX_EVENT_DATA_INPUT_FUNC;

typedef enum {
	WMX_EVENT_DATA_OUTPUT_FUNC_SET_OUTPUT_BIT,
	WMX_EVENT_DATA_OUTPUT_FUNC_NONE
}WMX_EVENT_DATA_OUTPUT_FUNC;

typedef enum {
	WMX_MOTION_EVENT_DATA_INPUT_FUNC_CHECK_EVENT
}WMX_MOTION_EVENT_DATA_INPUT_FUNC;

typedef enum {
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_STOP_S_AXIS,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_S_POS,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_S_MOV,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_M_POS,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_M_MOV,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_LIN_INT_POS,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_LIN_INT_MOV,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_LIN_INT2_POS,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_LIN_INT2_MOV,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_API_BUFF,
	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC_START_LIST_MOTION
}WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC;

typedef enum {
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_STOP_S_AXIS,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_S_POS,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_S_MOV,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_M_POS,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_M_MOV,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_LIN_INT_POS,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_LIN_INT_MOV,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_LIN_INT2_POS,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_LIN_INT2_MOV,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_API_BUFF,
	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC_START_LIST_MOTION
}WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC;

typedef enum {
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_STOP_S_AXIS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_START_S_POS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_START_S_MOV,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_START_M_POS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_START_M_MOV,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_START_LIN_INT_POS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_START_LIN_INT_MOV,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_START_LIN_INT2_POS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT1_START_LIN_INT2_MOV,

	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_STOP_S_AXIS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_START_S_POS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_START_S_MOV,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_START_M_POS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_START_M_MOV,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_START_LIN_INT_POS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_START_LIN_INT_MOV,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_START_LIN_INT2_POS,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT2_START_LIN_INT2_MOV,

	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT_START_API_BUFF,
	WMX_MOTION_DATA_OUTPUT_FUNC_EXT_EVENT_START_LIST_MOTION
}WMX_MOTION_EVENT_DATA_OUTPUT_FUNC;

typedef struct{
	unsigned char enabled;
	//unsigned int id;
	unsigned int priority;

	WMX_EVENT_DATA_INPUT_FUNC input_Func;
	unsigned int input_ByteAddress;
	unsigned char input_BitAddress;
	unsigned int input_ByteAddress2;
	unsigned char input_BitAddress2;
	unsigned char input_Invert;
	unsigned char input_UseOutput;
	unsigned char input_Invert2;
	unsigned char input_UseOutput2;
	unsigned int input_EventId;
	unsigned int input_DelayTime;
	unsigned int input_Axis;
	double input_Position;
	double input_Velocity;
	unsigned char input_DisablePDir;
	unsigned char input_DisableNDir;
	unsigned char input_UseFeedback;
	WMX_OPSTATE input_OpState;

	WMX_EVENT_DATA_OUTPUT_FUNC output_Func;
	unsigned int output_ByteAddress;
	unsigned char output_BitAddress;
	unsigned char output_Invert;
}WMX_EVENT_DATA, *PWMX_EVENT_DATA;

typedef struct{
	int count;
	unsigned short id[MAX_EVENTS];
}WMX_ALL_EVENT_ID_DATA, *PWMX_ALL_EVENT_ID_DATA;

//MPos block for any profile simple interpolation in motion event1
typedef struct {
	short axis;
	double target;
	double velocity;
	double acc;
	double dec;
	double jerkAcc;
	double jerkDec;
}WMX_MOTION_EXT_EVENT1_INT_BLOCK_IND, *PWMX_MOTION_EXT_EVENT1_INT_BLOCK_IND;

typedef struct {
	short axisCount;
	WMX_PROFILE_TYPE profile;
	WMX_MOTION_EXT_EVENT1_INT_BLOCK_IND pos_block[MAX_ALLAXES];
}WMX_MOTION_EXT_EVENT1_INT_BLOCK, *PWMX_MOTION_EXT_EVENT1_INT_BLOCK;

//MPos block for any profile composite vector interpolation in motion event1
typedef struct {
	short axis;
	double target;
	double velocity;
	double acc;
	double dec;
	double jerkAcc;
	double jerkDec;
}WMX_MOTION_EXT_EVENT1_INT_BLOCK2_IND, *PWMX_MOTION_EXT_EVENT1_INT_BLOCK2_IND;

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
	WMX_MOTION_EXT_EVENT1_INT_BLOCK2_IND pos_block[MAX_ALLAXES];
}WMX_MOTION_EXT_EVENT1_INT_BLOCK2, *PWMX_MOTION_EXT_EVENT1_INT_BLOCK2;

typedef struct{
	unsigned char enabled;
	//unsigned int id;
	unsigned int priority;

	WMX_MOTION_EVENT_DATA_INPUT_FUNC input_Func;
	unsigned int input_EventId;
	unsigned char input_Invert;

	WMX_MOTION_EXT_EVENT1_DATA_OUTPUT_FUNC output_Func;
	union{
		WMX_POS_BLOCK output_Block;
		WMX_MPOS_BLOCK output_MBlock;
		WMX_MOTION_EXT_EVENT1_INT_BLOCK output_Intblock;
		WMX_MOTION_EXT_EVENT1_INT_BLOCK2 output_Intblock2;
		unsigned int output_Channel;
	};
}WMX_MOTION_EXT_EVENT1_DATA, *PWMX_MOTION_EXT_EVENT1_DATA;

//MPos block for any profile simple interpolation in motion event2
typedef struct {
	short axis;
	double target;
	double velocity;
	double acc;
	double dec;
}WMX_MOTION_EXT_EVENT2_INT_BLOCK_IND, *PWMX_MOTION_EXT_EVENT2_INT_BLOCK_IND;

typedef struct {
	short axisCount;
	WMX_PROFILE_TYPE profile;
	double compJerkAccRatio;
	double compJerkDecRatio;
	WMX_MOTION_EXT_EVENT2_INT_BLOCK_IND pos_block[MAX_ALLAXES];
}WMX_MOTION_EXT_EVENT2_INT_BLOCK, *PWMX_MOTION_EXT_EVENT2_INT_BLOCK;

//MPos block for any profile composite vector interpolation in motion event2
typedef struct {
	short axis;
	double target;
	double velocity;
	double acc;
	double dec;
}WMX_MOTION_EXT_EVENT2_INT_BLOCK2_IND, *PWMX_MOTION_EXT_EVENT2_INT_BLOCK2_IND;

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
	WMX_MOTION_EXT_EVENT2_INT_BLOCK2_IND pos_block[MAX_ALLAXES];
}WMX_MOTION_EXT_EVENT2_INT_BLOCK2, *PWMX_MOTION_EXT_EVENT2_INT_BLOCK2;

typedef struct{
	unsigned char enabled;
	//unsigned int id;
	unsigned int priority;

	WMX_MOTION_EVENT_DATA_INPUT_FUNC input_Func;
	unsigned int input_EventId;
	unsigned char input_Invert;

	WMX_MOTION_EXT_EVENT2_DATA_OUTPUT_FUNC output_Func;
	union{
		WMX_POS_BLOCK output_Block;
		WMX_MPOS_BLOCK output_MBlock;
		WMX_MOTION_EXT_EVENT2_INT_BLOCK output_Intblock;
		WMX_MOTION_EXT_EVENT2_INT_BLOCK2 output_Intblock2;
		unsigned int output_Channel;
	};
}WMX_MOTION_EXT_EVENT2_DATA, *PWMX_MOTION_EXT_EVENT2_DATA;

typedef struct{
	unsigned char enabled;
	//unsigned int id;
	unsigned int priority;

	WMX_MOTION_EVENT_DATA_INPUT_FUNC input_Func;
	unsigned int input_EventId;
	unsigned char input_Invert;

	WMX_MOTION_EVENT_DATA_OUTPUT_FUNC output_Func;
	union{
		WMX_POS_BLOCK output_Block;
		WMX_MPOS_BLOCK output_MBlock;
		WMX_MOTION_EXT_EVENT1_INT_BLOCK output_Event1_Intblock;
		WMX_MOTION_EXT_EVENT1_INT_BLOCK2 output_Event1_Intblock2;
		WMX_MOTION_EXT_EVENT2_INT_BLOCK output_Event2_Intblock;
		WMX_MOTION_EXT_EVENT2_INT_BLOCK2 output_Event2_Intblock2;
		unsigned int output_Channel;
	};
}WMX_MOTION_EVENT_DATA, *PWMX_MOTION_EVENT_DATA;

typedef struct{
	int count;
	unsigned short id[MAX_MOTION_EVENTS];
}WMX_ALL_MOTION_EVENT_ID_DATA, *PWMX_ALL_MOTION_EVENT_ID_DATA;

typedef struct{
	int count;
	int idList[MAX_DEVICE_SIZE];
	WMX_DEV_TYPE typeList[MAX_DEVICE_SIZE];
	TCHAR nameList[MAX_DEVICE_SIZE][MAX_DEVICE_NAME_LENGTH];
}WMX_ACT_DEV_LIST, *PWMX_ACT_DEV_LIST;

typedef struct{
	unsigned long cmdid;
	WMX_API_ERROR_CODE errorCode;
}WMX_API_ERROR_LOG, *PWMX_API_ERROR_LOG;

typedef struct{
	int count;
	WMX_API_ERROR_LOG logs[MAX_WMX_API_ERROR_CODE_LOG];
}WMX_API_ERROR_LOG_DATA, *PWMX_API_ERROR_LOG_DATA;

typedef struct{
	short enable;
	int pitchOrigin;
	double pitchInterval;
	int pitchNum;
	double pitchCompValue[MAX_PITCH_ERROR_COMP_POINTS];
}WMX_PITCH_ERROR_COMPENSATION_DATA, *PWMX_PITCH_ERROR_COMPENSATION_DATA;

typedef struct{
	short enable;
	short axis;
	short refAxis;
	int pitchOrigin[2];
	double pitchInterval[2];
	int pitchNum[2];
	double pitchCompValue[MAX_2D_PITCH_ERROR_COMP_POINTS][MAX_2D_PITCH_ERROR_COMP_POINTS];
}WMX_2D_PITCH_ERROR_COMPENSATION_DATA, *PWMX_2D_PITCH_ERROR_COMPENSATION_DATA;

typedef struct{
	unsigned char enabled;
	unsigned int curIndex;
	unsigned int lastIndex;
	double data[MAX_DIRECT_CONTROL_BUFFER_POINTS];
}WMX_DIRECT_CONTROL_AXIS_DATA, *PWMX_DIRECT_CONTROL_AXIS_DATA;

typedef struct{
	WMX_DIRECT_CONTROL_AXIS_DATA dc[MAX_ALLAXES];
}WMX_DIRECT_CONTROL_DATA, *PWMX_DIRECT_CONTROL_DATA;

#endif
