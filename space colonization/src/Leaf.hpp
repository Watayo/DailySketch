//
//  Leaf.hpp
//  fractalSketch01
//
//  Created by ryo.w on 2020/04/20.
//

#ifndef Leaf_hpp
#define Leaf_hpp

#include "ofMain.h"

class Leaf {
public:
    Leaf(){};
    Leaf(float _radius);
    void display();
    
    ofPoint pos;
    bool reached;
    
private:
    float radius;
};

#endif /* Leaf_hpp */
