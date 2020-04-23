//
//  Leaf.cpp
//  fractalSketch01
//
//  Created by ryo.w on 2020/04/20.
//

#include "Leaf.hpp"

Leaf::Leaf(float _radius) {
    radius = _radius;
    float theta = ofRandom(TWO_PI);
    float phi = ofRandom(TWO_PI);
    float x = radius * sin(theta) * cos(phi);
    float z = radius * sin(theta) * sin(phi);
    float y = radius * 0.6 * cos(theta) + 150;
    pos = ofPoint(x, y, z);
    reached = false;
    
}

void Leaf::display() {
    ofDrawSphere(pos.x, pos.y, pos.z, 2);
}
