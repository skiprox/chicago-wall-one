//
//  DashedLine.cpp
//  DashedLines
//
//
//

#include "DashedLine.hpp"

DashedLine::DashedLine()
{
    start = glm::vec2(0, 0);
    end = glm::vec2(ofGetWidth(), ofGetHeight());
    color = ofColor(255, 40, 20);
    incMax = 500;
    setup();
}

DashedLine::DashedLine(glm::vec2 _start, glm::vec2 _end, ofColor _color, int _incMax) {
	start = _start;
	end = _end;
	color = _color;
	incMax = _incMax;
    setup();
}

void DashedLine::setup() {
	path.setCurveResolution(100);
	ofSetCircleResolution(100);
	// Need to figure out number of segments,
	// based on desired segment length
	numSegments = fabs(ofDist(start.x, start.y, end.x, end.y))/desiredStrokeLen;
	inc = 0;
}

void DashedLine::update(int _inc) {
	inc = min(_inc, incMax);
}

void DashedLine::draw() {
	ofPushStyle();
	path.clear();
	path.setStrokeColor(color);
	path.setFilled(false);
	path.setStrokeWidth(2);
	float segBreaker = (float)incMax/(float)numSegments;
	float distX = start.x - end.x;
	float distY = start.y - end.y;
	float segmentLenX = (distX/((float)incMax/segBreaker))/2.0;
	float segmentLenY = (distY/((float)incMax/segBreaker))/2.0;
	for (int i = 0; i < inc/segBreaker; i++) {
		float posX = ofLerp(start.x, end.x, (float)i/((float)incMax/segBreaker));
		float posY = ofLerp(start.y, end.y, (float)i/((float)incMax/segBreaker));
		path.moveTo(posX, posY);
		path.lineTo(posX + segmentLenX, posY + segmentLenY);
	}
	path.draw();
	ofPopStyle();
}
