#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Resource.h"
#include "MoldPath.h"
#include "particle.h"

class testApp : public ofBaseApp{
    
public:
    
    virtual ~testApp();
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    float EuclideanDistance(const ofPoint& x, const ofPoint& y);
    
    MoldPath path;
    Boolean mouseDown;
    float pathX;
    
    vector<Resource*>   resources;
    vector<Resource*>   repulsors;
    vector<Resource*>   availableResources;
    vector<Resource*>   visitedResources;
    Resource*           originResource;
    Resource*           targetResource;    
    vector<MoldPath>    vPaths;
    particle*           pParticle;
    
    bool found;
};

#endif
