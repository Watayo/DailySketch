//
//  Branch.cpp
//  fractalSketch01
//
//  Created by ryo.w on 2020/04/20.
//

#include "Branch.hpp"

Branch::Branch(ofPoint _parent, ofPoint _pos, ofPoint _dir) {
    parent = _parent;
    pos = _pos;
    dir = _dir;
    origDir.set(dir);
    count = 0;
    len = 5.0;
    
}

ofPoint Branch::next() {
    
    ofPoint nextPos = pos + dir * len;
    return nextPos;
}

void Branch::reset() {
    dir = origDir;
    count = 0;
}
void Branch::display() {
    ofDrawLine(pos.x, pos.y, pos.z, parent.x , parent.y, parent.z);
}

