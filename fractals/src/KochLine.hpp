//
//  KochLine.hpp
//  Fractal
//
//  Created by ryo.w on 2020/04/19.
//

#ifndef KochLine_hpp
#define KochLine_hpp

#include "ofMain.h"

class KochLine {
public:
    KochLine(){};
    KochLine(ofPoint a, ofPoint b, int iteration);
    void draw();
    void generateLine();
    
private:
    
    class Koch {
    public:
        Koch(){};
        
        Koch(ofPoint _a, ofPoint _b);
        void display();

        ofPoint kochA();
        ofPoint kochB();
        ofPoint kochC();
        ofPoint kochD();
        ofPoint kochE();

        private:

        ofPoint startP;
        ofPoint endP;
        
    };
    vector<Koch> lines;
    ofMesh mesh;
    
};

#endif /* KochLine_hpp */
