//
//  MoldPath.cpp
//  Slime_Mold
//
//  Created by Imanolgo on 2/13/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "MoldPath.h"

MoldPath::MoldPath() {
    
    m_initialized = false;
    
}

void MoldPath::setup(float aFromX, float aFromY, float aToX, float aToY, ofColor color, int aNumIterations, float aMaxOffset, float aBranchingProbability) {
    
	fromX = aFromX;
	fromY = aFromY;
	toX = aToX;
	toY = aToY;
    m_color = color;
	numIterations = aNumIterations;
    
	deviation = aMaxOffset;
	branchingProbability = aBranchingProbability;
	branchAngleMultiplier = 1.3;//1.6;
	branchScale = 0.8;
	branchIntensityFactor = 0.7;//0.5;
    m_width = 3.0f;
    m_initialized = true;
}

void MoldPath::parse() {
    
    if(!m_initialized)
    {
        return;
    }
	// start with one segment
	segments.clear();
	segments.push_back(Segment(ofVec2f(fromX, fromY), ofVec2f(toX, toY), 1.0));
    
	currentDeviation = deviation;
    
	// for each iteration
	for (int i = 0; i < numIterations; i++)
	{
		// remove segments from list
		vector<Segment> segmentsCopy = segments;
		segments.clear();
        
		// for each segment
		int max = segmentsCopy.size();
		for (int j = 0; j < max; j++) {
            
			// find midpoint between start and end
			ofVec2f midPoint = segmentsCopy[j].getMidPoint();
            
			// offset midpoint perpendicularly to segment with a random number with max amplitude
			float offset = ofRandom(0.0, 1.0) < 0.5 ? -currentDeviation : currentDeviation;
			midPoint.x += cos(segmentsCopy[j].getRadians() - 0.25 * PI) * offset;
			midPoint.y += sin(segmentsCopy[j].getRadians() - 0.25 * PI) * offset;
            
			// add two new segments to list
			Segment a(segmentsCopy[j].start, midPoint, segmentsCopy[j].intensity);
			Segment b(midPoint, segmentsCopy[j].end, segmentsCopy[j].intensity);
			segments.push_back(a);
			segments.push_back(b);
            
			if (ofRandom(0.0, 1.0) < branchingProbability)
			{
				// add branch:
				float branchAngle = a.getRadians() * branchAngleMultiplier;
				ofVec2f branchEnd(midPoint.x + cos(branchAngle) * branchScale * a.getLength(),
                                  midPoint.y + sin(branchAngle) * branchScale * a.getLength());
				Segment branch(midPoint, branchEnd, branchIntensityFactor * a.intensity);
				segments.push_back(branch);
			}
		}
        
		// halve max offset amplitude
		currentDeviation *= 0.5;
	}
}

void MoldPath::draw() {
    
    if(!m_initialized)
    {
        return;
    }
    
    glPushMatrix();
    glLineWidth(m_width);

	glBegin(GL_LINES);
    
    ofSetColor(m_color);
    
	int max = segments.size();
    //max = 10;
	for (int i = 0; i < max; i++)
	{
		float brightness = segments[i].intensity * 255;
		ofSetColor(m_color);
		//ofLine(segments[i].start.x, segments[i].start.y, segments[i].end.x, segments[i].end.y);
		glVertex2f(segments[i].start.x, segments[i].start.y);
		glVertex2f(segments[i].end.x, segments[i].end.y);
	}
    
	glEnd();
    glPopMatrix();
}
