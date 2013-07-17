/**
 * @file
 * @brief  Sample implementation of an AllJoyn client.
 */

/******************************************************************************
 *
 *
 * Copyright 2009-2012, Qualcomm Innovation Center, Inc.
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
#include <qcc/platform.h>

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <vector>

#include <qcc/String.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/version.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/Status.h>

#pragma "once"

using namespace std;
using namespace qcc;
using namespace ajn;

/*constants*/
static const char* INTERFACE_NAME = "org.alljoyn.Bus.sample";
static const char* SERVICE_NAME = "org.alljoyn.Bus.sample";
static const char* SERVICE_PATH = "/sample";
static const SessionPort SERVICE_PORT = 25  ;

class BasicClient : public BusListener, public SessionListener {
public:
    BasicClient();
    /** Create the interface, report the result to stdout, and return the result status. */
    QStatus CreateInterface(void);

    /** Start the message bus, report the result to stdout, and return the result status. */
    QStatus StartMessageBus(void);

    /** Handle the connection to the bus, report the result to stdout, and return the result status. */
    QStatus ConnectToBus(void);

    /** Register a bus listener in order to get discovery indications and report the event to stdout. */
    void RegisterBusListener(void);

    /** Begin discovery on the well-known name of the service to be called, report the result to
       stdout, and return the result status. */
    QStatus FindAdvertisedName(void);

    /** Wait for join session to complete, report the event to stdout, and return the result status. */
    QStatus WaitForJoinSessionCompletion(void);

    /** Do a method call, report the result to stdout, and return the result status. */
    QStatus MakeMethodCall(void);
    
    void FoundAdvertisedName(const char* name, TransportMask transport, const char* namePrefix)
    {
        if (0 == strcmp(name, SERVICE_NAME)) {
            printf("FoundAdvertisedName(name='%s', prefix='%s')\n", name, namePrefix);
            
            /* We found a remote bus that is advertising basic service's well-known name so connect to it. */
            /* Since we are in a callback we must enable concurrent callbacks before calling a synchronous method. */
            m_msgBus->EnableConcurrentCallbacks();
            SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
            QStatus status = m_msgBus->JoinSession(name, SERVICE_PORT, this, m_sessionId, opts);
            if (ER_OK == status) {
                printf("JoinSession SUCCESS (Session id=%d).\n", m_sessionId);
            } else {
                printf("JoinSession failed (status=%s).\n", QCC_StatusText(status));
            }
        }
        m_joinComplete = true;
    }
    
    void NameOwnerChanged(const char* busName, const char* previousOwner, const char* newOwner)
    {
        if (newOwner && (0 == strcmp(busName, SERVICE_NAME))) {
            printf("NameOwnerChanged: name='%s', oldOwner='%s', newOwner='%s'.\n",
                   busName,
                   previousOwner ? previousOwner : "<none>",
                   newOwner ? newOwner : "<none>");
        }
    }
    BusAttachment* m_msgBus;
    bool m_joinComplete;
    SessionId m_sessionId;
    
    int remoteMouseX, remoteMouseY;
    bool remoteMouseDown;
};