// StatusMapper.h
// WMX3 CoreMotionStatus to WMX 1.5 WMX_STATUS conversion

#ifndef STATUSMAPPER_H
#define STATUSMAPPER_H

#include "wmxapi_type.h"
#include "CoreMotionApi.h"
#include "IOApi.h"

class StatusMapper {
public:
    // WMX3 CoreMotionStatus + Io to WMX 1.5 WMX_STATUS conversion
    static void MapStatus(const wmx3Api::CoreMotionStatus& src, wmx3Api::Io* io, WMX_STATUS* dst);

private:
    // Helper methods for individual field mapping
    static void MapAxisStatus(const wmx3Api::CoreMotionStatus& src, WMX_STATUS* dst, int axisCount);
    static void MapIoStatus(wmx3Api::Io* io, WMX_STATUS* dst);
    static void MapEngineStatus(const wmx3Api::CoreMotionStatus& src, WMX_STATUS* dst);
};

#endif // STATUSMAPPER_H
