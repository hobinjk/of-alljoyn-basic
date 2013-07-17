/**
 * @file
 * @brief Sample implementation of an AllJoyn service.
 *
 * This sample will show how to set up an AllJoyn service that will registered with the
 * wellknown name 'org.alljoyn.Bus.method_sample'.  The service will register a method call
 * with the name 'cat'  this method will take two input strings and return a
 * Concatenated version of the two strings.
 *
 */

/******************************************************************************
 * Copyright 2010-2011, Qualcomm Innovation Center, Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 ******************************************************************************/

#include "BasicService.h"

using namespace std;
using namespace qcc;
using namespace ajn;

BusAttachment* BasicService::m_msgBus = NULL;

void BasicService::NameOwnerChanged(const char* busName, const char* previousOwner, const char* newOwner)
{
    if (newOwner && (0 == strcmp(busName, SERVICE_NAME))) {
        printf("NameOwnerChanged: name=%s, oldOwner=%s, newOwner=%s.\n",
               busName,
               previousOwner ? previousOwner : "<none>",
               newOwner ? newOwner : "<none>");
    }
}
bool BasicService::AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts)
{
    if (sessionPort != SERVICE_PORT) {
        printf("Rejecting join attempt on unexpected session port %d.\n", sessionPort);
        return false;
    }
    printf("Accepting join session request from %s (opts.proximity=%x, opts.traffic=%x, opts.transports=%x).\n",
           joiner, opts.proximity, opts.traffic, opts.transports);
    return true;
}

/** Create the interface, report the result to stdout, and return the result status. */
QStatus BasicService::CreateInterface(void)
{
    /* Add org.alljoyn.Bus.method_sample interface */
    InterfaceDescription* testIntf = NULL;
    QStatus status = m_msgBus->CreateInterface(INTERFACE_NAME, testIntf);

    if (status == ER_OK) {
        printf("Interface created.\n");
        testIntf->AddMethod("cat", "ss",  "s", "inStr1,inStr2,outStr", 0);
        testIntf->AddMethod("mouse", "",  "iib", "mouseX,mouseY,mouseDown", 0);
        
        testIntf->Activate();
    } else {
        printf("Failed to create interface '%s'.\n", INTERFACE_NAME);
    }

    return status;
}

/** Register the bus object and connect, report the result to stdout, and return the status code. */
QStatus BasicService::RegisterBusObject(BasicSampleObject* obj)
{
    QStatus status = m_msgBus->RegisterBusObject(*obj);

    if (ER_OK == status) {
        printf("RegisterBusObject succeeded.\n");
    } else {
        printf("RegisterBusObject failed (%s).\n", QCC_StatusText(status));
    }

    return status;
}

/** Connect to the daemon, report the result to stdout, and return the status code. */
QStatus BasicService::ConnectToDaemon(void)
{
    QStatus status = m_msgBus->Connect();

    if (ER_OK == status) {
        printf("Connect to '%s' succeeded.\n", m_msgBus->GetConnectSpec().c_str());
    } else {
        printf("Failed to connect to '%s' (%s).\n", m_msgBus->GetConnectSpec().c_str(), QCC_StatusText(status));
    }

    return status;
}

/** Start the message bus, report the result to stdout, and return the status code. */
QStatus BasicService::StartMessageBus(void)
{
    m_msgBus->RegisterBusListener(*this);
    
    /*if (ER_OK == status) {
        printf("Listening to m_msgBus.\n");
    } else {
        printf("Listening to m_msgBus failed (%s).\n", QCC_StatusText(status));
        return status;
    }*/
    
    QStatus status = m_msgBus->Start();
    
    if (ER_OK == status) {
        printf("BusAttachment started.\n");
    } else {
        printf("Start of BusAttachment failed (%s).\n", QCC_StatusText(status));
    }
    
    return status;
}

/** Create the session, report the result to stdout, and return the status code. */
QStatus BasicService::CreateSession(TransportMask mask)
{
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, mask);
    SessionPort sp = SERVICE_PORT;
    QStatus status = m_msgBus->BindSessionPort(sp, opts, *this);

    if (ER_OK == status) {
        printf("BindSessionPort succeeded.\n");
    } else {
        printf("BindSessionPort failed (%s).\n", QCC_StatusText(status));
    }

    return status;
}

/** Advertise the service name, report the result to stdout, and return the status code. */
QStatus BasicService::AdvertiseName(TransportMask mask)
{
    QStatus status = m_msgBus->AdvertiseName(SERVICE_NAME, mask);

    if (ER_OK == status) {
        printf("Advertisement of the service name '%s' succeeded.\n", SERVICE_NAME);
    } else {
        printf("Failed to advertise name '%s' (%s).\n", SERVICE_NAME, QCC_StatusText(status));
    }

    return status;
}

/** Request the service name, report the result to stdout, and return the status code. */
QStatus BasicService::RequestName(void)
{
    const uint32_t flags = DBUS_NAME_FLAG_REPLACE_EXISTING | DBUS_NAME_FLAG_DO_NOT_QUEUE;
    QStatus status = m_msgBus->RequestName(SERVICE_NAME, flags);

    if (ER_OK == status) {
        printf("RequestName('%s') succeeded.\n", SERVICE_NAME);
    } else {
        printf("RequestName('%s') failed (status=%s).\n", SERVICE_NAME, QCC_StatusText(status));
    }

    return status;
}

/** Main entry point */
BasicService::BasicService() {
    printf("AllJoyn Library version: %s.\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s.\n", ajn::GetBuildInfo());

    /* Create message bus */
    m_msgBus = new BusAttachment("myApp", true);
}
