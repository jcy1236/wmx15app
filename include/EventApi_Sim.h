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
    }

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
    };

} // namespace wmx3Api

#endif // EVENT_SIM_H
