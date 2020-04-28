//
//  Flock.hpp
//  boids01
//
//  Created by ryo.w on 2020/04/21.
//

#ifndef Flock_hpp
#define Flock_hpp

#include "ofMain.h"
#include "Boids.hpp"

class Flock {
public:
    vector<Boids> boids;
    void setup();
    void update();
    void draw();
    void addBoid(ofPoint _newPos);
    
    vector<ofPoint> getPos();
    vector<ofPoint> positions;
    
private:
//    ofMesh* m;
    //ofPoint newPos;
};

#endif /* Flock_hpp */
