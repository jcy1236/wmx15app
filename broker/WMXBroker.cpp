// WMXBroker.cpp
// WMX 1.5 API to WMX3 API Broker Implementation

#include "WMXBroker.h"
#include "StatusMapper.h"
#include "BasicMotionBroker.h"
#include "ExtMotion1Broker.h"
#include "ExtMotion2Broker.h"
#include "ExtList2Broker.h"
#include <tchar.h>
#include <cstdio>

// WMX3 headers
#include "WMX3Api.h"
#include "CoreMotionApi.h"
#include "IOApi.h"

namespace wmxAPI {

    //////////////////////////////////////////////////////////////////////////
    // WMXLIB class implementation
    //////////////////////////////////////////////////////////////////////////

    WMXLIB::WMXLIB()
        : wmx3(nullptr)
        , coreMotion(nullptr)
        , wmx3Io(nullptr)
        , isConnected(false)
        , basicMotion(nullptr)
        , extMotion1(nullptr)
        , extMotion2(nullptr)
        , extList2(nullptr)
        , lastError(WMX_API_ERROR_CODE())
    {
        // Create Io class instance
        io = new common::Io(this);

        // Initialize initial output buffer
        memset(initialOut, 0, sizeof(initialOut));
    }

    WMXLIB::~WMXLIB()
    {
        if (isConnected) {
            CloseDevice();
        }

        delete io;
        io = nullptr;

        // Motion namespaces are deleted in CloseDevice()
    }

    WMXAPIFUNC WMXLIB::CreateDevice(TCHAR* path, PLTFRM_TYPE type)
    {
        // Set DLL search path for WMX3 libraries
        TCHAR dllPath[MAX_PATH];
        _stprintf_s(dllPath, MAX_PATH, _T("%s\\Lib"), path);
        SetDllDirectory(dllPath);

        // Create WMX3 API instance
        wmx3 = new wmx3Api::WMX3Api();

        // Create WMX3 device
        // path is used as WMX3 installation path (e.g., "C:\Program Files\SoftServo\WMX3")
        long ret = wmx3->CreateDevice(path, wmx3Api::DeviceType::DeviceTypeNormal);
        if (ret != 0) {
            delete wmx3;
            wmx3 = nullptr;
            return ret;
        }

        wmx3->SetDeviceName(_T("WMXBroker"));
        // Create CoreMotion module
        coreMotion = new wmx3Api::CoreMotion(wmx3);

        // Create Io module
        wmx3Io = new wmx3Api::Io(wmx3);

        // Create Motion namespace instances
        basicMotion = new basicMotion::BasicMotion(this);
        extMotion1 = new extMotion1::ExtMotion1(this);
        extMotion2 = new extMotion2::ExtMotion2(this);
        extList2 = new extList2::ExtList2(this);

        isConnected = true;
        return 0;
    }

    WMXAPIFUNC WMXLIB::CloseDevice()
    {
        // Delete Motion namespace instances
        if (extList2) {
            delete extList2;
            extList2 = nullptr;
        }
        if (extMotion2) {
            delete extMotion2;
            extMotion2 = nullptr;
        }
        if (extMotion1) {
            delete extMotion1;
            extMotion1 = nullptr;
        }
        if (basicMotion) {
            delete basicMotion;
            basicMotion = nullptr;
        }

        if (wmx3Io) {
            delete wmx3Io;
            wmx3Io = nullptr;
        }

        if (coreMotion) {
            delete coreMotion;
            coreMotion = nullptr;
        }

        if (wmx3) {
            wmx3->CloseDevice();
            delete wmx3;
            wmx3 = nullptr;
        }

        isConnected = false;
        return 0;
    }

    WMXAPIFUNC WMXLIB::StartCommunication()
    {
        if (!wmx3) return -1;

        // Call WMX3 StartCommunication with 5 second timeout
        return wmx3->StartCommunication(5000);
    }

    WMXAPIFUNC WMXLIB::StopCommunication()
    {
        if (!wmx3) return -1;

        return wmx3->StopCommunication();
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS* st)
    {
        if (!wmx3 || !coreMotion || !wmx3Io || !st) return -1;

        // Get WMX3 status
        wmx3Api::CoreMotionStatus wmx3Status;
        long ret = coreMotion->GetStatus(&wmx3Status);
        if (ret != 0) return ret;

        // Convert WMX3 status to WMX 1.5 status
        StatusMapper::MapStatus(wmx3Status, wmx3Io, st);

        return 0;
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS* st, short axis)
    {
        // Single axis status query - get all and use the specified axis
        return GetStatus(st);
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS* st, short firstAxis, short lastAxis)
    {
        // Range axis status query - get all and use the specified range
        return GetStatus(st);
    }

    WMXAPIFUNC WMXLIB::GetVersion(double* pCeVersion, double* pPeVersion)
    {
        if (!coreMotion) return -1;

        // Get WMX3 version
        int major, minor, revision, fix;
        long ret = coreMotion->GetVersion(&major, &minor, &revision, &fix);
        if (ret != 0) return ret;

        // Convert to WMX 1.5 format
        if (pCeVersion) *pCeVersion = major + minor / 1000.0;
        if (pPeVersion) *pPeVersion = revision + fix / 1000.0;

        return 0;
    }

    //////////////////////////////////////////////////////////////////////////
    // Extended System APIs
    //////////////////////////////////////////////////////////////////////////

    WMXAPIFUNC WMXLIB::GetLastError()
    {
        return lastError;
    }

    WMXAPIFUNC WMXLIB::SetDeviceName(TCHAR* name)
    {
        if (!wmx3) return -1;
        return wmx3->SetDeviceName(name);
    }

    WMXAPIFUNC WMXLIB::GetActiveDeviceList(WMX_ACT_DEV_LIST* list)
    {
        if (!list) return -1;

        // WMX3 does not have direct equivalent - return current device info
        memset(list, 0, sizeof(WMX_ACT_DEV_LIST));
        if (isConnected) {
            list->count = 1;
            list->idList[0] = 0;
            list->typeList[0] = WMX_DEV_TYPE_NORMAL_DEVICE;
            _tcscpy_s(list->nameList[0], MAX_DEVICE_NAME_LENGTH, _T("WMXBroker"));
        }
        return 0;
    }

    WMXAPIFUNC WMXLIB::ForceCloseDevice(int id)
    {
        // Force close - same as CloseDevice but without error checking
        if (wmx3Io) {
            delete wmx3Io;
            wmx3Io = nullptr;
        }

        if (coreMotion) {
            delete coreMotion;
            coreMotion = nullptr;
        }

        if (wmx3) {
            wmx3->CloseDevice();
            delete wmx3;
            wmx3 = nullptr;
        }

        isConnected = false;
        return 0;
    }

} // namespace wmxAPI
