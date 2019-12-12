#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    numParticle = 100000;
    
    ofBackground(0);
    
    gui.setup();
    gui.add(aa.setup("a", 1, -3, 3));
    gui.add(bb.setup("b", 1, -3, 3));
    gui.add(cc.setup("c", 1, -3, 3));
    gui.add(dd.setup("d", 1, -3, 3));
    gui.add(color.setup("color", ofColor(255, 255, 255), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
//    a = -2.0;
//    b = 1.6;
//    c = -2.0;
//    d = 0.7;
//
}

//--------------------------------------------------------------
void ofApp::update(){
    co = color;
    float t = ofGetElapsedTimef()*0.05;
    a = aa*ofNoise(t);
    b = bb*ofNoise(t);
    c = cc*ofNoise(t);
    d = dd*ofNoise(t);
}

//--------------------------------------------------------------
void ofApp::draw(){
  cam.begin();
//  ofPopMatrix();
//
//    ofPushMatrix();
//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    VboMesh.clear();
    float x = 1.0;
    float y = 1.0;
    float z = 1.0;
      
    for(int i = 0; i < numParticle; i++) {
        xn = sin(a*y) + c * cos(a*x);
        yn = sin(b*x) + d * cos(b*y);
        zn = sin(d*y) + a * cos(c*x);
        
        x = xn;
        y = yn;
        z = zn;
        
        point[i].x = x * 120;
        point[i].y = y * 120;
        point[i].z = z * 120;
        
        VboMesh.addVertex(ofVec3f(point[i].x, point[i].y, point[i].z));
        VboMesh.addColor(co);
        
    }
    
    glPointSize(1.0);
    VboMesh.setMode(OF_PRIMITIVE_POINTS);
    VboMesh.draw();
    cam.end();
//    ofPopMatrix();
    
    
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
