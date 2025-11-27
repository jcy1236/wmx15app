// IoBroker.cpp
// WMX 1.5 Io 클래스 API를 WMX3 Io API로 변환

#include "IoBroker.h"
#include "IOApi.h"

namespace wmxAPI {
namespace common {

    //////////////////////////////////////////////////////////////////////////
    // Output APIs
    //////////////////////////////////////////////////////////////////////////

    WMXAPIFUNC Io::SetOutBit(short byte, short bit, unsigned char data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->SetOutBit((int)byte, (int)bit, data);
    }

    WMXAPIFUNC Io::SetOutByte(short offsetByte, unsigned char data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->SetOutByte((int)offsetByte, data);
    }

    WMXAPIFUNC Io::SetOutBytes(short offsetByte, short size, unsigned char* data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->SetOutBytes((int)offsetByte, (int)size, data);
    }

    //////////////////////////////////////////////////////////////////////////
    // Input APIs
    //////////////////////////////////////////////////////////////////////////

    WMXAPIFUNC Io::GetInBit(short byte, short bit, unsigned char* data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->GetInBit((int)byte, (int)bit, data);
    }

    WMXAPIFUNC Io::GetInByte(short offsetByte, unsigned char* data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->GetInByte((int)offsetByte, data);
    }

    WMXAPIFUNC Io::GetInBytes(short offsetByte, short size, unsigned char* data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->GetInBytes((int)offsetByte, (int)size, data);
    }

    //////////////////////////////////////////////////////////////////////////
    // Output Read APIs
    //////////////////////////////////////////////////////////////////////////

    WMXAPIFUNC Io::GetOutBit(short byte, short bit, unsigned char* data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->GetOutBit((int)byte, (int)bit, data);
    }

    WMXAPIFUNC Io::GetOutByte(short offsetByte, unsigned char* data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->GetOutByte((int)offsetByte, data);
    }

    WMXAPIFUNC Io::GetOutBytes(short offsetByte, short size, unsigned char* data)
    {
        wmx3Api::Io* wmx3Io = wmxlib->GetWMX3Io();
        if (!wmx3Io) return -1;

        return wmx3Io->GetOutBytes((int)offsetByte, (int)size, data);
    }

    //////////////////////////////////////////////////////////////////////////
    // Initial Output APIs (WMX3에는 해당 기능 없음 - 내부 버퍼에 저장)
    //////////////////////////////////////////////////////////////////////////

    WMXAPIFUNC Io::SetInitialOutBit(short byte, short bit, unsigned char data)
    {
        unsigned char* buffer = wmxlib->GetInitialOutBuffer();
        if (!buffer || byte < 0 || byte >= MAX_IOOUTSIZE || bit < 0 || bit > 7) {
            return -1;
        }

        if (data) {
            buffer[byte] |= (1 << bit);
        } else {
            buffer[byte] &= ~(1 << bit);
        }
        return 0;
    }

    WMXAPIFUNC Io::SetInitialOutByte(short offsetByte, unsigned char data)
    {
        unsigned char* buffer = wmxlib->GetInitialOutBuffer();
        if (!buffer || offsetByte < 0 || offsetByte >= MAX_IOOUTSIZE) {
            return -1;
        }

        buffer[offsetByte] = data;
        return 0;
    }

    WMXAPIFUNC Io::SetInitialOutBytes(short offsetByte, short size, unsigned char* data)
    {
        unsigned char* buffer = wmxlib->GetInitialOutBuffer();
        if (!buffer || !data || offsetByte < 0 || (offsetByte + size) > MAX_IOOUTSIZE) {
            return -1;
        }

        memcpy(&buffer[offsetByte], data, size);
        return 0;
    }

    WMXAPIFUNC Io::GetInitialOutBit(short byte, short bit, unsigned char* data)
    {
        unsigned char* buffer = wmxlib->GetInitialOutBuffer();
        if (!buffer || !data || byte < 0 || byte >= MAX_IOOUTSIZE || bit < 0 || bit > 7) {
            return -1;
        }

        *data = (buffer[byte] >> bit) & 0x01;
        return 0;
    }

    WMXAPIFUNC Io::GetInitialOutByte(short offsetByte, unsigned char* data)
    {
        unsigned char* buffer = wmxlib->GetInitialOutBuffer();
        if (!buffer || !data || offsetByte < 0 || offsetByte >= MAX_IOOUTSIZE) {
            return -1;
        }

        *data = buffer[offsetByte];
        return 0;
    }

    WMXAPIFUNC Io::GetInitialOutBytes(short offsetByte, short size, unsigned char* data)
    {
        unsigned char* buffer = wmxlib->GetInitialOutBuffer();
        if (!buffer || !data || offsetByte < 0 || (offsetByte + size) > MAX_IOOUTSIZE) {
            return -1;
        }

        memcpy(data, &buffer[offsetByte], size);
        return 0;
    }

} // namespace common
} // namespace wmxAPI
