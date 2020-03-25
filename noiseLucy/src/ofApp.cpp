#include "ofApp.h"
const int N = 256;
float spectrum[N];
float valume;
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(50, 50, 50, 0);
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    myModel.loadModel("Alucy.obj");
    
    
    shader.load("shader");
    
    
    sound.loadSound("surface.wav");
    sound.setLoop(true);
    sound.play();
    
    for (int i=0; i<N; i++) {
        spectrum[i] = 0.0f;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //音楽
    ofSoundUpdate();
    
    float *val = ofSoundGetSpectrum(N);
    for(int i = 0; i < N; i++) {
        spectrum[i] *= 0.95;
        spectrum[i] = max(spectrum[i], val[i]);
        valume += spectrum[i];
    }
    
    valume /= N;
    
    
    
    float time = ofGetElapsedTimef();
    
    float dt = ofClamp(time - time0, 0, 0.1);
    time0 = time;
    float speed = ofMap(mouseX, 0, ofGetHeight(), 0, 5);
    
    phase += speed * dt;
    
    distortAmount = ofMap(mouseX, 0, ofGetWidth(), 0, 1.0);
    
    cam.lookAt(ofVec3f(0,300,0));
    cam.setPosition(800*cos(ofGetElapsedTimef()), 500, 800*sin(ofGetElapsedTimef()));
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    
//    light.enable();
//    ofEnableSeparateSpecularLight();
//    ofEnableLighting();

    
    
//
    cam.begin();
    
    ofRotateX(180);
    shader.begin();
    
    
    shader.setUniform1f("phase", phase );
    shader.setUniform1f("distortAmount", distortAmount );
    shader.setUniform1fv( "specArray", spectrum, N );
    shader.setUniform1f( "audio", valume );
    //Enable the shader
    
    shader.setUniform1f("time", ofGetElapsedTimef());
    
    myModel.drawFaces();
    shader.end();
    
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

void setNormals(ofMesh &mesh) {
    //the number of the vertices.
    int nV = mesh.getNumVertices();
    
    //the number of the triangles.
    int nT = mesh.getNumIndices() / 3;
    
    vector<glm::vec3> norm(nV);
    
    for (int t = 0; t < nT; t++) {
        //Get indices of triangle's t
        int i1 = mesh.getIndex(3*t);
        int i2 = mesh.getIndex(3*t + 1);
        int i3 = mesh.getIndex(3*t + 2);
        
        const glm::vec3 &v1 = mesh.getVertex(i1);
        const glm::vec3 &v2 = mesh.getVertex(i2);
        const glm::vec3 &v3 = mesh.getVertex(i3);
        
        glm::vec3 dir = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        
        norm[i1] += dir;
        norm[i2] += dir;
        norm[i3] += dir;
    }
    //normlize the normal's length
    for(int i = 0; i < nV; i++) {
        norm[i] = glm::normalize(norm[i]);
    }
    
    mesh.clearNormals();
    mesh.addNormals(norm);
    
    
}

