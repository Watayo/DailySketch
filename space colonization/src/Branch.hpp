//
//  Branch.hpp
//  fractalSketch01
//
//  Created by ryo.w on 2020/04/20.
//

#ifndef Branch_hpp
#define Branch_hpp

#include "ofMain.h"
class Branch{
public:
    Branch(){};
    Branch(ofPoint _parent, ofPoint _pos, ofPoint _dir);
    ofPoint next();
    
    void display();
    void reset();

    ofPoint pos;
    ofPoint parent;
    ofPoint dir;
    int count;
    float len;
    
    
private:
    ofPoint origDir;
};


#endif /* Branch_hpp */
