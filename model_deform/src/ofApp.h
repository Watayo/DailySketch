#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

struct CameraData
{
    glm::vec3 pos;
    float fov;
};

struct DirectionalLight {
    glm::vec3 direction;
    glm::vec3 color;
    float intensity;
};


class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofMatrix3x3 mat4ToMat3(ofMatrix4x4 mat4);

    ofShader render;
    ofShader diffuseShader;
    
    ofVboMesh mesh;
    ofxAssimpModelLoader model;
    
    ofSpherePrimitive sphere;
    
    ofEasyCam camera;
    
    int deformMode;
    float power;
    
    ofxPanel gui;
    ofxFloatSlider att;
    ofxIntSlider scale;
    ofxIntSlider tes;
    ofxIntSlider deformAngle;
    ofxIntSlider normalMode;
    ofxToggle Draw;
    ofxToggle Wireframe;
    ofxToggle Faces;
    ofxToggle Vertices;
    ofxFloatColorSlider uniColor;
    
};

