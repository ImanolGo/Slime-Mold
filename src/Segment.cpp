/*
 *  Segment.cpp
 *  lightning
 *
 *  Created by rockabit on 15-06-10.
 *  Copyright 2010 Random. All rights reserved.
 *
 */

#include "Segment.h"

Segment::Segment(ofVec2f aStart, ofVec2f aEnd, float aIntensity = 1.0) {

	start = aStart;
	end = aEnd;
	intensity = aIntensity;
}

float Segment::getLength() {

	return start.distance(end);
}

float Segment::getRadians() {

	return atan2(end.y - start.y, end.x - start.x);
}

float Segment::getDegrees() {

	return atan2(end.y - start.y, end.x - start.x) * 180 / PI;
}

ofVec2f Segment::getMidPoint() {

	return start.getMiddle(end);
}
