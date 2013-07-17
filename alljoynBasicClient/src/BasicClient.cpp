#include "BasicClient.h"


BasicClient::BasicClient() {
    m_msgBus = new BusAttachment("myApp", true);
    m_joinComplete = false;
    m_sessionId = 0;
}

/** Create the interface, report the result to stdout, and return the result status. */
QStatus BasicClient::CreateInterface(void)
{
    /* Add org.alljoyn.Bus.method_sample interface */
    InterfaceDescription* testIntf = NULL;
    QStatus status = m_msgBus->CreateInterface(INTERFACE_NAME, testIntf);
    
    if (status == ER_OK) {
        printf("Interface '%s' created.\n", INTERFACE_NAME);
        testIntf->AddMethod("cat", "ss",  "s", "inStr1,inStr2,outStr", 0);
        testIntf->AddMethod("mouse", "",  "iib", "mouseX,mouseY,mouseDown", 0);
        
        testIntf->Activate();
    } else {
        printf("Failed to create interface '%s'.\n", INTERFACE_NAME);
    }
    
    return status;
}

/** Start the message bus, report the result to stdout, and return the result status. */
QStatus BasicClient::StartMessageBus(void)
{
    QStatus status = m_msgBus->Start();
    
    if (ER_OK == status) {
        printf("BusAttachment started.\n");
    } else {
        printf("BusAttachment::Start failed.\n");
    }
    
    return status;
}

/** Handle the connection to the bus, report the result to stdout, and return the result status. */
QStatus BasicClient::ConnectToBus(void)
{
    QStatus status = m_msgBus->Connect();
    
    if (ER_OK == status) {
        printf("BusAttachment connected to '%s'.\n", m_msgBus->GetConnectSpec().c_str());
    } else {
        printf("BusAttachment::Connect('%s') failed.\n", m_msgBus->GetConnectSpec().c_str());
    }
    
    return status;
}

/** Register a bus listener in order to get discovery indications and report the event to stdout. */
void BasicClient::RegisterBusListener(void)
{
    /* Static bus listener */
    // static BusListener s_busListener = *this;
    
    m_msgBus->RegisterBusListener(*this);
    printf("BusListener Registered.\n");
}

/** Begin discovery on the well-known name of the service to be called, report the result to
 stdout, and return the result status. */
QStatus BasicClient::FindAdvertisedName(void)
{
    /* Begin discovery on the well-known name of the service to be called */
    QStatus status = m_msgBus->FindAdvertisedName(SERVICE_NAME);
    
    if (status == ER_OK) {
        printf("org.alljoyn.Bus.FindAdvertisedName ('%s') succeeded.\n", SERVICE_NAME);
    } else {
        printf("org.alljoyn.Bus.FindAdvertisedName ('%s') failed (%s).\n", SERVICE_NAME, QCC_StatusText(status));
    }
    
    return status;
}

/** Wait for join session to complete, report the event to stdout, and return the result status. */
QStatus BasicClient::WaitForJoinSessionCompletion(void)
{
    unsigned int count = 0;
    
    while (!m_joinComplete) {
        if (0 == (count++ % 10)) {
            printf("Waited %u seconds for JoinSession completion.\n", count / 10);
        }
        
#ifdef _WIN32
        Sleep(100);
#else
        usleep(100 * 1000);
#endif
    }
    
    return m_joinComplete ? ER_OK : ER_ALLJOYN_JOINSESSION_REPLY_CONNECT_FAILED;
}

/** Do a method call, report the result to stdout, and return the result status. */
QStatus BasicClient::MakeMethodCall(void)
{
    ProxyBusObject remoteObj(*m_msgBus, SERVICE_NAME, SERVICE_PATH, m_sessionId);
    const InterfaceDescription* alljoynTestIntf = m_msgBus->GetInterface(INTERFACE_NAME);
    
    assert(alljoynTestIntf);
    remoteObj.AddInterface(*alljoynTestIntf);
    
    Message reply(*m_msgBus);
    MsgArg inputs[0];
    
    QStatus status = remoteObj.MethodCall(SERVICE_NAME, "mouse", NULL, 0, reply, 5000);
    
    if (ER_OK == status) {
        //printf("'%s.%s' (path='%s') returned '%d, %d'.\n", SERVICE_NAME, "mouse",
        //       SERVICE_PATH, reply->GetArg(0)->v_int32, reply->GetArg(1)->v_int32);
        remoteMouseX = reply->GetArg(0)->v_int32;
        remoteMouseY = reply->GetArg(1)->v_int32;
        remoteMouseDown = reply->GetArg(2)->v_bool;
    } else {
        printf("MethodCall on '%s.%s' failed.", SERVICE_NAME, "mouse");
    }
    return status;
}
