//
//  Flock.cpp
//  boids01
//
//  Created by ryo.w on 2020/04/21.
//

#include "Flock.hpp"

void Flock::setup() {
    boids.resize(100);
    float radius = 100;

    for (auto & b: boids){
        float theta = ofRandom(TWO_PI);
        float phi = ofRandom(TWO_PI);
        float x = radius * sin(theta) * cos(phi);
        float z = radius * sin(theta) * sin(phi);
        float y = radius * cos(theta);
        ofPoint pos = ofPoint(x, y, z);
        b.setup(pos);
    }
}

void Flock::update(){
    for (auto & b: boids){
        b.flock(boids);
        b.update();
        b.borders();
    }
}

void Flock::draw(){
//    for (auto & b: boids){
//        b.display();
//    }
}

vector<ofPoint> Flock::getPos() {
    positions.clear();
    for (auto & b: boids){
        positions.push_back(b.pos);
    }
    return positions;
    
}

void Flock::addBoid(ofPoint _newPos){
    Boids v;
    v.setup(_newPos);
    boids.push_back(v);
}
