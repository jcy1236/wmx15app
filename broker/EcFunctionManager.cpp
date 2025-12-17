// EcFunctionManager.cpp
// ECDEV handle to WMX3 object mapping manager implementation
// Uses WMX3ContextManager for shared WMX3 instance

#include "EcFunctionManager.h"
#include "WMX3ContextManager.h"
#include "WMX3Api.h"
// Include WMX3's EcApi.h (WMX3 Include path has priority in AdditionalIncludeDirectories)
#include "EcApi.h"

// Static instance
EcFunctionManager* EcFunctionManager::s_instance = NULL;

EcFunctionManager::EcFunctionManager()
    : m_nextDeviceId(1)
    , m_nextHandleId(1)
{
    InitializeCriticalSection(&m_cs);
}

EcFunctionManager::~EcFunctionManager()
{
    // Close all devices - release shared context for each
    EnterCriticalSection(&m_cs);
    for (std::map<ECDEV, EcDeviceContext>::iterator it = m_devices.begin();
         it != m_devices.end(); ++it) {
        // Release shared WMX3 context
        WMX3ContextManager::GetInstance()->ReleaseDevice();
    }
    m_devices.clear();
    LeaveCriticalSection(&m_cs);
    DeleteCriticalSection(&m_cs);
}

EcFunctionManager* EcFunctionManager::GetInstance()
{
    if (s_instance == NULL) {
        s_instance = new EcFunctionManager();
    }
    return s_instance;
}

void EcFunctionManager::DestroyInstance()
{
    if (s_instance != NULL) {
        delete s_instance;
        s_instance = NULL;
    }
}

long EcFunctionManager::CreateDevice(PECDEV pDev)
{
    if (pDev == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    if (*pDev != NULL) {
        return EC_API_ERROR_CODE_DEVICE_POINTER_IS_NOT_NULL;
    }

    EnterCriticalSection(&m_cs);

    // Use shared WMX3 context manager
    WMX3ContextManager* ctxMgr = WMX3ContextManager::GetInstance();
    long ret = ctxMgr->AcquireDevice();
    if (ret != 0) {
        LeaveCriticalSection(&m_cs);
        return ret;
    }

    // Create unique handle using sequential ID
    ECDEV handle = (ECDEV)(ULONG_PTR)m_nextHandleId++;

    // Store context
    EcDeviceContext ctx;
    ctx.deviceId = m_nextDeviceId++;
    ctx.lastError = 0;

    m_devices[handle] = ctx;
    *pDev = handle;

    LeaveCriticalSection(&m_cs);
    return EC_SUCCESS;
}

long EcFunctionManager::CloseDevice(ECDEV dev)
{
    if (dev == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    EnterCriticalSection(&m_cs);

    std::map<ECDEV, EcDeviceContext>::iterator it = m_devices.find(dev);
    if (it == m_devices.end()) {
        LeaveCriticalSection(&m_cs);
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    // Release shared WMX3 context
    WMX3ContextManager::GetInstance()->ReleaseDevice();

    m_devices.erase(it);

    LeaveCriticalSection(&m_cs);
    return EC_SUCCESS;
}

EcDeviceContext* EcFunctionManager::GetContext(ECDEV dev)
{
    if (dev == NULL) {
        return NULL;
    }

    EnterCriticalSection(&m_cs);

    std::map<ECDEV, EcDeviceContext>::iterator it = m_devices.find(dev);
    if (it == m_devices.end()) {
        LeaveCriticalSection(&m_cs);
        return NULL;
    }

    EcDeviceContext* ctx = &(it->second);
    LeaveCriticalSection(&m_cs);
    return ctx;
}

long EcFunctionManager::GetLastError(ECDEV dev)
{
    EcDeviceContext* ctx = GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }
    return ctx->lastError;
}

void EcFunctionManager::SetLastError(ECDEV dev, long error)
{
    EcDeviceContext* ctx = GetContext(dev);
    if (ctx != NULL) {
        ctx->lastError = error;
    }
}

long EcFunctionManager::GetDeviceID(ECDEV dev, int* pId)
{
    if (pId == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EcDeviceContext* ctx = GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    *pId = ctx->deviceId;
    return EC_SUCCESS;
}

long EcFunctionManager::GetDeviceCount(ECDEV dev, int* pCount)
{
    if (pCount == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    if (dev == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }

    EnterCriticalSection(&m_cs);
    *pCount = static_cast<int>(m_devices.size());
    LeaveCriticalSection(&m_cs);

    return EC_SUCCESS;
}

long EcFunctionManager::GetActiveDeviceList(EC_ACT_DEV_LIST* list)
{
    if (list == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    EnterCriticalSection(&m_cs);

    list->count = 0;
    for (std::map<ECDEV, EcDeviceContext>::iterator it = m_devices.begin();
         it != m_devices.end() && list->count < MAX_DATA_CHANNEL_INSTANCES; ++it) {
        list->idList[list->count++] = it->second.deviceId;
    }

    LeaveCriticalSection(&m_cs);
    return EC_SUCCESS;
}

long EcFunctionManager::ForceCloseDevice(int deviceId)
{
    EnterCriticalSection(&m_cs);

    for (std::map<ECDEV, EcDeviceContext>::iterator it = m_devices.begin();
         it != m_devices.end(); ++it) {
        if (it->second.deviceId == deviceId) {
            // Release shared WMX3 context
            WMX3ContextManager::GetInstance()->ReleaseDevice();
            m_devices.erase(it);
            LeaveCriticalSection(&m_cs);
            return EC_SUCCESS;
        }
    }

    LeaveCriticalSection(&m_cs);
    return EC_FAIL;
}
