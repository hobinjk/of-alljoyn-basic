//
//  BasicSampleObject.h
//  alljoynBasicServer
//
//  Created by elecTron on 7/15/13.
//
//

#ifndef __alljoynBasicServer__BasicSampleObject__
#define __alljoynBasicServer__BasicSampleObject__

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

using namespace ajn;
using namespace qcc;

class BasicSampleObject : public BusObject {
public:
    BasicSampleObject(BusAttachment& bus, const char* path);
    void ObjectRegistered();
    void Cat(const InterfaceDescription::Member* member, Message& msg);
    void Mouse(const InterfaceDescription::Member* member, Message& msg);
    
    void setMouse(int _mouseX, int _mouseY);
    void setMouseState(bool down);
private:
    int mouseX, mouseY;
    bool mouseDown;
};


#endif /* defined(__alljoynBasicServer__BasicSampleObject__) */
