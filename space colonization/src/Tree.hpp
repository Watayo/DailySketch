//
//  Tree.hpp
//  fractalSketch01
//
//  Created by ryo.w on 2020/04/20.
//

#ifndef Tree_hpp
#define Tree_hpp

#include "ofMain.h"
#include "Leaf.hpp"
#include "Branch.hpp"

class Tree
{
public:
    Tree();
    void grow();
    void display();
    

private:
    vector<Leaf> leaves;
    vector<Branch> branchs;
    Branch root;
    ofPoint parent;
    ofPoint pos;
    ofPoint dir;
    
    float max_dist = 1000;
    float min_dist = 10;
    
};



#endif /* Tree_hpp */
