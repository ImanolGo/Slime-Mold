//
//  Resource.cpp
//  Slime_Mold
//
//  Created by Imanolgo on 2/13/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Resource.h"
#include "ofMain.h"

Resource::Resource(ofPoint pos, float size, ofColor color)
{
    m_pos = pos;
    m_size = size;
    m_color = color;
    m_repulsor = false;
    m_crumb.loadImage("images/crumb.png");
    m_crumb.resize(m_size,m_size);

}

void Resource::draw()
{
    glPushMatrix();
    //ofEnableAlphaBlending();
    ofSetColor(255,255,255);
    if (m_repulsor) {
        ofSetColor(100,100,100);
    }
    //ofCircle(m_pos.x,m_pos.y,m_size);
    m_crumb.draw(m_pos.x,m_pos.y);
    //ofDisableAlphaBlending();
    glPopMatrix();
}
