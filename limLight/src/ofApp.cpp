#include "ofApp.h"

glm::vec3 getLightDirection(DirectionalLight& l) {
    return glm::normalize(l.direction * -1.0f);
}

glm::vec3 getLightColor(DirectionalLight& l) {
    return l.color * l.intensity;
}


//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    ofDisableArbTex();
    ofEnableDepthTest();

//    mesh.load("torus.ply");
    model.loadModel("Alucy.obj");
    mesh = model.getMesh(0);
    
    diffuseShader.load("shader");

}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    
    using namespace glm;
    DirectionalLight dirLight;
    float time = ofGetElapsedTimef() * 0.5;
    
    cam.pos = vec3(0, 20.0f, 15.0f);
    cam.fov = radians(60.0f);

    float cAngle = radians(0.0f);
    vec3 right = vec3(0, 1, 0);
    mat4 view = inverse(translate(cam.pos));
    mat4 model = rotate(time, right) * scale(vec3(0.03, 0.03, 0.03));
    mat3 normalMatrix = (transpose(inverse(mat3(model))));

    float aspect = 1024.0f / 768.0f;
    mat4 proj = perspective(cam.fov, aspect, 0.1f, 110.0f);
    mat4 mvp = proj * view * model;

    dirLight.direction = normalize(vec3(-1, 0, 1));
    dirLight.color = vec3(1, 1, 1);
    dirLight.intensity = 1.0f;

    diffuseShader.begin();
    
    diffuseShader.setUniformMatrix4f("model", model);
    diffuseShader.setUniformMatrix4f("mvp", mvp);
    diffuseShader.setUniform3f("meshCol", glm::vec3(1, 0.4, 0.8));
    diffuseShader.setUniform3f("lightDir", getLightDirection(dirLight));
    diffuseShader.setUniform3f("lightCol", getLightColor(dirLight));
    diffuseShader.setUniform3f("cameraPos", cam.pos);
    diffuseShader.setUniformMatrix3f("normal", normalMatrix);
    mesh.draw();
    diffuseShader.end();
    

}




//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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

