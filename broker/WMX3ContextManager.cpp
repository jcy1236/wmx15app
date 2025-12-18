// WMX3ContextManager.cpp
// Shared WMX3 context manager implementation

#include "WMX3ContextManager.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"
#include "AdvancedMotionApi.h"
#include "IOApi.h"
// Include WMX3's EcApi.h (WMX3 Include path has priority in AdditionalIncludeDirectories)
#include "EcApi.h"
#include "EventApi.h"

#include <tchar.h>
#include <cstdio>

// Static instance
WMX3ContextManager* WMX3ContextManager::s_instance = NULL;

// Fixed WMX3 installation path - use explicit char*/wchar_t* to avoid TCHAR ambiguity
// with WMX3 SDK overloads (WMX3.4 uses char*/wchar_t*, WMX3.6 uses const char*/const wchar_t*)
#ifdef UNICODE
static const wchar_t* WMX3_PATH = L"C:\\Program Files\\SoftServo\\WMX3";
static const wchar_t* WMX3_LIB_PATH = L"C:\\Program Files\\SoftServo\\WMX3\\Lib";
static const wchar_t* WMX3_IMDLL_PATH = L"C:\\Program Files\\SoftServo\\WMX3\\Lib\\IMDll.dll";
#else
static const char* WMX3_PATH = "C:\\Program Files\\SoftServo\\WMX3";
static const char* WMX3_LIB_PATH = "C:\\Program Files\\SoftServo\\WMX3\\Lib";
static const char* WMX3_IMDLL_PATH = "C:\\Program Files\\SoftServo\\WMX3\\Lib\\IMDll.dll";
#endif

WMX3ContextManager::WMX3ContextManager()
    : m_wmx3(NULL)
    , m_coreMotion(NULL)
    , m_advancedMotion(NULL)
    , m_io(NULL)
    , m_ecat(NULL)
    , m_eventControl(NULL)
    , m_refCount(0)
{
    InitializeCriticalSection(&m_cs);
}

WMX3ContextManager::~WMX3ContextManager()
{
    // Force close if still active
    EnterCriticalSection(&m_cs);
    if (m_wmx3 != NULL) {
        CloseDeviceInternal();
    }
    LeaveCriticalSection(&m_cs);
    DeleteCriticalSection(&m_cs);
}

WMX3ContextManager* WMX3ContextManager::GetInstance()
{
    if (s_instance == NULL) {
        s_instance = new WMX3ContextManager();
    }
    return s_instance;
}

void WMX3ContextManager::DestroyInstance()
{
    if (s_instance != NULL) {
        delete s_instance;
        s_instance = NULL;
    }
}

long WMX3ContextManager::CreateDeviceInternal()
{
    // Set DLL search path for WMX3 libraries
    SetDllDirectory(WMX3_LIB_PATH);

    // Load IMDll.dll from absolute path to avoid loading from executable directory
    LoadLibraryEx(WMX3_IMDLL_PATH, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

    // Create WMX3Api instance
    m_wmx3 = new wmx3Api::WMX3Api();
    if (m_wmx3 == NULL) {
        return -1;
    }

    // Create WMX3 device
    // WMX3.4 SDK uses char*/wchar_t* (non-const)
    // WMX3.6 SDK uses const char*/const wchar_t*
    // Use const_cast for WMX3.4 compatibility
#ifdef UNICODE
    long ret = m_wmx3->CreateDevice(const_cast<wchar_t*>(WMX3_PATH), wmx3Api::DeviceType::DeviceTypeNormal);
#else
    long ret = m_wmx3->CreateDevice(const_cast<char*>(WMX3_PATH), wmx3Api::DeviceType::DeviceTypeNormal);
#endif
    if (ret != 0) {
        delete m_wmx3;
        m_wmx3 = NULL;
        return ret;
    }

    // WMX3.4 SDK uses char*/wchar_t* (non-const)
    // WMX3.6 SDK uses const char*/const wchar_t*
    // Use const_cast for WMX3.4 compatibility
#ifdef UNICODE
    m_wmx3->SetDeviceName(const_cast<wchar_t*>(L"WMXBroker"));
#else
    m_wmx3->SetDeviceName(const_cast<char*>("WMXBroker"));
#endif

    // Create CoreMotion module
    m_coreMotion = new wmx3Api::CoreMotion(m_wmx3);
    if (m_coreMotion == NULL) {
        m_wmx3->CloseDevice();
        delete m_wmx3;
        m_wmx3 = NULL;
        return -1;
    }

    // Create Io module
    m_io = new wmx3Api::Io(m_wmx3);
    if (m_io == NULL) {
        delete m_coreMotion;
        m_coreMotion = NULL;
        m_wmx3->CloseDevice();
        delete m_wmx3;
        m_wmx3 = NULL;
        return -1;
    }

    // Create AdvancedMotion module (for coordinated motion)
    m_advancedMotion = new wmx3Api::AdvancedMotion(m_wmx3);
    if (m_advancedMotion == NULL) {
        delete m_io;
        m_io = NULL;
        delete m_coreMotion;
        m_coreMotion = NULL;
        m_wmx3->CloseDevice();
        delete m_wmx3;
        m_wmx3 = NULL;
        return -1;
    }

    // Create Ecat module (for EC_Network_Api)
    m_ecat = new wmx3Api::ecApi::Ecat(m_wmx3);
    if (m_ecat == NULL) {
        delete m_advancedMotion;
        m_advancedMotion = NULL;
        delete m_io;
        m_io = NULL;
        delete m_coreMotion;
        m_coreMotion = NULL;
        m_wmx3->CloseDevice();
        delete m_wmx3;
        m_wmx3 = NULL;
        return -1;
    }

    // Create EventControl module
    m_eventControl = new wmx3Api::EventControl(m_wmx3);
    if (m_eventControl == NULL) {
        delete m_ecat;
        m_ecat = NULL;
        delete m_advancedMotion;
        m_advancedMotion = NULL;
        delete m_io;
        m_io = NULL;
        delete m_coreMotion;
        m_coreMotion = NULL;
        m_wmx3->CloseDevice();
        delete m_wmx3;
        m_wmx3 = NULL;
        return -1;
    }

    return 0;
}

void WMX3ContextManager::CloseDeviceInternal()
{
    if (m_eventControl != NULL) {
        delete m_eventControl;
        m_eventControl = NULL;
    }

    if (m_ecat != NULL) {
        delete m_ecat;
        m_ecat = NULL;
    }

    if (m_advancedMotion != NULL) {
        delete m_advancedMotion;
        m_advancedMotion = NULL;
    }

    if (m_io != NULL) {
        delete m_io;
        m_io = NULL;
    }

    if (m_coreMotion != NULL) {
        delete m_coreMotion;
        m_coreMotion = NULL;
    }

    if (m_wmx3 != NULL) {
        m_wmx3->CloseDevice();
        delete m_wmx3;
        m_wmx3 = NULL;
    }
}

long WMX3ContextManager::AcquireDevice()
{
    EnterCriticalSection(&m_cs);

    // First acquisition - create device
    if (m_refCount == 0) {
        long ret = CreateDeviceInternal();
        if (ret != 0) {
            LeaveCriticalSection(&m_cs);
            return ret;
        }
    }

    m_refCount++;
    LeaveCriticalSection(&m_cs);
    return 0;
}

void WMX3ContextManager::ReleaseDevice()
{
    EnterCriticalSection(&m_cs);

    if (m_refCount > 0) {
        m_refCount--;

        // Last release - close device
        if (m_refCount == 0) {
            CloseDeviceInternal();
        }
    }

    LeaveCriticalSection(&m_cs);
}
