#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    
    /* This test for NULL is only required if new() behavior is to return NULL
     * instead of throwing an exception upon an out of memory failure.
     */
    basicClient = new BasicClient();
    QStatus status = ER_OK;
    if (!basicClient->m_msgBus) {
        status = ER_OUT_OF_MEMORY;
    }
    
    if (ER_OK == status) {
        status = basicClient->CreateInterface();
    }
    
    if (ER_OK == status) {
        status = basicClient->StartMessageBus();
    }
    
    if (ER_OK == status) {
        status = basicClient->ConnectToBus();
    }
    
    if (ER_OK == status) {
        basicClient->RegisterBusListener();
        status = basicClient->FindAdvertisedName();
    }
    printf("Basic client setup with status 0x%04x (%s).\n", status, QCC_StatusText(status));
}

//--------------------------------------------------------------
void testApp::update(){
    if(basicClient->m_joinComplete)
        basicClient->MakeMethodCall();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    ofSetColor(0xff, 0xa4, 0x00);
    if(!basicClient->m_joinComplete) {
        ofDrawBitmapString("waiting", 20, 50);
        return;
    }
    int rad = 8;
    if(basicClient->remoteMouseDown) {
        ofSetColor(0xa4, 0xff, 0x00);
        rad = 20;
    }
    ofEllipse(basicClient->remoteMouseX, basicClient->remoteMouseY, rad, rad);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}