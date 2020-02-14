//
//  lifegame.hpp
//  ca_lifegame
//
//  Created by ryo.w on 2020/02/12.
//

#ifndef lifegame_hpp
#define lifegame_hpp

#include "ofMain.h"

class lifegame {
public:
    lifegame();
    void init();
    void generate();
    void display();
    
    int grid;
    int columns;
    int rows;
    
    vector< vector<int> > board;
};

#endif /* lifegame_hpp */
