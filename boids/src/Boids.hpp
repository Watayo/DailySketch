//
//  Boids.hpp
//  Boids
//
//  Created by ryo.w on 2020/04/21.
//

#ifndef Boids_hpp
#define Boids_hpp

#include "ofMain.h"

class Boids {
public:
    ofPoint pos;
    ofPoint velocity;
    ofPoint acceleration;
    
    Boids(){};
    //Boids(ofPoint _pos);

    void setup(ofPoint _pos);
    void applyForce(ofPoint force);
    void borders();
    void update();
    
    void flock(vector<Boids> boids);
    
    ofPoint separate(vector<Boids> others);
    ofPoint align(vector<Boids> others);
    ofPoint cohesion(vector<Boids> others);
    ofPoint seek(ofPoint target);
    
    void display();
    
    const ofPoint& getLocation() const {
        return pos;
    }
    ofMesh getMesh();
    
private:
//    ofBoxPrimitive box;
    float topSpeed;
    float speed;
    float maxForce;
    int r;
    
    int w, h, d;
    
    
};

#endif /* Boids_hpp */
