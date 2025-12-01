// ExtList2Broker.h
// extList2 namespace - WMX 1.5 API to WMX3 API Broker
// List-based motion control

#ifndef EXTLIST2BROKER_H
#define EXTLIST2BROKER_H

#include "WMXBroker.h"

namespace wmxAPI {
namespace extList2 {

    class WMXBROKER_API ExtList2 {
    private:
        WMXLIB* wmxlib;

    public:
        ExtList2(WMXLIB* lib);
        ~ExtList2();

        // List management
        WMXAPIFUNC BeginList(unsigned int channel);
        WMXAPIFUNC EndList(unsigned int channel);
        WMXAPIFUNC ExecuteList(unsigned int channel);
        WMXAPIFUNC AbortList(unsigned int channel);
        WMXAPIFUNC ClearList(unsigned int channel);
        WMXAPIFUNC GetListStatus(unsigned int channel, WMX_LIST_STATUS* pStatus);
    };

} // namespace extList2
} // namespace wmxAPI

#endif // EXTLIST2BROKER_H
