#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Particle.hpp"



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
    
    
    static const int NUM_PARTICLES = 5000;
    
    ofVbo vbo;
    ofShader shader;
    ofImage img;
    
    ofEasyCam cam;
    
    
//    float mouseX;
//    float mouseY;
    
    float centerX;
    float centerY;
    float centerZ;
    vector<Particle> particles;
    vector<ofVec3f> vertices;
    vector<ofFloatColor> colors;
    vector<ofVec3f> sizes;
    
    ofxPanel gui;
    ofxFloatSlider size;
    ofxIntSlider num;
    

    ofSpherePrimitive sphere;

};
