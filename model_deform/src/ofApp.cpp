#include "ofApp.h"

glm::vec3 getLightDirection(DirectionalLight& l) {
    return glm::normalize(l.direction * -1.0f);
}

glm::vec3 getLightColor(DirectionalLight& l) {
    return l.color * l.intensity;
}

\
//using namespace glm;
//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true); // 垂直同期
    ofBackground(0);
    

//    mesh.load("torus.ply");
    model.loadModel("Alucy.obj", 20);
    mesh = model.getMesh(0);
    
    
    render.setGeometryInputType(GL_TRIANGLES);
    render.setGeometryOutputType(GL_TRIANGLE_STRIP);
    render.setGeometryOutputCount(3);
    render.load("shaders/render.vert", "shaders/render.frag", "shaders/render.geom");
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    gui.setup();
    gui.add(att.setup("attenuation", 0.001f, 0.001f, 0.01f));
    gui.add(scale.setup("scale", 0, 0, 80));
    gui.add(tes.setup("outputNum", 6, 6, 40));
    gui.add(normalMode.setup("normalMaode", 0, 0, 1));
    gui.add(deformAngle.setup("deform", 100, 1, 100));
    gui.add(Draw.setup("draw()", true));
    gui.add(Wireframe.setup("drawWireframe()", false));
    gui.add(Faces.setup("drawFaces()", false));
    gui.add(Vertices.setup("drawVertices()", false));
    gui.add(uniColor.setup("vColor", ofFloatColor(1.0, 1.0, 1.0, 0.3), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    
    deformMode = 1;
    power = 1.;
}

//--------------------------------------------------------------
void ofApp::update() {
    camera.setTarget(ofVec3f(0,0,0));
    float speed = 0.03;
    if(deformMode == 0) {
        power = (0.0001 - power) * speed + power;
    }
    if(deformMode == 1) {
        power = (1. - power) * speed + power;
    }
}
//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableDepthTest();
    
    float time = ofGetElapsedTimef() * 0.5;
    
    camera.begin();
    // modelMatrix
    ofMatrix4x4 modelMatrix;
    modelMatrix.translate(0, -300, 0);
    modelMatrix.scale(0.4, 0.4, 0.4);
    //modelMatrix.rotate(ofGetElapsedTimef()*10.0,0.0,2.0,0.0);
    
    ofMatrix4x4 viewMatrix;
    viewMatrix = ofGetCurrentViewMatrix();
    
    ofMatrix4x4 projectionMatrix;
    projectionMatrix = camera.getProjectionMatrix();
    
    ofMatrix4x4 mvpMatrix;
    mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
    
    ofMatrix4x4 invMatrix = mvpMatrix.getInverse();
    
    ofMatrix4x4 mvMatrix = modelMatrix * viewMatrix;
    ofMatrix4x4 newMat = mvMatrix.getInverse();
    ofMatrix3x3 normalMat =  mat4ToMat3(newMat);
    
    normalMat.transpose();
    
    ofVec3f lightPosition = ofVec3f(80 * cos(time * 0.8), 200.0*cos(time * 0.6)/2, 80 * sin(time * 0.8));
    sphere.setPosition(lightPosition);
    sphere.setRadius(5);
    
    ofVec4f ambientColor = ofVec4f(0.1, 0.1, 0.1, 1.0);
    
    
    render.begin();
    render.setUniform4f("uniColor", uniColor);
    render.setUniformMatrix4f("modelMat", modelMatrix);
    render.setUniformMatrix4f("viewMat", viewMatrix);
    render.setUniformMatrix4f("projectionMat", projectionMatrix);
    render.setUniformMatrix4f("mvpMat", mvpMatrix);
    render.setUniformMatrix4f("invMat", invMatrix);
    render.setUniformMatrix3f("normalMat", normalMat);
    
    render.setUniform1f("time", time);
    
    render.setUniform1i("NormalMode", normalMode);
    render.setUniform1f("power", power);
    render.setUniform1i("deformAngle", deformAngle);
    render.setUniform1i("scale", scale);
    render.setUniform3f("eyePos", camera.getPosition());
    render.setUniform3f("lightPos", lightPosition);
    render.setUniform1f("lightAttenuation", att);
    render.setUniform4f("ambientCol", ambientColor);
    
    
    if(Draw){
        mesh.draw();
    } else if(Wireframe){
        mesh.drawWireframe();
    } else if(Faces){
        mesh.drawFaces();
    } else if(Vertices){
        mesh.drawVertices();
    }
    
    render.end();
    
//    cout << &camera.getTarget() << endl;
//    ofPushStyle();
//    ofSetLineWidth(0.1);
//    ofSetColor(255, 0, 0);
//    ofDrawLine(-200, 0, 0, 400, 0, 0);
//    ofSetColor(0, 255, 0);
//    ofDrawLine(0, -200, 0, 0, 400, 0);
//    ofSetColor(0, 0, 255);
//    ofDrawLine(0, 0, -200, 0, 0, 400);
//    ofPopStyle();
//
    sphere.drawFaces();
    camera.end();
    
    ofDisableDepthTest();
    gui.draw();
    
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
//    if(key=='a' && deformMode == 1) {
//        deformMode = 0;
//    }
//    if(key=='a' && deformMode == 0) {
//        deformMode = 1;
//    }
     if(key=='a') {
         if(deformMode == 1) {
             deformMode = 0;
         } else {
             deformMode = 1;
         }
     }
    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

ofMatrix3x3 ofApp::mat4ToMat3(ofMatrix4x4 mat4) {
    return ofMatrix3x3(mat4._mat[0][0], mat4._mat[0][1], mat4._mat[0][2], mat4._mat[1][0], mat4._mat[1][1], mat4._mat[1][2], mat4._mat[2][0], mat4._mat[2][1], mat4._mat[2][2]);
}
