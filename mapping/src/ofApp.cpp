#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   // ofBackground(0);
    ofSetVerticalSync(true);
    
    
    mapShader.load("shader/mapping.vert", "shader/mapping.frag");
    
    string imgName[] = {
        "cube/cube_PX.png",
        "cube/cube_NX.png",
        "cube/cube_PY.png",
        "cube/cube_NY.png",
        "cube/cube_PZ.png",
        "cube/cube_NZ.png"
    };
    
    //Box = ofBoxPrimitive(100, 100, 100).getMesh();
    
    cubeTexture = loadCubeMap(imgName);
    createMesh();
    
    cam.setGlobalPosition(0, 0, 400.0);
       
    renderFbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    
    cam.begin();
    // model Matrix
    ofMatrix4x4 modelMatrix;
    modelMatrix.translate(0, 0, 0);
    modelMatrix.rotate(ofGetElapsedTimef()*10.0,0.0,2.0,0.0);
    
    // view Matrix
    ofMatrix4x4 viewMatrix;
    viewMatrix = ofGetCurrentViewMatrix();
    
    // projection Matrix
    ofMatrix4x4 projectionMatrix;
    projectionMatrix = cam.getProjectionMatrix();
    
    // model view projection Matrix
    ofMatrix4x4 mvpMatrix;
    mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
    
    ofMatrix4x4 invMatrix = mvpMatrix.getInverse();
    ofMatrix4x4 vpMatrix = viewMatrix * projectionMatrix;
    
    mapShader.begin();
    mapShader.setUniform3f("eyePosition", cam.getPosition());
    mapShader.setUniform1i("cubeTexture", 0);
    mapShader.setUniformMatrix4f("modelViewProjectionMatrix", mvpMatrix);
    mapShader.setUniformMatrix4f("invMatrix", invMatrix);
    mapShader.setUniform1f("time", ofGetElapsedTimef());
    
    // 図形の描写
    for (int i = 0; i < N; i++) {
        box[i].set(4 * i + 5, 7, 7);
        box[i].setPosition(i + (4 * i + 5) / 2, 3.0 * i, 0);
        ofPushMatrix();
        ofRotateZ(i * 0.5);
        ofRotateY(i*5);
        box[i].draw();
        ofPopMatrix();
    }
    for (int i = N; i >= 0; i--) {
        box[i+N-1].set(4 * i + 5, 7, 7);
        box[i+N-1].setPosition(i + (4 * i + 5) / 2, 3.0 * (2 * (N - 1) - i), 0);
        ofPushMatrix();
        ofRotateZ(i * 0.5);
        ofRotateY(-i*5);
        box[i+N-1].draw();
        ofPopMatrix();
    }
    
    mapShader.end();
    for(int i=0; i<6; i++) {
        image[i].bind();
        boxFaces[i].draw(OF_MESH_FILL);
        image[i].unbind();
    }
    cam.end();
    
    ofDisableBlendMode();
    
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
// ---------------------------------------------
unsigned int ofApp::loadCubeMap(string name[]) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    ofImage image[6];
    for(int i=0; i<6; i++) {
        image[i].load(name[i]);
        this->image[i] = image[i];
    }

    unsigned char *pixels;
    for(int i=0; i<6; i++){
        pixels = image[i].getPixels().getData();
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGBA,image[i].getWidth(),image[i].getHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void ofApp::createMesh() {
    // right Face
    int w = this->width*10;
    boxFaces[0].addVertex(ofVec3f(w,-w,w));
    boxFaces[0].addTexCoord(ofVec2f(0,width));
    boxFaces[0].addVertex(ofVec3f(w,-w,-w));
    boxFaces[0].addTexCoord(ofVec2f(width,width));
    boxFaces[0].addVertex(ofVec3f(w,w,-w));
    boxFaces[0].addTexCoord(ofVec2f(width,0));
    boxFaces[0].addVertex(ofVec3f(w,w,w));
    boxFaces[0].addTexCoord(ofVec2f(0,0));

    // left Face
    boxFaces[1].addVertex(ofVec3f(-w,-w,w));
    boxFaces[1].addTexCoord(ofVec2f(width,width));
    boxFaces[1].addVertex(ofVec3f(-w,w,w));
    boxFaces[1].addTexCoord(ofVec2f(width,0));
    boxFaces[1].addVertex(ofVec3f(-w,w,-w));
    boxFaces[1].addTexCoord(ofVec2f(0,0));
    boxFaces[1].addVertex(ofVec3f(-w,-w,-w));
    boxFaces[1].addTexCoord(ofVec2f(0,width));

    // top Face
    boxFaces[2].addVertex(ofVec3f(w,w,w));
    boxFaces[2].addTexCoord(ofVec2f(width,width));
    boxFaces[2].addVertex(ofVec3f(w,w,-w));
    boxFaces[2].addTexCoord(ofVec2f(width,0));
    boxFaces[2].addVertex(ofVec3f(-w,w,-w));
    boxFaces[2].addTexCoord(ofVec2f(0,0));
    boxFaces[2].addVertex(ofVec3f(-w,w,w));
    boxFaces[2].addTexCoord(ofVec2f(0,width));

    // bottom Face
    boxFaces[3].addVertex(ofVec3f(-w,-w,w));
    boxFaces[3].addTexCoord(ofVec2f(0,0));
    boxFaces[3].addVertex(ofVec3f(-w,-w,-w));
    boxFaces[3].addTexCoord(ofVec2f(0,width));
    boxFaces[3].addVertex(ofVec3f(w,-w,-w));
    boxFaces[3].addTexCoord(ofVec2f(width,width));
    boxFaces[3].addVertex(ofVec3f(w,-w,w));
    boxFaces[3].addTexCoord(ofVec2f(width,0));

    // front Face
    boxFaces[4].addVertex(ofVec3f(w,w,w));
    boxFaces[4].addTexCoord(ofVec2f(width,0));
    boxFaces[4].addVertex(ofVec3f(-w,w,w));
    boxFaces[4].addTexCoord(ofVec2f(0,0));
    boxFaces[4].addVertex(ofVec3f(-w,-w,w));
    boxFaces[4].addTexCoord(ofVec2f(0,width));
    boxFaces[4].addVertex(ofVec3f(w,-w,w));
    boxFaces[4].addTexCoord(ofVec2f(width,width));

    // backFace
    boxFaces[5].addVertex(ofVec3f(-w,-w,-w));
    boxFaces[5].addTexCoord(ofVec2f(width,width));
    boxFaces[5].addVertex(ofVec3f(-w,w,-w));
    boxFaces[5].addTexCoord(ofVec2f(width,0));
    boxFaces[5].addVertex(ofVec3f(w,w,-w));
    boxFaces[5].addTexCoord(ofVec2f(0,0));
    boxFaces[5].addVertex(ofVec3f(w,-w,-w));
    boxFaces[5].addTexCoord(ofVec2f(0,width));

    for(int i=0; i<6; i++) {
        boxFaces[i].setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    }
}
