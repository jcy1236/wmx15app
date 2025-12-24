// ApiBufferApi_Sim.h
// WMX3 ApiBuffer API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::ApiBuffer interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef APIBUFFERAPI_SIM_H
#define APIBUFFERAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    //=========================================================================
    // ApiBuffer Constants
    //=========================================================================
    namespace constants
    {
        static const int maxApiBufferChannel = 255;
        static const int maxApiBufferErrorLog = 10;
        static const int maxDefaultApiBufferSize = 524288;
    }

    //=========================================================================
    // ApiBuffer Error Codes
    //=========================================================================
    class ApiBufferErrorCode : public ErrorCode
    {
    public:
        enum
        {
            OverMaxLevel = 0x00012000,
            InvalidLevel,
            InvalidBuffControl,
            InvalidWatchTriggerRoutineChannel,
            WatchTriggerRoutineChannelSameAsExecChannel,
            RewindFailedFirstCommandOverwritten,
            AlreadyRecordingForSpecifiedChannel,
            NotRecording
        };
    };

    //=========================================================================
    // ApiBuffer Enums
    //=========================================================================
    class ApiBufferConditionType
    {
    public:
        enum T
        {
            NeverTrue,
            AlwaysTrue,
            IOInput,
            IOOutput,
            UserMemory,
            MinimumTrq,
            InPos,
            PosSET,
            DelayedPosSET,
            CommandDistributedEnd,
            RemainingTime,
            RemainingDistance,
            CompletedTime,
            CompletedDistance,
            DistanceToTarget,
            DecelerationStarted,
            AxisIdle,
            MotionStarted,
            MotionStartedOverrideReady,
            Event
        };
    };

    class ApiBufferState
    {
    public:
        enum T
        {
            Idle,
            Active,
            Stop,
            Delay
        };
    };

    class SizeUnit
    {
    public:
        enum T
        {
            Bytes,
            Kilobytes
        };
    };

    //=========================================================================
    // ApiBuffer Condition class
    //=========================================================================
    class ApiBufferCondition
    {
    public:
        ApiBufferCondition() : bufferConditionType(ApiBufferConditionType::NeverTrue)
        {
            memset(&arg, 0, sizeof(arg));
        }

        ApiBufferConditionType::T bufferConditionType;

        union ApiBufferConditionArguments
        {
            ApiBufferConditionArguments() { memset(this, 0, sizeof(*this)); }

            struct NeverTrue
            {
                int reserved;
            } neverTrue;

            struct AlwaysTrue
            {
                int reserved;
            } alwaysTrue;

            struct IOInput
            {
                unsigned int byteAddress;
                unsigned char bitAddress;
                unsigned char invert;
            } ioInput;

            struct IOOutput
            {
                unsigned int byteAddress;
                unsigned char bitAddress;
                unsigned char invert;
            } ioOutput;

            struct UserMemory
            {
                unsigned int byteAddress;
                unsigned char bitAddress;
                unsigned char invert;
            } userMemory;

            struct MinimumTrq
            {
                int axis;
                double torque;
            } minimumTrq;

            struct InPos
            {
                int axis;
                unsigned int channel;
            } inPos;

            struct PosSET
            {
                int axis;
            } posSET;

            struct DelayedPosSET
            {
                int axis;
            } delayedPosSET;

            struct CommandDistributedEnd
            {
                int axis;
            } commandDistributedEnd;

            struct RemainingTime
            {
                int axis;
                double timeMilliseconds;
            } remainingTime;

            struct RemainingDistance
            {
                int axis;
                double distance;
            } remainingDistance;

            struct CompletedTime
            {
                int axis;
                double timeMilliseconds;
            } completedTime;

            struct CompletedDistance
            {
                int axis;
                double distance;
            } completedDistance;

            struct DistanceToTarget
            {
                int axis;
                double distance;
            } distanceToTarget;

            struct DecelerationStarted
            {
                int axis;
            } decelerationStarted;

            struct AxisIdle
            {
                unsigned int axisCount;
                int axis[constants::maxAxes];
            } axisIdle;

            struct MotionStarted
            {
                int axis;
            } motionStarted;

            struct MotionStartedOverrideReady
            {
                int axis;
            } motionStartedOverrideReady;

            struct Event
            {
                unsigned int eventID;
            } event;
        } arg;
    };

    //=========================================================================
    // ApiBuffer Error Log class
    //=========================================================================
    class ApiBufferErrorLog
    {
    public:
        ApiBufferErrorLog() : execBlockNumber(0), errorCode(0) {}

        int execBlockNumber;
        int errorCode;
    };

    //=========================================================================
    // ApiBuffer Status class
    //=========================================================================
    class ApiBufferStatus
    {
    public:
        ApiBufferStatus()
            : state(ApiBufferState::Idle), blockCount(0), remainingBlockCount(0),
              bufferSize(0), freeSize(0), execBlockCount(0), errorCount(0),
              watchError(false), watchErrorCode(0), watchErrorAxis(0)
        {
            for (int i = 0; i < constants::maxApiBufferErrorLog; i++)
            {
                errorLog[i] = ApiBufferErrorLog();
            }
        }

        ApiBufferState::T state;
        int blockCount;
        int remainingBlockCount;
        int bufferSize;
        int freeSize;
        int execBlockCount;
        int errorCount;
        ApiBufferErrorLog errorLog[constants::maxApiBufferErrorLog];
        bool watchError;
        int watchErrorCode;
        int watchErrorAxis;
    };

    //=========================================================================
    // ApiBuffer Options class
    //=========================================================================
    class ApiBufferOptions
    {
    public:
        ApiBufferOptions()
            : stopOnError(false), autoRewind(false), stopOnLastBlock(false) {}

        bool stopOnError;
        bool autoRewind;
        bool stopOnLastBlock;
    };

    //=========================================================================
    // ApiBuffer Watch class
    //=========================================================================
    class ApiBufferWatch
    {
    public:
        ApiBufferWatch()
            : enableWatch(false), enableWatchTriggerRoutine(false),
              watchTriggerRoutineChannel(0) {}

        bool enableWatch;
        AxisSelection watchAxes;
        bool enableWatchTriggerRoutine;
        int watchTriggerRoutineChannel;
    };

    //=========================================================================
    // ApiBuffer class - Buffer-based API execution
    //=========================================================================
    class ApiBuffer
    {
    private:
        WMX3Api *m_wmx3Api;

    public:
        ApiBuffer(WMX3Api *wmx3Api) : m_wmx3Api(wmx3Api) {}
        ApiBuffer() : m_wmx3Api(NULL) {}
        ~ApiBuffer() {}

        // Copy constructor and assignment operator
        ApiBuffer(const ApiBuffer &src) : m_wmx3Api(src.m_wmx3Api) {}
        ApiBuffer &operator=(const ApiBuffer &src)
        {
            if (this != &src)
            {
                m_wmx3Api = src.m_wmx3Api;
            }
            return *this;
        }

        //=====================================================================
        // Static methods
        //=====================================================================
        static long GetLibVersion(int *pMajorVersion, int *pMinorVersion,
                                  int *pRevisionVersion, int *pFixVersion)
        {
            return WMX3Broker_ApiBuffer_GetLibVersion(pMajorVersion, pMinorVersion,
                                                      pRevisionVersion, pFixVersion);
        }

        //=====================================================================
        // Version
        //=====================================================================
        long GetVersion(int *pMajorVersion, int *pMinorVersion,
                        int *pRevisionVersion, int *pFixVersion)
        {
            return WMX3Broker_ApiBuffer_GetVersion(pMajorVersion, pMinorVersion,
                                                   pRevisionVersion, pFixVersion);
        }

        //=====================================================================
        // Buffer Management
        //=====================================================================
        long CreateApiBuffer(unsigned int channel, unsigned int size)
        {
            return WMX3Broker_ApiBuffer_CreateApiBuffer(channel, size);
        }

        long CreateApiBuffer(unsigned int channel)
        {
            return WMX3Broker_ApiBuffer_CreateApiBuffer(channel, constants::maxDefaultApiBufferSize);
        }

        long CreateApiBuffer(unsigned int channel, unsigned int size, SizeUnit::T sizeUnit)
        {
            unsigned int actualSize = size;
            if (sizeUnit == SizeUnit::Kilobytes)
            {
                actualSize = size * 1024;
            }
            return WMX3Broker_ApiBuffer_CreateApiBuffer(channel, actualSize);
        }

        long FreeApiBuffer(unsigned int channel)
        {
            return WMX3Broker_ApiBuffer_FreeApiBuffer(channel);
        }

        //=====================================================================
        // Recording
        //=====================================================================
        long StartRecordBufferChannel(unsigned int channel)
        {
            return WMX3Broker_ApiBuffer_StartRecordBufferChannel(channel);
        }

        long EndRecordBufferChannel()
        {
            return WMX3Broker_ApiBuffer_EndRecordBufferChannel();
        }

        long GetRecordingBufferChannel(int *channel, unsigned char *enable)
        {
            return WMX3Broker_ApiBuffer_GetRecordingBufferChannel(channel, enable);
        }

        //=====================================================================
        // Execution Control
        //=====================================================================
        long Execute(unsigned int channel)
        {
            return WMX3Broker_ApiBuffer_Execute(channel);
        }

        long Halt(unsigned int channel)
        {
            return WMX3Broker_ApiBuffer_Halt(channel);
        }

        long Clear(unsigned int channel)
        {
            return WMX3Broker_ApiBuffer_Clear(channel);
        }

        long Rewind(unsigned int channel)
        {
            return WMX3Broker_ApiBuffer_Rewind(channel);
        }

        //=====================================================================
        // Status and Options
        //=====================================================================
        long GetStatus(unsigned int channel, ApiBufferStatus *pStatus)
        {
            return WMX3Broker_ApiBuffer_GetStatus(channel, pStatus);
        }

        long SetOptions(unsigned int channel, ApiBufferOptions *pOptions)
        {
            return WMX3Broker_ApiBuffer_SetOptions(channel, pOptions);
        }

        long GetOptions(unsigned int channel, ApiBufferOptions *pOptions)
        {
            return WMX3Broker_ApiBuffer_GetOptions(channel, pOptions);
        }

        long SetWatch(unsigned int channel, ApiBufferWatch *pWatch)
        {
            return WMX3Broker_ApiBuffer_SetWatch(channel, pWatch);
        }

        long GetWatch(unsigned int channel, ApiBufferWatch *pWatch)
        {
            return WMX3Broker_ApiBuffer_GetWatch(channel, pWatch);
        }

        //=====================================================================
        // Wait and Sleep
        //=====================================================================
        long Sleep(unsigned int milliseconds)
        {
            return WMX3Broker_ApiBuffer_Sleep(milliseconds);
        }

        long Wait(int axis)
        {
            return WMX3Broker_ApiBuffer_Wait(axis);
        }

        long Wait(AxisSelection *pAxisSelection)
        {
            return WMX3Broker_ApiBuffer_WaitAxes(pAxisSelection);
        }

        long Wait(ApiBufferCondition *condition)
        {
            return WMX3Broker_ApiBuffer_WaitCondition(condition);
        }

        //=====================================================================
        // Flow Control
        //=====================================================================
        long FlowIf(ApiBufferCondition *condition, ApiBufferCondition *wait = NULL)
        {
            return WMX3Broker_ApiBuffer_FlowIf(condition, wait);
        }

        long FlowElseIf(ApiBufferCondition *condition)
        {
            return WMX3Broker_ApiBuffer_FlowElseIf(condition);
        }

        long FlowElse()
        {
            return WMX3Broker_ApiBuffer_FlowElse();
        }

        long FlowEndIf()
        {
            return WMX3Broker_ApiBuffer_FlowEndIf();
        }

        //=====================================================================
        // Device Validation
        //=====================================================================
        bool IsDeviceValid()
        {
            return WMX3Broker_ApiBuffer_IsDeviceValid() != 0;
        }

        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_ApiBuffer_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_ApiBuffer_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // APIBUFFERAPI_SIM_H
