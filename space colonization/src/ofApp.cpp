#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){
    tree.grow();

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofRotateY(ofGetElapsedTimef() * 2.0);
    tree.display();
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mouseX = x;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::branch(float length) {
    //float theta = ofRandom(0, 60);
    ofSetLineWidth(length * 0.12);
    ofDrawLine(0, 0, 0, -length);
    ofTranslate(0, -length);
     length *= 0.7;
    
    generation++;
    
    float noise = ofNoise(generation, ofGetElapsedTimef() * 0.1);
    float theta = ofMap(mouseX, 0, ofGetWidth(), -180, 180);
    
    if(length > 3.0) {
        ofPushMatrix();
        ofRotate(45 + theta + noise * 10-5);
        branch(length);
        ofPopMatrix();
        
        ofPushMatrix();
        ofRotate(-45 + theta - noise * 10-5);
        branch(length);
        ofPopMatrix();
    }
    
    generation--;
}
