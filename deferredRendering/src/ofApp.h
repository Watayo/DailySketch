#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "pointLight.h"

#define NUM 400
#define LightNUM 100
#define KarnelSample 64

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void setupScreenQuad();
        void drawScreenQuad();
    
    float lerp(float a, float b, float f) {
        // start a
        // end b
        // f => 0 ~ 1
        return a + f * (b - a);
    }
    
    const int width = ofGetWidth();
    const int height = ofGetHeight();
    
    ofBoxPrimitive box;
    ofConePrimitive cone;
    
    ofVec3f pos[NUM];
    PointLight pointlight[LightNUM];
    ofEasyCam cam;
    ofShader GeometryPass, LightingPass, SSAOPass, SSAOBlurPass;
    
    GLuint gBuffer;
    GLuint gPosition, gNormal, gAlbedo, gDepth;
    GLuint ssaoColorBuffer, ssaoColorBufferBlur;
    GLuint noiseTexture;
    GLuint ssaoFbo, ssaoBlurFBO;
    
    ofVec3f ssaoKernel[KarnelSample];
    
    ofTexture texture, normal;
    
    ofMesh quad;
//    int DebugMode;
    
    ofxPanel gui;
    ofxIntSlider DebugMode;
    
    
		
};
