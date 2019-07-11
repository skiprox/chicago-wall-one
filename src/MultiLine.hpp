//
//  MultiLine.hpp
//  Multi Line Class
//
//

#pragma once
#include "ofMain.h"

class MultiLine
{
public:

	MultiLine();
    MultiLine(vector<std::array<glm::vec2, 4>> _pts, ofColor _color, int _incMax);

    void setup();
	void update(int _inc);
	void draw();
	float quadEaseOut(float t);

	ofPath path;

    vector<std::array<glm::vec2, 4>> pts;

    int inc, incMax, numSegments;

	ofColor color;
};
