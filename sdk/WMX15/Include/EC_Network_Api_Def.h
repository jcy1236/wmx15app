#ifndef EC_NM_API_LIB_DEF
#define EC_NM_API_LIB_DEF

/** \file EC_Network_Api_Def.h
 * Date Modified: 04/20/2016
 *
 * Definitions for Platform Engine EtherCAT Network Management API
 *
 */

/**
 * Standard API call type
 */

#ifdef UNDER_RTSS
	#define EC_API long
#else
	#ifdef WIN32 
		#define EC_API long __stdcall
	#else
		#define EC_API HRESULT
	#endif
#endif

#define EC_NMAPI_VER_MAJOR 0 
#define EC_NMAPI_VER_MINOR 9


#ifndef MAX_DATA_CHANNEL_INSTANCES
#define MAX_DATA_CHANNEL_INSTANCES 256 //Maximum number of data channels
#endif

#define EC_MASTER_MAX_CYCLE_MONITOR_COUNT 10


/**
 * Device descriptor type.
 */
typedef HANDLE ECDEV, *PECDEV;

/**
 * Enum for Result of Network API call
 */
typedef enum
{
	EC_FAIL,		/**< Something has happened. Use ecGetLastError to get the detail of the error. */
	EC_SUCCESS		/**< Api call has succeeded. Check the result of the API. */
}EC_RESULT;

/**
 * Master status enum.
 * Enum to represent master status
 */
typedef enum
{
	EC_MASTER_STATE_BOOT = 0x00,		/**< Master state is in Boot. No EtherCAT communication is available. */
	EC_MASTER_STATE_INIT = 0x01,		/**< Master state is in Init. Basic EtherCAT non-cyclic communication is ready. */
	EC_MASTER_STATE_PREOP = 0x02,		/**< Master state is in PreOp. Finish loading the network definition file. */
	EC_MASTER_STATE_SAFEOP = 0x04,		/**< Master state is in SafeOp. Complete scanning and matching the actual network with the network definition. DC sync will be prepared if enabled. */
	EC_MASTER_STATE_OP = 0x08,			/**< Master state is in Op. ESM(EtherCAT State Machine) on all slaves are commanded to move to Op state. */
	EC_MASTER_STATE_BOOT_ERR= 0x10,		/**< Master is in Boot state after failed to transition to INIT state. */
	EC_MASTER_STATE_INIT_ERR = 0x11,	/**< Master is in Init state after failed to transition to PREOP state. */
	EC_MASTER_STATE_PREOP_ERR = 0x12,	/**< Master is in PreOp state after failed to transition to SAFEOP. */
	EC_MASTER_STATE_SAFEOP_ERR = 0x14,	/**< Master is in SafeOp state after failed to transition to OP. */
	EC_MASTER_STATE_OP_ERR = 0x18		/**< Master is in Op state with error flag. OBSOLETE */
}EC_MASTER_STATE, *PEC_MASTER_STATE;

/**
 * Master DC status enum.
 * Enumulator to represent DC status controlled by a master
 */
typedef enum{
	EC_MASTER_DC_DISABLED = 0,				/**< DC mode is disabled in a master setting. */
	EC_MASTER_DC_DISABLED_WITH_DC_SLAVE,	/**< DC mode is disabled in a master setting. There is at least one slave with DC Sync on the network. */
	EC_MASTER_DC_ENABLED,					/**< DC mode is enabled in a master setting and the master is working on to lock onto a DC clock on a master slave clock. */
	EC_MASTER_DC_ENABLED_AND_LOCKED			/**< DC mode is enabled in a master setting and the master is locked onto a DC clock on a master slave clock. */
}EC_MASTER_DC_STATE;

/**
 * Master Ring topology status enum.
 * Enum to represent Ring topology status in a master
 */
typedef enum{
	EC_MASTER_RING_DISABLED = 0,		/**< Ring topology is disabled.*/
	EC_MASTER_RING_BROKEN,				/**< Ring topology function is active, but current actual topology is not Ring.*/
	EC_MASTER_RING_INUSE				/**< Ring topology function is active and is in use.*/
}EC_MASTER_RING_STATE;

/**
 * Master HotConnect status enum.
 * Enum to represent HotConnect status in a master
 */
typedef enum{
	EC_MASTER_HOTCONNECT_DISABLED = 0,	/**< HotConnect is disabled.*/
	EC_MASTER_HOTCONNECT_IDLE,			/**< HotConnect function is active and waiting for event.*/
	EC_MASTER_HOTCONNECT_RUNNING		/**< HotConnect function is active and is running to check and reconfigure the network.*/
}EC_MASTER_HOTCONNECT_STATE;

/**
 * Master latched HotConnect abortion status enum.
 * Enum to represent latched HotConnect abortion status in a master
 */
typedef enum{
	EC_MASTER_HOTCONNECT_NO_ABORT = 0,	/**< No aborted HotConnect.*/
	EC_MASTER_HOTCONNECT_ABORTED		/**< Aborted HotConnect has latched.*/
}EC_MASTER_HOTCONNECT_ABORTION_STATUS;


/**
 * AL Status enum.
 * Enum to represent AL Status of the node
 */
typedef enum
{
	EC_SLAVE_STATE_BOOTSTRAP = 0x00,	/**< Slave state is in Boot. Refer to ETG document for detail. */
	EC_SLAVE_STATE_INIT = 0x01,			/**< Slave state is in Init. Refer to ETG document for detail. */
	EC_SLAVE_STATE_PREOP = 0x02,		/**< Slave state is in PreOp. Refer to ETG document for detail. */
	EC_SLAVE_STATE_SAFEOP = 0x04,		/**< Slave state is in SafeOp. Refer to ETG document for detail. */
	EC_SLAVE_STATE_OP = 0x08,			/**< Slave state is in Op. Refer to ETG document for detail. */
	EC_SLAVE_STATE_INIT_ERR = 0x11,		/**< Slave state is in Init with error flag. Refer to ETG document for detail. */
	EC_SLAVE_STATE_PREOP_ERR = 0x12,	/**< Slave state is in PreOp with error. Refer to ETG document for detail. */
	EC_SLAVE_STATE_SAFEOP_ERR = 0x14,	/**< Slave state is in SafeOp with error. Refer to ETG document for detail. */
	EC_SLAVE_STATE_UNKNOWN				/**< Slave state is in Unknown state. */
}EC_SLAVE_STATE, *PEC_SLAVE_STATE;


/**
 * SDO communication type
 * Enum to represent SDO communication type
 */
typedef enum{
	EC_MASTER_SDO_UNKNOWN,				/**< Invalid SDO communication type. */
	EC_MASTER_SDO_EXPEDITED,			/**< Expedited SDO communication type. This is the most common SDO compatible with CANOpen. */
	EC_MASTER_SDO_COMPLETE,				/**< Complete SDO communication type */
	EC_MASTER_SDO_NORMAL                /**< Normal SDO communication type */
}EC_MASTER_SDO_TYPE;

/**
 * Master status struct.
 * Structure to represent current master status and status of various master functions.
 */
typedef struct{
	EC_MASTER_STATE state;						/**< Master State*/
	EC_MASTER_DC_STATE dcState;					/**< DC related status*/
	EC_MASTER_RING_STATE ringState;				/**< Ring function status*/
	EC_MASTER_HOTCONNECT_STATE hotConnectState;	/**< HotConnect function status*/
	EC_MASTER_HOTCONNECT_ABORTION_STATUS latchedAbortedHotConnect; /**< HotConnect abortion has latched */
	int mappedAxisCount;						/**< Total number of axis mapped in this instance of the Master */
	int mappedIOInputSize;						/**< Total IO Input size mapped in this instance of the Master */
	int mappedIOOutputSize;						/**< Total IO Output size mapped in this instance of the Master */
}EC_MASTER_STATUS, *PEC_MASTER_STATUS;

/**
 * EtherCAT Network performance date struct.
 * Structure to represent network performance related data monitored by a master.
 */
typedef struct{
	int status;							/**< 1: valid data. -1: invalid data. */
	long isrCounter;					/**< ISR counter (WMX internal cycle counter) when the event happened.*/
	LARGE_INTEGER time;					/**< PC hardware system clock time when the event happened.*/
	LARGE_INTEGER actualInterval;		/**< Actual measured interval time in 100ns unit.*/
	LARGE_INTEGER programmedInterval;	/**< Programmed interval time in 100ns unit.*/
}EC_MASTER_CYCLE_TIMING_MONITOR, *PEC_MASTER_CYCLE_TIMING_MONITOR;

/**
 * EtherCAT Network performance cycle date struct.
 * Structure to represent cycle performance related data monitored by a master.
 */
typedef struct 
{
	EC_MASTER_CYCLE_TIMING_MONITOR shortestCycle[EC_MASTER_MAX_CYCLE_MONITOR_COUNT];	/**< Short cycle duration monitor. Top 10 cycle durations which took shortest actual time to wait.*/
	EC_MASTER_CYCLE_TIMING_MONITOR longestCycle[EC_MASTER_MAX_CYCLE_MONITOR_COUNT];		/**< Long cycle duration monitor. Top 10 cycle durations which took longest actual time to wait.*/
	int lostPacketCount;																/**< Total packet lost count since previous counter reset or starting of the communication.*/
	int lostCMDPacketCount;																/**< Total command packet lost count since previous counter reset or starting of the communication.*/
	int lostFBPacketCount;																/**< Total feedback packet lost count since previous counter reset or starting of the communication.*/
	int contLostPacketCount;															/**< Maximum continuous packet lost count since previous counter reset or starting of the communication.*/
	int contLostCMDPacketCount;															/**< Maximum continuous command packet lost count since previous counter reset or starting of the communication.*/
	int contLostFBPacketCount;															/**< Maximum continuous feedback packet lost count since previous counter reset or starting of the communication.*/
	int brokenPacketCount;
	int contFailedTXPacketCount;
	int timerPerformanceWarningFlag;													/**< 0: No warning. 1: There were at least one cycle with more than 20% difference between programmed and actual timer period. */
}EC_MASTER_PERFORM_DATA, *PEC_MASTER_PERFORM_DATA;

/**
 * Slave function list.
 * List of supported slave function with current PDO mapping in use for the slave.
 */
typedef struct
{
	unsigned char posControlEnabled;		/**< Position control(0x607a:00)\n - 0: disabled\n - 1: enabled */
	unsigned char followingErrorEnabled;	/**< Following error actual value monitor on the servo drive(0x60f4:00)\n - 0: disabled\n - 1: enabled */
	unsigned char velControlEnabled;		/**< Velocity control(0x6077:00)\n - 0: disabled\n - 1: enabled */
	unsigned char velFbEnabled;				/**< Velocity feedback(0x60ff:00)\n- 0: disabled\n - 1: enabled */
	unsigned char velOffsetEnabled;			/**< Velocity Offset(0x60b1:00)\n - 0: disabled\n - 1: enabled */
	unsigned char maxProfileVelEnabled;		/**< Max Profile Velocity(0x607f:00)\n - 0: disabled\n - 1: enabled */
	unsigned char servoDrive;				/**< Application node type\n - 0: IO or other non Servo Node\n - 1: Servo Node */
	unsigned char servoIoEnabled;			/**< IOs(POT, NOT, HS) for servo axis(0x60fd:00) - 0: disabled\n - 1: enabled */
	unsigned char torqueControlEnabled;		/**< Torque control\n - 0: disabled\n - 1: enabled */
	unsigned char torqueFbEnabled;			/**< Torque feedback\n - 0: disabled\n - 1: enabled\n */
	unsigned char torquePositiveLimitEnabled;	/**< Positive Torque limit\n - 0: disabled\n - 1: enabled */
	unsigned char torqueNegativeLimitEnabled;	/**< Negative Torque limit\n - 0: disabled\n - 1: enabled */
	unsigned char torqueMaxEnabled;			/**< Maximum Torque limit\n - 0: disabled\n - 1: enabled */
	unsigned char torqueOffsetEnabled;		/**< Torque Offset\n - 0: disabled\n - 1: enabled */
	unsigned char velVolControlEnabled;		/**< Direct voltage based velocity control for DX-110A\n - 0: disabled\n - 1: enabled */
	unsigned char touchProbeEnabled;		/**< TouchProbe for Z-Pulse latching function\n - 0: disabled\n - 1: enabled */
	unsigned char opModeEnabled;			/**< Mode of Operation(0x6060:00) mapped to PDO for dynamic operation mode modification\n - 0: disabled\n - 1: enabled */
	unsigned char runNumEnabled;			/**< Random number writing from the master\n - 0: Not used\n - 1: In use */
	unsigned short controlMode;				/**< Current control mode of the servo axis\n - 0x08: Position control\n - 0x09: Velocity control\n - 0x0a: Torque control \warning Reserved for future use */
}EC_SLAVE_APP_INFO_FUNC, PEC_SLAVE_APP_INFO_FUNC;

/**
 * Application node info.
 * Application node defines a function of a part of slave. One application node can have maximum of 1 axis and unlimited number of IOs. 2 axis EtherCAT slave will have at least 2 application nodes for example.
 * Detailed information of application node
 */
typedef struct
{
	EC_SLAVE_APP_INFO_FUNC func;			/**< Information of functions supported by this application node */
	unsigned short ioInSize;				/**< IO input size mapped to this application node */
	unsigned short ioOutSize;				/**< IO output size mapped to this application node */
	unsigned int ioInAddress;				/**< IO input address mapped to this application node */
	unsigned int ioOutAddress;				/**< IO output address mapped to this application node */
	unsigned int axisNum;					/**< Axis number assigned to this application node by master if this application is servo node.\n Refer to "servoDrive" in func to check if this node is servo drive or not. */
}EC_SLAVE_APP_INFO, PEC_SLAVE_APP_INFO;

/**
 * Basic physical node information
 */
typedef struct
{
	unsigned char online;					/**< Online status of the slave.\n - 0: Slave is offline or Unknown\n - 1: Slave is online\n */
	unsigned char unknownSlave;				/**< Offline slave can be known slave or unknown slave based on the network definition file in use or the network condition at the boot time environment if no network definition file is in use.\n */
	unsigned char fullSizeDC;				/**< Size of DC clock on the slave.\n - 0: 32bit\n - 1: 64bit\n */
	unsigned char aliasValid;				/**< Alias will be valid if this value is 1. */
	short alias;							/**< Station alias */
	unsigned int vendorId;					/**< VendorID\n 4bytes code showing the vendor ID of the slave */
	unsigned int productCode;				/**< ProductCode\n 4bytes code showing the product code of the slave assigned by the vendor */
	unsigned int serialNumber;				/**< Serial Number\n 4bytes number showing the serial number. The slave does not have serial number if this value is 0 */
	unsigned int revision;					/**< Revision Code\n 4bytes revision number of the slave hardware or firmware assigned by the slave vendor */
	int configuredId;						/**< Current ConfiguredID of the slave. ConfiguredID is a unique slave identification value assigned by a master during initialization. This ID must be used to specify this slave when using other Network APIs. */
	int location;							/**< Location number of the slave in negative value. Location number is a physical location of a slave on the network, used by a master to specify a slave to talk to, before the master complete assigning ConfiguredID.\n 1st slave: 0\n 2nd slave: -1\n 3rd slage: -2...etc*/
	char initFile[2048];					/**< Init filename in use for this slave. Default is "[VendorID]_[ProductCode].txt" */
	EC_SLAVE_STATE state;					/**< Current slave AL Status\n Refer to the slave document or ETG document for a detail. */
	unsigned short alStatusCode;			/**< Current slave AL Status code\n Refer to the slave document or ETG document for a detail */
	unsigned int child[4];					/**< Node number of the child of this slave.\n -1 means no slave is connected to the port.\n - child[0]: Child slave connected to port0\n \warning Reserved for future use.\n */
	unsigned int rx[4];						/**< Latched receive time on each port.\n \warning Reserved for future use.*/
	unsigned int portType[4];				/**< 0: Not Implemented, 1: Not Configured, 2: EBUS, 3: MII, 4: MII Fast HotConnect */
	int appNodeCount;						/**< Number of application node mapped to this slave */
	EC_SLAVE_APP_INFO appNode[8];			/**< Detailed information of application node the slave contains. */
}EC_SLAVE_INFO, *PEC_SLAVE_INFO;



/**
 * Active device list
 */

typedef struct{
	int count;
	int idList[MAX_DATA_CHANNEL_INSTANCES];
}EC_ACT_DEV_LIST, *PEC_ACT_DEV_LIST;


#endif