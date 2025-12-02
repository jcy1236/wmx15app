// EcDeviceManager.cpp
// ECDEV handle to WMX3 object mapping manager implementation

#include "EcDeviceManager.h"
#include "WMX3Api.h"
// Include WMX3's EcApi.h (not WMX1.5's) using full path to avoid conflict
#include "C:/Program Files/SoftServo/WMX3/Include/EcApi.h"

// Static instance
EcDeviceManager* EcDeviceManager::s_instance = NULL;

EcDeviceManager::EcDeviceManager()
    : m_nextDeviceId(1)
{
    InitializeCriticalSection(&m_cs);
}

EcDeviceManager::~EcDeviceManager()
{
    // Close all devices
    EnterCriticalSection(&m_cs);
    for (std::map<ECDEV, EcDeviceContext>::iterator it = m_devices.begin();
         it != m_devices.end(); ++it) {
        if (it->second.ecat) {
            delete it->second.ecat;
        }
        if (it->second.wmx3) {
            it->second.wmx3->CloseDevice();
            delete it->second.wmx3;
        }
    }
    m_devices.clear();
    LeaveCriticalSection(&m_cs);
    DeleteCriticalSection(&m_cs);
}

EcDeviceManager* EcDeviceManager::GetInstance()
{
    if (s_instance == NULL) {
        s_instance = new EcDeviceManager();
    }
    return s_instance;
}

void EcDeviceManager::DestroyInstance()
{
    if (s_instance != NULL) {
        delete s_instance;
        s_instance = NULL;
    }
}

long EcDeviceManager::CreateDevice(PECDEV pDev)
{
    if (pDev == NULL) {
        return EC_API_ERROR_CODE_NULL_ARG;
    }

    if (*pDev != NULL) {
        return EC_API_ERROR_CODE_DEVICE_POINTER_IS_NOT_NULL;
    }

    EnterCriticalSection(&m_cs);

    // Create WMX3Api instance
    wmx3Api::WMX3Api* wmx3 = new wmx3Api::WMX3Api();
    if (wmx3 == NULL) {
        LeaveCriticalSection(&m_cs);
        return EC_FAIL;
    }

    // Open WMX3 device (use NULL path for default installation)
    long ret = wmx3->CreateDevice((const char*)NULL, wmx3Api::DeviceType::DeviceTypeNormal);
    if (ret != 0) {
        delete wmx3;
        LeaveCriticalSection(&m_cs);
        return ret;
    }

    // Create Ecat instance
    wmx3Api::ecApi::Ecat* ecat = new wmx3Api::ecApi::Ecat(wmx3);
    if (ecat == NULL) {
        wmx3->CloseDevice();
        delete wmx3;
        LeaveCriticalSection(&m_cs);
        return EC_FAIL;
    }

    // Create handle (use unique pointer as handle)
    ECDEV handle = (ECDEV)ecat;

    // Store context
    EcDeviceContext ctx;
    ctx.wmx3 = wmx3;
    ctx.ecat = ecat;
    ctx.deviceId = m_nextDeviceId++;
    ctx.lastError = 0;

    m_devices[handle] = ctx;
    *pDev = handle;

    LeaveCriticalSection(&m_cs);
    return EC_SUCCESS;
}

long EcDeviceManager::CloseDevice(ECDEV dev)
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

    // Cleanup
    if (it->second.ecat) {
        delete it->second.ecat;
    }
    if (it->second.wmx3) {
        it->second.wmx3->CloseDevice();
        delete it->second.wmx3;
    }

    m_devices.erase(it);

    LeaveCriticalSection(&m_cs);
    return EC_SUCCESS;
}

EcDeviceContext* EcDeviceManager::GetContext(ECDEV dev)
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

long EcDeviceManager::GetLastError(ECDEV dev)
{
    EcDeviceContext* ctx = GetContext(dev);
    if (ctx == NULL) {
        return EC_API_ERROR_CODE_DEVICE_IS_NULL;
    }
    return ctx->lastError;
}

void EcDeviceManager::SetLastError(ECDEV dev, long error)
{
    EcDeviceContext* ctx = GetContext(dev);
    if (ctx != NULL) {
        ctx->lastError = error;
    }
}

long EcDeviceManager::GetDeviceID(ECDEV dev, int* pId)
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

long EcDeviceManager::GetDeviceCount(ECDEV dev, int* pCount)
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

long EcDeviceManager::GetActiveDeviceList(EC_ACT_DEV_LIST* list)
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

long EcDeviceManager::ForceCloseDevice(int deviceId)
{
    EnterCriticalSection(&m_cs);

    for (std::map<ECDEV, EcDeviceContext>::iterator it = m_devices.begin();
         it != m_devices.end(); ++it) {
        if (it->second.deviceId == deviceId) {
            // Cleanup
            if (it->second.ecat) {
                delete it->second.ecat;
            }
            if (it->second.wmx3) {
                it->second.wmx3->CloseDevice();
                delete it->second.wmx3;
            }
            m_devices.erase(it);
            LeaveCriticalSection(&m_cs);
            return EC_SUCCESS;
        }
    }

    LeaveCriticalSection(&m_cs);
    return EC_FAIL;
}
