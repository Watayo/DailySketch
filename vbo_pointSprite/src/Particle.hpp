//
//  Particle.hpp
//  particle_trail
//
//  Created by ryo.w on 2020/04/16.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "ofMain.h"

class Particle {
public:
    Particle();
    ~Particle();
    
    void setup(float width, float height);
    void update(float x, float y, float z, float t);
    void accelerate();
    
    ofFloatColor color;
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    float r;
//    float lifetime;
//    bool live;
};

#endif /* Particle_hpp */
