//
//  lifegame.cpp
//  ca_lifegame
//
//  Created by ryo.w on 2020/02/12.
//

#include "lifegame.hpp"

lifegame::lifegame() {
    grid = 3;
    columns = ofGetWidth()/grid;
    rows = ofGetHeight()/grid;
    
    board.resize(columns, std::vector<int>(rows));
    
    init();
}

void lifegame::init() {
    for (int i = 1; i < columns-1; i++) {
        for(int j = 1; j < rows-1; j++) {
            board[i][j] = int(ofRandom(2));
        }
    }
}

void lifegame::generate() {
    vector< vector<int> > next(columns, std::vector<int>(rows));
    
    for( int x = 1; x < columns-1; x++) {
        for (int y = 1; y < rows-1; y++) {
            int neighbors = 0;
            
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <=1; j++) {
                    neighbors += board[x+i][y+j];
                }
            }
            
            neighbors -= board[x][y];
            
            if ((board[x][y] == 1) && (neighbors < 2)) {
                next[x][y] = 0;
            } else if ((board[x][y] == 1) && (neighbors > 3)) {
                next[x][y] = 0;
            } else if ((board[x][y] == 0) && (neighbors == 3)) {
                next[x][y] = 1;
            } else {
                next[x][y] = board[x][y];
            }
            
        }
    }
    board = next;
}

void lifegame::display() {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            ofFill();
            
            if (board[i][j] == 1) {
                ofSetColor(0);
            } else {
                ofSetColor(255);
            }
            
            
            ofDrawRectangle(i*grid, j*grid, grid, grid);
        }
    }
}
