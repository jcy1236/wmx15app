// WMX3Api_Sim.h
// WMX3 Native API Header-only wrapper for VS2012 compatibility
// Provides wmx3Api namespace interface that internally calls WMX3Broker C API
//
// Usage:
//   Replace #include "WMX3Api.h" with #include "WMX3Api_Sim.h"
//   Link with WMXBroker.lib

#ifndef WMX3API_SIM_H
#define WMX3API_SIM_H

#include "WMX3BrokerC.h"
#include <windows.h>

namespace wmx3Api
{

    //=========================================================================
    // Constants (from WMX3Api.h)
    //=========================================================================
    namespace constants
    {
        static const int maxAxes = 128;
        static const int maxIoInSize = 8000;
        static const int maxIoOutSize = 8000;
        static const int maxDevices = 256;
        static const int maxInterrupts = 2;
        static const int maxDeviceName = 64;
    }

    //=========================================================================
    // ErrorCode class (from WMX3Api.h)
    //=========================================================================
    class ErrorCode
    {
    public:
        enum
        {
            None = 0x0,

            StartProcessFailed = 0x00000100,
            StartProcessNull,
            StartProcessMaxInstance,
            StartProcessLockError,
            StartProcessWaitEventFailed,
            StartProcessWaitTimeout,
            MemoryAllocFailed,
            IMLibIsNotRunning,
            ControlChannelLockFailed,
            ControlChannelEventFailed,
            ControlChannelWaitEventFailed,
            ControlChannelSharedMemoryFailed,
            ControlChannelLockWaitTimeOut,
            APIChannelError,
            APIChannelTimeOut,
            StatusChannelError,

            RtssFileNotFoundError,
            RtssStartError,
            RequestChannelTimeOut,
            FreeChannelTimeOut,
            CloseDeviceTimeOut,

            RequestChannelFailed,
            ReachMaxChannelNumber,
            FreeChannelFailed,
            InvalidChannelId,
            CloseDeviceFailed,

            StatusChannelNull,
            StatusChannelIdError,
            StatusSharedMemoryChannelIndexError,
            StatusChannelGettingInitialData,

            RequestQueueFailed,
            InvalidQueueId,
            InvalidQueueSize,
            RequestQueueTimeout,
            InvalidQueue,
            FreeQueueTimeout,
            InvalidQueueControlCommand,
            ControlQueueTimeout,
            SetQueueOptionsTimeout,
            FreeQueueFailed,
            RequestQueueIDAlreadyUsed,

            CreateDeviceLockError,
            CloseDeviceLockError,

            SetDeviceNameTimeout,
            GetActiveDeviceTimeout,

            DeviceIsNull,
            InvalidModuleId,
            InvalidDeterMode,
            NoSupportedFunction,
            CommandInvalidQueueId,
            CommandQueueAddFailed,
            CommandQueueIsFull,
            CommandQueueAddTimeOut,

            IMVersionMismatch,
            ModuleVersionMismatch,

            CommandIdLockError,
            CommandIdGetError,

            CallbackMallocFailed,
            CallbackThreadNull,
            CallbackThreadError,
            CallbackThreadTimeOut,

            IMLibNullParam,
            IMLibInvalidParam,

            ConflictingErrorCode,
            UtilDataChnlSizeTooSmall,
            UtilBuffAndDataSizeDiff,
            UtilNoEnoughDataChnlSize,
            UtilReachMaxDataChnlSize,
            UtilIndexOutOfRange,
            UtilInitFailed,
            UtilLockFailed,
            UtilQueueFull,
            UtilQueueEmpty,
            UtilBufferSizeNotEnough,

            WaitForDeviceEventTimeout,
            DeviceEventProcessFailed,
            ImCommandNotMatched,

            ApiLogCreateQueueFailed,
            ApiLogIsNotSet,
            ApiLogIsRunning,
            ApiLogIsNotRunning,
            ApiLogQueueError,
            ApiLogOpenFileFailed,
            ApiLogWriteFileFailed,
            ApiLogReadFileFailed,
            ApiLogFolderNotExist,
            ApiLogGetStatusError,

            SystemError = 0x00000500,
            SystemIsNoRunning,
            SystemInitializationNotDone,
            EngineNotStartedInSpecifiedTime,
            EngineNotStoppedInSpecifiedTime,
            CommNotStartedInSpecifiedTime,
            CommNotStoppedInSpecifiedTime,
            ModuleIsNotLoaded,
            StartCommunicationError,
            DeviceIsNotInUse,
            SetDeviceEventFailed,
            ResetDeviceEventFailed,
            WaitForDeviceEventFailed,

            Reserved = 0x00000600,
            CommNotStarted,
            CommNotStopped,
            VersionCheckError,
            CallbackFuncError,
            CallbackFuncTimeOut,
            CallbackFuncInvalidState,
            CallbackFuncInvalidMode,
            MissingRequiredRtdll,

            BusyReceivingAnotherAPICommand,
            NotIdleState,
            AxisOutOfRange,
            AxisCountOutOfRange,
            DuplicateAxis,
            IOAddressOutOfRange,
            IOSizeOutOfRange,
            ChannelOutOfRange,
            ChannelUninitialized,
            ChannelInUse,
            ArgumentOutOfRange,
            ArgumentIsNull,
            PrevSettingsBeingApplied,
            ParamOutOfRange,
            IDOutOfRange,
            IDNotDefined,
            ResourceInUse,
            FileOperationFailed,
            StartingPreviousCommand,
            StringConversionError,
            NoMotion,
            ServoOffline,
            ServoOff,
            AxisAmpAlarm,
            AxisSoftLimit,
            AxisNearLimit,
            AxisExternalLimit,
            AxisHardLimit,
            UserMemoryAddressOutOfRange,
            UserMemorySizeOutOfRange,
            InvalidCommandProcessingMode,
            InterruptMismatch,
            ErrorCodeNotDefined,
            BufferTooSmall,
            RequestedBufferTooLarge,
            RequestedBufferTooSmall,
            ModuleIDOutOfRange,
            UpdatesListUninitialized,
            UpdatesListDoesNotMatchInstalledUpdates,
            UpdatesListTimeout,

            UnknownError
        };
    };

    class EngineState
    {
    public:
        enum T
        {
            Idle,
            Running,
            Communicating,
            Shutdown,
            Unknown
        };
    };
    //=========================================================================
    // InterruptData class (from WMX3Api.h)
    //=========================================================================
    class InterruptData
    {
    public:
        InterruptData() {}

        int numOfAxes;
        int cycleTimeMicroseconds;
        long long cycleCounter;
    };

    //=========================================================================
    // EngineStatus class (from WMX3Api.h)
    //=========================================================================
    class EngineStatus
    {
    public:
        EngineStatus() {}

        EngineState::T state;
        unsigned int error;
        int numOfInterrupts;
        InterruptData interrupts[constants::maxInterrupts];
    };

    //=========================================================================
    // Enums (from WMX3Api.h)
    //=========================================================================
    class DeviceType
    {
    public:
        enum T
        {
            DeviceTypeNormal = 0,
            DeviceTypeLowPriority = 0x1,
            DeviceTypeExitWOCnt = 0x02,
            DeviceTypeLowpriorityExitWOCnt = 0x03
        };
    };

    //=========================================================================
    // DeviceInfoA class (from WMX3Api.h)
    //=========================================================================
    class DeviceInfoA
    {
    public:
        DeviceInfoA() : id(0), type(DeviceType::DeviceTypeNormal), watchdog(0), watchdogCount(0)
        {
            memset(name, 0, sizeof(name));
        }

        unsigned int id;
        DeviceType::T type;
        unsigned int watchdog;
        unsigned int watchdogCount;
        char name[constants::maxDeviceName];
    };

    //=========================================================================
    // DevicesInfoA class (from WMX3Api.h)
    //=========================================================================
    class DevicesInfoA
    {
    public:
        DevicesInfoA() : count(0) {}

        unsigned int count;
        DeviceInfoA devices[constants::maxDevices];
    };

    //=========================================================================
    // DeviceInfoW class (from WMX3Api.h)
    //=========================================================================
    class DeviceInfoW
    {
    public:
        DeviceInfoW() : id(0), type(DeviceType::DeviceTypeNormal), watchdog(0), watchdogCount(0)
        {
            memset(name, 0, sizeof(name));
        }

        unsigned int id;
        DeviceType::T type;
        unsigned int watchdog;
        unsigned int watchdogCount;
        wchar_t name[constants::maxDeviceName];
    };

    //=========================================================================
    // DevicesInfoW class (from WMX3Api.h)
    //=========================================================================
    class DevicesInfoW
    {
    public:
        DevicesInfoW() : count(0) {}

        unsigned int count;
        DeviceInfoW devices[constants::maxDevices];
    };

    class IOSourceType
    {
    public:
        enum T
        {
            Input,
            Output
        };
    };

    class OperationState
    {
    public:
        enum T
        {
            Idle,
            Pos,
            Jog,
            Home,
            Sync,
            GantryHome,
            Stop,
            Intpl,
            Velocity,
            ConstLinearVelocity,
            Trq,
            DirectControl,
            PVT,
            ECAM,
            SyncCatchUp,
            DancerControl
        };
    };

    class HomeState
    {
    public:
        enum T
        {
            Idle = 0,
            HSSearch,
            HSReverse,
            HSAndZPSearch,
            HSAndZPReverse,
            HSAndZPConfirm,
            ZPSearch,
            ZPReverse,
            ZPConfirm,
            LSSearch,
            LSReverse,
            LSAndZPSearch,
            LSAndZPReverse,
            LSAndZPConfirm,
            ShiftMove,
            TouchProbeSearch,
            TouchProbeReverse,
            TouchProbeConfirm,
            Done,
            Paused
        };
    };

    class AxisCommandMode
    {
    public:
        enum T
        {
            Position,
            Velocity,
            Torque
        };
    };

    //=========================================================================
    // AxisSelection class (from WMX3Api.h)
    //=========================================================================
    class AxisSelection
    {
    public:
        AxisSelection() : axisCount(0)
        {
            for (int i = 0; i < constants::maxAxes; i++)
                axis[i] = 0;
        }
        unsigned int axisCount;
        int axis[constants::maxAxes];
    };

    class ProfileType
    {
    public:
        enum T
        {
            Trapezoidal,
            SCurve,
            JerkRatio,
            Parabolic,
            Sin,
            AdvancedS,
            TrapezoidalMAT,
            JerkLimited,
            JerkLimitedSCurve,
            JerkLimitedAdvancedS,
            TwoVelocityTrapezoidal,
            TwoVelocitySCurve,
            TwoVelocityJerkRatio,
            TimeAccTrapezoidal,
            TimeAccSCurve,
            TimeAccJerkRatio,
            TimeAccParabolic,
            TimeAccSin,
            TimeAccAdvancedS,
            ConstantDec,
            JerkRatioFixedVelocityT,
            JerkRatioFixedVelocityS,
            JerkLimitedFixedVelocityT,
            JerkLimitedFixedVelocityS,
            ParabolicVelocity
        };
    };

    //=========================================================================
    // Profile class (from WMX3Api.h)
    //=========================================================================
    class Profile
    {
    public:
        Profile() : type(ProfileType::Trapezoidal), velocity(0), acc(0), dec(0),
                    jerkAcc(0), jerkDec(0), jerkAccRatio(0), jerkDecRatio(0),
                    startingVelocity(0), endVelocity(0), secondVelocity(0),
                    timeMilliseconds(0), accTimeMilliseconds(0), decTimeMilliseconds(0) {}

        ProfileType::T type;
        double velocity;
        double acc;
        double dec;
        double jerkAcc;
        double jerkDec;
        double jerkAccRatio;
        double jerkDecRatio;
        double startingVelocity;
        double endVelocity;
        double secondVelocity;
        double timeMilliseconds;
        double accTimeMilliseconds;
        double decTimeMilliseconds;

        // Static setup methods
        static Profile SetupTrapezoidal(double velocity, double acc, double dec,
                                        double startingVelocity = 0, double endVelocity = 0)
        {
            Profile p;
            p.type = ProfileType::Trapezoidal;
            p.velocity = velocity;
            p.acc = acc;
            p.dec = dec;
            p.startingVelocity = startingVelocity;
            p.endVelocity = endVelocity;
            return p;
        }

        static Profile SetupSCurve(double velocity, double acc, double dec,
                                   double startingVelocity = 0, double endVelocity = 0)
        {
            Profile p;
            p.type = ProfileType::SCurve;
            p.velocity = velocity;
            p.acc = acc;
            p.dec = dec;
            p.startingVelocity = startingVelocity;
            p.endVelocity = endVelocity;
            return p;
        }

        static Profile SetupJerkRatio(double velocity, double acc, double dec,
                                      double jerkAccRatio, double jerkDecRatio,
                                      double startingVelocity = 0, double endVelocity = 0)
        {
            Profile p;
            p.type = ProfileType::JerkRatio;
            p.velocity = velocity;
            p.acc = acc;
            p.dec = dec;
            p.jerkAccRatio = jerkAccRatio;
            p.jerkDecRatio = jerkDecRatio;
            p.startingVelocity = startingVelocity;
            p.endVelocity = endVelocity;
            return p;
        }
    };

    // Forward declarations
    // Note: CoreMotionAxisStatus and CoreMotionStatus are defined in CoreMotionApi_Sim.h
    class WMX3Api;
    class CoreMotion;
    class Io;

} // namespace wmx3Api

// Include sub-modules
#include "CoreMotionApi_Sim.h"
#include "IOApi_Sim.h"
#include "EcApi_Sim.h"
#include "EventApi_Sim.h"
#include "ApiBufferApi_Sim.h"
#include "LogApi_Sim.h"
#include "CyclicBufferApi_Sim.h"
#include "CompensationApi_Sim.h"
#include "UserMemoryApi_Sim.h"
#include "PMMotionApi_Sim.h"
#include "AdvancedMotionApi_Sim.h"
#include "SimuApi_Sim.h"

namespace wmx3Api
{

    //=========================================================================
    // WMX3Api main class
    //=========================================================================
    class WMX3Api
    {
    public:
        WMX3Api()
        {
            WMX3Broker_Initialize();
        }

        ~WMX3Api()
        {
            WMX3Broker_Uninitialize();
        }

        long CreateDevice(char *path, DeviceType::T type = DeviceType::DeviceTypeNormal,
                          unsigned int waitTimeMilliseconds = 0, int core = -1, DWORD_PTR affinityMask = 0)
        {
            return WMX3Broker_CreateDevice(path, static_cast<int>(type));
        }

        long CreateDevice(wchar_t *path, DeviceType::T type = DeviceType::DeviceTypeNormal,
                          unsigned int waitTimeMilliseconds = 0, int core = -1, DWORD_PTR affinityMask = 0)
        {
            return WMX3Broker_CreateDeviceW(path, static_cast<int>(type));
        }

        long CloseDevice()
        {
            return WMX3Broker_CloseDevice();
        }

        long GetDeviceID(int *id)
        {
            return WMX3Broker_GetDeviceID(id);
        }

        long StartCommunication(unsigned int waitTimeMilliseconds = 0)
        {
            return WMX3Broker_StartCommunication(waitTimeMilliseconds);
        }

        long StopCommunication(unsigned int waitTimeMilliseconds = 0)
        {
            return WMX3Broker_StopCommunication(waitTimeMilliseconds);
        }

        long SetDeviceName(const char *name)
        {
            return WMX3Broker_SetDeviceName(name);
        }

        long SetDeviceName(const wchar_t *name)
        {
            return WMX3Broker_SetDeviceNameW(name);
        }

        long GetDeviceName(char *nameBuf, unsigned int bufSize)
        {
            return WMX3Broker_GetDeviceName(nameBuf, bufSize);
        }

        long GetDeviceName(wchar_t *nameBuf, unsigned int bufSize)
        {
            return WMX3Broker_GetDeviceNameW(nameBuf, bufSize);
        }

        long SetWatchdog(unsigned int watchdog)
        {
            return WMX3Broker_SetWatchdog(watchdog);
        }

        long SetWatchdog(int deviceId, unsigned int watchdog)
        {
            return WMX3Broker_SetWatchdogEx(deviceId, watchdog);
        }

        long GetEngineStatus(EngineStatus *status)
        {
            return WMX3Broker_GetEngineStatus(status);
        }

        long GetAllDevices(DevicesInfoA *devices)
        {
            return WMX3Broker_GetAllDevices(devices);
        }

        long GetAllDevices(DevicesInfoW *devices)
        {
            return WMX3Broker_GetAllDevicesW(devices);
        }

        static long GetLibVersion(int *pMajorVersion, int *pMinorVersion, int *pRevisionVersion, int *pFixVersion)
        {
            return WMX3Broker_GetLibVersion(pMajorVersion, pMinorVersion, pRevisionVersion, pFixVersion);
        }

        static long GetIMDllVersion(int *pVersion, int *pRevision)
        {
            return WMX3Broker_GetIMDllVersion(pVersion, pRevision);
        }

        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_WMX3Api_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_WMX3Api_ErrorToStringW(errCode, pString, size);
        }

        bool IsDeviceValid()
        {
            return WMX3Broker_WMX3Api_IsDeviceValid() != 0;
        }
    };

} // namespace wmx3Api

#endif // WMX3API_SIM_H
