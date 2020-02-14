//
//  RealLife.hpp
//  ca_lifegame
//
//  Created by ryo.w on 2020/02/12.
//

#ifndef RealLife_hpp
#define RealLife_hpp

#include "ofMain.h"

class RealLife {
public:
    RealLife();
    void init();
    void generate(float _Tl, float _Th, float _F);
    void display();

    int grid;
    int columns;
    int rows;
    
    vector< vector<float> > board;

    float Tl, Th;
    
    float F;
    
    float inc(float F, float x);
    
    float dec(float F, float x);
    
    
    
};

#endif /* RealLife_hpp */
