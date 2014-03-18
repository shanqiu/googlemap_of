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
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    for (int i = 0; i < numUsers; i++){
        
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        user.drawMask();
        
        
        
        
        left_hand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
        //计算每次左手拉拽的行为
        //每50微秒 计算一次prev_hand 在这50微秒中 hand-prevhand > 某个值的时候 证明拉拽动作
        if(left_hand.x<200&&dist_time>50){switchT=true;}
        if(switchT){prev_time = ofGetElapsedTimef();switchT=false;prev_left_hand=left_hand;}
        float dist_left=ofDist(left_hand.x, left_hand.y, prev_left_hand.x, prev_left_hand.y);
        dist_time=current_time-prev_time;
        //判断拉拽行为
        if(dist_left>100&&dist_time<50){
            bool left_drag=true;
        }
        //结束计算
        
        
        
        ofSetColor(255, 0, 0);
        ofCircle(left_hand.x, left_hand.y, 10);
//      cout << left_knee.z << endl;
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