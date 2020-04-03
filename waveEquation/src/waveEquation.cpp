//
//  waveEquation.cpp
//  wave_equation
//
//  Created by ryo.w on 2020/04/02.
//

#include "waveEquation.hpp"

void waveEquation::init(int _grid_x, int _grid_y, float _point_size, float _c) {
    grid_x = _grid_x;
    grid_y = _grid_y;
    point_size = _point_size;
    c = _c;
    

    glPointSize(point_size);
    wave_mesh.setMode(OF_PRIMITIVE_POINTS);

    _u0.resize(grid_x * grid_y);
    _u1.resize(grid_x * grid_y);
    _uminus1.resize(grid_x * grid_y);
    
    for (int y = 0; y < grid_y; ++y) {
        for (int x = 0; x < grid_x; ++x) {
            index[x][y] = grid_x * y + x;
            wave_mesh.addVertex(ofVec3f(x, y, value));
            wave_mesh.addIndex(index[x][y]);
        }
    }
}

void waveEquation::reset() {
    auto gauss = [](float x, float sigma) {
        return 1.0f / glm::sqrt(glm::two_pi<float>()) * sigma * glm::exp(-x * x / (2.0f * sigma * sigma));
    };
//    int cx1 = grid_x / 3;
//    int cy1 = grid_y / 3;
//    int cx2 = grid_x * 2 / 3;
//    int cy2 = grid_y * 2 / 3;
//
    int half_x = grid_x / 2;
    int half_y = grid_y / 2;
    int a = 3;
    for (int y = -a; y < a; y++) {
        for (int x = -a; x < a; x++) {
            float norm = 1.0;
//            value += gauss(norm, 3.0f) * 20.0f;
//
            _u0[index[x + half_x][y + half_y]] = 10;
            
        }
        
        
    }

    _uminus1 = _u1 = _u0;
    
    
}

void waveEquation::update() {
    float mul = dt * dt * c * c / (dx * dx);
    
    for (int y = 1; y < grid_y - 1; y++) {
        for (int x = 1; x < grid_x - 1; x++) {
            
            float uminus1 = _uminus1[index[x][y]];
            float u0 = _u0[index[x][y]];
            
            float uL = _u0[index[x-1][y]];
            float uR = _u0[index[x+1][y]];
            float uT = _u0[index[x][y-1]];
            float uB = _u0[index[x][y+1]];
            
            float u1 =  u0 + u0 - uminus1 + mul *  (-4.0f * u0 + uL + uR + uT + uB);
            
            _u1[index[x][y]] = u1;
        }
    }
    
    std::swap(_uminus1, _u0);
    std::swap(_u0, _u1);
    
    for (int y = 1; y < grid_y - 1; ++y) {
        for (int x = 1; x < grid_x - 1; ++x) {
            wave_mesh.setVertex(index[x][y], ofVec3f(x, y, _u1[index[x][y]]));
        }
    }
}


void waveEquation::draw() {
    
    ofPushMatrix();
    ofTranslate(-grid_x/2, -grid_y/2);
    wave_mesh.draw();
    ofPopMatrix();
}
