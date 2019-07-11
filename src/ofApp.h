#pragma once

#include "ofMain.h"
#include "Constants.hpp"
#include "ofxSimpleSerial.h"
#include "CurvedArrow.hpp"
#include "MultiLine.hpp"
#include "DashedLine.hpp"
#include "HandMarker.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void updateSerials();
		void draw();
		void drawBackground();
		void drawHandMarkers();
		void drawAnimations();
		void onNewMessage(string & message);
		void keyReleased(int key);
		void runAnimation(int animationNum);

		ofxSimpleSerial	mySerial;
		int baud = 57600;
		ofColor colorOn = ofColor(203, 255, 181);
        ofColor red = ofColor(220, 20, 30);
    	int serial1 = 0;
    	int serial2 = 0;

    	float width;
    	float height;

    	float universalCounter = 0.0;

    	string message;

    	vector<int> serialInput;

    	std::array<int, 9> touchThreshold = {{0, 0, 0, 0, 0, 0, 0, 0, 0}};

    	std::array<bool, 9> shouldRunAnimation = {{false, false, false, false, false, false, false, false, false}};
    	std::array<int, 9> animationCounter = {{0, 0, 0, 0, 0, 0, 0, 0, 0}};
    	std::array<int, 9> animationCounterMax = {{500, 500, 500, 500, 500, 500, 500, 500, 500}};

    	// All animations declared here
    	CurvedArrow animationOne;
    	MultiLine animationTwo;
    	DashedLine animationThree;

    	// All the hand markers declared here
    	std::array<HandMarker, 3> handMarkers;
		
};
