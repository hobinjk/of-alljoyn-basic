#include "testApp.h"
#include <qcc/Log.h>

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    basicServiceThread = new BasicServiceThread();
    basicServiceThread->startThread(false, true);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    ofSetColor(0xff, 0xa4, 0x00);
    basicServiceThread->basicSampleObject->setMouse(ofGetMouseX(),ofGetMouseY());
    basicServiceThread->basicSampleObject->setMouseState(ofGetMousePressed());
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