/*
 *  Segment.h
 *  lightning
 *
 *  Created by rockabit on 15-06-10.
 *  Copyright 2010 Random. All rights reserved.
 *
 */

#ifndef SEGMENT_H
#define SEGMENT_H

#include "ofMain.h"
//#include "ofxVectorMath.h"

class Segment {

public:
	ofVec2f start;
	ofVec2f end;
	float intensity;

	float getLength();
	float getRadians();
	float getDegrees();
	ofVec2f getMidPoint();
	Segment(ofVec2f start, ofVec2f end, float intensity);
};

#endif
