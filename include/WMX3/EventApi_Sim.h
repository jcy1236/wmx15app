// EventApi_Sim.h
// WMX3 EventControl API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::EventControl interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef EVENTAPI_SIM_H
#define EVENTAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    //=========================================================================
    // Event Constants
    //=========================================================================
    namespace constants
    {
        static const int maxEvents = 512;
        static const int maxHardwareTouchProbeLatchedValues = 256;
        static const int maxTouchprobeChannel = 64;
        static const int maxEventInterpolationAxes = 8;
    }

    class EventErrorCode : public ErrorCode
    {
    public:
        enum
        {
            MaxEventDefinitionsDefined = 0x00016000,
            MaxEventInputsDefined,
            MaxEventOutputsDefined,
            MaxEventBitArrayUsed,
            IDOutOfRange,
            IDNotDefined,
            IDBusyUpdating,
            ChannelUninitialized,
            IDInUse,
            HardTouchProbeChannelOutOfRange,
            EventInDataSizeOutOfRange,
            EventOutDataSizeOutOfRange,
            EventConfigureOfModuleDataSizeOutOfRange,
            EventNotDefined,
            EventInputModuleIdNotMatched,
            EventOutputModuleIdNotMatched,
            EventInputDataAllocateFailed,
            EventOutputDataAllocateFailed,
            GetFunctionDoesNotMatchSetFunction,
            ChannelEnabled,
            InterruptIdForActiveChannelError,
            InvalidModuleID,
            EventIsEnabled,
            EventIsClearing,
            SourceTypeOutOfRange,
            PointCountOutOfRange,
            IntervalOutOfRange
        };
    };

    //=========================================================================
    // EventOption class
    //=========================================================================
    class EventOption
    {
    public:
        EventOption() : singleShot(false), disableAfterActivate(false), enable(true) {}

        bool singleShot;
        bool disableAfterActivate;
        bool enable;
    };

    //=========================================================================
    // CustomEventOption class
    //=========================================================================
    class CustomEventOption
    {
    public:
        CustomEventOption() : initialState(0) {}

        EventOption option;
        char initialState;
    };

    //=========================================================================
    // AllEventID class
    //=========================================================================
    class AllEventID
    {
    public:
        AllEventID() : count(0)
        {
            for (int i = 0; i < constants::maxEvents; i++)
            {
                id[i] = 0;
            }
        }

        int count;
        int id[constants::maxEvents];
    };

    //=========================================================================
    // EventControl class - Event-based control system
    //=========================================================================
    class EventControl
    {
    public:
        //=====================================================================
        // Inner Enums
        //=====================================================================

        //[Deprecated]
        class EventInputFunction
        {
        public:
            enum T
            {
                None,
                IOBit,
                NotIOBit,
                OrIOBit,
                AndIOBit,
                XorIOBit,
                NandIOBit,
                NorIOBit,
                XnorIOBit,
                DelayIOBit,

                MBit,
                NotMBit,
                OrMBit,
                AndMBit,
                XorMBit,
                NandMBit,
                NorMBit,
                XnorMBit,
                DelayMBit,

                AnotherEvent,
                DelayAnotherEvent,

                EqualPos,
                GreaterPos,
                LessPos,
                EqualVelocity,
                GreaterVelocity,
                LessVelocity,
                EqualTrq,
                GreaterTrq,
                LessTrq,

                OpState,
                PosSET,
                DelayedPosSET,
                CommandDistributedEnd,
                RemainingTime,
                RemainingDistance,
                CompletedTime,
                CompletedDistance,

                Unknown
            };
        };

        //[Deprecated]
        class EventOutputFunction
        {
        public:
            enum T
            {
                None,
                SetIOOutBit,
                SetMBit,
                EnableAnotherEvent,
                StopSingleAxis,
                StartSinglePos,
                StartSingleMov,
                StartMultiplePos,
                StartMultipleMov,
                LinearIntplPos,
                LinearIntplMov,
                StartAPIBuffer,
                ExecQuickStopSingleAxis,
                OverrideVelSingleAxis,
                ExecEStop,
                TriggerFlightRecorder,
                ResetFlightRecorder,
                Unknown
            };
        };

        class TouchProbeSource
        {
        public:
            enum T
            {
                ZPulse,
                TouchProbe
            };
        };

        class TouchProbeMode
        {
        public:
            enum T
            {
                LatchFirst,
                LatchLast
            };
        };

        //=====================================================================
        // Inner Data Classes
        //=====================================================================
        class HardwareTouchProbeStatus
        {
        public:
            HardwareTouchProbeStatus()
            {
                memset(this, 0, sizeof(HardwareTouchProbeStatus));
                mode = TouchProbeMode::LatchFirst;
                triggerSource = TouchProbeSource::ZPulse;
            }

            int axis;
            unsigned char enabled;
            TouchProbeMode::T mode;
            TouchProbeSource::T triggerSource;
            unsigned int channel;
            unsigned char latched;
            unsigned int latchedValueCount;
            unsigned int latchedValue[constants::maxHardwareTouchProbeLatchedValues];
            double latchedPos[constants::maxHardwareTouchProbeLatchedValues];
        };

        //[Deprecated]
        class Event
        {
        public:
            Event()
            {
                memset(this, 0, sizeof(Event));
                inputFunction = EventInputFunction::None;
                outputFunction = EventOutputFunction::None;
            }

            EventInputFunction::T inputFunction;
            union InputFunctionArguments
            {
                InputFunctionArguments() { memset(this, 0, sizeof(InputFunctionArguments)); }

                struct None
                {
                    unsigned int reserved;
                } none;
                struct IOBit
                {
                    unsigned int byteAddress;
                    unsigned char bitAddress;
                    unsigned char invert;
                    IOSourceType::T ioSourceType;
                } ioBit;
                struct NotIOBit
                {
                    unsigned int byteAddress;
                    unsigned char bitAddress;
                    unsigned char invert;
                    IOSourceType::T ioSourceType;
                } notIOBit;
                struct OrIOBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                    IOSourceType::T ioSourceType[2];
                } orIOBit;
                struct AndIOBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                    IOSourceType::T ioSourceType[2];
                } andIOBit;
                struct XorIOBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                    IOSourceType::T ioSourceType[2];
                } xorIOBit;
                struct NandIOBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                    IOSourceType::T ioSourceType[2];
                } nandIOBit;
                struct NorIOBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                    IOSourceType::T ioSourceType[2];
                } norIOBit;
                struct XnorIOBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                    IOSourceType::T ioSourceType[2];
                } xnorIOBit;
                struct DelayIOBit
                {
                    unsigned int byteAddress;
                    unsigned char bitAddress;
                    unsigned char invert;
                    IOSourceType::T ioSourceType;
                    unsigned int delayTime;
                } delayIOBit;
                struct MBit
                {
                    unsigned int byteAddress;
                    unsigned char bitAddress;
                    unsigned char invert;
                } mBit;
                struct NotMBit
                {
                    unsigned int byteAddress;
                    unsigned char bitAddress;
                    unsigned char invert;
                } notMBit;
                struct OrMBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                } orMBit;
                struct AndMBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                } andMBit;
                struct XorMBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                } xorMBit;
                struct NandMBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                } nandMBit;
                struct NorMBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                } norMBit;
                struct XnorMBit
                {
                    unsigned int byteAddress[2];
                    unsigned char bitAddress[2];
                    unsigned char invert[2];
                } xnorMBit;
                struct DelayMBit
                {
                    unsigned int byteAddress;
                    unsigned char bitAddress;
                    unsigned char invert;
                    unsigned int delayTime;
                } delayMBit;
                struct AnotherEvent
                {
                    unsigned int eventID;
                    unsigned char invert;
                } anotherEvent;
                struct DelayAnotherEvent
                {
                    unsigned int eventID;
                    unsigned char invert;
                    unsigned int delayTime;
                } delayAnotherEvent;
                struct EqualPos
                {
                    unsigned int axis;
                    double pos;
                    unsigned char disablePositiveDirection;
                    unsigned char disableNegativeDirection;
                    unsigned char useFeedback;
                    unsigned char invert;
                    unsigned char enableTolerance;
                    double tolerance;
                } equalPos;
                struct GreaterPos
                {
                    unsigned int axis;
                    double pos;
                    unsigned char disablePositiveDirection;
                    unsigned char disableNegativeDirection;
                    unsigned char useFeedback;
                    unsigned char invert;
                } greaterPos;
                struct LessPos
                {
                    unsigned int axis;
                    double pos;
                    unsigned char disablePositiveDirection;
                    unsigned char disableNegativeDirection;
                    unsigned char useFeedback;
                    unsigned char invert;
                } lessPos;
                struct EqualVelocity
                {
                    unsigned int axis;
                    double velocity;
                    unsigned char useFeedback;
                    unsigned char invert;
                    unsigned char enableTolerance;
                    double tolerance;
                    unsigned char enableUnsigned;
                } equalVelocity;
                struct GreaterVelocity
                {
                    unsigned int axis;
                    double velocity;
                    unsigned char useFeedback;
                    unsigned char invert;
                    unsigned char enableUnsigned;
                } greaterVelocity;
                struct LessVelocity
                {
                    unsigned int axis;
                    double velocity;
                    unsigned char useFeedback;
                    unsigned char invert;
                    unsigned char enableUnsigned;
                } lessVelocity;
                struct EqualTrq
                {
                    unsigned int axis;
                    double trq;
                    unsigned char invert;
                    unsigned char enableTolerance;
                    double tolerance;
                    unsigned char enableUnsigned;
                } equalTrq;
                struct GreaterTrq
                {
                    unsigned int axis;
                    double trq;
                    unsigned char invert;
                    unsigned char enableUnsigned;
                } greaterTrq;
                struct LessTrq
                {
                    unsigned int axis;
                    double trq;
                    unsigned char invert;
                    unsigned char enableUnsigned;
                } lessTrq;
                struct OpState
                {
                    unsigned int axis;
                    OperationState::T opState;
                    unsigned char invert;
                } opState;
                struct PosSET
                {
                    unsigned int axis;
                    unsigned char invert;
                } posSET;
                struct DelayedPosSET
                {
                    unsigned int axis;
                    unsigned char invert;
                } delayedPosSET;
                struct CommandDistributedEnd
                {
                    unsigned int axis;
                    unsigned char invert;
                } commandDistributedEnd;
                struct RemainingTime
                {
                    unsigned int axis;
                    unsigned char invert;
                    double timeMilliseconds;
                    unsigned char disableIdleAxisTrigger;
                } remainingTime;
                struct RemainingDistance
                {
                    unsigned int axis;
                    unsigned char invert;
                    double distance;
                    unsigned char disableIdleAxisTrigger;
                } remainingDistance;
                struct CompletedTime
                {
                    unsigned int axis;
                    unsigned char invert;
                    double timeMilliseconds;
                    unsigned char disableIdleAxisTrigger;
                } completedTime;
                struct CompletedDistance
                {
                    unsigned int axis;
                    unsigned char invert;
                    double distance;
                    unsigned char disableIdleAxisTrigger;
                } completedDistance;
            } input;

            EventOutputFunction::T outputFunction;
            union OutputFunctionArguments
            {
                OutputFunctionArguments() { memset(this, 0, sizeof(OutputFunctionArguments)); }

                struct None
                {
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } none;
                struct SetIOOutBit
                {
                    unsigned int byteAddress;
                    unsigned char bitAddress;
                    unsigned char invert;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                    unsigned char setOffState;
                } setIOOutBit;
                struct SetMBit
                {
                    unsigned int byteAddress;
                    unsigned char bitAddress;
                    unsigned char invert;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                    unsigned char setOffState;
                } setMBit;
                struct EnableAnotherEvent
                {
                    unsigned int eventID;
                    unsigned char invert;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                    unsigned char setOffState;
                } enableAnotherEvent;
                struct StopSingleAxis
                {
                    int axis;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } stopSingleAxis;
                struct StartSinglePos
                {
                    int axis;
                    double target;
                    ProfileType::T type;
                    double velocity;
                    double acc;
                    double dec;
                    double jerkAcc;
                    double jerkDec;
                    double jerkAccRatio;
                    double jerkDecRatio;
                    double accTime;
                    double decTime;
                    double startingVelocity;
                    double endVelocity;
                    double secondVelocity;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } startSinglePos;
                struct StartSingleMov
                {
                    int axis;
                    double target;
                    ProfileType::T type;
                    double velocity;
                    double acc;
                    double dec;
                    double jerkAcc;
                    double jerkDec;
                    double jerkAccRatio;
                    double jerkDecRatio;
                    double accTime;
                    double decTime;
                    double startingVelocity;
                    double endVelocity;
                    double secondVelocity;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } startSingleMov;
                struct StartMultiplePos
                {
                    unsigned int axisCount;
                    int axis[constants::maxEventInterpolationAxes];
                    double target[constants::maxEventInterpolationAxes];
                    ProfileType::T type[constants::maxEventInterpolationAxes];
                    double velocity[constants::maxEventInterpolationAxes];
                    double acc[constants::maxEventInterpolationAxes];
                    double dec[constants::maxEventInterpolationAxes];
                    double jerkAcc[constants::maxEventInterpolationAxes];
                    double jerkDec[constants::maxEventInterpolationAxes];
                    double jerkAccRatio[constants::maxEventInterpolationAxes];
                    double jerkDecRatio[constants::maxEventInterpolationAxes];
                    double accTime[constants::maxEventInterpolationAxes];
                    double decTime[constants::maxEventInterpolationAxes];
                    double startingVelocity[constants::maxEventInterpolationAxes];
                    double endVelocity[constants::maxEventInterpolationAxes];
                    double secondVelocity[constants::maxEventInterpolationAxes];
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } startMultiplePos;
                struct StartMultipleMov
                {
                    unsigned int axisCount;
                    int axis[constants::maxEventInterpolationAxes];
                    double target[constants::maxEventInterpolationAxes];
                    ProfileType::T type[constants::maxEventInterpolationAxes];
                    double velocity[constants::maxEventInterpolationAxes];
                    double acc[constants::maxEventInterpolationAxes];
                    double dec[constants::maxEventInterpolationAxes];
                    double jerkAcc[constants::maxEventInterpolationAxes];
                    double jerkDec[constants::maxEventInterpolationAxes];
                    double jerkAccRatio[constants::maxEventInterpolationAxes];
                    double jerkDecRatio[constants::maxEventInterpolationAxes];
                    double accTime[constants::maxEventInterpolationAxes];
                    double decTime[constants::maxEventInterpolationAxes];
                    double startingVelocity[constants::maxEventInterpolationAxes];
                    double endVelocity[constants::maxEventInterpolationAxes];
                    double secondVelocity[constants::maxEventInterpolationAxes];
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } startMultipleMov;
                struct LinearIntplPos
                {
                    unsigned int axisCount;
                    int axis[constants::maxEventInterpolationAxes];
                    double target[constants::maxEventInterpolationAxes];
                    double maxVelocity[constants::maxEventInterpolationAxes];
                    double maxAcc[constants::maxEventInterpolationAxes];
                    double maxDec[constants::maxEventInterpolationAxes];
                    double maxJerkAcc[constants::maxEventInterpolationAxes];
                    double maxJerkDec[constants::maxEventInterpolationAxes];
                    ProfileType::T type;
                    double velocity;
                    double acc;
                    double dec;
                    double jerkAcc;
                    double jerkDec;
                    double jerkAccRatio;
                    double jerkDecRatio;
                    double accTime;
                    double decTime;
                    double startingVelocity;
                    double endVelocity;
                    double secondVelocity;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } linearIntplPos;
                struct LinearIntplMov
                {
                    unsigned int axisCount;
                    int axis[constants::maxEventInterpolationAxes];
                    double target[constants::maxEventInterpolationAxes];
                    double maxVelocity[constants::maxEventInterpolationAxes];
                    double maxAcc[constants::maxEventInterpolationAxes];
                    double maxDec[constants::maxEventInterpolationAxes];
                    double maxJerkAcc[constants::maxEventInterpolationAxes];
                    double maxJerkDec[constants::maxEventInterpolationAxes];
                    ProfileType::T type;
                    double velocity;
                    double acc;
                    double dec;
                    double jerkAcc;
                    double jerkDec;
                    double jerkAccRatio;
                    double jerkDecRatio;
                    double accTime;
                    double decTime;
                    double startingVelocity;
                    double endVelocity;
                    double secondVelocity;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } linearIntplMov;
                struct StartAPIBuffer
                {
                    unsigned int channel;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } startAPIBuffer;
                struct ExecQuickStopSingleAxis
                {
                    int axis;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } execQuickStopSingleAxis;
                struct OverrideVelSingleAxis
                {
                    int axis;
                    double velocity;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } overrideVelSingleAxis;
                struct ExecEStop
                {
                    EStopLevel::T eStopLevel;
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } execEStop;
                struct TriggerFlightRecorder
                {
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } triggerFlightRecorder;
                struct ResetFlightRecorder
                {
                    unsigned char singleShot;
                    unsigned char disableAfterActivate;
                } resetFlightRecorder;
            } output;

            unsigned char enabled;
        };

    private:
        WMX3Api *m_wmx3Api;

    public:
        EventControl(WMX3Api *wmx3Api) : m_wmx3Api(wmx3Api) {}
        EventControl() : m_wmx3Api(NULL) {}
        ~EventControl() {}

        // Copy constructor and assignment operator
        EventControl(const EventControl &src) : m_wmx3Api(src.m_wmx3Api) {}
        EventControl &operator=(const EventControl &src)
        {
            if (this != &src)
            {
                m_wmx3Api = src.m_wmx3Api;
            }
            return *this;
        }

        //=====================================================================
        // SetEvent APIs
        //=====================================================================
        // Note: pEventInput and pEventOutput should point to SDK EventInput/EventOutput derived classes
        // pOption should point to wmx3Api::EventOption
        long SetEvent(int *pId, void *pEventInput, void *pEventOutput, EventOption *pOption = NULL)
        {
            return WMX3Broker_Event_SetEvent(pId, pEventInput, pEventOutput, pOption);
        }

        long SetEvent(int *pId, void *pEventInput, void *pEventOutput, int id, EventOption *pOption = NULL)
        {
            return WMX3Broker_Event_SetEventWithId(pId, pEventInput, pEventOutput, id, pOption);
        }

        //[Deprecated]
        long SetEvent(int *pId, Event *pEventData)
        {
            return WMX3Broker_Event_SetEventDeprecated(pId, pEventData);
        }

        //[Deprecated]
        long SetEvent(int *pId, Event *pEventData, int id)
        {
            return WMX3Broker_Event_SetEventDeprecatedWithId(pId, pEventData, id);
        }

        //=====================================================================
        // Event Management APIs
        //=====================================================================
        long EnableEvent(int id, unsigned char enable)
        {
            return WMX3Broker_Event_EnableEvent(id, enable);
        }

        long RemoveEvent(int id)
        {
            return WMX3Broker_Event_RemoveEvent(id);
        }

        long ClearAllEvent()
        {
            return WMX3Broker_Event_ClearAllEvent();
        }

        long GetAllEventID(AllEventID *pEventIdData, int filterInputModuleId = -1,
                           int filterOutputModuleId = -1)
        {
            return WMX3Broker_Event_GetAllEventID(pEventIdData, filterInputModuleId,
                                                  filterOutputModuleId);
        }

        //=====================================================================
        // Software Touch Probe APIs
        //=====================================================================
        long SetSoftwareTouchProbe(unsigned int channel, unsigned char enable,
                                   int axis, int byteAddrs, int bitOffset, unsigned char logic,
                                   TouchProbeMode::T mode)
        {
            return WMX3Broker_Event_SetSoftwareTouchProbe(channel, enable, axis,
                                                          byteAddrs, bitOffset, logic, static_cast<int>(mode));
        }

        long EnableSoftwareTouchProbe(unsigned int channel, unsigned char enable)
        {
            return WMX3Broker_Event_EnableSoftwareTouchProbe(channel, enable);
        }

        long GetSoftwareTouchProbe(unsigned int channel, unsigned char *pEnabled,
                                   int *pAxis, int *pByteAddrs, int *pBitOffset, unsigned char *pLogic,
                                   TouchProbeMode::T *pMode)
        {
            int mode = 0;
            long ret = WMX3Broker_Event_GetSoftwareTouchProbe(channel, pEnabled,
                                                              pAxis, pByteAddrs, pBitOffset, pLogic, &mode);
            if (pMode)
                *pMode = static_cast<TouchProbeMode::T>(mode);
            return ret;
        }

        long IsSoftwareTouchProbeLatched(unsigned int channel, unsigned char *pLatched)
        {
            return WMX3Broker_Event_IsSoftwareTouchProbeLatched(channel, pLatched);
        }

        long GetSoftwareTouchProbeCounterValue(unsigned int channel,
                                               unsigned char *pLatched, double *pCounterValue)
        {
            return WMX3Broker_Event_GetSoftwareTouchProbeCounterValue(channel,
                                                                      pLatched, pCounterValue);
        }

        //=====================================================================
        // Hardware Touch Probe APIs
        //=====================================================================
        long SetHardwareTouchProbe(int axis, unsigned char enable,
                                   TouchProbeMode::T mode, TouchProbeSource::T triggerSource,
                                   unsigned int channel)
        {
            return WMX3Broker_Event_SetHardwareTouchProbe(axis, enable,
                                                          static_cast<int>(mode), static_cast<int>(triggerSource), channel);
        }

        long GetHardwareTouchProbeStatus(int axis, HardwareTouchProbeStatus *pStatus)
        {
            return WMX3Broker_Event_GetHardwareTouchProbeStatus(axis, pStatus);
        }

        long EnableHardwareTouchProbe(int axis, unsigned char enable)
        {
            return WMX3Broker_Event_EnableHardwareTouchProbe(axis, enable);
        }

        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_EventControl_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_EventControl_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // EVENT_SIM_H
