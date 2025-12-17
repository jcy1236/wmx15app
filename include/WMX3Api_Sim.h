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

namespace wmx3Api {

    //=========================================================================
    // Constants (from WMX3Api.h)
    //=========================================================================
    namespace constants {
        static const int maxAxes = 128;
        static const int maxIoInSize = 8000;
        static const int maxIoOutSize = 8000;
        static const int maxDevices = 256;
        static const int maxInterrupts = 2;
    }

    //=========================================================================
    // Enums (from WMX3Api.h)
    //=========================================================================
    class DeviceType {
    public:
        enum T {
            DeviceTypeNormal = 0,
            DeviceTypeLowPriority = 0x1,
            DeviceTypeExitWOCnt = 0x02,
            DeviceTypeLowpriorityExitWOCnt = 0x03
        };
    };

    class EngineState {
    public:
        enum T {
            Idle,
            Running,
            Communicating,
            Shutdown,
            Unknown
        };
    };

    class ProfileType {
    public:
        enum T {
            Trapezoidal = 0,
            SCurve,
            JerkRatio,
            Parabolic,
            Sin,
            AdvancedS,
            JerkLimited,
            TimeAccTrapezoidal,
            TimeAccSCurve,
            TimeAccJerkRatio,
            TimeDecTrapezoidal,
            TimeDecSCurve,
            TimeDecJerkRatio,
            TimeAccDecTrapezoidal,
            TimeAccDecSCurve,
            TimeAccDecJerkRatio,
            TimeTrapezoidal,
            TimeSCurve,
            TimeJerkRatio
        };
    };

    class AxisCommandMode {
    public:
        enum T {
            Position,
            Velocity,
            Torque
        };
    };

    class OperationState {
    public:
        enum T {
            Idle = 0,
            Pos = 1,
            Jog = 2,
            Home = 3,
            Velocity = 4,
            Interpolation = 5,
            Torque = 6,
            Sync = 7,
            ECAM = 8,
            DancerControl = 9
        };
    };

    class HomeState {
    public:
        enum T {
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

    //=========================================================================
    // Profile class (from WMX3Api.h)
    //=========================================================================
    class Profile {
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
            double startingVelocity = 0, double endVelocity = 0) {
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
            double startingVelocity = 0, double endVelocity = 0) {
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
            double startingVelocity = 0, double endVelocity = 0) {
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

    //=========================================================================
    // AxisSelection class (from WMX3Api.h)
    //=========================================================================
    class AxisSelection {
    public:
        AxisSelection() : axisCount(0) {
            for (int i = 0; i < constants::maxAxes; i++) axis[i] = 0;
        }
        unsigned int axisCount;
        int axis[constants::maxAxes];
    };

    //=========================================================================
    // CoreMotionAxisStatus (from CoreMotionApi.h)
    //=========================================================================
    class CoreMotionAxisStatus {
    public:
        CoreMotionAxisStatus() {
            memset(this, 0, sizeof(CoreMotionAxisStatus));
        }

        bool servoOn;
        bool servoOffline;
        bool ampAlarm;
        unsigned int ampAlarmCode;
        double posCmd;
        double actualPos;
        double compPosCmd;
        double compActualPos;
        double velocityCmd;
        double actualVelocity;
        double velocityLag;
        double torqueCmd;
        double actualTorque;
        double followingError;
        double profileTotalMilliseconds;
        double profileAccMilliseconds;
        double profileCruiseMilliseconds;
        double profileDecMilliseconds;
        OperationState::T opState;
        int detailOpState;
        bool positiveLS;
        bool negativeLS;
        bool nearPositiveLS;
        bool nearNegativeLS;
        bool externalPositiveLS;
        bool externalNegativeLS;
        bool inPos;
        bool inPos2;
        bool inPos3;
        bool inPos4;
        bool inPos5;
        bool homeSwitch;
        bool homeDone;
        bool homePaused;
        HomeState::T homeState;
        bool cmdDistributionEnd;
        bool posSet;
        bool delayedPosSet;
        bool positiveSoftLimit;
        bool negativeSoftLimit;
        int masterAxis;
    };

    //=========================================================================
    // CoreMotionStatus (from CoreMotionApi.h)
    //=========================================================================
    class CoreMotionStatus {
    public:
        CoreMotionStatus() : invalidLicenseError(false), engineState(EngineState::Idle),
            numOfInterrupts(0), emergencyStop(false), emergencyStopLevel(0) {
            for (int i = 0; i < constants::maxInterrupts; i++) {
                cycleTimeMilliseconds[i] = 0;
                cycleCounter[i] = 0;
            }
        }

        bool invalidLicenseError;
        EngineState::T engineState;
        int numOfInterrupts;
        double cycleTimeMilliseconds[constants::maxInterrupts];
        long long cycleCounter[constants::maxInterrupts];
        bool emergencyStop;
        int emergencyStopLevel;
        CoreMotionAxisStatus axesStatus[constants::maxAxes];
    };

    // Forward declarations
    class WMX3Api;
    class CoreMotion;
    class Io;

} // namespace wmx3Api

// Include sub-modules
#include "CoreMotion_Sim.h"
#include "Io_Sim.h"
#include "Ecat_Sim.h"

namespace wmx3Api {

    //=========================================================================
    // WMX3Api main class
    //=========================================================================
    class WMX3Api {
    public:
        WMX3Api() {
            WMX3Broker_Initialize();
        }

        ~WMX3Api() {
            WMX3Broker_Uninitialize();
        }

        long CreateDevice(char* path, DeviceType::T type = DeviceType::DeviceTypeNormal,
            unsigned int waitTimeMilliseconds = 0, int core = -1, DWORD_PTR affinityMask = 0) {
            return WMX3Broker_CreateDevice(path, static_cast<int>(type));
        }

        long CreateDevice(wchar_t* path, DeviceType::T type = DeviceType::DeviceTypeNormal,
            unsigned int waitTimeMilliseconds = 0, int core = -1, DWORD_PTR affinityMask = 0) {
            return WMX3Broker_CreateDeviceW(path, static_cast<int>(type));
        }

        long CloseDevice() {
            return WMX3Broker_CloseDevice();
        }

        long GetDeviceID(int* id) {
            return WMX3Broker_GetDeviceID(id);
        }

        long StartCommunication(unsigned int waitTimeMilliseconds = 0) {
            return WMX3Broker_StartCommunication(waitTimeMilliseconds);
        }

        long StopCommunication(unsigned int waitTimeMilliseconds = 0) {
            return WMX3Broker_StopCommunication(waitTimeMilliseconds);
        }

        long SetDeviceName(char* name) {
            return WMX3Broker_SetDeviceName(name);
        }

        long SetDeviceName(wchar_t* name) {
            return WMX3Broker_SetDeviceNameW(name);
        }
    };

} // namespace wmx3Api

#endif // WMX3API_SIM_H
