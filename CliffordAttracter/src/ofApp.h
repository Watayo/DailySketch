#pragma once

#include "ofMain.h"
#include "ofxGui.h"
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
		
    
    ofxPanel gui;
    ofxFloatSlider aa;
    ofxFloatSlider bb;
    ofxFloatSlider cc;
    ofxFloatSlider dd;
//    
    ofPoint point[10000000];
    
    ofMesh VboMesh;
    int numParticle;
    
    float xn;
    float yn;
    float zn;
    
    float a, b, c, d;
  
    ofxColorSlider color;
    ofColor co;
    ofEasyCam cam;
};
