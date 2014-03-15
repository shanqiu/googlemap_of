//
//  Ball.cpp
//  empty
//
//  Created by Tong Wen on 3/4/14.
//
//

#include "Ball.h"

Ball::Ball(int x, int y, int _size){
    pos.x= x;
    pos.y=y;
    
    forceX=ofRandom(5);
    forceY=ofRandom(5);
    size=_size;
    
   
d
}
//------------------------------------
void Ball::update(){
    color.r = ofMap(pos.x, 0, ofGetWidth(), 0, 255);
    color.g = ofMap(pos.x, 0, ofGetHeight(), 0, 255);
    color.b = ofMap(pos.x, 0, ofGetWidth(), 0, 255);
    
    color.a=ofMap(forceX, 0, 5, 0, 255);
    forceX-=0.02;
    forceY-=0.02;
    
    if(forceX<0.2)forceX=0;
    if(forceY<0.2)forceY=0;
    pos.x += forceX;
    pos.y +=forceY;

}
//-----------------------
void Ball::draw(){
    ofSetColor(color);
    ofCircle(pos,size);
}
//---------------------------------
void Ball::addForce(float x, float y){

    forceX +=x;
    forceY +=y;
}