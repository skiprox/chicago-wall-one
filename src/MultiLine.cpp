//
//  MultiLine.cpp
//  MultiLines
//
//
//

#include "MultiLine.hpp"

MultiLine::MultiLine()
{
	float width = ofGetWidth();
	float height = ofGetHeight();
	array<glm::vec2, 4> newPoints1 = {glm::vec2(50, height/2 - 50), glm::vec2(50, height/2 + 50), glm::vec2(width - 50, height/2 + 25), glm::vec2(width - 50, height/2 - 25)};
	pts.push_back(newPoints1);
	array<glm::vec2, 4> newPoints2 = {glm::vec2(width - 100, height/2 - 25), glm::vec2(width - 50, height/2 - 25), glm::vec2(width - 60, 50), glm::vec2(width - 90, 50)};
	pts.push_back(newPoints2);
	color = ofColor(240, 60, 40);
	incMax = 250;
    setup();
}

MultiLine::MultiLine(vector<std::array<glm::vec2, 4>> _pts, ofColor _color, int _incMax) {
	pts = _pts;
	color = _color;
	incMax = _incMax;
    setup();
}

void MultiLine::setup() {
	inc = 0;
	numSegments = pts.size();
	path.setCurveResolution(100);
	ofSetCircleResolution(100);
}

void MultiLine::update(int _inc) {
	inc = _inc;
}

void MultiLine::draw() {
	ofPushStyle();
	path.clear();
	path.setFillColor(ofColor(255, 40, 60));
	path.setFilled(true);
	for (int i = 0; i < numSegments; i++) {
		if (inc >= (incMax/(numSegments) * i) && inc <= incMax/(numSegments) * (i + 1)) {
			for (int j = 0; j < i; j++) {
				path.moveTo(pts[j][0]);
				path.lineTo(pts[j][1]);
				path.lineTo(pts[j][2]);
				path.lineTo(pts[j][3]);
				path.close();
				path.draw();
			}
			path.moveTo(pts[i][0]);
			path.lineTo(pts[i][1]);
			float upperEq = (float)inc - ((float)incMax/((float)numSegments) * i);
			float lowerEq = ((float)incMax/((float)numSegments) * ((float)i + 1.0)) - ((float)incMax/((float)numSegments) * i);
			float easedIncrement = quadEaseOut(upperEq/lowerEq);
			path.lineTo(ofLerp(pts[i][1].x, pts[i][2].x, easedIncrement), ofLerp(pts[i][1].y, pts[i][2].y, easedIncrement));
			path.lineTo(ofLerp(pts[i][0].x, pts[i][3].x, easedIncrement), ofLerp(pts[i][0].y, pts[i][3].y, easedIncrement));
			path.close();
			path.draw();
		} else if (inc >= incMax) {
			path.moveTo(pts[i][0]);
			path.lineTo(pts[i][1]);
			path.lineTo(pts[i][2]);
			path.lineTo(pts[i][3]);
			path.close();
			path.draw();
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
float MultiLine::quadEaseOut(float t) {
	return -1.0 *(t)*(t-2);
}
