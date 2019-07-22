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
	setupAnimations();
}

//--------------------------------------------------------------
void ofApp::setupAnimations(){
	/**
	 * ALL THE ANIMATIONS GO HERE
	 */
	vector<std::array<glm::vec2, 2>> pts;
	// ONE ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(0, 0), glm::vec2(width/2.0, height/2.0)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/2.0, height/2.0), glm::vec2(width/1.2, 100)}});
	animationOne = Line(pts, 2.0, ofColor(240, 40, 20), 250, true);
	pts.clear();
	// TWO ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(0, height/1.1), glm::vec2(100, height/2)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(98, height/2 - 2), glm::vec2(width/1.1, height/1.6)}});
	animationTwo = Line(pts, 10.0, ofColor(240, 40, 20), 250, true);
	pts.clear();
	// THREE ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(0, height/1.1), glm::vec2(100, height/2)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(98, height/2 - 2), glm::vec2(width/1.1, height/1.3)}});
	animationThree = DashedLine(DashedLine(pts, 2.0, ofColor(240, 40, 20), 250, true));
	pts.clear();
	// FOUR ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/1.1, height/3), glm::vec2(200, 100)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(202, 102), glm::vec2(100, height/1.6)}});
	animationFour = DashedLine(DashedLine(pts, 5.0, ofColor(240, 40, 20), 250, true));
	pts.clear();
	// FIVE ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(0, 0), glm::vec2(width/2.1, height/2.2)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/2.1, height/2.2), glm::vec2(width/1.3, 100)}});
	animationFive = DottedLine(pts, 2.0, ofColor(240, 40, 20), 250, true);
	pts.clear();
	// SIX ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/6.0, height/1.1), glm::vec2(width/4.4, height/2.2)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/4.4, height/2.2), glm::vec2(width/1.3, height/2.3)}});
	animationSix = DottedLine(pts, 5.0, ofColor(240, 40, 20), 250, true);
	pts.clear();
	/**
	 * ALL THE HAND MARKERS GO HERE
	 */
	handMarkers[0] = HandMarker(glm::vec2(100, 400), ofColor(240, 220, 40));
	handMarkers[1] = HandMarker(glm::vec2(400, 600), ofColor(40, 190, 240));
	handMarkers[2] = HandMarker(glm::vec2(1200, 300), ofColor(20, 240, 180));
}

//--------------------------------------------------------------
void ofApp::update(){
	updateSerials();
	if (fabs(universalCounter - TWO_PI) < 0.0001) {
		universalCounter = 0.0f;
	} else {
		universalCounter = (universalCounter + PI/100.0);
	}
	for (int i = 0; i < handMarkers.size(); i++) {
		handMarkers[i].update(universalCounter);
	}
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
	drawHandMarkers();
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
void ofApp::drawHandMarkers(){
	for (int i = 0; i < handMarkers.size(); i++) {
		handMarkers[i].draw();
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
			if (animationCounter[i] <= animationCounterMax[i]) {
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
	ofSetColor(red);
	switch(animationNum) {
		case 1:
			animationOne.update(animationCounter[0]);
			animationOne.draw();
			break;
		case 2:
			animationTwo.update(animationCounter[1]);
			animationTwo.draw();
			break;
		case 3:
			animationThree.update(animationCounter[2]);
			animationThree.draw();
			break;
		case 4:
			animationFour.update(animationCounter[3]);
			animationFour.draw();
			break;
		case 5:
			animationFive.update(animationCounter[4]);
			animationFive.draw();
			break;
		case 6:
			animationSix.update(animationCounter[5]);
			animationSix.draw();
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
