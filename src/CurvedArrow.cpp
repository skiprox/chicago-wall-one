//
//  CurvedArrow.cpp
//  CurvedArrows
//
//
//

#include "CurvedArrow.hpp"

CurvedArrow::CurvedArrow()
{
	float width = ofGetWidth();
	float height = ofGetHeight();
    start = glm::vec2(ofRandom(width), ofRandom(height));
    middle = glm::vec2(ofRandom(width), ofRandom(height));
    end = glm::vec2(ofRandom(width), ofRandom(height));
    color = ofColor(255, 40, 20);
    incMax = 500;
    setup();
}

CurvedArrow::CurvedArrow(glm::vec2 _start, glm::vec2 _middle, glm::vec2 _end, ofColor _color, int _incMax) {
	start = _start;
	middle = _middle;
	end = _end;
	color = _color;
	incMax = _incMax;
    setup();
}

void CurvedArrow::setup() {
	path.setCurveResolution(100);
	ofSetCircleResolution(100);
	inc = 0;
}

void CurvedArrow::update(int _inc) {
	inc = _inc;
}

void CurvedArrow::draw() {
	ofPushStyle();
	path.clear();
	path.setStrokeColor(color);
	path.setFilled(false);
	path.setStrokeWidth(4);
	path.moveTo(start);
	// Lerp the ending X and Y positions,
	// so that we start by going halfway to the middle position,
	// and then switch to heading towards the desired end position
	float lerpEndX, lerpEndY;
	if (abs(start.x - end.x) < abs(start.y - end.y)) {
		lerpEndX = inc < incMax/2.0 ? ofLerp(start.x, middle.x/2.0, (float)inc/(incMax/2.0)) : ofLerp(middle.x/2.0, end.x, ofClamp(((float)inc - incMax/2.0)/(incMax/2.0), 0.0, 1.0));
		lerpEndY = ofLerp(start.y, end.y, ofClamp((float)inc/incMax, 0.0, 1.0));
	} else {
		lerpEndX = ofLerp(start.x, end.x, ofClamp((float)inc/incMax, 0.0, 1.0));
		lerpEndY = inc < incMax/2.0 ? ofLerp(start.y, middle.y/2.0, (float)inc/(incMax/2.0)) : ofLerp(middle.y/2.0, end.y, ofClamp(((float)inc - incMax/2.0)/(incMax/2.0), 0.0, 1.0));
	}
	// Quad Bezier function through the three points to create the animated curve
	path.quadBezierTo(glm::vec2(start.x, start.y), glm::vec2(ofLerp(start.x, middle.x, ofClamp((float)inc/incMax, 0.0, 1.0)), ofLerp(start.y, middle.y, ofClamp((float)inc/incMax, 0.0, 1.0))), glm::vec2(lerpEndX, lerpEndY));
	path.draw();
	ofPopStyle();
}
