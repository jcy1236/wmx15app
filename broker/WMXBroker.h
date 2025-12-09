// WMXBroker.h
// WMX 1.5 API to WMX3 API Broker Layer
// Provides WMXLIB compatible interface to minimize code changes

#ifndef WMXBROKER_H
#define WMXBROKER_H

#include <windows.h>
#include <tchar.h>

// DLL Export/Import macros
#ifdef WMXBROKER_EXPORTS
#define WMXBROKER_API __declspec(dllexport)
#else
#define WMXBROKER_API __declspec(dllimport)
#endif

// WMX 1.5 type definitions (wmxapi_type.h includes wmxapi_def.h)
#include "wmxapi_type.h"

//////////////////////////////////////////////////////////////////////////
// Additional type definitions for WMX Broker
// Some types not present in original WMX 1.5
//////////////////////////////////////////////////////////////////////////

// Axis mode (Position/Velocity/Torque)
typedef enum {
    WMX_AXIS_MODE_POSITION = 0,
    WMX_AXIS_MODE_VELOCITY,
    WMX_AXIS_MODE_TORQUE
} WMX_AXIS_MODE;

// Home direction
typedef enum {
    WMX_HOME_DIRECTION_POSITIVE = 0,
    WMX_HOME_DIRECTION_NEGATIVE
} WMX_HOME_DIRECTION;

// Limit switch type
typedef enum {
    WMX_LIMIT_SWITCH_TYPE_NONE = 0,
    WMX_LIMIT_SWITCH_TYPE_SERVO_OFF,
    WMX_LIMIT_SWITCH_TYPE_DEC_SERVO_OFF,
    WMX_LIMIT_SWITCH_TYPE_DEC,
    WMX_LIMIT_SWITCH_TYPE_SLOW_DEC_SERVO_OFF,
    WMX_LIMIT_SWITCH_TYPE_SLOW_DEC
} WMX_LIMIT_SWITCH_TYPE;

// Following error type
typedef enum {
    WMX_FOLLOWING_ERROR_TYPE_NO_ACTION = 0,
    WMX_FOLLOWING_ERROR_TYPE_QUICK_STOP
} WMX_FOLLOWING_ERROR_TYPE;

// Home data structure per axis
#ifndef WMX_HOME_DATA_DEFINED
#define WMX_HOME_DATA_DEFINED

#ifndef MAX_AXIS
#define MAX_AXIS 64
#endif

typedef struct {
    double distHStoZPulse;
    double distLStoZPulse;
} WMX_AXIS_HOME_DATA;

typedef struct {
    WMX_AXIS_HOME_DATA axesHomeData[MAX_AXIS];
} WMX_HOME_DATA;

#endif // WMX_HOME_DATA_DEFINED

// Axis parameter (for full axis config access)
typedef struct {
    WMX_AXIS_MODE axisCommandMode;
    double gearRatioNumerator;
    double gearRatioDenominator;
    bool singleTurnMode;
    unsigned int singleTurnEncoderCount;
    double maxTrqLimit;
    double positiveTrqLimit;
    double negativeTrqLimit;
    double axisUnit;
    double velocityFeedforwardGain;
    char axisPolarity;
    double maxMotorSpeed;
} WMX_AXIS_PARAM;

//////////////////////////////////////////////////////////////////////////
// Motion Block Structures for ExtMotion2 and ExtList2
//////////////////////////////////////////////////////////////////////////

#ifndef MAX_ALLAXES
#define MAX_ALLAXES 64
#endif

#ifndef POSBLOCKEXT2_DEFINED
#define POSBLOCKEXT2_DEFINED

// PosBlockExt2 - extMotion2 any profile positioning
typedef struct {
    short axis;
    WMX_PROFILE_TYPE profile;
    double target;
    double velocity;
    double acc;
    double dec;
    double jerkAccRatio;
    double jerkDecRatio;
    double startingVelocity;
    double endVelocity;
} PosBlockExt2Ind, *PPosBlockExt2Ind;
typedef struct {
    short axisCount;
    PosBlockExt2Ind pos_block[MAX_ALLAXES];
} PosBlockExt2, *PPosBlockExt2;

// IntBlockExt2 - extMotion2 any profile simple interpolation
typedef struct {
    short axis;
    double target;
    double velocity;
    double acc;
    double dec;
} IntBlockExt2Ind, *PIntBlockExt2Ind;
typedef struct {
    short axisCount;
    WMX_PROFILE_TYPE profile;
    double compJerkAccRatio;
    double compJerkDecRatio;
    IntBlockExt2Ind pos_block[MAX_ALLAXES];
} IntBlockExt2, *PIntBlockExt2;

// PosBlockListExt2 - extList2 positioning
typedef struct {
    WMX_PROFILE_TYPE profile;
    short axis;
    double target;
    double velocity;
    double acc;
    double dec;
    double jerkAccRatio;
    double jerkDecRatio;
    double startingVelocity;
    double endVelocity;
} PosBlockListExt2Ind, *PPosBlockListExt2Ind;
typedef struct {
    short axisCount;
    PosBlockListExt2Ind pos_block[MAX_ALLAXES];
} PosBlockListExt2, *PPosBlockListExt2;

// CoordinatedPosBlockListExt2 - extList2 coordinated positioning
typedef struct {
    short axis;
    WMX_PROFILE_TYPE profile;
    double target;
    double velocity;
    double acc;
    double dec;
    double jerkAccRatio;
    double jerkDecRatio;
    double startingVelocity;
    double endVelocity;
    short axis2;
    double axis2target;
    double axis2smoothRatio;
} CoordinatedPosBlockListExt2Ind, *PCoordinatedPosBlockListExt2Ind;
typedef struct {
    short axisCount;
    CoordinatedPosBlockListExt2Ind pos_block[MAX_ALLAXES];
} CoordinatedPosBlockListExt2, *PCoordinatedPosBlockListExt2;

#endif // POSBLOCKEXT2_DEFINED

#ifndef COORDINATED_POSBLOCK_EXT2_DEFINED
#define COORDINATED_POSBLOCK_EXT2_DEFINED

// CoordinatedPosBlockExt2 - extMotion2 coordinated positioning
typedef struct {
    short axis;
    WMX_PROFILE_TYPE profile;
    double target;
    double velocity;
    double acc;
    double dec;
    double jerkAccRatio;
    double jerkDecRatio;
    double startingVelocity;
    double endVelocity;
    short axis2;
    double axis2target;
    double axis2smoothRatio;
} CoordinatedPosBlockExt2Ind, *PCoordinatedPosBlockExt2Ind;
typedef struct {
    short axisCount;
    CoordinatedPosBlockExt2Ind pos_block[MAX_ALLAXES];
} CoordinatedPosBlockExt2, *PCoordinatedPosBlockExt2;

#endif // COORDINATED_POSBLOCK_EXT2_DEFINED

// Forward declarations for WMX3
namespace wmx3Api {
    class WMX3Api;
    class CoreMotion;
    class AdvancedMotion;
    class Io;
}

// Forward declarations for Motion namespaces (PascalCase to match WMX 1.5)
namespace wmxAPI {
namespace basicMotion { class BasicMotion; }
namespace extMotion1 { class ExtMotion1; }
namespace extMotion2 { class ExtMotion2; }
namespace extList2 { class ExtList2; }
namespace axisControl { class AxisControl; }
namespace home { class Home; }
namespace config { class Config; }
namespace basicVelocity { class BasicVelocity; }
namespace extVelocity2 { class ExtVelocity2; }
namespace torque { class TorqueControl; }
}

namespace wmxAPI {

    // Forward declaration
    class WMXLIB;

    namespace common {

        // Io class - maintains WMX 1.5 interface
        class WMXBROKER_API Io {
        public:
            WMXLIB* wmxlib;
            Io(WMXLIB* f) : wmxlib(f) {}

            // I/O APIs
            WMXAPIFUNC SetOutBit(short byte, short bit, unsigned char data);
            WMXAPIFUNC SetOutByte(short offsetByte, unsigned char data);
            WMXAPIFUNC SetOutBytes(short offsetByte, short size, unsigned char* data);
            WMXAPIFUNC GetInBit(short byte, short bit, unsigned char* data);
            WMXAPIFUNC GetInByte(short offsetByte, unsigned char* data);
            WMXAPIFUNC GetInBytes(short offsetByte, short size, unsigned char* data);
            WMXAPIFUNC GetOutBit(short byte, short bit, unsigned char* data);
            WMXAPIFUNC GetOutByte(short offsetByte, unsigned char* data);
            WMXAPIFUNC GetOutBytes(short offsetByte, short size, unsigned char* data);

            // Initial Output APIs (not available in WMX3 - stored internally)
            WMXAPIFUNC SetInitialOutBit(short byte, short bit, unsigned char data);
            WMXAPIFUNC SetInitialOutByte(short offsetByte, unsigned char data);
            WMXAPIFUNC SetInitialOutBytes(short offsetByte, short size, unsigned char* data);
            WMXAPIFUNC GetInitialOutBit(short byte, short bit, unsigned char* data);
            WMXAPIFUNC GetInitialOutByte(short offsetByte, unsigned char* data);
            WMXAPIFUNC GetInitialOutBytes(short offsetByte, short size, unsigned char* data);
        };

    } // namespace common

    // WMXLIB class - maintains WMX 1.5 interface, internally uses WMX3
    // Uses WMX3ContextManager for shared WMX3 instance
    class WMXBROKER_API WMXLIB {
    private:
        // Pointers to shared WMX3 objects (owned by WMX3ContextManager)
        wmx3Api::WMX3Api* wmx3;
        wmx3Api::CoreMotion* coreMotion;
        wmx3Api::AdvancedMotion* advancedMotion;
        wmx3Api::Io* wmx3Io;
        bool isConnected;

        // Initial output buffer
        unsigned char initialOut[MAX_IOOUTSIZE];

    public:
        WMXLIB();
        ~WMXLIB();

        // WMX3 internal object access (for Broker internal use)
        wmx3Api::WMX3Api* GetWMX3Api() { return wmx3; }
        wmx3Api::CoreMotion* GetCoreMotion() { return coreMotion; }
        wmx3Api::AdvancedMotion* GetAdvancedMotion() { return advancedMotion; }
        wmx3Api::Io* GetWMX3Io() { return wmx3Io; }
        unsigned char* GetInitialOutBuffer() { return initialOut; }

        // System APIs
        WMXAPIFUNC CreateDevice(TCHAR* path, PLTFRM_TYPE type);
        WMXAPIFUNC CloseDevice();
        WMXAPIFUNC StartCommunication();
        WMXAPIFUNC StopCommunication();
        WMXAPIFUNC GetStatus(WMX_STATUS* st);
        WMXAPIFUNC GetStatus(WMX_STATUS* st, short axis);
        WMXAPIFUNC GetStatus(WMX_STATUS* st, short firstAxis, short lastAxis);
        WMXAPIFUNC GetVersion(double* pCeVersion, double* pPeVersion);

        // Extended System APIs
        WMXAPIFUNC GetLastError();
        WMXAPIFUNC SetDeviceName(const TCHAR* name);
        WMXAPIFUNC GetActiveDeviceList(WMX_ACT_DEV_LIST* list);
        WMXAPIFUNC ForceCloseDevice(int id);

        // Io class instance
        common::Io* io;

        // Motion namespace instances (PascalCase to match WMX 1.5)
        basicMotion::BasicMotion* basicMotion;
        extMotion1::ExtMotion1* extMotion1;
        extMotion2::ExtMotion2* extMotion2;
        extList2::ExtList2* extList2;

        // New namespace instances
        axisControl::AxisControl* axisControl;
        home::Home* home;
        config::Config* config;
        basicVelocity::BasicVelocity* basicVelocity;
        extVelocity2::ExtVelocity2* extVelocity2;
        torque::TorqueControl* torqueControl;

        // Error code
        WMX_API_ERROR_CODE lastError;
    };

} // namespace wmxAPI

#endif // WMXBROKER_H
