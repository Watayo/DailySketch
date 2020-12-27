#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    updateShader.load("shaders/updateGrayScott");
    render.load("shaders/render");

    cellWidth = ofGetWidth();
    cellHeight = ofGetHeight();

    vector<float> color(cellWidth * cellHeight * 3);

    int center = 100;

    for (int x = 0; x < cellWidth; x++) {
        for (int y = 0; y < cellHeight; y++) {

            int i = y * cellWidth + x;
            color[i * 3 + 0] = 0.0;
            color[i * 3 + 1] = 0.0;
            color[i * 3 + 2] = 0.0;
        
        }
    }

    pingPong.allocate(cellWidth, cellHeight, GL_RGB32F);
    pingPong.src->getTexture().loadData(color.data(), cellWidth, cellHeight, GL_RGB);
    pingPong.dst->getTexture().loadData(color.data(), cellWidth, cellHeight, GL_RGB);

    gui.setup();
    gui.add(feed.set("feed", 0.055, 0.0, 1.0));
    gui.add(kill.set("kill", 0.062, 0.0, 1.0));
    gui.add(dA.set("dA", 1e-5, 0.0, 1.0));
    gui.add(dB.set("dB", 2e-5, 0.0, 1.0));
    gui.add(dt.set("dt", 1.0, 0.0, 1.2));
    gui.add(color1.set("color1", ofFloatColor(0.0, 0.0, 0.0, 0.1), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(color2.set("color2", ofFloatColor(0.2, 0.2, 0.2, 0.2), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(color3.set("color3", ofFloatColor(0.4, 0.4, 0.4, 0.21), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(color4.set("color4", ofFloatColor(0.8, 0.8, 0.8, 0.4), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(color5.set("color5", ofFloatColor(1.0, 1.0, 1.0, 0.6), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
}

//--------------------------------------------------------------
void ofApp::update(){

    ofSetWindowTitle(name);

    pingPong.dst->begin();
    ofClear(0);

    updateShader.begin();
    updateShader.setUniformTexture("backBuffer", pingPong.src->getTexture(), 0);
    updateShader.setUniform1f("u_feed", feed);
    updateShader.setUniform1f("u_kill", kill);
    updateShader.setUniform1f("u_dA", dA);
    updateShader.setUniform1f("u_dB", dB);
    updateShader.setUniform1f("u_dt", dt);
    pingPong.src->draw(0, 0, cellWidth, cellHeight);
    updateShader.end();

    pingPong.dst->end();

    pingPong.swap();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //cam.begin();

    render.begin();
    render.setUniformTexture("grayScottTex", pingPong.dst->getTexture(), 0);
    render.setUniform4f("color1", color1);
    render.setUniform4f("color2", color2);
    render.setUniform4f("color3", color3);
    render.setUniform4f("color4", color4);
    render.setUniform4f("color5", color5);
    ofDrawRectangle(0, 0, cellWidth, cellHeight);
    render.end();

    //cam.end();
    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
    case '0':
        name = "none";
        feed = 0.055;
        kill = 0.062;
        break;
    case '1':
        name = "stripe";
        feed = 0.022;
        kill = 0.051;
        break;
    case '2':
        name = "spot";
        feed = 0.035;
        kill = 0.065;
        break;
    case '3':
        name = "amorphous";
        feed = 0.04;
        kill = 0.06;
        break;
    case '4':
        name = "bubble";
        feed = 0.012;
        kill = 0.05;
        break;

    case '5':
        name = "wave";
        feed = 0.025;
        kill = 0.005;
        break;
    case 'G':
        pingPong.dst->begin();
        ofClear(0);
        ofSetColor(255);
        ofDrawCircle(cellWidth/2 + 50 * cos(PI / 2), cellHeight/2 + 50 * sin(PI/2), 50);
        ofDrawCircle(cellWidth / 2 + 50 * cos(PI / 2 + 2*PI/3), cellHeight / 2 + 50 * sin(PI / 2 + 2 * PI / 3), 50);
        ofDrawCircle(cellWidth /2 + 50 * cos(PI / 2 + 4 * PI / 3), cellHeight / 2 + 50 * sin(PI / 2 + 2 * PI / 3), 50);
        pingPong.src->draw(0, 0);
        pingPong.dst->end();
        pingPong.swap();
        break;
    default:
        break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    pingPong.dst->begin();
    ofClear(0);
    ofSetColor(255);
    ofDrawCircle(x, y, 30);
    pingPong.src->draw(0, 0);
    pingPong.dst->end();

    pingPong.swap();
}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){


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
