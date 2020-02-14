//
//  RealLife.cpp
//  ca_lifegame
//
//  Created by ryo.w on 2020/02/12.
//

#include "RealLife.hpp"

RealLife::RealLife() {
    grid = 3;
    columns = ofGetWidth()/grid;
    rows = ofGetHeight()/grid;
    
    board.resize(columns, std::vector<float>(rows));
    
    init();
}

float RealLife::inc(float F, float x) {
    return x/F;
}

float RealLife::dec(float F, float x) {
    return x/F + (F-1)/F;
}

void RealLife::init() {
    for (int i = 1; i < columns-1; i++) {
        for(int j = 1; j < rows-1; j++) {
            board[i][j] = ofRandom(2);
        }
    }
}
void RealLife::generate(float _Tl, float _Th, float _F) {
    float Tl = _Tl;
    float Th = _Th;
    float F = _F;
    //次のフレームのvector * vector　を用意。
    vector< vector<float> > next(columns, std::vector<float>(rows));
    for( int x = 1; x < columns-1; x++) {
        for (int y = 1; y < rows-1; y++) {
            int neighbors = 0;
            
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <=1; j++) {
                    neighbors += board[x+i][y+j];
                }
            }
            
            neighbors -= board[x][y];
            
            if((Tl <= neighbors) && (neighbors <= Th)) {
                next[x][y] = inc(F, board[x][y]);
            } else {
                next[x][y] = dec(F, board[x][y]);
            }
        }
    }
    board = next;
}

void RealLife::display() {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            ofFill();
            
            ofSetColor(0, 0, 0, board[i][j]*255);
            
            
            ofDrawCircle(i*grid, j*grid, 1.5);
        }
    }
}
