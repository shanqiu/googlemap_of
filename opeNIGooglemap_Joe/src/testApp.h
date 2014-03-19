#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"

class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    
    void holdKey();

    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
    
    ofTrueTypeFont verdana;
    ofTrueTypeFont  font;
    
    ofVec3f left_hand, prev_left_hand;
    
    float current_time, prev_time, dist_time;
    
    bool switchT=false;
    
    bool left_drag;
    
    int numUsers;
    
    int currTime;
    int keyTime; //moment we pressed key
    bool keyFlag;
};

#endif
