#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    for(int i=0;i<myBalls.size(); i++){
        Ball tempBall = *new Ball( 10*i,10*i,ofRandom(50));
        myBalls.push_back(tempBall);
    }
}

//--------------------------------------------------------------
void testApp::update(){

    for(int i=0;i<myBalls.size();i++){
        myBalls[i].update();
    }
   
    SetCursorPos(50,50);
    

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    for(int i=0;i<myBalls.size();i++){
        myBalls[i].draw();
    }
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("a", 10,10);
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    for(int i=0;i<50;i++){
    Ball tempBall = *new Ball(x,y,5);
    myBalls.push_back(tempBall);
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

    
}



