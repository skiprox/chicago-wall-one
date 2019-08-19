#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetCircleResolution(100);
	width = ofGetWidth();
	height = ofGetHeight();
	// Small square size
	smSqSize = height/5.0;
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
	animationOne = Line(pts, 2.0, red, 250, true);
	pts.clear();
	// TWO ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(0, height/1.1), glm::vec2(100, height/2)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(98, height/2 - 2), glm::vec2(width/1.1, height/1.6)}});
	animationTwo = Line(pts, 5.0, red, 250, true);
	pts.clear();
	// THREE ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(400, height/1.1), glm::vec2(100, height/2)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(98, height/2 - 2), glm::vec2(width/1.1, height/1.3)}});
	animationThree = DashedLine(DashedLine(pts, 2.0, red, 250, true));
	pts.clear();
	// FOUR ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/1.1, height/3), glm::vec2(200, 100)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(202, 102), glm::vec2(100, height/1.6)}});
	animationFour = DashedLine(DashedLine(pts, 5.0, red, 250, true));
	pts.clear();
	// FIVE ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(0, 0), glm::vec2(width/2.1, height/2.2)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/2.1, height/2.2), glm::vec2(width/1.3, 100)}});
	animationFive = DottedLine(pts, 2.0, red, 250, true);
	pts.clear();
	// SIX ANIMATION
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/6.0, height/1.1), glm::vec2(width/4.4, height/2.2)}});
	pts.push_back(array<glm::vec2, 2> {{glm::vec2(width/4.4, height/2.2), glm::vec2(width/1.3, height/2.3)}});
	animationSix = DottedLine(pts, 5.0, red, 250, true);
	pts.clear();
	/**
	 * ALL THE HAND MARKERS GO HERE
	 */
	// Top left
	handMarkers[0] = HandMarker(glm::vec2(width/3.0 - (width/3.0)/2.0, smSqSize - 100), red);
	// Top center
	handMarkers[1] = HandMarker(glm::vec2(width/2.0, smSqSize - 100), red);
	// Top right
	handMarkers[2] = HandMarker(glm::vec2(width - (width/3.0)/2.0, smSqSize - 100), red);
	// middle left
	handMarkers[3] = HandMarker(glm::vec2(width/3.0 - (width/3.0)/2.0, height - smSqSize - 100), red);
	// middle center
	handMarkers[4] = HandMarker(glm::vec2(width/2.0, height - smSqSize - 100), red);
	// middle right
	handMarkers[5] = HandMarker(glm::vec2(width - (width/3.0)/2.0, height - smSqSize - 100), red);
	// bottom left
	handMarkers[6] = HandMarker(glm::vec2(width/3.0 - (width/3.0)/2.0, height - smSqSize + 100), red);
	// bottom center
	handMarkers[7] = HandMarker(glm::vec2(width/2.0, height - smSqSize + 100), red);
	// bottom right
	handMarkers[8] = HandMarker(glm::vec2(width - (width/3.0)/2.0, height - smSqSize + 100), red);
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
				// If it's the first button, we should run the animation
				if (i == 0) {
					shouldRunAnimation[i] = true;
				} else if (i == 1 || i == 2) {
					if (shouldRunAnimation[0]) {
						shouldRunAnimation[i];
					}
				} else if (i == 3 || i == 4) {
					if (shouldRunAnimation[1] || shouldRunAnimation[2]) {
						shouldRunAnimation[i];
					}
				}
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
		float divConst = 5.0;
		if (i == 0) {
			ofDrawRectangle(0, height/divConst, width, 2);
		} else {
			ofDrawRectangle(0, height - height/divConst, width, 2);
		}
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
void ofApp::keyPressed(int key){
	// Keys 1 through 9 are 49 through 57
	// so use this to determine the index of the animation we should run
	if (key >= 49 && key <= 57) {
		int keyIndex = key - 49;
		// Simulate increasing the threshold number,
		touchThreshold[keyIndex] = 50;
		// and once that reaches 50 we can run the animation
		if (touchThreshold[keyIndex] >= 50) {
			// Reset the threshold
			touchThreshold[keyIndex] = 0;
			// If it's the first button, we should run the animation
			if (keyIndex == 0) {
				cout << "WE SHOULD BE HERE WHAT THE FUCK" << endl;
				shouldRunAnimation[keyIndex] = true;
			} else if (keyIndex == 1 || keyIndex == 2) {
				cout << "WHAT ARE We RUNNING " << shouldRunAnimation[0] << endl;
				if (shouldRunAnimation[0]) {
					shouldRunAnimation[keyIndex] = true;
				}
			} else if (keyIndex == 3 || keyIndex == 4) {
				if (shouldRunAnimation[1] || shouldRunAnimation[2]) {
					shouldRunAnimation[keyIndex] = true;
				}
			} else if (keyIndex == 8) {
				for (int j = 0; j < shouldRunAnimation.size(); j++) {
					shouldRunAnimation[j] = false;
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::runAnimation(int animationNum){
	ofSetColor(red);
	switch(animationNum) {
		case 1:
			// animationOne.update(animationCounter[0]);
			// animationOne.draw();
			ofDrawRectangle(0, 0, width/3.0, height/5.0);
			break;
		case 2:
			// animationTwo.update(animationCounter[1]);
			// animationTwo.draw();
			ofDrawRectangle(width/3.0, 0, width/3.0, height/5.0);
			break;
		case 3:
			// animationThree.update(animationCounter[2]);
			// animationThree.draw();
			ofDrawRectangle(width - width/3.0, 0, width/3.0, height/5.0);
			break;
		case 4:
			// animationFour.update(animationCounter[3]);
			// animationFour.draw();
			ofDrawRectangle(0, height/5.0, width/3.0, height - 2.0 * (height/5.0));
			break;
		case 5:
			// animationFive.update(animationCounter[4]);
			// animationFive.draw();
			ofDrawRectangle(width/3.0, height/5.0, width/3.0, height - 2.0 * (height/5.0));
			break;
		case 6:
			// animationSix.update(animationCounter[5]);
			// animationSix.draw();
			ofDrawRectangle(width - width/3.0, height/5.0, width/3.0, height - 2.0 * (height/5.0));
			break;
		case 7:
			ofDrawRectangle(0, height - height/5.0, width/3.0, height/3.0);
			break;
		case 8:
			ofDrawRectangle(width/3.0, height - height/5.0, width/3.0, height/3.0);
			break;
		case 9:
			ofDrawRectangle(width/3.0 * 2, height - height/5.0, width/3.0, height/3.0);
			break;
		default:
			cout << "WHAT FUCKING KEY IS THIS?? " << animationNum << endl;
			break;
	}
}
