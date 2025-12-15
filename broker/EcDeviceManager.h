// EcDeviceManager.h
// ECDEV handle to WMX3 object mapping manager
// Provides singleton pattern for managing EC device handles

#ifndef EC_DEVICE_MANAGER_H
#define EC_DEVICE_MANAGER_H

#include <windows.h>
#include <map>

//=============================================================================
// WMX 1.5 EC_Network_Api type definitions (avoid header conflict with WMX3)
//=============================================================================

// Device descriptor type
typedef HANDLE ECDEV, *PECDEV;

// Error codes from EC_Network_Api_Err.h
#define EC_FAIL                                     0
#define EC_SUCCESS                                  1
#define EC_API_ERROR_CODE_NULL_ARG                  0x20000001
#define EC_API_ERROR_CODE_DEVICE_IS_NULL            0x00000131
#define EC_API_ERROR_CODE_DEVICE_POINTER_IS_NOT_NULL 0x00000132
#define EC_API_ERROR_CODE_NOT_SUPPORTED             0x20000002

// Maximum data channel instances
#ifndef MAX_DATA_CHANNEL_INSTANCES
#define MAX_DATA_CHANNEL_INSTANCES 256
#endif

// Active device list structure
typedef struct {
    int count;
    int idList[MAX_DATA_CHANNEL_INSTANCES];
} EC_ACT_DEV_LIST, *PEC_ACT_DEV_LIST;

//=============================================================================
// Forward declarations for WMX3
//=============================================================================
namespace wmx3Api {
    class WMX3Api;
    namespace ecApi {
        class Ecat;
    }
}

//=============================================================================
// Device context structure
// Note: wmx3 and ecat are now shared via WMX3ContextManager
//=============================================================================
struct EcDeviceContext {
    int deviceId;
    long lastError;

    EcDeviceContext() : deviceId(0), lastError(0) {}
};

//=============================================================================
// EcDeviceManager - Singleton class for managing ECDEV handles
// Uses WMX3ContextManager for shared WMX3 instance
//=============================================================================
class EcDeviceManager {
private:
    std::map<ECDEV, EcDeviceContext> m_devices;
    int m_nextDeviceId;
    int m_nextHandleId;  // For generating unique ECDEV handles
    CRITICAL_SECTION m_cs;

    static EcDeviceManager* s_instance;

    // Private constructor for singleton
    EcDeviceManager();
    ~EcDeviceManager();

    // Prevent copying
    EcDeviceManager(const EcDeviceManager&);
    EcDeviceManager& operator=(const EcDeviceManager&);

public:
    // Singleton access
    static EcDeviceManager* GetInstance();
    static void DestroyInstance();

    // Device management
    long CreateDevice(PECDEV pDev);
    long CloseDevice(ECDEV dev);

    // Context access
    EcDeviceContext* GetContext(ECDEV dev);

    // Last error management
    long GetLastError(ECDEV dev);
    void SetLastError(ECDEV dev, long error);

    // Device info
    long GetDeviceID(ECDEV dev, int* pId);
    long GetDeviceCount(ECDEV dev, int* pCount);

    // Active device management
    long GetActiveDeviceList(EC_ACT_DEV_LIST* list);
    long ForceCloseDevice(int deviceId);
};

#endif // EC_DEVICE_MANAGER_H
