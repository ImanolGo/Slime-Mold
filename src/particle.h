#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"
//#include "ofxVectorMath.h"
#include "ofPoint.h"

class particle
{
    public:
        ofPoint pos;
        ofPoint prevPos;
        ofPoint vel;
        ofPoint frc;   // frc is also know as acceleration (newton says "f=ma")

        particle();
		virtual ~particle(){};

        void resetForce();
		void addForce(ofPoint force);

		void addRepulsionForce(ofPoint force, float radius, float scale);
		void addAttractionForce(ofPoint force, float radius, float scale);

		void addDampingForce();

		void setInitialCondition(ofPoint p, ofPoint v);
        void update();
        void draw();
        void particleToPoint(ofPoint catchPoint);

		void bounceOffWalls();
		float damping;

		float x0, y0;
		float		catchUpSpeed;		// take this pct of where I want to be, and 1-catchUpSpeed of my pos
        float		angle;
        int     randomSeed;
        int     alpha;
        float   size;

    protected:
    private:
};

#endif // PARTICLE_H
