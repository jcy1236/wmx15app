// IOApi_Sim.h
// WMX3 Io API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::Io interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef IOAPI_SIM_H
#define IOAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    //=========================================================================
    // Io class - Digital and Analog I/O operations
    //=========================================================================
    class Io
    {
    private:
        WMX3Api *m_wmx3Api;

    public:
        Io(WMX3Api *wmx3Api) : m_wmx3Api(wmx3Api) {}
        Io() : m_wmx3Api(NULL) {}
        ~Io() {}

        // Copy constructor and assignment operator
        Io(const Io &src) : m_wmx3Api(src.m_wmx3Api) {}
        Io &operator=(const Io &src)
        {
            if (this != &src)
            {
                m_wmx3Api = src.m_wmx3Api;
            }
            return *this;
        }

        //=====================================================================
        // Digital Output
        //=====================================================================
        long SetOutBit(int addr, int bit, unsigned char data)
        {
            return WMX3Broker_Io_SetOutBit(addr, bit, data);
        }

        long SetOutByte(int addr, unsigned char data)
        {
            return WMX3Broker_Io_SetOutByte(addr, data);
        }

        long SetOutBytes(int addr, int size, unsigned char *pData)
        {
            return WMX3Broker_Io_SetOutBytes(addr, size, pData);
        }

        //=====================================================================
        // Digital Input
        //=====================================================================
        long GetInBit(int addr, int bit, unsigned char *pData)
        {
            return WMX3Broker_Io_GetInBit(addr, bit, pData);
        }

        long GetInByte(int addr, unsigned char *pData)
        {
            return WMX3Broker_Io_GetInByte(addr, pData);
        }

        long GetInBytes(int addr, int size, unsigned char *pData)
        {
            return WMX3Broker_Io_GetInBytes(addr, size, pData);
        }

        //=====================================================================
        // Digital Output Read (read back output state)
        //=====================================================================
        long GetOutBit(int addr, int bit, unsigned char *pData)
        {
            return WMX3Broker_Io_GetOutBit(addr, bit, pData);
        }

        long GetOutByte(int addr, unsigned char *pData)
        {
            return WMX3Broker_Io_GetOutByte(addr, pData);
        }

        long GetOutBytes(int addr, int size, unsigned char *pData)
        {
            return WMX3Broker_Io_GetOutBytes(addr, size, pData);
        }

        //=====================================================================
        // Analog Output
        //=====================================================================
        long SetOutAnalogDataShort(int addr, short analogData)
        {
            return WMX3Broker_Io_SetOutAnalogDataShort(addr, analogData);
        }

        long SetOutAnalogDataInt(int addr, int analogData)
        {
            return WMX3Broker_Io_SetOutAnalogDataInt(addr, analogData);
        }

        //=====================================================================
        // Analog Input
        //=====================================================================
        long GetInAnalogDataShort(int addr, short *pAnalogData)
        {
            return WMX3Broker_Io_GetInAnalogDataShort(addr, pAnalogData);
        }

        long GetInAnalogDataInt(int addr, int *pAnalogData)
        {
            return WMX3Broker_Io_GetInAnalogDataInt(addr, pAnalogData);
        }
    };

} // namespace wmx3Api

#endif // IO_SIM_H
