//
//  Boids.cpp
//  Boids
//
//  Created by ryo.w on 2020/04/21.
//

#include "Boids.hpp"


void Boids::setup(ofPoint _pos) {
    acceleration = ofPoint(0, 0, 0);
    velocity = ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    pos = _pos;
    
    r = 2;
    maxForce = 0.05;
    topSpeed = 3;
    
    w = 200;
    h = 200;
    d = 200;
}


void Boids::applyForce(ofPoint force) {
    acceleration += force;
}


void Boids::borders() {
    if(pos.x < -w) {
        velocity.x *= -1;
        pos.x = -w + 3;
    }
    if(pos.y < -h) {
        velocity.y *= -1;
        pos.y = -h + 3;
    }
    if(pos.x > w) {
        velocity.x *= -1;
        pos.x = w - 3;
    }
    if(pos.y > h) {
        velocity.y *= -1;
        pos.y = h - 3;
    }
    if(pos.z < -d) {
        velocity.z *= -1;
        pos.z = -d + 3;
    }
    if(pos.z > d) {
        velocity.z *= -1;
        pos.z = d - 3;
    }
    
}


void Boids::update() {
    velocity += acceleration;
    velocity.limit(topSpeed);
    pos += velocity;
    acceleration *= 0;
}


void Boids::flock(vector<Boids> boids) {
    ofPoint sep = separate(boids);
    ofPoint ali = align(boids);         ofPoint coh = cohesion(boids);
    // Arbitrarily weight these forces
    sep *= 1.5;
    ali *= 1.0;
    coh *= 1.0;

    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
}


ofPoint Boids::separate(vector<Boids> others) {
    float desiredseparation = 25.0f;
    ofPoint sum;
    int count = 0;
    for (int i = 0; i < others.size(); i++) {
        ofPoint v = pos - others[i].pos;
        float d = v.length();
        
        if((d > 0) && (d < desiredseparation)) {
            ofPoint diff = v;
            diff.normalize();
            sum += diff;
            count++;
        }
        
    }
    
    if(count > 0) {
        sum /= count;
        sum.normalize();
        sum *= topSpeed;
        
        ofPoint steer = sum - velocity;
        steer.limit(maxForce);
        
        return steer;
    }
    return ofPoint(0, 0, 0);
}


ofPoint Boids::align(vector<Boids> others) {
    float neighbordist = 50;
    ofPoint sum = ofPoint(0, 0, 0);
    int count = 0;
    for(int i = 0; i < others.size(); i++) {
        ofPoint v = pos - others[i].pos;
        float d = v.length();
        if ((d > 0) && (d < neighbordist)) {
            sum += others[i].velocity;
            count++;
        }
    }
    if (count > 0) {
        sum /= (float)count;
        sum.normalize();
        sum *= topSpeed;
        ofPoint steer = sum - velocity;
        steer.limit(maxForce);
        return steer;
    } else {
        return ofPoint(0,0);
    }
    
}

ofPoint Boids::cohesion(vector<Boids> others) {
    float neighbordist = 50;
    ofPoint sum = ofPoint(0, 0, 0);
    int count = 0;
    for(int i = 0; i < others.size(); i++) {
        ofPoint v = pos - others[i].pos;
        float d = v.length();
        if((d > 0) && (d < neighbordist)) {
            sum += others[i].pos;
            count++;
        }
    }
    if(count > 0) {
        sum /= count;
        ofPoint steer = sum - velocity;
        return seek(steer);
    } else {
        return ofPoint(0, 0, 0);
    }
    
}


ofPoint Boids::seek(ofPoint target) {
    ofPoint desired = target - pos;  // A vector pointing from the location to the target
    
    // Normalize desired and scale to maximum speed
    desired.normalize();
    desired *= topSpeed;
    // Steering = Desired minus velocity
    ofPoint steer = desired - velocity;
    steer.limit(maxForce);  // Limit to maximum steering force
    
    return steer;
}


ofMesh Boids::getMesh() {
//    return box.getMesh();
}


void Boids::display() {
//    ofSetRectMode(OF_RECTMODE_CENTER);
//    ofPushMatrix();
//    ofTranslate(pos.x, pos.y, pos.z);
//    ofBox(0, 0, 0, 10, 10, 10);
//    ofPopMatrix();
}
