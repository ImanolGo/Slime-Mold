#include "particle.h"
#include "ofMain.h"
#include "ofxVectorMath.h"

//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.01f;
	catchUpSpeed = 0.01f;
	angle = 0;
	randomSeed = ofRandom(0,2*PI);
	alpha = ofRandom(127,255);
	size = ofRandom(10,20);
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

void particle::addRepulsionForce(float x, float y, float radius, float scale){

	// ----------- (1) make a vector of where this position is:

	ofxVec2f posOfForce;
	posOfForce.set(x,y);

	// ----------- (2) calculate the difference & length

	ofxVec2f diff	= pos - posOfForce;
	float length	= diff.length();

	// ----------- (3) check close enough

	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }

	// ----------- (4) if so, update force

	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
}

void particle::addAttractionForce(float x, float y, float radius, float scale){

	// ----------- (1) make a vector of where this position is:

	ofxVec2f posOfForce;
	posOfForce.set(x,y);

	// ----------- (2) calculate the difference & length

	ofxVec2f diff	= pos - posOfForce;
	float length	= diff.length();

	// ----------- (3) check close enough

	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }

	// ----------- (4) if so, update force

	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
    }
}



//------------------------------------------------------------
void particle::addDampingForce(){

	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity
	// damping is a force operating in the oposite direction of the
	// velocity vector

    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void particle::update(){
	vel = vel + frc;
	pos = pos + vel;

	if(pos.x<=0.0||pos.x>=ofGetWidth())
       vel = -vel;

    if(pos.y<=0.0||pos.y>=ofGetHeight())
        vel = -vel;


}

//------------------------------------------------------------
void particle::draw(){
   // ofCircle(pos.x, pos.y, 3);

    ofFill();
	ofSetRectMode(OF_RECTMODE_CENTER); // center around the position

    float speed = sqrt(vel.x*vel.x + vel.y*vel.y);
	glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		glRotatef(angle * RAD_TO_DEG, 0,0,1);
		ofEllipse(0,0, size + speed,size);
	glPopMatrix();
}

void particle::particleToPoint(float catchX, float catchY){

	prevPos = pos;
	pos.x = catchUpSpeed * catchX + (1-catchUpSpeed) * pos.x;
	pos.y = catchUpSpeed * catchY + (1-catchUpSpeed) * pos.y;
	angle = atan2(pos.y - prevPos.y, pos.x - prevPos.x);

}


//------------------------------------------------------------
void particle::bounceOffWalls(){

	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;

	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();

	if (pos.x > maxx){
		pos.x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}

	if (pos.y > maxy){
		pos.y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}

	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}

}
