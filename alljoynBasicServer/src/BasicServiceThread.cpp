//
//  BasicServiceThread.cpp
//  alljoynBasicServer
//
//  Created by elecTron on 7/16/13.
//
//

#include "BasicServiceThread.h"


void BasicServiceThread::threadedFunction() {
    QStatus status = ER_OK;
    basicService = new BasicService();
    if (ER_OK == status) {
        status = basicService->CreateInterface();
    }
    
    if (ER_OK == status) {
        status = basicService->StartMessageBus();
    }
    basicSampleObject = new BasicSampleObject(*(basicService->m_msgBus), SERVICE_PATH);
    
    if (ER_OK == status) {
        
        status = basicService->RegisterBusObject(basicSampleObject);
    }
    
    if (ER_OK == status) {
        status = basicService->ConnectToDaemon();
    }
    
    /*
     * Advertise this service on the bus.
     * There are three steps to advertising this service on the bus.
     * 1) Request a well-known name that will be used by the client to discover
     *    this service.
     * 2) Create a session.
     * 3) Advertise the well-known name.
     */
    if (ER_OK == status) {
        status = basicService->RequestName();
    }
    
    const TransportMask SERVICE_TRANSPORT_TYPE = TRANSPORT_ANY;
    
    if (ER_OK == status) {
        status = basicService->CreateSession(SERVICE_TRANSPORT_TYPE);
    }
    
    if (ER_OK == status) {
        status = basicService->AdvertiseName(SERVICE_TRANSPORT_TYPE);
    }
    
    printf("Basic service running with status 0x%04x (%s).\n", status, QCC_StatusText(status));
    
    while(isThreadRunning()) {
        usleep(100 * 1000);
    }
}