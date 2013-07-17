//
//  BasicService.h
//  alljoynBasicServer
//
//  Created by elecTron on 7/15/13.
//
//

#ifndef alljoynBasicServer_BasicService_h
#define alljoynBasicServer_BasicService_h

#include <qcc/platform.h>

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <vector>

#include <qcc/String.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/version.h>

#include <alljoyn/Status.h>

#include "BasicServiceConstants.h"
#include "BasicSampleObject.h"

using namespace ajn;
using namespace qcc;



class BasicService : public BusListener, public SessionPortListener {
public:
    static BusAttachment* m_msgBus;
    
    BasicService();
    QStatus CreateInterface();
    QStatus RegisterBusObject(BasicSampleObject* obj);
    QStatus ConnectToDaemon();
    QStatus StartMessageBus();
    QStatus CreateSession(TransportMask mask);
    QStatus AdvertiseName(TransportMask mask);
    QStatus RequestName(void);

    //BusListener/SessionPortListener implementation
    void NameOwnerChanged(const char* busName, const char* previousOwner, const char* newOwner) override;
    bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) override;
};

#endif
