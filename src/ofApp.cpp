#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetCircleResolution(100);
	width = ofGetWidth();
	height = ofGetHeight();
	mySerial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = mySerial.getDeviceList();
	mySerial.setup(0, baud); //open the first device
	mySerial.startContinuousRead();
	ofAddListener(mySerial.NEW_MESSAGE,this,&ofApp::onNewMessage);
	message = "";
}

//--------------------------------------------------------------
void ofApp::update(){
	updateSerials();
}

//--------------------------------------------------------------
void ofApp::updateSerials(){
	// Loop through the serial inputs
	for (int i = 0; i < serialInput.size(); i++) {
		// If we have something going on with the serial input...
		if (serialInput[i] == 1) {
			// Increase the threshold number,
			touchThreshold[i]++;
			// and once that reaches 10 we can run the animation
			if (touchThreshold[i] >= 50) {
				// Reset the threshold
				touchThreshold[i] = 0;
				// Run the animation
				shouldRunAnimation[i] = true;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::onNewMessage(string & message)
{
	vector<string> input = ofSplitString(message, ",");
	serialInput.clear();
	for (int i = 0; i < input.size() - 1; i++) {
		serialInput.push_back(ofToInt(input[i]));
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawBackground();
	drawAnimations();
}

//--------------------------------------------------------------
void ofApp::drawBackground(){
	ofBackground(0);
	ofSetColor(255);
	// Draw up and down lines
	for (int i = 0; i < 2; i++) {
		ofDrawRectangle(width/3.0 * (i + 1) - 1, 0, 2, height);
		ofDrawRectangle(0, height/3.0 * (i + 1) - 1, width, 2);
	}
}

//--------------------------------------------------------------
void ofApp::drawAnimations(){
	// Run through the `shouldRunAnimation` array, and run any of the animations that we should
	for (int i = 0; i < shouldRunAnimation.size(); i++) {
		if (shouldRunAnimation[i]) {
			// Increase the animation counter,
			// which is what we're using to run the animation for
			// a set amount of time
			animationCounter[i]++;
			// If we haven't hit the threshold for how long to
			// run the animation, fucking run it
			if (animationCounter[i] < 500) {
				runAnimation(i + 1);
			} else { // Otherwise stop running the animation
				shouldRunAnimation[i] = false;
				animationCounter[i] = 0;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// Keys 1 through 9 are 49 through 57
	// so use this to determine the index of the animation we should run
	if (key >= 49 && key <= 57) {
		int keyIndex = key - 49;
		shouldRunAnimation[keyIndex] = true;
	}
}

//--------------------------------------------------------------
void ofApp::runAnimation(int animationNum){
	ofSetColor(colorOn);
	switch(animationNum) {
		case 1:
			ofDrawRectangle(0, 0, width/3.0, height/3.0);
			break;
		case 2:
			ofDrawRectangle(width/3.0, 0, width/3.0, height/3.0);
			break;
		case 3:
			ofDrawRectangle(width/3.0 * 2, 0, width/3.0, height/3.0);
			break;
		case 4:
			ofDrawRectangle(0, height/3.0, width/3.0, height/3.0);
			break;
		case 5:
			ofDrawRectangle(width/3.0, height/3.0, width/3.0, height/3.0);
			break;
		case 6:
			ofDrawRectangle(width/3.0 * 2, height/3.0, width/3.0, height/3.0);
			break;
		case 7:
			ofDrawRectangle(0, height/3.0 * 2, width/3.0, height/3.0);
			break;
		case 8:
			ofDrawRectangle(width/3.0, height/3.0 * 2, width/3.0, height/3.0);
			break;
		case 9:
			ofDrawRectangle(width/3.0 * 2, height/3.0 * 2, width/3.0, height/3.0);
			break;
		default:
			cout << "WHAT FUCKING KEY IS THIS?? " << animationNum << endl;
			break;
	}
}
