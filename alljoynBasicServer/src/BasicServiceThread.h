//
//  BasicServiceThread.h
//  alljoynBasicServer
//
//  Created by elecTron on 7/16/13.
//
//

#ifndef __alljoynBasicServer__BasicServiceThread__
#define __alljoynBasicServer__BasicServiceThread__

#include <iostream>
#include "ofMain.h"
#include "BasicService.h"

class BasicServiceThread: public ofThread {
public:
    void threadedFunction();
    BasicService *basicService;
    BasicSampleObject *basicSampleObject;
};

#endif /* defined(__alljoynBasicServer__BasicServiceThread__) */
