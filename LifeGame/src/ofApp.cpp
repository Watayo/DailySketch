#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(255);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(Tl.setup("Tl", 0, 1.5, 8));
    gui.add(alpha.setup("Th", 0, 3.0, 8));
    gui.add(F.setup("F", 1, 1, 10));
    gui.add(change.setup("change"));

    
}

//--------------------------------------------------------------
void ofApp::update(){
    Th = Tl + alpha;
    if(change) {
        lg.generate();
    } else {
        rl.generate(Tl, Th, F);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(change) {
        lg.display();
    } else {
        rl.display();
    }
    
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
    lg.init();
    rl.init();
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
