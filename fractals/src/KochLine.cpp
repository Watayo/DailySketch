//
//  KochLine.cpp
//  Fractal
//
//  Created by ryo.w on 2020/04/19.
//

#include "KochLine.hpp"

KochLine::KochLine(ofPoint a, ofPoint b, int iteration) {
    Koch kl = Koch(a, b);
    lines.push_back(kl);
    for(int i = 0; i < iteration; i++) {
        generateLine();
    }
}


void KochLine::draw() {
    for(int i = 0; i < lines.size(); i++) {
        lines[i].display();
    }
}

void KochLine::generateLine(){
    vector<Koch> next;
    
    for(int i = 0; i < lines.size(); i++) {
        ofPoint a = lines[i].kochA();
        ofPoint b = lines[i].kochB();
        ofPoint c = lines[i].kochC();
        ofPoint d = lines[i].kochD();
        ofPoint e = lines[i].kochE();

        next.push_back( Koch(a,b));
        next.push_back( Koch(b,c));
        next.push_back( Koch(c,d));
        next.push_back( Koch(d,e));
    }
    lines = next;
}


/*
 LINE FUNCTION
 */

KochLine::Koch::Koch(ofPoint _a, ofPoint _b){
    startP = _a;
    endP = _b;
}

ofPoint KochLine::Koch::kochA(){
    return startP;
}

ofPoint KochLine::Koch::kochB(){
    ofPoint v = endP - startP;
    v /= 3;
    v += startP;
    return v;
}

ofPoint KochLine::Koch::kochC(){
    ofPoint a = startP;
    ofPoint v = endP - startP;
    v /= 3;
    a += v;
    v.rotate(-60, ofVec3f(0, 0, 1));
    a += v;
    return a;
}

ofPoint KochLine::Koch::kochD(){
    ofPoint v = endP - startP;
    v /= 3;
    v *= 2;
    v += startP;
    return v;
}

ofPoint KochLine::Koch::kochE(){
    return endP;
}

void KochLine::Koch::display() {
    ofDrawLine(startP.x, startP.y, endP.x, endP.y);
}

