//
//  BasicSampleObject.cpp
//  alljoynBasicServer
//
//  Created by elecTron on 7/15/13.
//
//

#include "BasicSampleObject.h"


using namespace ajn;
using namespace qcc;

BasicSampleObject::BasicSampleObject(BusAttachment& bus, const char* path) : BusObject(path)
{
    /** Add the test interface to this object */
    const InterfaceDescription* exampleIntf = bus.GetInterface(INTERFACE_NAME);
    assert(exampleIntf);
    AddInterface(*exampleIntf);
    
    
    /** Register the method handlers with the object */
    const MethodEntry methodEntries[] = {
        { exampleIntf->GetMember("cat"), static_cast<MessageReceiver::MethodHandler>(&BasicSampleObject::Cat) },
        { exampleIntf->GetMember("mouse"), static_cast<MessageReceiver::MethodHandler>(&BasicSampleObject::Mouse) }
    };
    QStatus status = AddMethodHandlers(methodEntries, 2);
    if (ER_OK != status) {
        printf("Failed to register method handlers for BasicSampleObject.\n");
    }
}

void BasicSampleObject::ObjectRegistered()
{
    BusObject::ObjectRegistered();
    printf("ObjectRegistered has been called.\n");
}


void BasicSampleObject::Cat(const InterfaceDescription::Member* member, Message& msg)
{
    /* Concatenate the two input strings and reply with the result. */
    qcc::String inStr1 = msg->GetArg(0)->v_string.str;
    qcc::String inStr2 = msg->GetArg(1)->v_string.str;
    qcc::String outStr = inStr1 + inStr2;
    
    MsgArg outArg("s", outStr.c_str());
    QStatus status = MethodReply(msg, &outArg, 1);
    if (ER_OK != status) {
        printf("Ping: Error sending reply.\n");
    }
}

void BasicSampleObject::Mouse(const InterfaceDescription::Member* member, Message& msg)
{
    MsgArg outMouse[] = {
        MsgArg("i", mouseX),
        MsgArg("i", mouseY),
        MsgArg("b", mouseDown)
    };
    
    QStatus status = MethodReply(msg, outMouse, 3);
    if (ER_OK != status) {
        printf("Ping: Error sending reply.\n");
    }
}

void BasicSampleObject::setMouse(int _mouseX, int _mouseY) {
    mouseX = _mouseX;
    mouseY = _mouseY;
}

void BasicSampleObject::setMouseState(bool down) {
    mouseDown = down;
}