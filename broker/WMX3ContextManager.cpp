// WMX3ContextManager.cpp
// Shared WMX3 context manager implementation

#include "WMX3ContextManager.h"
#include "WMX3Api.h"
#include "CoreMotionApi.h"
#include "IOApi.h"
// Include WMX3's EcApi.h (not WMX1.5's) using full path to avoid conflict
#include "C:/Program Files/SoftServo/WMX3/Include/EcApi.h"

#include <tchar.h>
#include <cstdio>

// Static instance
WMX3ContextManager* WMX3ContextManager::s_instance = NULL;

// Fixed WMX3 installation path
static const TCHAR* WMX3_PATH = _T("C:\\Program Files\\SoftServo\\WMX3");

WMX3ContextManager::WMX3ContextManager()
    : m_wmx3(NULL)
    , m_coreMotion(NULL)
    , m_io(NULL)
    , m_ecat(NULL)
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
    TCHAR dllPath[MAX_PATH];
    _stprintf_s(dllPath, MAX_PATH, _T("%s\\Lib"), WMX3_PATH);
    SetDllDirectory(dllPath);

    // Load IMDll.dll from absolute path to avoid loading from executable directory
    LoadLibraryEx(_T("C:\\Program Files\\SoftServo\\WMX3\\Lib\\IMDll.dll"), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

    // Create WMX3Api instance
    m_wmx3 = new wmx3Api::WMX3Api();
    if (m_wmx3 == NULL) {
        return -1;
    }

    // Create WMX3 device
    long ret = m_wmx3->CreateDevice(WMX3_PATH, wmx3Api::DeviceType::DeviceTypeNormal);
    if (ret != 0) {
        delete m_wmx3;
        m_wmx3 = NULL;
        return ret;
    }

    m_wmx3->SetDeviceName(_T("WMXBroker"));

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

    // Create Ecat module (for EC_Network_Api)
    m_ecat = new wmx3Api::ecApi::Ecat(m_wmx3);
    if (m_ecat == NULL) {
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
    if (m_ecat != NULL) {
        delete m_ecat;
        m_ecat = NULL;
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
