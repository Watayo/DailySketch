//
//  Tree.cpp
//  fractalSketch01
//
//  Created by ryo.w on 2020/04/20.
//

#include "Tree.hpp"

Tree::Tree()
{
    for(int i = 0; i < 300; i++) {
        leaves.push_back(*new Leaf(150));
    }
    
    parent = ofPoint(0, 0, 0);
    pos = ofPoint(0, 0, 0);
    dir = ofPoint(0, 1, 0);
    root = Branch(parent, pos, dir);
    
    branchs.push_back(root);
    
    Branch current = root;
    
    bool found = false;
    
    while(!found) {
        for (int i = 0; i < leaves.size(); i++) {
            ofVec3f v = current.pos - leaves[i].pos;
            float d = v.length();
            if(d < max_dist) {
                found = true;
            }
        }
        if(!found) {
            parent = pos;
            pos = current.next();
            current = Branch(parent, pos, dir);
            branchs.push_back(current);
        }
    }
    
}

void Tree::grow() {
    for (int i = 0; i < leaves.size(); i++) {
        auto leaf = leaves[i];
        auto closestIndex = -1;
        float record = 10000;
        for(int j = 0; j < branchs.size(); j++) {
            auto branch = branchs[j];
            ofVec3f v = leaf.pos - branch.pos;
            float d = v.length();
            if(d < min_dist) {
                leaf.reached = true;
                closestIndex = -1;
                break;
            } else if (d > max_dist) {
                break;
            } else if((closestIndex < 0) || (d < record)) {
                closestIndex = j;
                record = d;
            }
        }
        
        if((closestIndex >= 0) && !leaf.reached) {
            ofPoint newDir = leaf.pos - branchs[closestIndex].pos;
            newDir.normalize();
            branchs[closestIndex].dir += newDir;
            branchs[closestIndex].count++;
        }
        
        if(leaf.reached) {
            leaves.erase(leaves.begin() + i);
        }
    }
    
    for (int i = branchs.size() - 1; i >= 0; i--) {
        auto branch = branchs[i];
        if(branch.count > 0) {
            branch.dir /= branch.count;
            auto newBranch = Branch(branch.pos, branch.next(), branch.dir);
            branchs.push_back(newBranch);
        }
        branch.reset();
    }
}

void Tree::display() {
    for (int i = 0; i < leaves.size(); i++) {
        leaves[i].display();
    }
    for (int i = 0; i < branchs.size(); i++) {
        branchs[i].display();
    }
}

