//
//  Resource.h
//  Slime_Mold
//
//  Created by Imanolgo on 2/13/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#ifndef RESOURCE_H
#define RESOURCE_H

#include "ofPoint.h"
#include "ofColor.h"
#include "ofImage.h"

/*

 */
class Resource {
    
public:
    
    Resource(ofPoint pos, float size, ofColor color);
	void draw();
    const ofPoint& getPos() const {return m_pos;}
    void  setRepulsor(){m_repulsor = true;};
    
private:
    
    ofPoint m_pos;
    float   m_size;   
    ofColor m_color;
    
    ofImage m_crumb;
    bool    m_repulsor;
    
};

#endif
