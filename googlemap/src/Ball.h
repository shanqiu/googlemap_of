//
//  Ball.h
//  empty
//
//  Created by Tong Wen on 3/4/14.
//
//

#pragma once
#include "ofMain.h"

class Ball{
    
public:
    Ball(int x, int y, int _size);
    void update();
    void draw();
    void addForce(float x, float y);
    int size;
    float forceX;
    float forceY;
    
    ofPoint pos;
    ofColor color;
    
private:
    
};