#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();

    openNIDevice.setUseMaskTextureAllUsers(true);
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will
      
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
    font.loadFont("verdana.ttf", 60);
    
    prev_time = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    
    int holdTime = 500;
    currTime = ofGetElapsedTimeMillis();
    if((currTime - keyTime) > holdTime && keyFlag){
        cout << "RELEASE KEY" << endl;
        CGEventRef b =  CGEventCreateKeyboardEvent(NULL, 123, 0);
        CGEventPost(kCGHIDEventTap, b);
        keyFlag = false;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    numUsers = openNIDevice.getNumTrackedUsers();
    
    for (int i = 0; i < numUsers; i++){
        
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(0);
        user.drawMask();
       
       current_time=ofGetElapsedTimef();
       left_hand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
        
       //计算每次左手拉拽的行为
       //每100微秒 计算一次prev_hand 在这100微秒中 hand-prevhand > 某个值的时候 证明拉拽动作
        dist_time=current_time-prev_time;
        if(dist_time>200) switchT = true;
        if(switchT){
            prev_time = ofGetElapsedTimef();
            prev_left_hand=left_hand; switchT=false;
        }
        
        float dist_left=ofDist(left_hand.x, left_hand.y, prev_left_hand.x, prev_left_hand.y);
        
        CGPoint point;
        point.x = left_hand.x;
        point.y = left_hand.y;
        CGWarpMouseCursorPosition(point);
        
        
        
      //判断拉拽行为
        if(dist_left>20&&dist_time<200){
            left_drag=true;
        } else { left_drag = false;}
        
        if (left_drag) {
            ofSetColor(255,0,0);
            ofCircle(20, 20, 20);
            holdKey();
            //CGEventRef a =  CGEventCreateKeyboardEvent(NULL, 123, 1);
            //CGEventPost(kCGHIDEventTap, a);
        } else {
            //CGEventRef b =  CGEventCreateKeyboardEvent(NULL, 123, 0);
            //CGEventPost(kCGHIDEventTap, b);
        }
        
       //结束计算
        
        ofSetColor(0,255,0);
        font.drawString( ofToString(left_hand.x) , 200, 200);
        font.drawString( ofToString(left_hand.y) , 200, 250);
        //font.drawString( "Prev"+ofToString(prev_left_hand) , 200, 300);
        font.drawString( ofToString(dist_left) , 200, 350);
        //cout << ofGetElapsedTimeMillis()<<endl;
        
        
        ofSetColor(255, 0, 0);
        ofCircle(left_hand.x, left_hand.y, 10);
               ofPushMatrix();
        ofTranslate(320, 240, 10);
        user.drawPointCloud();        
        ofPopMatrix();
        prev_left_hand=left_hand;
        
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
	ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
    
	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
    
    cout << ofGetElapsedTimeMillis()<<endl;
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
//    
//    CGPoint point;
//    point.x = left_hand.x;
//    point.y = left_hand.y ;
//    CGPostMouseEvent(point, 1, 1, 1);
//    CGPostMouseEvent(point, 1, 1, 0 );
    
    //CGEventCreateMouseEvent(<#CGEventSourceRef source#>, <#CGEventType mouseType#>, <#CGPoint mouseCursorPosition#>, <#CGMouseButton mouseButton#>)
    
    

    
}
//--------------------------------------------------------------
void testApp::holdKey(){
    if(!keyFlag){
        cout << "PRESS KEY" << endl;
        keyTime = ofGetElapsedTimeMillis();
        CGEventRef a =  CGEventCreateKeyboardEvent(NULL, 123, 1); //PRESS KEY
        CGEventPost(kCGHIDEventTap, a);
        keyFlag = true;
    }

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

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}