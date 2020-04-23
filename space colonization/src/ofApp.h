#pragma once

#include "ofMain.h"
#include "Tree.hpp"
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
		
    //2次元ツリーの関数
    void branch(float length);
    
    float mouseX;
    
    int generation;
    
    ofEasyCam cam;
    
    
    //呼び出すだけでコンストラクタ働くの便利やなどうなっているんだろう
    Tree tree;
    
    
};
