#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numParticle = 64 * 64; // パーティクルの数
    ofSetFrameRate(60);
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    width = ofGetWindowWidth();
    height = ofGetWindowHeight();
    mouseFrag = false;

    // シェーダを読み込む
    updatePos.load("shaders/passthru.vert", "shaders/posUpdate.frag");
    
    updateRender.load("shaders/render.vert", "shaders/render.frag");
    
    // テクスチャのサイズをnumParticleから計算して設定
    textureRes = (int)sqrt((float)numParticle);
    numParticle = textureRes * textureRes;
    
    // パーティクルの座標、速度、加速度の保存用FBO
    // RGB32Fの形式で3つのカラーバッファを用意
    posPingPong.allocate(textureRes, textureRes, GL_RGB32F, 2);

    // パーティクルの位置の初期設定
    vector<float> pos(numParticle*3);
    for(int x = 0; x < textureRes; x++) {
        for(int y = 0; y < textureRes; y++) {
            int i = textureRes * y + x;

            pos[i*3 + 0] = ofRandom(1.0);
            pos[i*3 + 1] = ofRandom(1.0);
            pos[i*3 + 2] = ofRandom(1.0);
        }
    }
    // pingPongBufferに初期値を書き込む
    posPingPong.src->getTexture(0).loadData(pos.data(), textureRes, textureRes, GL_RGBA);

    // パーティクルの速度の初期設定
    vector<float> vel(numParticle*3);
    for(int i = 0; i < numParticle; i++) {
        vel[i*3 + 0] = ofRandom(-0.01, 0.01);
        vel[i*3 + 1] = ofRandom(-0.01, 0.01);
        vel[i*3 + 2] = ofRandom(-0.01, 0.01);
    }
    
    // pingPongBufferに初期値を書き込む
    posPingPong.src->getTexture(1).loadData(vel.data(), textureRes, textureRes, GL_RGBA);
    

    // renderFBOを初期化
    renderFBO.allocate(width, height, GL_RGB32F);
    renderFBO.begin();
    ofClear(0, 0, 0, 255);
    renderFBO.end();

    // VBOMeshの初期設定
    mesh.setMode(OF_PRIMITIVE_POINTS);
    for(int x = 0; x < textureRes; x++) {
        for(int y = 0; y < textureRes; y++) {
            int i = y * textureRes + x;
            mesh.addVertex(ofVec3f(x, y));
            mesh.addTexCoord(ofVec2f(x, y));
        }
    }
    
    // GUI
    gui.setup();
    gui.setPosition(20, 20);
    gui.add(separationDistance.set("separationDistance",0.01, 0.01, 0.1));
    gui.add(alignmentDistance.set("alignmentDistance", 0.01, 0.01, 0.1));
    gui.add(cohesionDistance.set("cohesionDistance", 0.01, 0.01, 0.1));
    gui.add(maxSpeed.set("maxSpeed", 0.005, 0.005, 1));
    gui.add(maxForce.set("maxForce", 0.01, 0.005, 0.1));
    
    glPointSize(2.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.01;
    
    // Position PingPong
    posPingPong.dst->begin();
    ofClear(0);
    updatePos.begin();
    updatePos.setUniformTexture("posData", posPingPong.src->getTexture(0), 0); // 位置のテクスチャ
    updatePos.setUniformTexture("velData", posPingPong.src->getTexture(1), 1); // 速度のテクスチャ
    updatePos.setUniform2f("mouse", m);
    updatePos.setUniform2f("resolution", posPingPong.src->getWidth(), posPingPong.src->getHeight() ); // resolution
    updatePos.setUniform3f("screen", width, height, width);
    
    updatePos.setUniform1f("separationDistance", separationDistance);
    updatePos.setUniform1f("alignmentDistance", alignmentDistance);
    updatePos.setUniform1f("cohesionDistance", cohesionDistance);
    updatePos.setUniform1f("speed", maxSpeed);
    updatePos.setUniform1f("force", maxForce);
    
    posPingPong.src->draw(0, 0);
    updatePos.end();
    posPingPong.dst->end();

    // srcとdstを入れ替え
    posPingPong.swap();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    cam.begin();
    
    ofBackground(0);
    
    updateRender.begin();
    updateRender.setUniformTexture("posTex", posPingPong.dst->getTexture(), 0);
    updateRender.setUniform1i("resolution", (float)textureRes);
    updateRender.setUniform2f("screen", (float)width, (float)height);
    updateRender.setUniform1f("time", time);

    mesh.draw(OF_MESH_WIREFRAME);

    updateRender.end();
    
    cam.end();
    
    ofDisableBlendMode();
    ofDisableDepthTest();
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
    m.x = x;
    m.y = ofGetHeight() - y;

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
