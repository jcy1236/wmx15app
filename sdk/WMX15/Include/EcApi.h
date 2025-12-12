#ifndef EC_API_LIB
#define EC_API_LIB
#include <windows.h>

#define EC_API_MAJOR_VERSION 1
#define EC_API_MINOR_VERSION 1

#ifdef WIN32 
#define ECAPIFUNC long __stdcall 
#else
#define ECAPIFUNC HRESULT
#endif

#ifndef EC_MAX_DEVICE
#define EC_MAX_DEVICE									256
#endif

#ifndef EC_MAX_SLAVE_SIZE
#define EC_MAX_SLAVE_SIZE								256
#endif

#ifndef EC_MAX_SLAVE_AXIS_SIZE
#define EC_MAX_SLAVE_AXIS_SIZE							6
#endif

#ifndef EC_MAX_FOE_FILE_PATH_LEN
#define EC_MAX_FOE_FILE_PATH_LEN						256
#endif

#ifndef EC_MAX_FOE_FILE_NAME_LEN
#define EC_MAX_FOE_FILE_NAME_LEN						64
#endif

#ifndef EC_MAX_SDO_INFO_OD_NAME_LEN
#define EC_MAX_SDO_INFO_OD_NAME_LEN						64
#endif

#ifndef EC_MAX_SDO_INFO_OD_LIST_SIZE
#define EC_MAX_SDO_INFO_OD_LIST_SIZE					450
#endif

#ifndef EC_MAX_SDO_INFO_ED_LIST_SIZE
#define EC_MAX_SDO_INFO_ED_LIST_SIZE					50
#endif

#ifndef EC_MAX_DEVICE_NAME_SIZE
#define EC_MAX_DEVICE_NAME_SIZE							36
#endif

namespace ecAPI{
	class StateMachine{
	public:
		enum T {			
			None = 0x00,
			Init = 0x01,
			Preop = 0x02,
			Boot = 0x03,
			Safeop = 0x04,
			Op = 0x08
		};
	};

	class SdoType{
	public:
		enum T {
			Expedited = 0x00,
			Normal = 0x01
		};
	};

	class ObjectDescriptionListType{
	public:
		enum T
		{
			Len = 0x00,
			AllObjects = 0x01,
			RxPdo = 0x02,
			TxPdo = 0x03,
			DevReplacement = 0x04,
			Startup = 0x05,
		};
	};

	class HotconnectState{
	public:
		enum T
		{
			Idle = 0x00,
			Running,
			Abort,

			Unknown
		};
	};

	class HotconnectAbortCode{
	public:
		enum T
		{
			None = 0x00,
			PortOpenError,
			Timeout,
			ScanNetworkFailed,
			ApplyNewTopologyError,
			InitNewSlavesError,
			RecalculateDcError,
			ClearDLEventError,

			Unknown
		};
	};

	class OperationMode{
	public:
		enum T
		{
			NONE = 0x00,
			PP = 0x01,
			VL = 0x02,
			PV = 0x03,
			TQ = 0x04,
			HM = 0x06,
			IP = 0x07,
			CSP = 0x08,
			CSV = 0x09,
			CST = 0x0a,
			CSTCA = 0x0b,

			Unknown
		};
	};

	class ErrorCode{
	public:
		enum T
		{
			None = 0x0, //No error
			CallError = 0x5, //Error, use GetLastError to obtain detailed error code

			MemoryAllocFailed      = 0x00000100,
			PeIsNotRunning,
			ControlChannelLockFailed,
			ControlChannelEventFailed,
			ControlChannelWaitEventFailed,
			ControlChannelSharedMemoryFailed,
			ControlChannelLockWaitTimeOut,
			APIChannelError,
			APIChannelTimeOut,
			StatusChannelError,

			RtssFileNotFoundError,
			RtssStartError,
			RequestChannelTimeOut,
			FreeChannelTimeOut,
			CloseDeviceTimeOut,

			RequestChannelFailed,
			ReachMaxChannelNumber,
			FreeChannelFailed,
			InvalidChannelId,
			CloseDeviceFailed,

			StatusChannelNull,
			StatusChannelIdError,
			StatusSharedMemoryVersionError,
			StatusSharedMemoryChannelIndexError,

			CreateDeviceLockError,
			CloseDeviceLockError,

			DeviceIsNull,
			NoSupportedFunction,

			CommandQueueAddFailed,
			CommandQueueIsFull,
			CommandQueueAddTimeOut,		

			CommandIdLockError,
			CommandIdGetError,

			CallbackMallocFailed,
			CallbackThreadNull,
			CallbackThreadError,
			CallbackThreadTimeOut,

			SetDeviceNameFailed,
			SetDeviceNameTimeout,
			GetDeviceNameFailed,
			GetDeviceNameTimeout,

			ArgumentOutOfRange = 0x20000000,
			ArgumentIsNull,
			ScanNetworkFailed,
			SlaveStateChangeError,
			SlaveSdoStatusBelowPreop,
			SlaveInvalidAddressingMode,
			SlaveMailboxBeingUsed,
			SlaveSdoDownloadError,
			SlaveSdoUploadError,
			SlaveSdoInfoGetODListError,
			SlaveSdoInfoGetODError,
			SlaveSdoInfoGetEDError,
			SlaveAcutalSizeLargerThanBufferSize,
			CallbackFuncError,
			CallbackFuncTimeOut,
			CallbackFuncInvalidState,
			SlaveRegWriteError,
			SlaveRegReadError,
			SlaveSIIWriteError,
			SlaveSIIReadError,
			SlavePdoReadWriteNotAllowed,
			SlavePdoReadWriteTimeout,
			SlavePdoNotMapped,
			SlaveTxPdoWriteNotAllowed,
			SlaveFoENotInBootState,			
			SlaveFoEFileOpenError,			
			SlaveFoEReadError,			
			SlaveFoEWriteError,
			SlaveFoEFilePathTooLong,
			SlaveFoEFileNameTooLong,
			AxisNotServoOn,
			NotInPPMode,
			PdoNotMapped,
			NotInHMMode,

			OpenComFailed,
			CreateComProcessThreadFailed,

			OtherError,	 
			UnknownError,
			ErrorSize
		};
	};

	class ActiveDeviceList{
	public:
		unsigned int count;
		unsigned int id[EC_MAX_DEVICE];
		TCHAR name[EC_MAX_DEVICE][EC_MAX_DEVICE_NAME_SIZE];
	};

	class SlaveSDOInfoObjectDescription{
	public:
		unsigned short index;
		unsigned short dataType;
		unsigned char maxSubIndex;	
		unsigned short objectCode;
		char name[EC_MAX_SDO_INFO_OD_NAME_LEN];
	};

	class SlaveSDOInfoObjectDescriptionList{
	public:
		unsigned short num;
		SlaveSDOInfoObjectDescription objects[EC_MAX_SDO_INFO_OD_LIST_SIZE];
	};

	class SlaveSDOInfoEntryDescription {
	public:
		unsigned short index;
		unsigned char subIndex;
		unsigned char valueInfo;
		unsigned short dataType;
		unsigned short bitLen;
		unsigned short objectAccess;

		unsigned short unitType;
		int defaultValue;
		int minimumValue;
		int maximumValue;
		char name[EC_MAX_SDO_INFO_OD_NAME_LEN];
	};


	class SlaveSDOInfoEntryDescriptionList {
	public:
		unsigned short num;
		SlaveSDOInfoEntryDescription entry[EC_MAX_SDO_INFO_ED_LIST_SIZE];
	};


	class SlavePdo{
	public:
		bool enable;
		unsigned char size;
		unsigned short offset;		
	};

	class SlavePdoInfo{
	public:
		SlavePdo statusWord;										// 	
		SlavePdo modesOfOperationDisplay;							// 	
		SlavePdo positionActualValue;								// 	
		SlavePdo velocityActualValue;								// 	
		SlavePdo torqueActualValue;									// 	
		SlavePdo errorCode;											// 	
		SlavePdo touchProbeStatus;									// 	
		SlavePdo touchProbePositionPos1;							// 	
		SlavePdo touchProbePositionPos2;							// 	
		SlavePdo followingError;									// 	
		SlavePdo digitalInput;										// 	
		 
		SlavePdo controlWord;										// 	
		SlavePdo modesOfOperation;									// 	
		SlavePdo targetPosition;									// 	
		SlavePdo targetVelocity;									// 	
		SlavePdo targetTorque;										// 	
		SlavePdo maxTorque;											// 	
		SlavePdo positiveTorqueLimit;								// 	
		SlavePdo negativeTorqueLimit;								// 	
		SlavePdo touchProbeFunction;								// 		
		SlavePdo velocityOffset;									// 	
		SlavePdo torqueOffset;										// 	
		SlavePdo maxMotorSpeed;										// 	
		SlavePdo digitalOutput;										//
	};

	class SlaveAxisInfo{
	public:
		int axisIndex;
		short digitalInOffset;
		unsigned short digitalInSize;
		short digitalOutOffset;
		unsigned short digitalOutSize;
		SlavePdoInfo pdoInfo;
		OperationMode::T operationMode;
		unsigned char status;
	};

	class SlaveInfo{
	public:
		int id;

		short position;	
		short address;	

		unsigned int vendorId;
		unsigned int productCode;
		unsigned int revisionNo;
		unsigned int serialNo;
		unsigned int alias; 
		unsigned int numOfAxes;
		SlaveAxisInfo axisInfo[EC_MAX_SLAVE_AXIS_SIZE];

		StateMachine::T state;
		unsigned short alStatusCode;

		unsigned char offline;
		unsigned char inaccessible;
		unsigned char newSlave;
		unsigned char unknown;

		unsigned char dcSupport;
		unsigned char dcWidth;			//0: none, 1: 32bit, 2: 64bit
		unsigned char portState[4];		//bit0: physical link, bit1: Loop, bit2: Communication
		int neighbor[4];
		unsigned int propagaDelay;
		unsigned long long systemTime;
		unsigned long long systemTimeOffset;
		unsigned long long startTime;

		unsigned short inOffset;
		unsigned short inSize;
		unsigned short outOffset;
		unsigned short outSize;

		unsigned int rxLogicAddr;
		unsigned int rxPhyAddr;
		unsigned int rxSize;
		unsigned int txLogicAddr;
		unsigned int txPhyAddr;
		unsigned int txSize;
	};

	class MasterStatisticsInfo{
	public:
		long commPeriod;
		long cycleCounter;
		double interruntpInterval[9];
		double cycleProcessTime[6];
		double ceProcessTime[6];
		double peCommandProcessTime[6];
		double peFeedbackProcessTime[6];
		double peCommunicateProcessTime[6];

		unsigned int txDelay;
		unsigned int minTxDelay;
		unsigned int maxTxDelay;
		unsigned int packetLoss;
		unsigned int packetTimeout;

		unsigned long long minRefClockInterval;
		unsigned long long maxRefClockInterval;
		unsigned long long avgRefClockInterval;

		unsigned long long curRefClock;
		unsigned long long nextDcClock;

		int diffFromNextDcClock;
		int minDiffFromNextDcClock;
		int maxDiffFromNextDcClock;

		unsigned int totalAxesNum;

		unsigned int totalRxPdoSize;
		unsigned int totalTxPdoSize;
		unsigned int totalInputSize;
		unsigned int totalOutputSize;	

		unsigned int overCycle;

		unsigned int ringNum;

		unsigned int numOfCyclicFrames; 

		HotconnectState::T hcState;
		HotconnectAbortCode::T hcAbortCode;
		long hcErrorCode;
	};

	class MasterInfo {
	public:
		StateMachine::T state;
		unsigned int numOfSlaves;
		SlaveInfo slaves[EC_MAX_SLAVE_SIZE];

		MasterStatisticsInfo statisticsInfo;

		int GetOnlineSlaveCount();
		int GetOfflineSlaveCount();
		int GetInaccessibleSlaveCount();
	};
	

	typedef int (*EcSdoDownloadCallBackFunc)(int, int, int, int, SdoType::T, int, unsigned char*, unsigned int); //result, slaveid, index, subindex, sdoType, len, data, error code
	typedef int (*EcSdoUploadCallBackFunc)(int, int, int, int, SdoType::T, int, unsigned char*, unsigned int);	//result, slaveid, index, subindex, sdoType, len, data, error code
	typedef int (*EcRegWriteCallBackFunc)(int, int, int, int, unsigned char*); //result, slaveid, off, len, data
	typedef int (*EcRegReadCallBackFunc)(int, int, int, int, unsigned char*); //result, slaveid, off, len, data
	typedef int (*EcBroadcastRegWriteCallBackFunc)(int, int, int, unsigned char*, int); //result, off, len, data, wkc
	typedef int (*EcBroadcastRegReadCallBackFunc)(int, int, int, unsigned char*, int); //result, off, len, data, wkc
	typedef int (*EcSdoInfoGetODListCallBackFunc)(int, int, ObjectDescriptionListType::T, SlaveSDOInfoObjectDescriptionList*); //result, slaveid, type, list
	typedef int (*EcSdoInfoGetEDListCallBackFunc)(int, int, int, SlaveSDOInfoEntryDescriptionList*); //result, slaveid, index, list
	typedef int (*EcFoEReadCallBackFunc)(int, int, TCHAR*, char*, unsigned int, unsigned int); //result, slaveId, filePath, fileName, password, error code
	typedef int (*EcFoEWriteCallBackFunc)(int, int, TCHAR*, char*, unsigned int, unsigned int); //result, slaveId, filePath, fileName, password, error code
	typedef int (*EcSIIWriteCallBackFunc)(int, int, int, int, unsigned char*); //result, slaveid, addr, len, data
	typedef int (*EcSIIReadCallBackFunc)(int, int, int, int, unsigned char*); //result, slaveid, addr, len, data

	class EcAPI;

	class EcAPI{
		public:
			HANDLE dev;
			EcAPI();
			~EcAPI();

		ECAPIFUNC CreateDevice();
		ECAPIFUNC CreateDeviceEx();
		ECAPIFUNC CloseDevice();
		ECAPIFUNC GetDeviceID(int *id);
		ECAPIFUNC GetLastError();
		ECAPIFUNC ecAPI::EcAPI::SetLastError(ErrorCode::T error);
		ECAPIFUNC ErrorToString(int errCode, TCHAR *pString, unsigned int size);
		ECAPIFUNC GetActiveDevices(ActiveDeviceList* devs);
		ECAPIFUNC SetDeviceName(TCHAR* name);
		ECAPIFUNC GetDeviceName(TCHAR* nameBuf, unsigned int bufSize);
		ECAPIFUNC ForceCloseDevice(int id);

		ECAPIFUNC ScanNetwork();

		ECAPIFUNC ChangeSlaveState(int slaveId, StateMachine::T state, int* errorCode);

		ECAPIFUNC StartHotconnect();
		ECAPIFUNC ResetRefClockInfo();
		ECAPIFUNC ResetTransmitStaticInfo();

		ECAPIFUNC GetMasterInfo(MasterInfo* master);

		ECAPIFUNC WriteReg(int slaveId, int regAddr, int len, unsigned char* data);
		ECAPIFUNC ReadReg(int slaveId, int regAddr, int len, unsigned char* buff);
		ECAPIFUNC WriteReg(int slaveId, int regAddr, int len, unsigned char* data, EcRegWriteCallBackFunc callbackFunc, unsigned int waitTime);
		ECAPIFUNC ReadReg(int slaveId, int regAddr, int len, EcRegReadCallBackFunc callbackFunc, unsigned int waitTime);

		ECAPIFUNC BroadcastWriteReg(int regAddr, int len, unsigned char* data, unsigned short* wkc);
		ECAPIFUNC BroadcastReadReg(int regAddr, int len, unsigned char* buff, unsigned short* wkc);
		ECAPIFUNC BroadcastWriteReg(int regAddr, int len, unsigned char* data, EcBroadcastRegWriteCallBackFunc callbackFunc, unsigned int waitTime);
		ECAPIFUNC BroadcastReadReg(int regAddr, int len, EcBroadcastRegReadCallBackFunc callbackFunc, unsigned int waitTime);

		//Expedited SDO download/upload
		ECAPIFUNC DownloadSDO(int slaveId, int index, int subindex, int sdoDataSize, unsigned char* sdoData, unsigned int* errCode, unsigned int waitTime = 0);
		ECAPIFUNC UploadSDO(int slaveId, int index, int subindex, int sdoBuffSize, unsigned char* sdoBuff, unsigned int* actualSize, unsigned int* errCode, unsigned int waitTime = 0);
		ECAPIFUNC DownloadSDO(int slaveId, int index, int subindex, int sdoDataSize, unsigned char* sdoData, EcSdoDownloadCallBackFunc callbackFunc, unsigned int waitTime);
		ECAPIFUNC UploadSDO(int slaveId, int index, int subindex, EcSdoUploadCallBackFunc callbackFunc, unsigned int waitTime);
		//SDO download/upload with specified type
		ECAPIFUNC DownloadSDO(int slaveId, int index, int subindex, SdoType::T sdoType, int sdoDataSize, unsigned char* sdoData, unsigned int* errCode, unsigned int waitTime = 0);
		ECAPIFUNC UploadSDO(int slaveId, int index, int subindex, SdoType::T sdoType, int sdoBuffSize, unsigned char* sdoBuff, unsigned int* actualSize, unsigned int* errCode, unsigned int waitTime = 0);
		ECAPIFUNC DownloadSDOEx(int slaveId, int index, int subindex, SdoType::T sdoType, int sdoDataSize, unsigned char* sdoData, unsigned int* errCode, int retryCount, int retryInterval);
		ECAPIFUNC UploadSDOEx(int slaveId, int index, int subindex, SdoType::T sdoType, int sdoBuffSize, unsigned char* sdoBuff, unsigned int* actualSize, unsigned int* errCode, int retryCount, int retryInterval);
		ECAPIFUNC DownloadSDO(int slaveId, int index, int subindex, SdoType::T sdoType, int sdoDataSize, unsigned char* sdoData, EcSdoDownloadCallBackFunc callbackFunc, unsigned int waitTime);
		ECAPIFUNC UploadSDO(int slaveId, int index, int subindex, SdoType::T sdoType, EcSdoUploadCallBackFunc callbackFunc, unsigned int waitTime);
		
		ECAPIFUNC GetSDOInfoODList(int slaveId, ObjectDescriptionListType::T type, SlaveSDOInfoObjectDescriptionList* list);
		ECAPIFUNC GetSDOInfoEDList(int slaveId, int index, SlaveSDOInfoEntryDescriptionList* list);
		ECAPIFUNC GetSDOInfoODList(int slaveId, ObjectDescriptionListType::T type, EcSdoInfoGetODListCallBackFunc callbackFunc, unsigned int waitTime);
		ECAPIFUNC GetSDOInfoEDList(int slaveId, int index, EcSdoInfoGetEDListCallBackFunc callbackFunc, unsigned int waitTime);

		ECAPIFUNC WriteTxPDO(int slaveId, int index, int subindex, int pdoDataSize, unsigned char* pdoData);
		ECAPIFUNC ReadRxTxPDO(int slaveId, int index, int subindex, int pdoBuffSize, unsigned char* pdoBuff, unsigned int* actualSize);
		
		ECAPIFUNC FoERead(int slaveId, TCHAR* filePath, char* fileName, unsigned int password, unsigned int* errCode);
		ECAPIFUNC FoEWrite(int slaveId, TCHAR* filePath, char* fileName, unsigned int password, unsigned int* errCode);
		ECAPIFUNC FoERead(int slaveId, TCHAR* filePath, char* fileName, unsigned int password, EcFoEReadCallBackFunc callbackFunc, unsigned int waitTime);
		ECAPIFUNC FoEWrite(int slaveId, TCHAR* filePath, char* fileName, unsigned int password, EcFoEWriteCallBackFunc callbackFunc, unsigned int waitTime);

		ECAPIFUNC WriteSII(int slaveId, int siiAddr, int len, unsigned char* data);
		ECAPIFUNC ReadSII(int slaveId, int siiAddr, int len, unsigned char* buff);
		ECAPIFUNC WriteSII(int slaveId, int siiAddr, int len, unsigned char* data, EcSIIWriteCallBackFunc callbackFunc, unsigned int waitTime);
		ECAPIFUNC ReadSII(int slaveId, int siiAddr, int len, EcSIIReadCallBackFunc callbackFunc, unsigned int waitTime);

		ECAPIFUNC SetAxisMode(int slaveId, int axisId, OperationMode::T mode);
		ECAPIFUNC StartAxisPP(int slaveId, int axisIndex, int targetPos, unsigned int profileVel, unsigned int profileAcc, unsigned int profileDec, char immediately = -1, char relative = -1);
		ECAPIFUNC StartAxisHM(int slaveId, int axisIndex, int method, unsigned int switchSpeed, unsigned int zeroSpeed, unsigned int hmAcc);


		ECAPIFUNC OpenSerialChannel(int slaveId, int chnlId, TCHAR* comName, DCB* dcb, COMMTIMEOUTS* timeout, DWORD* error = NULL);
		ECAPIFUNC CloseSerialChannel(int slaveId, int chnlId);

		private:
			ErrorCode::T lastError;
	};
}

#endif