//
//  waveEquation.hpp
//  wave_equation
//
//  Created by ryo.w on 2020/04/02.
//

#ifndef waveEquation_hpp
#define waveEquation_hpp

#include "ofMain.h"

class waveEquation {
public:
    void init(int _grid_x, int _grid_y, float _point_size, float _c);
    void update();
    void draw();
    void reset();
    
    int grid_x, grid_y;
    float point_size;
    float c;
    
    float dx = 1.5;
    float dt = 0.05;
    
    int index[1000][1000];
    
    float value;
 
    ofMesh wave_mesh;
    
private:
    std::vector<float> _uminus1;
    std::vector<float> _u0;
    std::vector<float> _u1;

    
    
    
};

#endif /* waveEquation_hpp */
