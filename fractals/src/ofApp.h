#pragma once

#include "ofMain.h"
#include "KochLine.hpp"
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
    
    //再帰の円
    void drawCircle(float x, float y, float radius);
    
    
    //カントール集合
    void cantor(float x, float y, float len);
    
    
    //謎の図形
    void drawDiamond(float x, float y, float size);
    
    //謎の図形2
    void myRect(float x, float y, float size, float angle);
    
    vector<KochLine> kc;
    vector<KochLine> kc2;
    vector<KochLine> kc3;
    
    ofPoint a;
    ofPoint b;
    ofPoint a2;
    ofPoint b2;
    ofPoint a3;
    ofPoint b3;
    
    ofxPanel gui;
    ofxFloatSlider radius;
    ofxIntSlider iter;
    
    
};
