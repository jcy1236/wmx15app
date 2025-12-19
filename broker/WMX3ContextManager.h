// WMX3ContextManager.h
// Shared WMX3 context manager with reference counting
// Provides singleton pattern for sharing WMX3Api instance across WMXLIB and EcFunctionManager

#ifndef WMX3_CONTEXT_MANAGER_H
#define WMX3_CONTEXT_MANAGER_H

#include <windows.h>

// Forward declarations for WMX3
namespace wmx3Api {
    class WMX3Api;
    class CoreMotion;
    class AdvancedMotion;
    class Io;
    class EventControl;
    class ApiBuffer;
    class Log;
    namespace ecApi {
        class Ecat;
    }
}

//=============================================================================
// WMX3ContextManager - Singleton class for sharing WMX3 context
//=============================================================================
class WMX3ContextManager {
private:
    // WMX3 objects (shared)
    wmx3Api::WMX3Api* m_wmx3;
    wmx3Api::CoreMotion* m_coreMotion;
    wmx3Api::AdvancedMotion* m_advancedMotion;
    wmx3Api::Io* m_io;
    wmx3Api::ecApi::Ecat* m_ecat;
    wmx3Api::EventControl* m_eventControl;
    wmx3Api::ApiBuffer* m_apiBuffer;
    wmx3Api::Log* m_log;

    // Reference counting
    int m_refCount;

    // Thread safety
    CRITICAL_SECTION m_cs;

    // Singleton instance
    static WMX3ContextManager* s_instance;

    // Private constructor/destructor for singleton
    WMX3ContextManager();
    ~WMX3ContextManager();

    // Prevent copying
    WMX3ContextManager(const WMX3ContextManager&);
    WMX3ContextManager& operator=(const WMX3ContextManager&);

    // Internal device creation
    long CreateDeviceInternal();
    void CloseDeviceInternal();

public:
    // Singleton access
    static WMX3ContextManager* GetInstance();
    static void DestroyInstance();

    // Reference counting based device management
    // AcquireDevice: Increment ref count, create device on first call
    // Returns: 0 on success, error code on failure
    long AcquireDevice();

    // ReleaseDevice: Decrement ref count, close device when count reaches 0
    void ReleaseDevice();

    // Check if device is active
    bool IsDeviceActive() const { return m_wmx3 != NULL; }

    // Get current reference count
    int GetRefCount() const { return m_refCount; }

    // Shared object accessors
    wmx3Api::WMX3Api* GetWMX3() { return m_wmx3; }
    wmx3Api::CoreMotion* GetCoreMotion() { return m_coreMotion; }
    wmx3Api::AdvancedMotion* GetAdvancedMotion() { return m_advancedMotion; }
    wmx3Api::Io* GetIo() { return m_io; }
    wmx3Api::ecApi::Ecat* GetEcat() { return m_ecat; }
    wmx3Api::EventControl* GetEventControl() { return m_eventControl; }
    wmx3Api::ApiBuffer* GetApiBuffer() { return m_apiBuffer; }
    wmx3Api::Log* GetLog() { return m_log; }
};

#endif // WMX3_CONTEXT_MANAGER_H
