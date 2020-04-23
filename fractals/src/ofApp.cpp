#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    gui.setup();
    gui.add(radius.setup("radius", 200, 100, 400));
    gui.add(iter.setup("iter", 2, 2, 8));
    
//    radius = 350;
//    iter = 7;

    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    a = ofPoint(-radius*cos(PI/6), -radius*sin(PI/6), 0);
    b = ofPoint(radius*cos(PI/6), -radius*sin(PI/6), 0);
    a2 = ofPoint(radius*cos(PI/6), -radius*sin(PI/6), 0);
    b2 = ofPoint(radius*cos(PI/2), radius*sin(PI/2), 0);
    a3 = ofPoint(radius*cos(PI/2), radius*sin(PI/2), 0);
    b3 = ofPoint(-radius*cos(PI/6), -radius*sin(PI/6), 0);

    KochLine top = KochLine(a, b, iter);
    KochLine left = KochLine(a2, b2, iter);
    KochLine right = KochLine(a3, b3, iter);
  
    kc.push_back(top);
    kc2.push_back(left);
    kc3.push_back(right);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /*
    再帰の円
    drawCircle(w, h, ofGetWidth()/2.0);
     */
    
    
    /*
    カントール集合
    cantor(w - 500, h, 1000);
    
    謎図形１
    drawDiamond(w, h, 200);
    
    謎図形２
    myRect(w, h, 200, 0);
    */

    float w = ofGetWidth()/2;
    float h = ofGetHeight()/2;
    
    ofPushMatrix();
    ofTranslate(w, h);
    for(int i = 0; i < kc.size(); i++) {
        kc[i].draw();
    }
    for(int i = 0; i < kc2.size(); i++) {
        kc2[i].draw();
    }
    for(int i = 0; i < kc3.size(); i++) {
        kc3[i].draw();
    }
    ofPopMatrix();
    
    kc.clear();
    kc2.clear();
    kc3.clear();
    
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
//再帰の円
void ofApp::drawCircle(float x, float y, float radius) {
    ofSetCircleResolution(60);
    ofNoFill();
    ofDrawCircle(x, y, radius);
    if (radius > 8.0){
        radius *= 0.75;
        drawCircle(x + radius/2, y, radius/2);
        drawCircle(x - radius/2, y, radius/2);
        drawCircle(x, y+ radius/2, radius/2);
        drawCircle(x, y - radius/2, radius/2);
    }
}

//カントール集合
void ofApp::cantor(float x, float y, float len) {
    if(len > 1.0) {
        ofDrawLine(x, y, x+len, y);
        
        y += 20;
    
        cantor(x, y, len/3);
        cantor(x + 2 * len/3, y, len/3);
    }
}

//謎の図形
void ofApp::drawDiamond(float x, float y, float size ){
    ofSetRectMode( OF_RECTMODE_CENTER );
    ofNoFill();
    if( size > 16 ){
        drawDiamond( x + size/2, y, size/2 );
        drawDiamond( x - size/2, y, size/2 );
        
        drawDiamond( x, y + size/2, size/2 );
        drawDiamond( x, y - size/2, size/2 );
    }
    
    ofPushMatrix();{
        ofTranslate( x, y);
        ofRotate( 45 );
        ofRect( 0, 0, size, size );
    }ofPopMatrix();
    
}

//謎の図形2
void ofApp::myRect(float x, float y, float size, float angle) {
    ofSetRectMode( OF_RECTMODE_CENTER );
    
    ofNoFill();
    if( size > 16 ){
        angle += 45;
        myRect(x, y, sqrt(2) * size/2, angle);
    }
    
    ofPushMatrix();{
        ofTranslate(x, y);
        ofRotate( angle );
        ofRect( 0, 0, size, size );
    }ofPopMatrix();
}


