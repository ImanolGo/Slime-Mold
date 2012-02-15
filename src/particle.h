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
		void addForce(float x, float y);

		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);

		void addDampingForce();

		void setInitialCondition(float px, float py, float vx, float vy);
        void update();
        void draw();
        void particleToPoint(float catchX, float catchY);

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
