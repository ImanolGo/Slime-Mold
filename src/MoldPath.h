//
//  MoldPath.h
//  Slime_Mold
//
//  Created by Imanolgo on 2/13/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


/*
 *  LightningBolt.cpp
 *  lightning
 *
 *  Created by rockabit on 15-06-10.
 *  Copyright 2010 Random. All rights reserved.
 *
 */





#ifndef MOLD_PATH_H
#define MOLD_PATH_H

#include "ofMain.h"
#include "Segment.h"
#include "ofxVectorMath.h"

/*
 *	A simple lightning renderer. Specify a start and end location to create one.
 *
 *	Usage:
 *	bolt.setup(ofxVec2f(0, 0), ofxVec2f(mouseX, mouseY), 6, ofRandom(80, 100), 0.04);
 *	bolt.parse();
 *	bolt.draw();
 */
class MoldPath {
    
public:
    
	vector<Segment> segments;
	MoldPath();
	void setup(float fromX, float fromY, float toX, float toY, ofColor color, int aNumIterations=6, float aMaxOffset=120.0, float aBranchingProbability=.4);
    void setWidth(float width){m_width = width;};
	void parse();
	void draw();
    
protected:
	float fromX;
	float fromY;
	float toX;
	float toY;
	int numIterations;
	float deviation;
	float currentDeviation;
	float branchingProbability;
	float branchAngleMultiplier;
	float branchScale;
	float branchIntensityFactor;
    ofColor m_color;
    
    float   m_width;
    bool    m_initialized;
    
};

#endif
