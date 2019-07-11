//
//  DashedLine.hpp
//  Dashed Line Class
//
//

#pragma once
#include "ofMain.h"

class DashedLine
{
public:

	DashedLine();
    DashedLine(glm::vec2 _start, glm::vec2 _end, ofColor _color, int _incMax);

    void setup();
	void update(int _inc);
	void draw();

	ofPath path;

    glm::vec2 start, end;

    int inc, incMax;

	ofColor color;
};
