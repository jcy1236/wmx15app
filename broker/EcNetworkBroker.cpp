// EcNetworkBroker.cpp
// EC_Network_Api to WMX3 EcApi Broker Layer Implementation

#include "EcNetworkBroker.h"
#include "EcDeviceManager.h"
#include "WMX3ContextManager.h"
#include "WMX3Api.h"
// Include WMX3's EcApi.h (WMX3 Include path has priority in AdditionalIncludeDirectories)
#include "EcApi.h"
#include <cstring>

// Helper macro to get shared Ecat instance
#define GET_SHARED_ECAT() WMX3ContextManager::GetInstance()->GetEcat()

//=============================================================================
// Helper Functions
//=============================================================================

// Convert WMX3 EcStateMachine to WMX 1.5 EC_MASTER_STATE
static EC_MASTER_STATE ConvertToMasterState(wmx3Api::ecApi::EcStateMachine::T state)
{
    switch (state) {
    case wmx3Api::ecApi::EcStateMachine::None:
        return EC_MASTER_STATE_BOOT;
    case wmx3Api::ecApi::EcStateMachine::Init:
        return EC_MASTER_STATE_INIT;
    case wmx3Api::ecApi::EcStateMachine::Preop:
        return EC_MASTER_STATE_PREOP;
    case wmx3Api::ecApi::EcStateMachine::Boot:
        return EC_MASTER_STATE_BOOT;
    case wmx3Api::ecApi::EcStateMachine::Safeop:
        return EC_MASTER_STATE_SAFEOP;
    case wmx3Api::ecApi::EcStateMachine::Op:
        return EC_MASTER_STATE_OP;
    default:
        return EC_MASTER_STATE_BOOT;
    }
}

// Convert WMX3 EcStateMachine to WMX 1.5 EC_SLAVE_STATE
static EC_SLAVE_STATE ConvertToSlaveState(wmx3Api::ecApi::EcStateMachine::T state)
{
    switch (state) {
    case wmx3Api::ecApi::EcStateMachine::None:
        return EC_SLAVE_STATE_UNKNOWN;
    case wmx3Api::ecApi::EcStateMachine::Init:
        return EC_SLAVE_STATE_INIT;
    case wmx3Api::ecApi::EcStateMachine::Preop:
        return EC_SLAVE_STATE_PREOP;
    case wmx3Api::ecApi::EcStateMachine::Boot:
        return EC_SLAVE_STATE_BOOTSTRAP;
    case wmx3Api::ecApi::EcStateMachine::Safeop:
        return EC_SLAVE_STATE_SAFEOP;
    case wmx3Api::ecApi::EcStateMachine::Op:
        return EC_SLAVE_STATE_OP;
    default:
        return EC_SLAVE_STATE_UNKNOWN;
    }
}

// Convert WMX 1.5 EC_SLAVE_STATE to WMX3 EcStateMachine
static wmx3Api::ecApi::EcStateMachine::T ConvertFromSlaveState(EC_SLAVE_STATE state)
{
    switch (state) {
    case EC_SLAVE_STATE_BOOTSTRAP:
        return wmx3Api::ecApi::EcStateMachine::Boot;
    case EC_SLAVE_STATE_INIT:
    case EC_SLAVE_STATE_INIT_ERR:
        return wmx3Api::ecApi::EcStateMachine::Init;
    case EC_SLAVE_STATE_PREOP:
    case EC_SLAVE_STATE_PREOP_ERR:
        return wmx3Api::ecApi::EcStateMachine::Preop;
    case EC_SLAVE_STATE_SAFEOP:
    case EC_SLAVE_STATE_SAFEOP_ERR:
        return wmx3Api::ecApi::EcStateMachine::Safeop;
    case EC_SLAVE_STATE_OP:
        return wmx3Api::ecApi::EcStateMachine::Op;
    default:
        return wmx3Api::ecApi::EcStateMachine::None;
    }
}

// Convert WMX 1.5 SDO type to WMX3 SDO type
static wmx3Api::ecApi::EcSdoType::T ConvertSdoType(EC_MASTER_SDO_TYPE sdoType)
{
    switch (sdoType) {
    case EC_MASTER_SDO_EXPEDITED:
        return wmx3Api::ecApi::EcSdoType::Expedited;
    case EC_MASTER_SDO_NORMAL:
    case EC_MASTER_SDO_COMPLETE:
        return wmx3Api::ecApi::EcSdoType::Normal;
    default:
        return wmx3Api::ecApi::EcSdoType::Expedited;
    }
}

// Convert WMX3 HotConnect state to WMX 1.5 state
static EC_MASTER_HOTCONNECT_STATE ConvertHotConnectState(wmx3Api::ecApi::EcHotconnectState::T state)
{
    switch (state) {
    case wmx3Api::ecApi::EcHotconnectState::Idle:
        return EC_MASTER_HOTCONNECT_IDLE;
    case wmx3Api::ecApi::EcHotconnectState::Running:
        return EC_MASTER_HOTCONNECT_RUNNING;
    case wmx3Api::ecApi::EcHotconnectState::Abort:
    case wmx3Api::ecApi::EcHotconnectState::Unknown:
    default:
        return EC_MASTER_HOTCONNECT_DISABLED;
    }
}

//=============================================================================
// Device Management APIs
//=============================================================================

extern "C" ECBROKER_API long __stdcall ecCreateDevice(PECDEV pDev)
{
    return EcDeviceManager::GetInstance()->CreateDevice(pDev);
}

extern "C" ECBROKER_API long __stdcall ecCloseDevice(ECDEV dev)
{
    return EcDeviceManager::GetInstance()->CloseDevice(dev);
}

extern "C" ECBROKER_API long __stdcall ecGetLastError(ECDEV dev)
{
    return EcDeviceManager::GetInstance()->GetLastError(dev);
}

extern "C" ECBROKER_API long __stdcall ecForceCloseDevice(int deviceId)
{
    return EcDeviceManager::GetInstance()->ForceCloseDevice(deviceId);
}

extern "C" ECBROKER_API long __stdcall ecGetActiveDeviceList(EC_ACT_DEV_LIST* list)
{
    return EcDeviceManager::GetInstance()->GetActiveDeviceList(list);
}

extern "C" ECBROKER_API long __stdcall ecGetDeviceID(ECDEV dev, int* pId)
{
    return EcDeviceManager::GetInstance()->GetDeviceID(dev, pId);
}

extern "C" ECBROKER_API long __stdcall ecGetDeviceCount(ECDEV dev, int* pCount)
{
    return EcDeviceManager::GetInstance()->GetDeviceCount(dev, pCount);
}

//=============================================================================
// Master Status APIs
//=============================================================================

extern "C" ECBROKER_API long __stdcall ecGetMasterState(ECDEV dev, PEC_MASTER_STATE pCurState)
{
    if (pCurState == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    *pCurState = ConvertToMasterState(masterInfo.state);
    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecGetMasterStatus(ECDEV dev, PEC_MASTER_STATUS pStatus)
{
    if (pStatus == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    // Map master status
    pStatus->state = ConvertToMasterState(masterInfo.state);
    pStatus->dcState = EC_MASTER_DC_DISABLED; // Simplified - need detailed DC info
    pStatus->ringState = (masterInfo.statisticsInfo.ringNum > 0) ?
        EC_MASTER_RING_INUSE : EC_MASTER_RING_DISABLED;
    pStatus->hotConnectState = ConvertHotConnectState(masterInfo.statisticsInfo.hcState);
    pStatus->latchedAbortedHotConnect = (masterInfo.statisticsInfo.hcAbortCode !=
        wmx3Api::ecApi::EcHotconnectAbortCode::None) ?
        EC_MASTER_HOTCONNECT_ABORTED : EC_MASTER_HOTCONNECT_NO_ABORT;
    pStatus->mappedAxisCount = static_cast<int>(masterInfo.statisticsInfo.totalAxesNum);
    pStatus->mappedIOInputSize = static_cast<int>(masterInfo.statisticsInfo.totalInputSize);
    pStatus->mappedIOOutputSize = static_cast<int>(masterInfo.statisticsInfo.totalOutputSize);

    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecGetMasterStatistics(ECDEV dev, PEC_MASTER_PERFORM_DATA performData)
{
    if (performData == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    // Initialize to zero
    memset(performData, 0, sizeof(EC_MASTER_PERFORM_DATA));

    // Map statistics info
    performData->lostPacketCount = static_cast<int>(masterInfo.statisticsInfo.packetLoss);
    performData->lostCMDPacketCount = 0; // Not directly mapped
    performData->lostFBPacketCount = 0; // Not directly mapped
    performData->contLostPacketCount = 0; // Not directly mapped
    performData->timerPerformanceWarningFlag =
        (masterInfo.statisticsInfo.overCycle > 0) ? 1 : 0;

    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecClearMasterStatistics(ECDEV dev)
{
#if defined(WMX_VERSION_34U4_WIN) || defined(WMX_VERSION_34U4_RTX)
    // ResetTransmitStatisticsInfo is not available in WMX3.4
    (void)dev;
    return EC_API_ERROR_CODE_NOT_SUPPORTED;
#else
    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    long ret = ecat->ResetTransmitStatisticsInfo();
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
#endif
}

//=============================================================================
// Network Status APIs
//=============================================================================

extern "C" ECBROKER_API long __stdcall ecGetTotalSlaveCount(ECDEV dev, int* pCount)
{
    if (pCount == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    *pCount = static_cast<int>(masterInfo.numOfSlaves);
    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecGetOnlineSlaveCount(ECDEV dev, int* pCount)
{
    if (pCount == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    *pCount = masterInfo.GetOnlineSlaveCount();
    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecGetOfflineSlaveCount(ECDEV dev, int* pCount)
{
    if (pCount == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    *pCount = masterInfo.GetOfflineSlaveCount();
    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecGetUnknownSlaveCount(ECDEV dev, int* pCount)
{
    if (pCount == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    // Count new (unknown) slaves
    int unknownCount = 0;
    for (unsigned int i = 0; i < masterInfo.numOfSlaves; ++i) {
        if (masterInfo.slaves[i].newSlave) {
            unknownCount++;
        }
    }

    *pCount = unknownCount;
    return EC_SUCCESS;
}

//=============================================================================
// Slave Control APIs
//=============================================================================

extern "C" ECBROKER_API long __stdcall ecGetSlaveInfo(ECDEV dev, int nodeId, PEC_SLAVE_INFO pSlaveInfo)
{
    if (pSlaveInfo == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    if (nodeId < 0 || nodeId >= static_cast<int>(masterInfo.numOfSlaves)) {
        return EC_FAIL;
    }

    const wmx3Api::ecApi::EcSlaveInfo& slave = masterInfo.slaves[nodeId];

    // Initialize to zero
    memset(pSlaveInfo, 0, sizeof(EC_SLAVE_INFO));

    // Map slave info
    pSlaveInfo->online = slave.offline ? 0 : 1;
    pSlaveInfo->unknownSlave = slave.newSlave;
    pSlaveInfo->fullSizeDC = (slave.dcWidth == 2) ? 1 : 0;
    pSlaveInfo->aliasValid = (slave.alias != 0) ? 1 : 0;
    pSlaveInfo->alias = static_cast<short>(slave.alias);
    pSlaveInfo->vendorId = slave.vendorId;
    pSlaveInfo->productCode = slave.productCode;
    pSlaveInfo->serialNumber = slave.serialNo;
    pSlaveInfo->revision = slave.revisionNo;
    pSlaveInfo->configuredId = slave.id;
    pSlaveInfo->location = -slave.position;  // WMX 1.5 uses negative location
    pSlaveInfo->state = ConvertToSlaveState(slave.state);
    pSlaveInfo->alStatusCode = slave.alStatusCode;

    // Map neighbor info
    for (int i = 0; i < 4; ++i) {
        pSlaveInfo->child[i] = slave.neighbor[i];
        pSlaveInfo->portType[i] = slave.portState[i];
    }

    // Map application node info
    pSlaveInfo->appNodeCount = static_cast<int>(slave.numOfAxes);
    for (unsigned int i = 0; i < slave.numOfAxes && i < 8; ++i) {
        pSlaveInfo->appNode[i].axisNum = slave.axisInfo[i].axisIndex;
        pSlaveInfo->appNode[i].ioInSize = slave.axisInfo[i].digitalInputSize;
        pSlaveInfo->appNode[i].ioOutSize = slave.axisInfo[i].digitalOutputSize;
        pSlaveInfo->appNode[i].ioInAddress = slave.axisInfo[i].digitalInputAddr;
        pSlaveInfo->appNode[i].ioOutAddress = slave.axisInfo[i].digitalOutputAddr;
        pSlaveInfo->appNode[i].func.servoDrive =
            (slave.axisInfo[i].axisIndex >= 0) ? 1 : 0;
    }

    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecGetSlaveState(ECDEV dev, int configuredId, PEC_SLAVE_STATE pCurState)
{
    if (pCurState == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcMasterInfo masterInfo;
    long ret = ecat->GetMasterInfo(&masterInfo);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    // Find slave by configuredId
    for (unsigned int i = 0; i < masterInfo.numOfSlaves; ++i) {
        if (masterInfo.slaves[i].id == configuredId) {
            *pCurState = ConvertToSlaveState(masterInfo.slaves[i].state);
            return EC_SUCCESS;
        }
    }

    return EC_FAIL;
}

extern "C" ECBROKER_API long __stdcall ecSetSlaveState(ECDEV dev, int configuredId, EC_SLAVE_STATE newState)
{
    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::EcStateMachine::T wmx3State = ConvertFromSlaveState(newState);
    int errorCode = 0;

    long ret = ecat->ChangeSlaveState(configuredId, wmx3State, &errorCode);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
}

//=============================================================================
// SDO Communication APIs
//=============================================================================

extern "C" ECBROKER_API long __stdcall ecDownloadSDO(ECDEV dev, int configuredId,
    unsigned short index, unsigned char subIndex, int length,
    EC_MASTER_SDO_TYPE sdoType, unsigned char* data)
{
    if (data == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    unsigned int errCode = 0;
    wmx3Api::ecApi::EcSdoType::T wmx3SdoType = ConvertSdoType(sdoType);

    long ret = ecat->SdoDownload(configuredId, index, subIndex,
        wmx3SdoType, length, data, &errCode, 0);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecUploadSDO(ECDEV dev, int configuredId,
    unsigned short index, unsigned char subIndex, int length,
    EC_MASTER_SDO_TYPE sdoType, unsigned char* data)
{
    if (data == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    unsigned int actualSize = 0;
    unsigned int errCode = 0;
    wmx3Api::ecApi::EcSdoType::T wmx3SdoType = ConvertSdoType(sdoType);

    long ret = ecat->SdoUpload(configuredId, index, subIndex,
        wmx3SdoType, length, data, &actualSize, &errCode, 0);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
}

//=============================================================================
// HotConnect APIs
//=============================================================================

extern "C" ECBROKER_API long __stdcall ecStartHotConnect(ECDEV dev)
{
    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    long ret = ecat->StartHotconnect();
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecStartHotConnectWithRes(ECDEV dev)
{
    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    // Start HotConnect
    long ret = ecat->StartHotconnect();
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    // Poll until completion
    const int maxWait = 30000; // 30 seconds
    const int pollInterval = 100; // 100ms
    int waited = 0;

    while (waited < maxWait) {
        wmx3Api::ecApi::EcMasterInfo masterInfo;
        ret = ecat->GetMasterInfo(&masterInfo);
        if (ret != 0) {
            ctx->lastError = ret;
            return EC_FAIL;
        }

        if (masterInfo.statisticsInfo.hcState == wmx3Api::ecApi::EcHotconnectState::Idle) {
            // Check for abort
            if (masterInfo.statisticsInfo.hcAbortCode != wmx3Api::ecApi::EcHotconnectAbortCode::None) {
                return EC_FAIL;
            }
            return EC_SUCCESS;
        }

        Sleep(pollInterval);
        waited += pollInterval;
    }

    // Timeout
    return EC_FAIL;
}

extern "C" ECBROKER_API long __stdcall ecClearHotConnectAbortionFlag(ECDEV dev)
{
    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    // WMX3 does not have direct API for this
    // The flag is typically cleared on next successful HotConnect
    return EC_SUCCESS;
}

//=============================================================================
// Config APIs
//=============================================================================

extern "C" ECBROKER_API long __stdcall ecGetMasterConfigFilename(ECDEV dev, TCHAR* filename, int bufferSize)
{
    if (filename == NULL || bufferSize <= 0) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

#if defined(WMX_VERSION_34U4_WIN) || defined(WMX_VERSION_34U4_RTX)
    // GetEniFilePath is not available in WMX3.4
    (void)dev;
    filename[0] = '\0';
    return EC_API_ERROR_CODE_NOT_SUPPORTED;
#else
    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    long ret = ecat->GetEniFilePath(0, filename, bufferSize);

    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
#endif
}

extern "C" ECBROKER_API long __stdcall ecSetMasterConfigFilename(ECDEV dev, TCHAR* filename)
{
    if (filename == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

#ifdef UNICODE
    long ret = ecat->SetEniFilePath(0, filename);
#else
    long ret = ecat->SetEniFilePath(0, filename);
#endif

    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
}

//=============================================================================
// Raw Register Read/Write APIs
//=============================================================================

extern "C" ECBROKER_API long __stdcall ecRawWrite(ECDEV dev, int location, unsigned short address, unsigned int size, unsigned char* data)
{
    if (data == NULL || size == 0) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    // WMX 1.5 location uses negative values for slave position
    // Convert to WMX3 slaveId (0-based index)
    int slaveId = (location < 0) ? -location : location;

    // WMX3 RegisterWrite: slaveId, regAddr, len, data
    long ret = ecat->RegisterWrite(slaveId, static_cast<int>(address), static_cast<int>(size), data);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
}

extern "C" ECBROKER_API long __stdcall ecRawRead(ECDEV dev, int location, unsigned short address, unsigned int size, unsigned char* data)
{
    if (data == NULL || size == 0) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = EcDeviceManager::GetInstance()->GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    wmx3Api::ecApi::Ecat* ecat = GET_SHARED_ECAT();
    if (ecat == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    // WMX 1.5 location uses negative values for slave position
    // Convert to WMX3 slaveId (0-based index)
    int slaveId = (location < 0) ? -location : location;

    // WMX3 RegisterRead: slaveId, regAddr, len, buff
    long ret = ecat->RegisterRead(slaveId, static_cast<int>(address), static_cast<int>(size), data);
    if (ret != 0) {
        ctx->lastError = ret;
        return EC_FAIL;
    }

    return EC_SUCCESS;
}
