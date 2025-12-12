//WMX v0.987718

#ifndef WMXAPI_DEF
#define WMXAPI_DEF
#include <windows.h>

#ifdef WIN32 
#define WMXAPIFUNC long __stdcall 
#else
#define WMXAPIFUNC HRESULT
#endif

#ifndef MAX_ALLAXES
#define MAX_ALLAXES 64
#endif

#ifndef MAX_IOINSIZE
#define MAX_IOINSIZE 1450
#endif

#ifndef MAX_IOOUTSIZE
#define MAX_IOOUTSIZE 1450
#endif

#ifndef MAX_IOOUTSIZE_VIRTUAL
#define MAX_IOOUTSIZE_VIRTUAL 300
#endif

#ifndef MAX_IOOUTSIZE_TOTAL
#define MAX_IOOUTSIZE_TOTAL (MAX_IOOUTSIZE+MAX_IOOUTSIZE_VIRTUAL)
#endif

#ifndef MAX_IO_LOG_FORMAT_SIZE
#define MAX_IO_LOG_FORMAT_SIZE 100
#endif

#ifndef MAX_VIRTUAL_AXES
#define MAX_VIRTUAL_AXES MAX_ALLAXES
#endif

#ifndef MAX_TOUCHPROBE_CHANNEL
#define MAX_TOUCHPROBE_CHANNEL 64
#endif

#ifndef MAX_PSO_CHANNEL
#define MAX_PSO_CHANNEL 64
#endif 

#ifndef MAX_PSO_DATA
#define MAX_PSO_DATA 128
#endif

#ifndef MAX_PSO_IO_ENC_SIZE
#define MAX_PSO_IO_ENC_SIZE 4
#endif

#ifndef MAX_PVELO_CHANNEL
#define MAX_PVELO_CHANNEL 64
#endif 

#ifndef MAX_PVELO_DATA
#define MAX_PVELO_DATA 20
#endif

#ifndef MAX_PVELO_IO_ENC_SIZE
#define MAX_PVELO_IO_ENC_SIZE 4
#endif

#ifndef MAX_LIST_MOTION_CHANNEL
#define MAX_LIST_MOTION_CHANNEL 100
#endif

#ifndef MAX_LIST_MOTION_STEPS
#define MAX_LIST_MOTION_STEPS 1024
#endif

#ifndef MAX_LIST_MOTION_BUFFER_BYTES
#define MAX_LIST_MOTION_BUFFER_BYTES (512*1024)
#endif

#ifndef MAX_BUFFER_CHANNEL
#define MAX_BUFFER_CHANNEL 100
#endif

#ifndef MAX_BUFFER_BLOCKS
#define MAX_BUFFER_BLOCKS 1024
#endif

#ifndef MAX_BUFFER_BYTES
#define MAX_BUFFER_BYTES (512*1024)
#endif

#ifndef MAX_BUFFER_ERROR_LOG
#define MAX_BUFFER_ERROR_LOG 10
#endif

#ifndef MAX_API_CALL_LOG_BLOCKS
#define MAX_API_CALL_LOG_BLOCKS 1024
#endif

#ifndef MAX_API_CALL_LOG_BYTES
#define MAX_API_CALL_LOG_BYTES (1024*1024)
#endif

#ifndef MAX_CMD_ID
#define MAX_CMD_ID (MAX_ALLAXES * 2)
#endif

#ifndef MAX_LOG_BUFFER_SIZE
#define MAX_LOG_BUFFER_SIZE 1024
#endif

#ifndef MAX_LOG_CHANNEL
#define MAX_LOG_CHANNEL 8
#endif

#ifndef MAX_MEM_LOG_BUFFER_SIZE
#define MAX_MEM_LOG_BUFFER_SIZE 1024
#endif

#ifndef MAX_MEM_LOG_CHANNEL
#define MAX_MEM_LOG_CHANNEL 1
#endif

#ifndef MAX_MEM_LOG_AXES_SIZE
#define MAX_MEM_LOG_AXES_SIZE 32
#endif

#ifndef MAX_MEM_LOG_DATA_SIZE
#define MAX_MEM_LOG_DATA_SIZE 100
#endif

#ifndef MAX_MEM_LOG_IO_INPUT_BYTE_SIZE
#define MAX_MEM_LOG_IO_INPUT_BYTE_SIZE 128
#endif

#ifndef MAX_MEM_LOG_IO_OUTPUT_BYTE_SIZE
#define MAX_MEM_LOG_IO_OUTPUT_BYTE_SIZE 128
#endif

#ifndef MAX_MEM_LOG_TRIGGER_EVENT_SIZE
#define MAX_MEM_LOG_TRIGGER_EVENT_SIZE 32
#endif

#ifndef MAX_LOG_HEADER_BYTES
#define MAX_LOG_HEADER_BYTES 4096
#endif

#ifndef MAX_LOG_HEADER_LINES
#define MAX_LOG_HEADER_LINES 2048
#endif

#ifndef MAX_FLIGHT_RECORDER_BUFFER_SIZE
#define MAX_FLIGHT_RECORDER_BUFFER_SIZE 5000
#endif

#ifndef MAX_SPLINE_DIMENSIONS
#define MAX_SPLINE_DIMENSIONS 3
#endif

#ifndef MAX_SPLINE_POINTS
#define MAX_SPLINE_POINTS 256
#endif

#ifndef MAX_SPATIAL_DIMENSIONS
#define MAX_SPATIAL_DIMENSIONS 3
#endif

#ifndef MAX_EVENTS
#define MAX_EVENTS 4096
#endif

#ifndef MAX_EVENT_INPUTS
#define MAX_EVENT_INPUTS MAX_EVENTS
#endif

#ifndef MAX_EVENT_OUTPUTS
#define MAX_EVENT_OUTPUTS MAX_EVENTS
#endif

#ifndef MAX_MOTION_EVENTS
#define MAX_MOTION_EVENTS 4096
#endif

#ifndef MAX_MOTION_EVENT_INPUTS
#define MAX_MOTION_EVENT_INPUTS MAX_MOTION_EVENTS
#endif

#ifndef MAX_MOTION_EVENT_OUTPUTS
#define MAX_MOTION_EVENT_OUTPUTS MAX_MOTION_EVENTS
#endif

#ifndef MAX_BIT_ARRAY
#define MAX_BIT_ARRAY 1024
#endif

#ifndef MAX_HARDWARE_TOUCH_PROBE_LATCHED_VALUES
#define MAX_HARDWARE_TOUCH_PROBE_LATCHED_VALUES 256
#endif

#ifndef MAX_PROFILE_QUEUE_RING_BUFFER_SIZE
#define MAX_PROFILE_QUEUE_RING_BUFFER_SIZE (MAX_ALLAXES+MAX_ALLAXES+MAX_LIST_MOTION_CHANNEL+1)
#endif

#ifndef MAX_EX_API_HANDL_INSTANCE
#define MAX_EX_API_HANDL_INSTANCE 5
#endif

#ifndef MAX_EX_API_HANDL_QUEUE
#define MAX_EX_API_HANDL_QUEUE 256
#endif

#ifndef MAX_EX_API_HANDL_ERRCODE
#define MAX_EX_API_HANDL_ERRCODE 2048
#endif

#ifndef MAX_WMX_API_ERROR_CODE_LOG
#define MAX_WMX_API_ERROR_CODE_LOG 10
#endif

#ifndef MAX_WMX_API_ERROR_CODE_LOG_BUFFER_SIZE
#define MAX_WMX_API_ERROR_CODE_LOG_BUFFER_SIZE 64
#endif

#ifndef MAX_API_EXECUTION
#define MAX_API_EXECUTION 10
#endif

#ifndef MAX_DATA_CHANNEL_INSTANCES
#define MAX_DATA_CHANNEL_INSTANCES 256 //Maximum number of data channels
#endif

#ifndef MAX_DEVICE_NAME_LENGTH
#define MAX_DEVICE_NAME_LENGTH 50
#endif

#ifndef MAX_PITCH_ERROR_COMP_POINTS
#define MAX_PITCH_ERROR_COMP_POINTS 1024
#endif

#ifndef MAX_2D_PITCH_ERROR_COMP_POINTS
#define MAX_2D_PITCH_ERROR_COMP_POINTS 128
#endif

#ifndef MAX_2D_PITCH_ERROR_COMP_CHANNEL
#define MAX_2D_PITCH_ERROR_COMP_CHANNEL 5
#endif

#ifndef MAX_DEVICE_SIZE
#define MAX_DEVICE_SIZE (MAX_DATA_CHANNEL_INSTANCES + MAX_EX_API_HANDL_INSTANCE)
#endif

#ifndef MAX_SYNC_GROUP
#define MAX_SYNC_GROUP 32
#endif

#ifndef MAX_DIRECT_CONTROL_BUFFER_POINTS
#define MAX_DIRECT_CONTROL_BUFFER_POINTS 1024
#endif

#ifndef MAX_PVT_POINTS
#define MAX_PVT_POINTS 256
#endif

#ifndef MAX_PVT_INTERPOLATE_AXES
#define MAX_PVT_INTERPOLATE_AXES 4
#endif

#ifndef MAX_PATH_INTERPOLATE_POINTS
#define MAX_PATH_INTERPOLATE_POINTS 256
#endif

#ifndef MAX_PATH_INTERPOLATE_DIMENSIONS
#define MAX_PATH_INTERPOLATE_DIMENSIONS 2
#endif

#ifndef MAX_AUXILIARY_DATA_COUNT
#define MAX_AUXILIARY_DATA_COUNT 5
#endif

#ifndef MAX_AUXILIARY_DATA_SIZE
#define MAX_AUXILIARY_DATA_SIZE 8
#endif

#ifndef MAX_AUXILIARY_DATA_NAME_SIZE
#define MAX_AUXILIARY_DATA_NAME_SIZE 16
#endif

typedef enum{
	WMX_SIM_ENGINE,
	WMX_RTEX_ENGINE,
	WMX_EXT_ENGINE
}PLTFRM_TYPE;

typedef enum{
	WMX_AXIS_COUNT_1 = 1,
	WMX_AXIS_COUNT_2 = 2,
	WMX_AXIS_COUNT_4 = 4,
	WMX_AXIS_COUNT_8 = 8,
	WMX_AXIS_COUNT_16 = 16,
	WMX_AXIS_COUNT_32 = 32,
	WMX_AXIS_COUNT_64 = 64
}WMX_AXIS_COUNT;

typedef enum{
	WMX_HOME_CURPOS,
	WMX_HOME_ZP,
	WMX_HOME_HS,				// Search Home Switch location and use as zero point
	WMX_HOME_HS_HS,				// Search Home Switch with rapid search speed and then shift back once found. Search Home Switch once more with grid search speed from somewhere near to the Home Switch and use as zero point
	WMX_HOME_HS_ZP,				// Search Home Switch and then search for the first Z pulse after the Home Switch
	WMX_HOME_HS_REV_ZP,
	WMX_HOME_LS_REV_ZP,
	WMX_HOME_LS_REV_ZP_NEAR,
	WMX_HOME_LS_REV_ZP_EXT,
	WMX_HOME_TOR_LIMIT,
	WMX_HOME_HSTP,
	WMX_HOME_HS_HSTP,
	WMX_HOME_LS,
	WMX_HOME_LS_NEAR,
	WMX_HOME_LS_EXT
}WMX_HOME_TYPE;

typedef enum{
	WMX_LIMITSWITCH_NONE,			//Do not process limit switch
	WMX_LIMITSWITCH_SVO_OFF,		//Servo off immediately
	WMX_LIMITSWITCH_DEC_SVO_OFF,	//Decelerate then servo off
	WMX_LIMITSWITCH_DEC,			//Decelerate
	WMX_LIMITSWITCH_SLOW_DEC_SVO_OFF, //Slow decelerate then servo off
	WMX_LIMITSWITCH_SLOW_DEC,		//Slow decelerate
	WMX_LIMITSWITCH_SEPARATE_PLSNLS //
}WMX_LIMITSWITCH_TYPE;

typedef enum{
	WMX_MASTER_DESYNC_NO_ACTION, //No action on master if slave desyncs
	WMX_MASTER_DESYNC_SVO_OFF, //Turn master servo off if slave desyncs
	WMX_MASTER_DESYNC_DEC_SVO_OFF, //Decelerate, then turn master servo off if slave desyncs
	WMX_MASTER_DESYNC_DEC //Decelerate and stop master if slave desyncs
}WMX_MASTER_DESYNC_TYPE;

typedef enum{
	WMX_SLAVE_DESYNC_NO_ACTION, //No action on slave if master desyncs
	WMX_SLAVE_DESYNC_SVO_OFF, //Turn slave servo off if master desyncs
	WMX_SLAVE_DESYNC_RESOLVE_SYNC, //Resolve sync if master desyncs
}WMX_SLAVE_DESYNC_TYPE;

typedef enum{
	WMX_OPSTATE_IDLE,
	WMX_OPSTATE_POS,
	WMX_OPSTATE_JOG,
	WMX_OPSTATE_HOME,
	WMX_OPSTATE_SYNC,
	WMX_OPSTATE_GANTRY_HOME,
	WMX_OPSTATE_STOPPING,
	WMX_OPSTATE_INTPL,
	WMX_OPSTATE_DVC,
	WMX_OPSTATE_LIST,
	WMX_OPSTATE_CLV,
	WMX_OPSTATE_TRQ,
	WMX_OPSTATE_DIRECT_CONTROL,
	WMX_OPSTATE_PVT,
	WMX_OPSTATE_OFFLINE
}WMX_OPSTATE;

typedef enum{
	WMX_AXIS_COMMAND_MODE_POSITION = 0,
	WMX_AXIS_COMMAND_MODE_VELOCITY,
	WMX_AXIS_COMMAND_MODE_TORQUE
}WMX_AXIS_COMMAND_MODE, *PWMX_AXIS_COMMAND_MODE;

typedef enum{
	WMX_AXIS_SYNC_MODE_NOT_SYNC,
	WMX_AXIS_SYNC_MODE_SYNC_NO_OFFSET,
	WMX_AXIS_SYNC_MODE_SYNC_VELOCITY_OFFSET,
	WMX_AXIS_SYNC_MODE_SYNC_POSITION_OFFSET
}WMX_AXIS_SYNC_MODE, *PWMX_AXIS_SYNC_MODE;

/**
 * Status of P.E. State machine
 */
typedef enum wmx_pe_state{
	WMX_PE_ST_IDLE = 0,				/**< Engine is in an idle state. Engine not running.*/
	WMX_PE_ST_START,					/**< Engine is trying to start up.*/
	WMX_PE_ST_RUNNING,					/**< Engine is running, communication is not started yet.*/
	WMX_PE_ST_START_COMMUNICATION,		/**< Starting the communication.*/
	WMX_PE_ST_COMMUNICATING,			/**< Communicating. Motion API can be executed with this mode.*/
	WMX_PE_ST_STOP_COMMUNICATION,		/**< Engine is going to stop.*/
	WMX_PE_ST_SHUTDOWN,				/**< Engine is about to shut down.*/
	WMX_PE_ST_ERROR					/**< Engine got serious error.*/
}WMX_PE_STATE;						/**< */

typedef enum{
	WMX_COMP_DISABLE,
	WMX_COMP_EQUAL,
	WMX_COMP_EQUAL_PDIR,
	WMX_COMP_EQUAL_NDIR,
	WMX_COMP_MORE_THAN,
	WMX_COMP_LESS_THAN,
}WMX_COMP_TYPE, *PWMX_COMP_TYPE;

typedef enum{
	WMX_COMP_SRC_POS_CMD,
	WMX_COMP_SRC_POS_FB,
	WMX_COMP_SRC_FOL_ERR,
	//WMX_COMP_SRC_IO_ENC
}WMX_COMP_SOURCE_TYPE, *PWMX_COMP_SOURCE_TYPE;

typedef enum{
	WMX_HOME_DIR_NORM,
	WMX_HOME_DIR_REV
}WMX_HOME_DIR;

typedef enum{
	WMX_HOME_STATE_IDLE,
	WMX_HOME_STATE_ZP_SEARCH,
	WMX_HOME_STATE_ZP_SEARCH_REV,
	WMX_HOME_STATE_ZP_SEARCH_REV_PAUSE,
	WMX_HOME_STATE_HS_SEARCH,
	WMX_HOME_STATE_HS_SEARCH_PAUSE,
	WMX_HOME_STATE_HS_AND_ZP_SEARCH,
	WMX_HOME_STATE_HS_AND_ZP_SEARCH_PAUSE,
	WMX_HOME_STATE_LS_SEARCH,
	WMX_HOME_STATE_LS_SEARCH_PAUSE,
	WMX_HOME_STATE_HS_CLEAR_REV,
	WMX_HOME_STATE_HS_CLEAR_REV_PAUSE,
	WMX_HOME_STATE_HS_FALLING_EDGE_SEARCH_REV,
	WMX_HOME_STATE_HS_FALLING_EDGE_SEARCH_REV_PAUSE,
	WMX_HOME_STATE_LS_FALLING_EDGE_SEARCH_REV,
	WMX_HOME_STATE_LS_FALLING_EDGE_SEARCH_REV_PAUSE,
	WMX_HOME_STATE_HSTP_SEARCH,
	WMX_HOME_STATE_HSTP_SEARCH_PAUSE,
	WMX_HOME_STATE_SECOND_HS_SEARCH,
	WMX_HOME_STATE_SECOND_HS_SEARCH_PAUSE,
	WMX_HOME_STATE_SECOND_HSTP_SEARCH,
	WMX_HOME_STATE_SECOND_HSTP_SEARCH_PAUSE,
	WMX_HOME_STATE_HOME_SHIFT,
	WMX_HOME_STATE_HOME_SHIFT_PAUSE,
	WMX_HOME_STATE_CANCEL,
	WMX_HOME_STATE_OTHER
}WMX_HOME_STATE;

typedef enum{
	WMX_HOME_ERROR_NONE = 0,
	WMX_HOME_ERROR_LS_TRIGGERED,
	WMX_HOME_ERROR_MAX_LS_REVERSE_DISTANCE_TRAVELED,
	WMX_HOME_ERROR_MAX_HS_ON_AT_START_REVERSE_DISTANCE_TRAVELED,
	WMX_HOME_ERROR_ZPULSE_DISTANCE_CHECK_ERROR
}WMX_HOME_ERROR;

typedef enum{
	WMX_PROFILE_TYPE_TRAPEZOIDAL,
	WMX_PROFILE_TYPE_SCURVE,
	WMX_PROFILE_TYPE_JERKLIMITED,
	WMX_PROFILE_TYPE_SIN,
	WMX_PROFILE_TYPE_PARABOLIC,
	WMX_PROFILE_TYPE_ADVANCEDS
}WMX_PROFILE_TYPE;

typedef enum{
	WMX_IO_ACTION_TYPE_POS,
	WMX_IO_ACTION_TYPE_JERKPOS,
	WMX_IO_ACTION_TYPE_STOP,
	WMX_IO_ACTION_TYPE_JOG
}WMX_IO_ACTION_TYPE;

typedef enum{
	WMX_ALARM_FOLLOWING_ERROR_TYPE_NOACTION,
	WMX_ALARM_FOLLOWING_ERROR_TYPE_QSTOP
}WMX_ALARM_FOLLOWING_ERROR_TYPE;

typedef enum{
	WMX_ALARM_VELOCITY_FOLLOWING_ERROR_TYPE_NOACTION,
	WMX_ALARM_VELOCITY_FOLLOWING_ERROR_TYPE_QSTOP,
	WMX_ALARM_VELOCITY_FOLLOWING_ERROR_TYPE_WARNING
}WMX_ALARM_VELOCITY_FOLLOWING_ERROR_TYPE;

typedef enum{
	WMX_LOG_STATE_IDLE, //Not currently logging data
	WMX_LOG_STATE_RUNNING, //Currently logging data
	WMX_LOG_STATE_WRITE_FAIL, //Stopped because of write fail
	WMX_LOG_STATE_BUFFER_OVERFLOW, //Stopped because of buffer overflow
	WMX_LOG_STATE_FINISHED //Finished logging data
}WMX_LOG_STATE;

typedef enum{
	WMX_IO_FORMAT_TYPE_CHAR,
	WMX_IO_FORMAT_TYPE_UCHAR,
	WMX_IO_FORMAT_TYPE_SHORT,
	WMX_IO_FORMAT_TYPE_USHORT,
	WMX_IO_FORMAT_TYPE_INT,
	WMX_IO_FORMAT_TYPE_UINT,
	WMX_IO_FORMAT_TYPE_LONG,
	WMX_IO_FORMAT_TYPE_ULONG,
	WMX_IO_FORMAT_TYPE_FLOAT,
	WMX_IO_FORMAT_TYPE_DOUBLE
}WMX_IO_FORMAT_TYPE;

typedef enum{
	WMX_BUF_FINISH_TYPE_IMMEDIATE,
	WMX_BUF_FINISH_TYPE_AXES_IDLE,
	WMX_BUF_FINISH_TYPE_MOTION_STARTED
}WMX_BUF_FINISH_TYPE, *PWMX_BUF_FINISH_TYPE;

typedef enum{
	WMX_BUF_CONDITION_TYPE_NONE,
	WMX_BUF_CONDITION_TYPE_IO_INPUT,
	WMX_BUF_CONDITION_TYPE_IO_OUTPUT,
	WMX_BUF_CONDITION_TYPE_EVENT,
	WMX_BUF_CONDITION_TYPE_MIN_TORQUE
}WMX_BUF_CONDITION_TYPE;

typedef enum{
	WMX_LIST_STATE_IDLE, //Not in any other state
	WMX_LIST_STATE_RUNNING, //Currently running list motion
	WMX_LIST_STATE_START_FAILED, //Failed to start list motion because a commanded axis
	                             //was not in idle state, was not a position command axis,
								 //or was not on.
	WMX_LIST_STATE_PAUSED, //Currently paused running list motion
	WMX_LIST_STATE_PROFILE_FAILED, //Profile generation failed during execution of current step,
	                               //list motion is aborted
	WMX_LIST_STATE_FOLLOWING_ERROR //Following error was detected in one of the commanded axes
}WMX_LIST_STATE;

typedef enum{
	WMX_TRIGGER_TYPE_REMAINING_TIME,
	WMX_TRIGGER_TYPE_REMAINING_DISTANCE,
	WMX_TRIGGER_TYPE_SAME_TIME_COMPLETION,
	WMX_TRIGGER_TYPE_COMPLETED_DISTANCE,
	WMX_TRIGGER_TYPE_STAGGERED_TIME_COMPLETION,
	WMX_TRIGGER_TYPE_STAGGERED_DISTANCE_COMPLETION
}WMX_TRIGGER_TYPE;

typedef enum{
	WMX_STOP_PARAM_MODE_NONE,
	WMX_STOP_PARAM_MODE_QUICK_STOP,
	WMX_STOP_PARAM_MODE_USER_DEFINED,
	WMX_STOP_PARAM_MODE_TIME
}WMX_STOP_PARAM_MODE;

typedef enum{
	WMX_ESTOP_FINAL,
	WMX_ESTOP_LEVEL1
}WMX_ESTOP_LEVEL;

typedef enum{
	WMX_DEV_TYPE_NORMAL_DEVICE,
	WMX_DEV_TYPE_EXPEDITED_DEVICE,
	WMX_DEV_TYPE_UNKNOWN_DEVICE
}WMX_DEV_TYPE;

typedef enum{
	WMX_SYNC_GROUP_STARTUP_TYPE_NORMAL,
	WMX_SYNC_GROUP_STARTUP_TYPE_CATCH_UP
}WMX_SYNC_GROUP_STARTUP_TYPE;

typedef enum {
	WMX_PITCH_ERROR_COMP_STATE_DISABLE,
	WMX_PITCH_ERROR_COMP_STATE_ENABLE,
	WMX_PITCH_ERROR_COMP_STATE_ERROR
}WMX_PITCH_ERROR_COMP_STATE;

typedef enum {
	WMX_PATH_INTERPOLATE_SEGMENT_TYPE_LINEAR,
	WMX_PATH_INTERPOLATE_SEGMENT_TYPE_CIRCULAR
}WMX_PATH_INTERPOLATE_SEGMENT_TYPE;

typedef enum{
	WMX_API_ERROR_NONE = 0x0, //No error
	WMX_API_CALL_ERROR = 0x5, //Error, use GetLastError to obtain detailed error code
	
	//Error codes for errors returned by GetLastError when CreateDevice fails
	WMX_API_ERROR_RTX_PROP_ERROR,
	WMX_API_ERROR_RTX_NOT_RUNNING,
	WMX_API_ERROR_MEM_ALLOC,
	WMX_API_ERROR_CT_STAT_LOCK,
	WMX_API_ERROR_CT_STSH_MEM,
	WMX_API_ERROR_CT_CF_SYNC,
	WMX_API_ERROR_CT_EVTH_CF_SYNC,
	WMX_API_ERROR_PLATFORM_NOT_FOUND,
	WMX_API_ERROR_PE_NOT_FOUND,
	WMX_API_ERROR_PE_CP,
	WMX_API_ERROR_PE_START_TIMEOUT,
	WMX_API_ERROR_PE_START,
	WMX_API_ERROR_CT_CTRL_MUTEX,
	WMX_API_ERROR_CT_CTRL_EV,
	WMX_API_ERROR_CT_CTRL_WT_EV,
	WMX_API_ERROR_CT_CTRL_SHMEM,
	WMX_API_ERROR_APIHANLDER_NOT_FOUND,
	WMX_API_ERROR_APIHANDLER_CP,
	WMX_API_ERROR_APIHANDLER_START_TIMEOUT,
	WMX_API_ERROR_APIHANDLER_START,
	WMX_API_ERROR_APIHANDLER_TIMEOUT,
	WMX_API_ERROR_PE_HANDLE,
	WMX_API_ERROR_APIHANDLER_HANDLE,
	WMX_API_ERROR_OP_STAT_LOCK,
	WMX_API_ERROR_OP_STAT_MUTEX,
	WMX_API_ERROR_OP_STSH_MEM,
	WMX_API_ERROR_OP_EVTH_SYNC,
	WMX_API_ERROR_OP_MEVTH_SYNC,
	WMX_API_ERROR_OP_PROFTH_SYNC,
	WMX_API_ERROR_OP_STTH_SYNC,
	WMX_API_ERROR_OP_BUFTH_SYNC,
	WMX_API_ERROR_OP_DVWTTH_SYNC,
	WMX_API_ERROR_OP_LGTH_SYNC,
	WMX_API_ERROR_OP_CTRL_EV,
	WMX_API_ERROR_OP_CTRL_WT_EV,
	WMX_API_ERROR_OP_CTRL_SHMEM,
	WMX_API_ERROR_CREATEDEVICE_LOCK,
	WMX_API_ERROR_CREATEPROCESS_CLOSE_FAIL,
	WMX_API_ERROR_CLOSEDEVICE_LOCK,
	WMX_API_ERROR_CLOSEDEVICE_MODE_ERROR,
	WMX_API_ERROR_DEVICE_ALREADY_EXISTS,
	WMX_API_ERROR_ENGINE_FILE_PATH_NOT_FULLY_QUALIFIED,

	//Error codes for errors returned by GetLastError
	WMX_API_ERROR_CTRLCHANNEL_ERROR = 0x10000000, //Control channel error
	WMX_API_ERROR_DATACHANNEL_ERROR = 0x10000001, //Data channel error
	WMX_API_ERROR_COMM_NOT_STARTED = 0x10000002, //Communication is not started
	WMX_API_ERROR_DEVICE_IS_NULL = 0x10000003, //Device handler is null
	WMX_API_ERROR_ENGINE_START_ERROR = 0x10000004, //Failed to start engine
	WMX_API_ERROR_DEVICE_ID_OUT_OF_RANGE, //Device ID is out of range
	WMX_API_ERROR_COMM_NOT_STOPPED, //Communication is not stopped
	WMX_API_ERROR_ENGINE_STATE_INVALID, //Engine is in invalid state
	WMX_API_ERROR_PARAMETER_SETTINGS_INVALID, //Invalid parameter settings
	WMX_API_ERROR_SERVO_ON_ERROR, //Error turning servo on or off
	WMX_API_ERROR_FUNCTION_NOT_SUPPORTED,//Function is not supported
	WMX_API_ERROR_AXIS_BUSY_RECEIVING_ANOTHER_API_COMMAND, //Axis is currently busy receiving a different API command
	WMX_API_ERROR_AXIS_IS_SYNC_SLAVE, //One or more specified axes are sync slave axes
	WMX_API_ERROR_AXIS_IS_SYNC_MASTER, //One or more specified axes are sync master axes
	WMX_API_ERROR_AXIS_NOT_SERVO_ON, //One or more specified axes are in servo off state
	WMX_API_ERROR_AXIS_NOT_SERVO_OFF, //One or more specified axes are in servo on state
	WMX_API_ERROR_AXIS_NOT_IDLE_OR_POS_STATE, //One or more axes are not in idle or pos state
	WMX_API_ERROR_AXIS_NOT_POS_STATE, //One or more axes are not in pos state
	WMX_API_ERROR_AXIS_NOT_IDLE_STATE, //One or more axes are not in idle state
	WMX_API_ERROR_AXIS_NOT_IDLE_OR_JOG_STATE, //One or more axes are not in idle or jog state
	WMX_API_ERROR_AXIS_NOT_IDLE_OR_DVC_STATE, //One or more axes are not in idle or DVC (velocity) state
	WMX_API_ERROR_AXIS_NOT_IDLE_OR_INTPL_STATE, //One or more axes are not in idle or interpolation state
	WMX_API_ERROR_AXIS_NOT_DVC_STATE, //One or more axes are not in DVC (velocity) state
	WMX_API_ERROR_AXIS_NOT_POS_OR_JOG_OR_DVC_STATE, //One or more axes are not in pos, jog, or DVC (velocity) state
	WMX_API_ERROR_AXIS_NOT_JOG_STATE, //One or more axes are not in jog state
	WMX_API_ERROR_AXIS_NOT_TRQ_STATE, //One or more axes are not in torque state
	WMX_API_ERROR_AXIS_NOT_IDLE_OR_TRQ_STATE, //One or more axes are not in idle or torque state
	WMX_API_ERROR_AXIS_NOT_IDLE_OR_SYNC_STATE, //One or more axes are not in idle or sync state
	WMX_API_ERROR_AXIS_NOT_POSITION_MODE, //One or more axes are not in position control mode
	WMX_API_ERROR_AXIS_NOT_VELOCITY_MODE, //One or more axes are not in velocity control mode
	WMX_API_ERROR_AXIS_NOT_TORQUE_MODE, //One or more axes are not in torque control mode
	WMX_API_ERROR_AXIS_NOT_POSITION_OR_VELOCITY_MODE, //One or more axes are not in position or velocity control mode
	WMX_API_ERROR_AXIS_NOT_SYNC_SLAVE, //One or more specified axes are not sync slave axes
	WMX_API_ERROR_AXIS_NOT_CLV_SLAVE, //One or more specified axes are not CLV slave axes
	WMX_API_ERROR_CLV_MINR_TOO_SMALL, //Specified minR value is too small for CLV operation
	WMX_API_ERROR_CLV_POSITIVEMAXR_TOO_SMALL, //Specified positiveMaxR value is too small for CLV operation
	WMX_API_ERROR_CLV_NEGATIVEMAXR_TOO_SMALL, //Specified negativeMaxR value is too small for CLV operation
	WMX_API_ERROR_AXIS_INVALID_CURRENT_VELOCITY, //One or more specified axes' current velocity is invalid
	WMX_API_ERROR_AXIS_NOT_IN_MOTION, //One or more specified axes are not in motion
	WMX_API_ERROR_AXIS_OUT_OF_RANGE, //One or more axes are out of range
	WMX_API_ERROR_AXIS_NOT_HOME_STATE, //One or more axes are not in home state
	WMX_API_ERROR_AXIS_NOT_PAUSED_HOMING, //One or more axes are not paused during homing
	WMX_API_ERROR_AXIS_COUNT_OUT_OF_RANGE, //Axis count is out of range
	WMX_API_ERROR_AXIS_DOES_NOT_SUPPORT_POSITION_MODE, //Axis does not support position mode
	WMX_API_ERROR_AXIS_DOES_NOT_SUPPORT_VELOCITY_MODE, //Axis does not support velocity mode
	WMX_API_ERROR_AXIS_NOT_PAUSED, //One or more axes are not paused
	WMX_API_ERROR_AXIS_HOME_TYPE_NOT_SUPPORTED_IN_GANTRY_MODE, //One or more axes' home types does not support gantry mode homing
	WMX_API_ERROR_INVALID_PROFILE, //One or more axes have an invalid profile
	WMX_API_ERROR_IO_ADDRESS_OUT_OF_RANGE, //I/O address out of range
	WMX_API_ERROR_CHANNEL_OUT_OF_RANGE, //Channel out of range
	WMX_API_ERROR_CHANNEL_UNINITIALIZED, //Channel has not been initialized
	WMX_API_ERROR_CHANNEL_EXECUTING_LIST_MOTION, //Channel is currently executing list motion
	WMX_API_ERROR_CHANNEL_NOT_EXECUTING_LIST_MOTION, //Channel is currently not executing list motion
	WMX_API_ERROR_CHANNEL_RECORDING_LIST_MOTION, //Channel is currently recording list motion
	WMX_API_ERROR_CHANNEL_REPEAT_EXECUTION_DISABLED_LIST_MOTION, //Channel can not repeat execution of list motion
	WMX_API_ERROR_CHANNEL_NOT_RECORDING_LIST_MOTION, //Channel is currently not recording list motion commands
	WMX_API_ERROR_CHANNEL_EMPTY_LIST_MOTION, //Channel contains no list motion commands
	WMX_API_ERROR_CHANNEL_NOT_PAUSED, //Channel is currently not paused
	WMX_API_ERROR_CHANNEL_PAUSED, //Channel is currently paused
	WMX_API_ERROR_CHANNEL_MAX_LIST_MOTION_STEPS_REACHED, //Channel has reached the maximum number of list motion steps
	WMX_API_ERROR_CHANNEL_MAX_LIST_MOTION_DATA_REACHED, //Channel has reached the maximum number of list motion bytes
	WMX_API_ERROR_CHANNEL_STEP_OUT_OF_RANGE, //Step used to query error code is out of range
	WMX_API_ERROR_APIBUFFER_STARTED, //API buffer is already started
	WMX_API_ERROR_APIBUFFER_STOPPED, //API buffer is already stopped
	WMX_API_ERROR_APIBUFFER_EMPTY, //API buffer is empty
	WMX_API_ERROR_APIBUFFER_MAX_BLOCKS_REACHED, //API buffer has reached the maximum number of buffer blocks
	WMX_API_ERROR_APIBUFFER_MAX_DATA_REACHED, //API buffer has reached the maximum number of buffer data bytes
	WMX_API_ERROR_APIBUFFER_EXECUTING_COMMANDS, //API buffer has been started and is executing commands
	WMX_API_ERROR_APIBUFFER_INDEX_OUT_OF_RANGE, //Index used to query error code is out of range
	WMX_API_ERROR_APIBUFFER_REPEAT_EXECUTION_DISABLED, //API buffer repeat execution is disabled
	WMX_API_ERROR_ARGUMENT_OUT_OF_RANGE, //One or more arguments are out of range
	WMX_API_ERROR_ARGUMENT_IS_NULL, //One or more arguments are null
	WMX_API_ERROR_ARGUMENT_AXIS_OUT_OF_RANGE, //One or more axis arguments are out of range
	WMX_API_ERROR_ARGUMENT_PROFILE_OUT_OF_RANGE, //One or more profile arguments are out of range
	WMX_API_ERROR_ARGUMENT_VELOCITY_OUT_OF_RANGE, //One or more velocity arguments are out of range
	WMX_API_ERROR_ARGUMENT_ACC_OUT_OF_RANGE, //One or more acceleration arguments are out of range
	WMX_API_ERROR_ARGUMENT_DEC_OUT_OF_RANGE, //One or more deceleration arguments are out of range
	WMX_API_ERROR_ARGUMENT_JERKACC_OUT_OF_RANGE, //One or more jerk acceleration arguments are out of range
	WMX_API_ERROR_ARGUMENT_JERKDEC_OUT_OF_RANGE, //One or more jerk deceleration arguments are out of range
	WMX_API_ERROR_ARGUMENT_JERKACCRATIO_OUT_OF_RANGE, //One or more jerk acceleration ratio arguments are out of range
	WMX_API_ERROR_ARGUMENT_JERKDECRATIO_OUT_OF_RANGE, //One or more jerk deceleration ratio arguments are out of range
	WMX_API_ERROR_ARGUMENT_STARTINGVELOCITY_OUT_OF_RANGE, //One or more starting velocity arguments are out of range
	WMX_API_ERROR_ARGUMENT_ENDVELOCITY_OUT_OF_RANGE, //One or more end velocity arguments are out of range
	WMX_API_ERROR_ARGUMENT_SECONDVELOCITY_OUT_OF_RANGE, //One or more second velocity arguments are out of range
	WMX_API_ERROR_ARGUMENT_RUNTIME_OUT_OF_RANGE, //One or more run time arguments are out of range
	WMX_API_ERROR_ARGUMENT_TRIGGERTYPE_OUT_OF_RANGE, //One or more trigger type arguments are out of range
	WMX_API_ERROR_ARGUMENT_TRIGGERAXIS_OUT_OF_RANGE, //One or more trigger axis arguments are out of range
	WMX_API_ERROR_ARGUMENT_TRIGGERVALUE_OUT_OF_RANGE, //One or more trigger value arguments are out of range
	WMX_API_ERROR_ACCEL_DECEL_COULD_NOT_BE_CALCULATED, //Acceleration or deceleraiton could not be calculated
	WMX_API_ERROR_RADIUS_COULD_NOT_BE_CALCULATED, //Radius could not be calculated
	WMX_API_ERROR_PREVIOUS_SETTINGS_BEING_APPLIED, //Previous settings are still being applied
	WMX_API_ERROR_CURRENTLY_COLLECTING_LOG_DATA, //Currently collecting log data, stop collection first
	WMX_API_ERROR_CURRENTLY_NOT_COLLECTING_LOG_DATA, //Currently not collecting log data.
	WMX_API_ERROR_NO_FREE_VIRTUAL_AXIS, //There are no free virtual axes
	WMX_API_ERROR_NO_FREE_COMMAND_ID, //There are no free command IDs
	WMX_API_ERROR_PARAMETER_OUT_OF_RANGE, //Specified parameter is out of range
	WMX_API_ERROR_ID_OUT_OF_RANGE, //Specified ID is out of range
	WMX_API_ERROR_ID_BUSY_UPDATING, //Specified ID is busy updating from previous API call
	WMX_API_ERROR_ID_NOT_DEFINED, //Specified ID is not defined yet
	WMX_API_ERROR_LENGTH_OUT_OF_RANGE, //Specified length out of range
	WMX_API_ERROR_MAX_EVENT_DEFINITIONS_DEFINED, //Maximum number of event definitions defined
	WMX_API_ERROR_MAX_EVENT_INPUTS_DEFINED, //Maximum number of event inputs defined
	WMX_API_ERROR_MAX_EVENT_OUTPUTS_DEFINED, //Maximum number of event outputs defined
	WMX_API_ERROR_MAX_EVENT_BIT_ARRAY_USED, //Maximum number of event bit array data used
	WMX_API_ERROR_MAX_MOTION_EVENT_DEFINITIONS_DEFINED, //Maximum number of motion event definitions defined
	WMX_API_ERROR_MAX_MOTION_EVENT_INPUTS_DEFINED, //Maximum number of motion event inputs defined
	WMX_API_ERROR_MAX_MOTION_EVENT_OUTPUTS_DEFINED, //Maximum number of motion event outputs defined
	WMX_API_ERROR_MAX_MOTION_EVENT_BIT_ARRAY_USED, //Maximum number of motion event bit array data used
	WMX_API_ERROR_OPENING_WAIT_EVENT, //Error opening wait for axis idle or command completion event
	WMX_API_ERROR_AXIS_NOT_SINGLE_TURN, //One or more axes are not single turn axes
	WMX_API_ERROR_SYNC_AXIS_SINGLE_TURN_STATE_DOES_NOT_MATCH, //Master and slave axis single turn mode and encoder count do not match
	WMX_API_ERROR_AXIS_SERVO_ON_SINCE_COMM_START, //One or more axes have been turned on since communication start
	WMX_API_ERROR_AXIS_NO_MOTION, //One or more axes have no motion
	WMX_API_ERROR_RESOURCE_IN_USE, //Resources required for the API could not be obtained
	WMX_API_ERROR_SPECIAL_PARAM_FN_OUT_OF_RANGE, //Special parameter fn out of range
	WMX_API_ERROR_ROOT_DEVICE_CLOSED, //Root device has been closed, engine must be restarted
	WMX_API_ERROR_PROFILE_ERROR_TIMEOUT, //Profile failed to complete
	WMX_API_ERROR_PROFILE_ERROR_ON_TARGET_POS, //Profile error - on target position
	WMX_API_ERROR_PROFILE_ERROR_USAGE_ERROR, //Profile error - usage error
	WMX_API_ERROR_PROFILE_ERROR_ACCELERATION_IS_INVALID, //Profile error - acceleration is invalid
	WMX_API_ERROR_PROFILE_ERROR_DECELERATION_IS_INVALID, //Profile error - deceleration is invalid
	WMX_API_ERROR_PROFILE_ERROR_JERK_IS_INVALID, //Profile error - jerk is invalid
	WMX_API_ERROR_PROFILE_ERROR_VELOCITY_IS_INVALID, //Profile error - velocity is invalid
	WMX_API_ERROR_PROFILE_ERROR_NULL_CALCULATION, //Profile error - null calculation
	WMX_API_ERROR_PROFILE_ERROR_NO_MOTION, //Profile error - no motion
	WMX_API_ERROR_PROFILE_ERROR_USER_RANGE_IS_INVALID, //Profile error - user range is invalid
	WMX_API_ERROR_PROFILE_ERROR_OTHER, //Profile error - other error
	WMX_API_ERROR_PROFILE_ERROR_UNKNOWN_ERROR, //Profile error - unknown error
	WMX_API_ERROR_PROFILE_ERROR_SETUP_FAILED, //Profile error - profile setup failed
	WMX_API_ERROR_PROFILE_ERROR_OVERTRAVEL_CANCEL, //Profile error - canceled because of overrun
	WMX_API_ERROR_FILE_OPERATION_FAILED, //Failed file operation
	WMX_API_ERROR_SYNC_GROUP_ID_OUT_OF_RANGE, //Sync group ID out of range
	WMX_API_ERROR_SYNC_GROUP_IS_ENABLED, //Sync group is enabled
	WMX_API_ERROR_SYNC_GROUP_MASTER_AXIS_UNDEFINED, //Sync group master axis is undefined
	WMX_API_ERROR_SYNC_GROUP_AXIS_IS_IN_ANOTHER_GROUP, //Sync group axis is in another group
	WMX_API_ERROR_LICENSE_VALIDATION_FAILED, //License validation failed
	WMX_API_ERROR_LICENSE_VALIDATION_UNKNOWN, //License validation result unknown
	WMX_API_ERROR_LICENSE_VALIDATION_NOT_WMX_OR_MXR_LICENSE, //License is not a WMX or MXR license
	WMX_API_ERROR_PICTH_ERROR_COMP_IS_ENABLED, //Pitch error compensation is enable
	WMX_API_ERROR_PICTH_ERROR_COMP_CAN_NOT_DISABLED, //Pitch error compensation can not be disable
	WMX_API_ERROR_PICTH_ERROR_COMP_DATA_IS_NOT_SET, //Pitch error compensation data is not set
	WMX_API_ERROR_OPEN_SHARED_MEMORY_ERROR, //Open shared memory error
	WMX_API_ERROR_AXIS_NOT_DIRECT_CONTROL_STATE, //One or more axes are not in direct control state
	WMX_API_ERROR_AXIS_MULTIPLIER_NOT_EQUAL, //One or more axes have different axis multipliers
	WMX_API_ERROR_POINT_COUNT_OUT_OF_RANGE, //Point count out of range
	WMX_API_ERROR_AUX_INDEX_OUT_OF_RANGE, //Auxiliary command/feedback index out of range
	WMX_API_ERROR_AUX_ADDRESS_OUT_OF_RANGE, //Auxiliary command/feedback address out of range

	WMX_API_ERROR_EXPEDITED_API_QUEUE_LOCK_ERROR, //Expedited api queue lock error
	WMX_API_ERROR_EXPEDITED_API_QUEUE_WAIT_TIMEOUT, //Expedited api queue lock timeout
	WMX_API_ERROR_EXPEDITED_API_QUEUE_IS_FULL, //Expedited api queue is full
	WMX_API_ERROR_EXPEDITED_API_GET_ERROR_CODE_NO_MATCH, //No matched error code is obtained
	WMX_API_ERROR_EXPEDITED_API_GET_ERROR_LOG_WAIT_TIMEOUT, //Get error log timeout
	WMX_API_ERROR_EXPEDITED_API_IS_RUNNING, //expedited api is still running
	WMX_API_ERROR_EXPEDITED_API_FAST_API_TIME_OUT, //Wait for fast api result timeout
	WMX_API_ERROR_EXPEDITED_API_COMMAND_ID_GENERATION_ERROR, //Command id generation error

	WMX_API_ERROR_OTHER //Miscellaneous errors
}WMX_API_ERROR_CODE;


#endif
