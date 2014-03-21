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
    
    int holdTime = 300;
    currTime = ofGetElapsedTimeMillis();
    
    if((currTime - keyTime) > holdTime && leftKeyFlag){
        cout << "RELEASE LEFT KEY" << endl;
        CGEventRef b =  CGEventCreateKeyboardEvent(NULL, 123, 0);
        CGEventPost(kCGHIDEventTap, b);
        leftKeyFlag = false;
    }
    
    if((currTime - keyTime) > holdTime && rightKeyFlag){
        cout << "RELEASE RIGHT KEY" << endl;
        CGEventRef f =  CGEventCreateKeyboardEvent(NULL, 124, 0);
        CGEventPost(kCGHIDEventTap, f);
        rightKeyFlag = false;
    }
    
    if((currTime - keyTime) > holdTime && upKeyFlag){
        cout << "RELEASE UP KEY" << endl;
        CGEventRef d =  CGEventCreateKeyboardEvent(NULL, 126, 0);
        CGEventPost(kCGHIDEventTap, d);
        upKeyFlag = false;
 
    }
    
    if (upKeyFlag == 1) {
        leftByRun = 1;
        rightByRun = 1;
    } else {
        leftByRun = 0;
        rightByRun = 0;}
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
       right_hand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
       left_foot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        
       //计算每次左手拉拽的行为
       //每100微秒 计算一次prev_hand 在这100微秒中 hand-prevhand > 某个值的时候 证明拉拽动作
        dist_time=current_time-prev_time;
        if(dist_time>200) switchT = true;
        if(switchT){
            prev_time = ofGetElapsedTimef();
            prev_left_hand = left_hand;
            prev_right_hand = right_hand;
            prev_left_foot = left_foot;
            switchT=false;
        }
        
        float dist_left_hand=ofDist(left_hand.x, left_hand.y, prev_left_hand.x, prev_left_hand.y);
        float dist_right_hand=ofDist(right_hand.x, right_hand.y, prev_right_hand.x, prev_right_hand.y);
        float dist_left_foot=ofDist(left_foot.x, left_foot.y, prev_left_foot.x, prev_left_foot.y);
        
        CGPoint point;
        point.x = left_hand.x;
        point.y = left_hand.y;
        CGWarpMouseCursorPosition(point);
        
        
        
      //判断左手
        if(dist_left_hand>20&&dist_time<200){
            left_drag=true;
        } else { left_drag = false;}
        
        if (left_drag && leftByRun == 0) {
            ofSetColor(255,0,0);
            ofCircle(20, 20, 20);
            holdLeftKey();
            //CGEventRef a =  CGEventCreateKeyboardEvent(NULL, 123, 1);
            //CGEventPost(kCGHIDEventTap, a);
        } //else {
            //CGEventRef b =  CGEventCreateKeyboardEvent(NULL, 123, 0);
            //CGEventPost(kCGHIDEventTap, b);
        //}
        
        
        //判断右手
        if(dist_right_hand>20 && dist_time<200){
            right_drag=true;
        } else { right_drag = false;}
        
        if (right_drag && rightByRun == 0) {
            ofSetColor(255,0,0);
            ofCircle(50, 20, 20);
            holdRightKey();
            //CGEventRef a =  CGEventCreateKeyboardEvent(NULL, 123, 1);
            //CGEventPost(kCGHIDEventTap, a);
        }
        
        //判断跑步
        if(dist_left_foot>10 && dist_time<200){
            running=true;
        } else { running = false;}
        
        if (running) {
            ofSetColor(255);
            ofCircle(20, 50, 20);
            holdUpKey();
            //CGEventRef a =  CGEventCreateKeyboardEvent(NULL, 123, 1);
            //CGEventPost(kCGHIDEventTap, a);
        }
        
        ofSetColor(0,255,0);
        font.drawString( ofToString(left_hand.x) , 200, 200);
        font.drawString( ofToString(left_hand.y) , 200, 250);
        //font.drawString( "Prev"+ofToString(prev_left_hand) , 200, 300);
        font.drawString( "dist_left_hand"+ofToString(dist_left_hand) , 200, 350);
        font.drawString( "dist_right_hand"+ofToString(dist_right_hand) , 200, 400);
        font.drawString( "dist_left_foot"+ofToString(dist_left_foot) , 200, 450);
        
        //cout << ofGetElapsedTimeMillis()<<endl;
        
        
        ofSetColor(255, 0, 0);
        ofCircle(left_hand.x, left_hand.y, 10);
               ofPushMatrix();
        ofTranslate(320, 240, 10);
        user.drawPointCloud();        
        ofPopMatrix();
        prev_left_hand = left_hand;
        prev_left_foot = left_foot;
        prev_right_hand = right_hand;
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
	//ofSetColor(0, 255, 0);
	//string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
	//verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
    
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
void testApp::holdLeftKey(){
    if(!leftKeyFlag){
        cout << "PRESS LEFT KEY" << endl;
        keyTime = ofGetElapsedTimeMillis();
        CGEventRef a =  CGEventCreateKeyboardEvent(NULL, 123, 1); //PRESS LEFT KEY
        CGEventPost(kCGHIDEventTap, a);
        leftKeyFlag = true;
    }
}

//--------------------------------------------------------------
void testApp::holdRightKey(){
    if(!rightKeyFlag){
        cout << "PRESS RIGHT KEY" << endl;
        keyTime = ofGetElapsedTimeMillis();
        CGEventRef e =  CGEventCreateKeyboardEvent(NULL, 124, 1); //PRESS UP KEY
        CGEventPost(kCGHIDEventTap, e);
        rightKeyFlag = true;
    }
}

//--------------------------------------------------------------
void testApp::holdUpKey(){
    if(!upKeyFlag){
        cout << "PRESS UP KEY" << endl;
        keyTime = ofGetElapsedTimeMillis();
        CGEventRef c =  CGEventCreateKeyboardEvent(NULL, 126, 1); //PRESS UP KEY
        CGEventPost(kCGHIDEventTap, c);
        upKeyFlag = true;
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