//
//  MultiLine.hpp
//  Curved Arrows Class
//
//

#pragma once
#include "ofMain.h"

class MultiLine
{
public:

	MultiLine();
    MultiLine(glm::vec2 _start, glm::vec2 _middle, glm::vec2 _end, int _incMax);

    void setup();
	void update(int _inc);
	void draw();

	ofPath path;

    glm::vec2 start, middle, end;

    int inc, incMax;

	ofColor color;
};
