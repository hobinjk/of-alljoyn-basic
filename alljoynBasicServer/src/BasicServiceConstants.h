//
//  BasicServiceConstants.h
//  alljoynBasicServer
//
//  Created by elecTron on 7/15/13.
//
//

#ifndef alljoynBasicServer_BasicServiceConstants_h
#define alljoynBasicServer_BasicServiceConstants_h

#include <qcc/String.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/version.h>

#include <alljoyn/Status.h>

using namespace qcc;

/*constants*/
static const char* INTERFACE_NAME = "org.alljoyn.Bus.sample";
static const char* SERVICE_NAME = "org.alljoyn.Bus.sample";
static const char* SERVICE_PATH = "/sample";
static const ajn::SessionPort SERVICE_PORT = 25;


#endif
