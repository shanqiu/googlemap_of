

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	ofBackground(255,255,255);
    
    buttonState = "digital pin:";
    potValue = "analog pin:";
    
	font.loadFont("franklinGothic.otf", 20);
    smallFont.loadFont("franklinGothic.otf", 14);
    
	ard.connect("/dev/tty.usbmodem1421", 57600);
	
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;	
}

//--------------------------------------------------------------
void testApp::update(){

	updateArduino();

}

//--------------------------------------------------------------
void testApp::setupArduino(const int & version) {
	

	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    bSetupArduino = true;

    //ard.sendAnalogPinReporting(0, ARD_ANALOG);
    
	ard.sendDigitalPinMode(13, ARD_OUTPUT);
    ard.sendDigitalPinMode(6, ARD_OUTPUT);
    ard.sendDigitalPinMode(7, ARD_OUTPUT);
    ard.sendDigitalPinMode(8, ARD_OUTPUT);
    ard.sendDigitalPinMode(9, ARD_OUTPUT);

    // set pin D11 as PWM (analog output)
	ard.sendDigitalPinMode(11, ARD_PWM);

    ofAddListener(ard.EDigitalPinChanged, this, &testApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);    
}

//--------------------------------------------------------------
void testApp::updateArduino(){

    ard.update();
	if (bSetupArduino) {
		ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
	}

}
void testApp::digitalPinChanged(const int & pinNum) {
       buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
}

void testApp::analogPinChanged(const int & pinNum) {
       potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
}


//--------------------------------------------------------------
void testApp::draw(){
	
    
    //ofEnableAlphaBlending();
    
    ofSetColor(255, 120, 120);
	if (!bSetupArduino){
		font.drawString("arduino not ready...\n", 515, 40);
	} else {
		font.drawString(potValue + "\n" + buttonState +
						"\nsending pwm: " + ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 515, 40);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch (key) {
        case OF_KEY_RIGHT:
            ard.sendDigital(6, ARD_HIGH);
            ard.sendDigital(7, ARD_LOW);
            ard.sendDigital(8, ARD_LOW);
            ard.sendDigital(9, ARD_LOW);
     
            break;
        case OF_KEY_LEFT:
            // rotate servo head to 0 degrees
            ard.sendDigital(6, ARD_LOW);
            ard.sendDigital(7, ARD_HIGH);
            ard.sendDigital(8, ARD_LOW);
            ard.sendDigital(9, ARD_LOW);
            break;
        case OF_KEY_UP:
            ard.sendDigital(6, ARD_LOW);
            ard.sendDigital(7, ARD_LOW);
            ard.sendDigital(8, ARD_HIGH);
            ard.sendDigital(9, ARD_LOW);
        case OF_KEY_UP:
            ard.sendDigital(6, ARD_LOW);
            ard.sendDigital(7, ARD_LOW);
            ard.sendDigital(8, ARD_LOW);
            ard.sendDigital(9, ARD_HIGH);
        default:
            break;
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
    ard.sendDigital(13, ARD_HIGH);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	ard.sendDigital(13, ARD_LOW);
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