#pragma once

#include "ofMain.h"
#include "Constants.hpp"
#include "ofxSimpleSerial.h"
#include "Line.hpp"
#include "DashedLine.hpp"
#include "DottedLine.hpp"
#include "HandMarker.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
        void setupAnimations();
		void update();
		void updateSerials();
		void draw();
		void drawBackground();
		void drawHandMarkers();
		void drawAnimations();
		void onNewMessage(string & message);
		void keyPressed(int key);
		void runAnimation(int animationNum);

		ofxSimpleSerial	mySerial;
		int baud = 57600;
        ofColor red = ofColor(220, 20, 30);
    	int serial1 = 0;
    	int serial2 = 0;

    	float width;
    	float height;

        float smSqSize;

    	float universalCounter = 0.0;

    	string message;

    	vector<int> serialInput;

    	std::array<int, 9> touchThreshold = {{0, 0, 0, 0, 0, 0, 0, 0, 0}};

    	std::array<bool, 9> shouldRunAnimation = {{false, false, false, false, false, false, false, false, false}};
    	std::array<int, 9> animationCounter = {{0, 0, 0, 0, 0, 0, 0, 0, 0}};
    	std::array<int, 9> animationCounterMax = {{5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000}};

    	// All animations declared here
    	Line animationOne;
    	Line animationTwo;
    	DashedLine animationThree;
        DashedLine animationFour;
        DottedLine animationFive;
        DottedLine animationSix;

        // All arbitrary animation variables which we'll need to create animations
        vector<std::array<glm::vec2, 4>> _pts;
        array<glm::vec2, 4> newPoints1, newPoints2, newPoints3, newPoints4;

    	// All the hand markers declared here
    	std::array<HandMarker, 9> handMarkers;
		
};
