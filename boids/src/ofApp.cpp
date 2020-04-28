#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // shader setings
    shader.load("shaders/shader");
    
// ----------------------------- debug
   // projection
   std::cout << "Fov : " << cam.getFov() << endl;
   std::cout << "AspectRatio : " << cam.getAspectRatio() << endl;
   std::cout << "NearClip : " << cam.getNearClip() << endl;
   std::cout << "FarClip : " << cam.getFarClip() << endl;
   // view
   std::cout << "Position: " << cam.getPosition() << endl;
   std::cout << "LookAt : " << cam.getLookAtDir() << endl;
   std::cout << "Up : " << cam.getUpDir() << endl;


    
    // camera setting
    cam.setNearClip(0);
    cam.setFarClip(1500);
    
    
    
    
    f.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();
    f.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.begin();
    shader.begin();
    //cout << .size() << endl;
    
    ofMatrix4x4 viewMatrix;
    viewMatrix = ofGetCurrentViewMatrix();
    ofMatrix4x4 projectionMatrix;
    projectionMatrix = cam.getProjectionMatrix();
    
    for(int i=0; i<100; i++){
        // model Matrix
        ofMatrix4x4 modelMatrix;
        modelMatrix.translate(ofPoint(f.getPos()[i]));
        //modelMatrix.rotate(time*10, 1.0, 0.5, 0.0);
        //pos * modelMatrix;
        sphere.setPosition(ofVec3f(0, 0, 0));
        sphere.setRadius(5);

        // view Matrix
//        ofMatrix4x4 viewMatrix;
//        viewMatrix = ofGetCurrentViewMatrix();

        // projection Matrix
//        ofMatrix4x4 projectionMatrix;
//        projectionMatrix = cam.getProjectionMatrix();

        // mvp Matrix
        ofMatrix4x4 mvpMatrix;
        mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;

        // inv Matrix
        ofMatrix4x4 invMatrix;
        invMatrix = modelMatrix.getInverse();


        shader.setUniformMatrix4f("model", modelMatrix);
        shader.setUniformMatrix4f("view", viewMatrix);
        shader.setUniformMatrix4f("projection", projectionMatrix);
        shader.setUniformMatrix4f("mvp", mvpMatrix);
        shader.setUniformMatrix4f("inv", invMatrix);
        

        vboMesh = sphere.getMesh();
        for(int j=0; j<vboMesh.getVertices().size(); j++){
            vboMesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
        }
        
        // light position
        ofVec3f lightPosition = ofVec3f(200 * cos(time * 0.8), 200.0*cos(time * 0.6), 200 * sin(time * 0.6));
        lightsphere.setPosition(lightPosition);
        lightsphere.setRadius(10);
        
        // eyeDirection
        ofVec3f eyeDirection = ofVec3f(cam.getPosition());

        // ambient Color
        ofVec4f ambientColor = ofVec4f(0.1, 0.1, 0.1, 1.0);
        
        shader.setUniform3f("lightPosition", lightPosition);
        shader.setUniform3f("eyeDirection", eyeDirection);
        shader.setUniform4f("ambientColor", ambientColor);
        
        vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        vboMesh.draw();
        
    }
    
    
    //f.draw();
    
    shader.end();
    
    // draw axis (x, y, z)
    ofSetLineWidth(0.1);
    ofSetColor(255, 0, 0);
    ofDrawLine(-500, 0, 0, 500, 0, 0);
    ofSetColor(0, 255, 0);
    ofDrawLine(0, -400, 0, 0, 400, 0);
    ofSetColor(0, 0, 255);
    ofDrawLine(0, 0, -400, 0, 0, 400);
    
    ofSetColor(255);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofDrawBox(0, 0, 0, 400, 400, 400);
    ofPopStyle();
    
    lightsphere.draw();
    
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
