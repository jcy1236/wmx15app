// WMXBroker.cpp
// WMX 1.5 API to WMX3 API Broker Implementation

#include "WMXBroker.h"
#include "WMX3ContextManager.h"
#include "StatusMapper.h"
#include "BasicMotionBroker.h"
#include "ExtMotion1Broker.h"
#include "ExtMotion2Broker.h"
#include "ExtList2Broker.h"
#include "AxisControlBroker.h"
#include "HomeBroker.h"
#include "ConfigBroker.h"
#include "BasicVelocityBroker.h"
#include "ExtVelocity2Broker.h"
#include "TorqueControlBroker.h"
#include "WMXBrokerC.h"  // For WMXBroker_SetGlobalInstance/ClearGlobalInstance
#include <tchar.h>
#include <cstdio>

// WMX3 headers
#include "WMX3Api.h"
#include "CoreMotionApi.h"
#include "IOApi.h"

namespace wmxAPI
{

    //////////////////////////////////////////////////////////////////////////
    // WMXLIB class implementation
    //////////////////////////////////////////////////////////////////////////

    WMXLIB::WMXLIB()
        : wmx3(nullptr), coreMotion(nullptr), advancedMotion(nullptr), wmx3Io(nullptr), isConnected(false)
        , BasicMotion(nullptr), ExtMotion1(nullptr), ExtMotion2(nullptr), ExtList2(nullptr)
        , AxisControl(nullptr), Home(nullptr), Config(nullptr)
        , BasicVelocity(nullptr), ExtVelocity2(nullptr), TorqueControl(nullptr)
        , lastError(WMX_API_ERROR_CODE())
    {
        // Create Io class instance
        io = new common::Io(this);

        // Initialize initial output buffer
        memset(initialOut, 0, sizeof(initialOut));

        // Register this instance as global (first instance becomes g_wmxlib)
        WMXBroker_SetGlobalInstance(this);
    }

    WMXLIB::~WMXLIB()
    {
        if (isConnected)
        {
            CloseDevice();
        }

        delete io;
        io = nullptr;

        // Motion namespaces are deleted in CloseDevice()

        // Clear global instance if this was the registered one
        WMXBroker_ClearGlobalInstance(this);
    }

    WMXAPIFUNC WMXLIB::CreateDevice(TCHAR *path, PLTFRM_TYPE type)
    {
        // Use shared WMX3 context manager
        WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
        long ret = ctx->AcquireDevice();
        if (ret != 0)
        {
            return ret;
        }

        // Get shared WMX3 objects (owned by WMX3ContextManager)
        wmx3 = ctx->GetWMX3();
        coreMotion = ctx->GetCoreMotion();
        advancedMotion = ctx->GetAdvancedMotion();
        wmx3Io = ctx->GetIo();

        // Create Motion namespace instances (owned by WMXLIB) - PascalCase
        BasicMotion = new wmxAPI::BasicMotion::BasicMotion(this);
        ExtMotion1 = new wmxAPI::ExtMotion1::ExtMotion1(this);
        ExtMotion2 = new wmxAPI::ExtMotion2::ExtMotion2(this);
        ExtList2 = new wmxAPI::ExtList2::ExtList2(this);

        // Create new namespace instances
        AxisControl = new axisControl::AxisControl(this);
        Home = new home::Home(this);
        Config = new config::Config(this);
        BasicVelocity = new basicVelocity::BasicVelocity(this);
        ExtVelocity2 = new extVelocity2::ExtVelocity2(this);
        TorqueControl = new torque::TorqueControl(this);

        isConnected = true;
        return 0;
    }

    WMXAPIFUNC WMXLIB::CloseDevice()
    {
        // Delete new namespace instances
        if (TorqueControl)
        {
            delete TorqueControl;
            TorqueControl = nullptr;
        }

        if (ExtVelocity2)
        {
            delete ExtVelocity2;
            ExtVelocity2 = nullptr;
        }

        if (BasicVelocity)
        {
            delete BasicVelocity;
            BasicVelocity = nullptr;
        }

        if (Config)
        {
            delete Config;
            Config = nullptr;
        }

        if (Home)
        {
            delete Home;
            Home = nullptr;
        }

        if (AxisControl)
        {
            delete AxisControl;
            AxisControl = nullptr;
        }

        // Delete Motion namespace instances (owned by WMXLIB) - PascalCase
        if (ExtList2)
        {
            delete ExtList2;
            ExtList2 = nullptr;
        }

        if (ExtMotion2)
        {
            delete ExtMotion2;
            ExtMotion2 = nullptr;
        }

        if (ExtMotion1)
        {
            delete ExtMotion1;
            ExtMotion1 = nullptr;
        }

        if (BasicMotion)
        {
            delete BasicMotion;
            BasicMotion = nullptr;
        }

        // Clear pointers to shared objects (do NOT delete - owned by WMX3ContextManager)
        wmx3Io = nullptr;
        advancedMotion = nullptr;
        coreMotion = nullptr;
        wmx3 = nullptr;

        // Release shared WMX3 context
        WMX3ContextManager::GetInstance()->ReleaseDevice();

        isConnected = false;
        return 0;
    }

    WMXAPIFUNC WMXLIB::StartCommunication()
    {
        if (!wmx3)
            return -1;

        // Call WMX3 StartCommunication with 5 second timeout
        return wmx3->StartCommunication(5000);
    }

    WMXAPIFUNC WMXLIB::StopCommunication()
    {
        if (!wmx3)
            return -1;

        return wmx3->StopCommunication();
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS *st)
    {
        if (!wmx3 || !coreMotion || !wmx3Io || !st)
            return -1;

        // Get WMX3 status
        wmx3Api::CoreMotionStatus wmx3Status;
        long ret = coreMotion->GetStatus(&wmx3Status);
        if (ret != 0)
            return ret;

        // Convert WMX3 status to WMX 1.5 status
        StatusMapper::MapStatus(wmx3Status, wmx3Io, st);

        return 0;
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS *st, short axis)
    {
        // Single axis status query - get all and use the specified axis
        return GetStatus(st);
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS *st, short firstAxis, short lastAxis)
    {
        // Range axis status query - get all and use the specified range
        return GetStatus(st);
    }

    WMXAPIFUNC WMXLIB::GetVersion(double *pCeVersion, double *pPeVersion)
    {
        if (!coreMotion)
            return -1;

        // Get WMX3 version
        int major, minor, revision, fix;
        long ret = coreMotion->GetVersion(&major, &minor, &revision, &fix);
        if (ret != 0)
            return ret;

        // Convert to WMX 1.5 format
        if (pCeVersion)
            *pCeVersion = major + minor / 1000.0;
        if (pPeVersion)
            *pPeVersion = revision + fix / 1000.0;

        return 0;
    }

    //////////////////////////////////////////////////////////////////////////
    // Extended System APIs
    //////////////////////////////////////////////////////////////////////////

    WMXAPIFUNC WMXLIB::GetLastError()
    {
        return lastError;
    }

    WMXAPIFUNC WMXLIB::SetDeviceName(const TCHAR *name)
    {
        if (!wmx3)
            return -1;
        return wmx3->SetDeviceName(name);
    }

    WMXAPIFUNC WMXLIB::GetActiveDeviceList(WMX_ACT_DEV_LIST *list)
    {
        if (!list)
            return -1;

        // WMX3 does not have direct equivalent - return current device info
        memset(list, 0, sizeof(WMX_ACT_DEV_LIST));
        if (isConnected)
        {
            list->count = 1;
            list->idList[0] = 0;
            list->typeList[0] = WMX_DEV_TYPE_NORMAL_DEVICE;
            _tcscpy_s(list->nameList[0], MAX_DEVICE_NAME_LENGTH, _T("WMXBroker"));
        }
        return 0;
    }

    WMXAPIFUNC WMXLIB::ForceCloseDevice(int id)
    {
        // Force close - same as CloseDevice
        // Clear pointers to shared objects (do NOT delete - owned by WMX3ContextManager)
        wmx3Io = nullptr;
        advancedMotion = nullptr;
        coreMotion = nullptr;
        wmx3 = nullptr;

        // Release shared WMX3 context
        WMX3ContextManager::GetInstance()->ReleaseDevice();

        isConnected = false;
        return 0;
    }

} // namespace wmxAPI
