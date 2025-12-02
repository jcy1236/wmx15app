// EcNetworkBroker.h
// EC_Network_Api to WMX3 EcApi Broker Layer
// Provides WMX 1.5 EC_Network_Api compatible interface

#ifndef EC_NETWORK_BROKER_H
#define EC_NETWORK_BROKER_H

#include <windows.h>
#include <tchar.h>
#include "EcDeviceManager.h"  // For ECDEV, PECDEV, EC_ACT_DEV_LIST

// DLL Export/Import macros
#ifdef WMXBROKER_EXPORTS
#define ECBROKER_API __declspec(dllexport)
#else
#define ECBROKER_API __declspec(dllimport)
#endif

//=============================================================================
// WMX 1.5 EC_Network_Api type definitions (avoid header conflict with WMX3)
//=============================================================================

// Master state enum
typedef enum {
    EC_MASTER_STATE_BOOT = 0x00,
    EC_MASTER_STATE_INIT = 0x01,
    EC_MASTER_STATE_PREOP = 0x02,
    EC_MASTER_STATE_SAFEOP = 0x04,
    EC_MASTER_STATE_OP = 0x08,
    EC_MASTER_STATE_BOOT_ERR = 0x10,
    EC_MASTER_STATE_INIT_ERR = 0x11,
    EC_MASTER_STATE_PREOP_ERR = 0x12,
    EC_MASTER_STATE_SAFEOP_ERR = 0x14,
    EC_MASTER_STATE_OP_ERR = 0x18
} EC_MASTER_STATE, *PEC_MASTER_STATE;

// Master DC state enum
typedef enum {
    EC_MASTER_DC_DISABLED = 0,
    EC_MASTER_DC_DISABLED_WITH_DC_SLAVE,
    EC_MASTER_DC_ENABLED,
    EC_MASTER_DC_ENABLED_AND_LOCKED
} EC_MASTER_DC_STATE;

// Master Ring state enum
typedef enum {
    EC_MASTER_RING_DISABLED = 0,
    EC_MASTER_RING_BROKEN,
    EC_MASTER_RING_INUSE
} EC_MASTER_RING_STATE;

// Master HotConnect state enum
typedef enum {
    EC_MASTER_HOTCONNECT_DISABLED = 0,
    EC_MASTER_HOTCONNECT_IDLE,
    EC_MASTER_HOTCONNECT_RUNNING
} EC_MASTER_HOTCONNECT_STATE;

// Master HotConnect abortion status enum
typedef enum {
    EC_MASTER_HOTCONNECT_NO_ABORT = 0,
    EC_MASTER_HOTCONNECT_ABORTED
} EC_MASTER_HOTCONNECT_ABORTION_STATUS;

// Slave state enum
typedef enum {
    EC_SLAVE_STATE_BOOTSTRAP = 0x00,
    EC_SLAVE_STATE_INIT = 0x01,
    EC_SLAVE_STATE_PREOP = 0x02,
    EC_SLAVE_STATE_SAFEOP = 0x04,
    EC_SLAVE_STATE_OP = 0x08,
    EC_SLAVE_STATE_INIT_ERR = 0x11,
    EC_SLAVE_STATE_PREOP_ERR = 0x12,
    EC_SLAVE_STATE_SAFEOP_ERR = 0x14,
    EC_SLAVE_STATE_UNKNOWN
} EC_SLAVE_STATE, *PEC_SLAVE_STATE;

// SDO type enum
typedef enum {
    EC_MASTER_SDO_UNKNOWN,
    EC_MASTER_SDO_EXPEDITED,
    EC_MASTER_SDO_COMPLETE,
    EC_MASTER_SDO_NORMAL
} EC_MASTER_SDO_TYPE;

// Master status struct
typedef struct {
    EC_MASTER_STATE state;
    EC_MASTER_DC_STATE dcState;
    EC_MASTER_RING_STATE ringState;
    EC_MASTER_HOTCONNECT_STATE hotConnectState;
    EC_MASTER_HOTCONNECT_ABORTION_STATUS latchedAbortedHotConnect;
    int mappedAxisCount;
    int mappedIOInputSize;
    int mappedIOOutputSize;
} EC_MASTER_STATUS, *PEC_MASTER_STATUS;

#define EC_MASTER_MAX_CYCLE_MONITOR_COUNT 10

// Cycle timing monitor struct
typedef struct {
    int status;
    long isrCounter;
    LARGE_INTEGER time;
    LARGE_INTEGER actualInterval;
    LARGE_INTEGER programmedInterval;
} EC_MASTER_CYCLE_TIMING_MONITOR, *PEC_MASTER_CYCLE_TIMING_MONITOR;

// Master performance data struct
typedef struct {
    EC_MASTER_CYCLE_TIMING_MONITOR shortestCycle[EC_MASTER_MAX_CYCLE_MONITOR_COUNT];
    EC_MASTER_CYCLE_TIMING_MONITOR longestCycle[EC_MASTER_MAX_CYCLE_MONITOR_COUNT];
    int lostPacketCount;
    int lostCMDPacketCount;
    int lostFBPacketCount;
    int contLostPacketCount;
    int contLostCMDPacketCount;
    int contLostFBPacketCount;
    int brokenPacketCount;
    int contFailedTXPacketCount;
    int timerPerformanceWarningFlag;
} EC_MASTER_PERFORM_DATA, *PEC_MASTER_PERFORM_DATA;

// Slave function info
typedef struct {
    unsigned char posControlEnabled;
    unsigned char followingErrorEnabled;
    unsigned char velControlEnabled;
    unsigned char velFbEnabled;
    unsigned char velOffsetEnabled;
    unsigned char maxProfileVelEnabled;
    unsigned char servoDrive;
    unsigned char servoIoEnabled;
    unsigned char torqueControlEnabled;
    unsigned char torqueFbEnabled;
    unsigned char torquePositiveLimitEnabled;
    unsigned char torqueNegativeLimitEnabled;
    unsigned char torqueMaxEnabled;
    unsigned char torqueOffsetEnabled;
    unsigned char velVolControlEnabled;
    unsigned char touchProbeEnabled;
    unsigned char opModeEnabled;
    unsigned char runNumEnabled;
    unsigned short controlMode;
} EC_SLAVE_APP_INFO_FUNC;

// Slave application info
typedef struct {
    EC_SLAVE_APP_INFO_FUNC func;
    unsigned short ioInSize;
    unsigned short ioOutSize;
    unsigned int ioInAddress;
    unsigned int ioOutAddress;
    unsigned int axisNum;
} EC_SLAVE_APP_INFO;

// Slave info struct
typedef struct {
    unsigned char online;
    unsigned char unknownSlave;
    unsigned char fullSizeDC;
    unsigned char aliasValid;
    short alias;
    unsigned int vendorId;
    unsigned int productCode;
    unsigned int serialNumber;
    unsigned int revision;
    int configuredId;
    int location;
    char initFile[2048];
    EC_SLAVE_STATE state;
    unsigned short alStatusCode;
    unsigned int child[4];
    unsigned int rx[4];
    unsigned int portType[4];
    int appNodeCount;
    EC_SLAVE_APP_INFO appNode[8];
} EC_SLAVE_INFO, *PEC_SLAVE_INFO;

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// Device Management APIs
//=============================================================================

ECBROKER_API long __stdcall ecCreateDevice(PECDEV pDev);
ECBROKER_API long __stdcall ecCloseDevice(ECDEV dev);
ECBROKER_API long __stdcall ecGetLastError(ECDEV dev);
ECBROKER_API long __stdcall ecForceCloseDevice(int deviceId);
ECBROKER_API long __stdcall ecGetActiveDeviceList(EC_ACT_DEV_LIST* list);
ECBROKER_API long __stdcall ecGetDeviceID(ECDEV dev, int* pId);
ECBROKER_API long __stdcall ecGetDeviceCount(ECDEV dev, int* pCount);

//=============================================================================
// Master Status APIs
//=============================================================================

ECBROKER_API long __stdcall ecGetMasterState(ECDEV dev, PEC_MASTER_STATE pCurState);
ECBROKER_API long __stdcall ecGetMasterStatus(ECDEV dev, PEC_MASTER_STATUS pStatus);
ECBROKER_API long __stdcall ecGetMasterStatistics(ECDEV dev, PEC_MASTER_PERFORM_DATA performData);
ECBROKER_API long __stdcall ecClearMasterStatistics(ECDEV dev);

//=============================================================================
// Network Status APIs
//=============================================================================

ECBROKER_API long __stdcall ecGetTotalSlaveCount(ECDEV dev, int* pCount);
ECBROKER_API long __stdcall ecGetOnlineSlaveCount(ECDEV dev, int* pCount);
ECBROKER_API long __stdcall ecGetOfflineSlaveCount(ECDEV dev, int* pCount);
ECBROKER_API long __stdcall ecGetUnknownSlaveCount(ECDEV dev, int* pCount);

//=============================================================================
// Slave Control APIs
//=============================================================================

ECBROKER_API long __stdcall ecGetSlaveInfo(ECDEV dev, int nodeId, PEC_SLAVE_INFO pSlaveInfo);
ECBROKER_API long __stdcall ecGetSlaveState(ECDEV dev, int configuredId, PEC_SLAVE_STATE pCurState);
ECBROKER_API long __stdcall ecSetSlaveState(ECDEV dev, int configuredId, EC_SLAVE_STATE newState);

//=============================================================================
// SDO Communication APIs
//=============================================================================

ECBROKER_API long __stdcall ecDownloadSDO(ECDEV dev, int configuredId, unsigned short index,
    unsigned char subIndex, int length, EC_MASTER_SDO_TYPE sdoType, unsigned char* data);
ECBROKER_API long __stdcall ecUploadSDO(ECDEV dev, int configuredId, unsigned short index,
    unsigned char subIndex, int length, EC_MASTER_SDO_TYPE sdoType, unsigned char* data);

//=============================================================================
// HotConnect APIs
//=============================================================================

ECBROKER_API long __stdcall ecStartHotConnect(ECDEV dev);
ECBROKER_API long __stdcall ecStartHotConnectWithRes(ECDEV dev);
ECBROKER_API long __stdcall ecClearHotConnectAbortionFlag(ECDEV dev);

//=============================================================================
// Config APIs
//=============================================================================

ECBROKER_API long __stdcall ecGetMasterConfigFilename(ECDEV dev, TCHAR* filename, int bufferSize);
ECBROKER_API long __stdcall ecSetMasterConfigFilename(ECDEV dev, TCHAR* filename);

#ifdef __cplusplus
}
#endif

#endif // EC_NETWORK_BROKER_H
