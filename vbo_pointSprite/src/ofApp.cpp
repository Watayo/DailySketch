#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
 
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    ofDisableArbTex();
    
    img.load("particle.png");
    img.setUseTexture(false);
    
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_TEXTURE_2D);
    
    shader.load("shaders/point.vert", "shaders/point.frag");
    
    gui.setup();
    gui.add(size.setup("size", 0.01, 0.005, 0.05));
    
    cam.setPosition(0, 0, 1000);
    
    int first_num = 1000;

    for(int i = 0; i < NUM_PARTICLES; i++) {
        particles.push_back(*new Particle());
        //      particles[i].setup(ofGetWidth(), ofGetHeight(), 60);
        //      particles[i].update(ofGetWidth() / 2, ofGetHeight() / 2, 0);
        particles[i].setup(ofGetWidth(), ofGetHeight());
        particles[i].update(0, 0, 0, 0);
    }
    
//    mouseX = ofGetWidth() / 2;
//    mouseY = ofGetHeight() / 2;
    
//    mouseX = 0;
//    mouseY = 0;
    centerX = 0;
    centerY = 0;
    centerZ = 0;
    sphere.setPosition(0, 0, 0);
    sphere.setRadius(120);
}

//--------------------------------------------------------------
void ofApp::update(){
    img.setUseTexture(true);
    
    vertices.resize(NUM_PARTICLES);
    colors.resize(NUM_PARTICLES);
    sizes.resize(NUM_PARTICLES);
    
    for(int i = 0; i < particles.size(); i++) {
        particles[i].update(centerX, centerY, centerZ, ofGetFrameNum() / 50);
        vertices[i].set(particles[i].position.x, particles[i].position.y, particles[i].position.z);
        colors[i].set(particles[i].color);
        sizes[i].set(ofNoise(particles[i].position.x), ofNoise(particles[i].position.y), ofNoise(particles[i].position.x, particles[i].position.y));
    }
    cout << sizes[40] << endl;
    
    
    vbo.setVertexData(&vertices[0], NUM_PARTICLES, GL_DYNAMIC_DRAW);
    vbo.setColorData(&colors[0], NUM_PARTICLES, GL_DYNAMIC_DRAW);
    vbo.setNormalData(&sizes[0], NUM_PARTICLES, GL_DYNAMIC_DRAW);
    
    float time = ofGetElapsedTimef() * 0.2;
    centerX = 100 * ofNoise(time) * cos(time * 1.5);
    centerY = 100 * ofNoise(time) * sin(time * 1.3);
    centerZ = 100 * ofNoise(time) * sin(time * 1.3);
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    glDepthMask(GL_FALSE);

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();
    
    shader.begin();
    cam.begin();
    shader.setUniform1f("size", size);
    
    img.getTexture().bind();
    int total = (int)particles.size();
    vbo.draw(GL_POINTS, 0, total);
    img.getTexture().unbind();
    
    cam.end();
    shader.end();
    
    ofDisablePointSprites();
    ofDisableBlendMode();
    
    ofEnableAlphaBlending();
    cam.begin();
    ofSetColor(255, 120);
    //sphere.draw();
    cam.end();
  //  ofDisableAlphaBlending();
    
    glDepthMask(GL_TRUE);
    
    
    
    
    
    

    gui.draw();
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//    mouseX = x;
//    mouseY = y;
//
//    mouseX = x - ofGetWidth()/2;
//    mouseY = -y + ofGetHeight()/2;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    for(int i = 0; i < NUM_PARTICLES; i++) {
//        particles[i].accelerate();
//    }
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
