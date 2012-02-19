#include "testApp.h"

testApp::~testApp()
{
    for(int i=0;i<resources.size();i++)
    {
        delete resources[i];
    }
    
    for(int i=0;i<repulsors.size();i++)
    {
        delete repulsors[i];
    }
    
    for(int i=0;i<visitedResources.size();i++)
    {
        delete visitedResources[i];
    }
    
    for(int i=0;i<availableResources.size();i++)
    {
        delete availableResources[i];
    }
    
    
    delete pParticle;
    delete originResource;
    delete targetResource;
    
}


//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	ofEnableAlphaBlending();
	
	mouseDown = false;
    
    float x = 0.0f;
    float y = 0.0f;
    for(int i=0;i<10;i++)
    {
        x = ofRandom(0+ofGetScreenWidth()/10,ofGetScreenWidth()-ofGetScreenWidth()/10);
        y = ofRandom(0+ofGetScreenHeight()/10,ofGetScreenHeight()-ofGetScreenHeight()/10);
        Resource* resource = new Resource(ofPoint(x,y),20,ofColor(250,250,250,120));
        resources.push_back(resource);
        availableResources.push_back(resource);
        
        x = ofRandom(0+ofGetScreenWidth()/10,ofGetScreenWidth()-ofGetScreenWidth()/10);
        y = ofRandom(0+ofGetScreenHeight()/10,ofGetScreenHeight()-ofGetScreenHeight()/10);
        Resource* repulsor = new Resource(ofPoint(x,y),20,ofColor(250,250,250,120));
        repulsor->setRepulsor();
        repulsors.push_back(repulsor);
    }
    
    originResource = resources[0];
    targetResource = originResource;
    visitedResources.push_back(originResource);
    vector<Resource*>::iterator it = find (availableResources.begin(), availableResources.end(), originResource);
    availableResources.erase(it);
    
    pParticle = new particle();
    pParticle->setInitialCondition(originResource->getPos(),ofPoint(0,0));
    
    found = true;
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    for(int i=0;i<availableResources.size();i++)
    {
        //pParticle->addAttractionForce(availableResources[i]->getPos(), 500,100.9);
    }
    
    for(int i=0;i<repulsors.size();i++)
    {
        pParticle->addRepulsionForce(repulsors[i]->getPos(), 50,10.9);
    }
    
    
    if(found)
    {
        float dist = 1000000.0f;
        int n = 0;
        for(int i=0;i<availableResources.size();i++)
        {
            float current_dist = EuclideanDistance(availableResources[i]->getPos(), originResource->getPos());
            if(dist>current_dist)
            {
                dist = current_dist;
                n = i;
                
            }
           
        }
        
        targetResource = availableResources[n];
        availableResources.erase(availableResources.begin()+n);
        found = false;
    }
    
    //pParticle->addAttractionForce(availableResources[i]->getPos(), 500,100.9);
    //pParticle->addDampingForce();
    //pParticle->addAttractionForce(ofPoint(200,200), 500,1.10);
    //pParticle->update();
    
    path.setup(originResource->getPos().x, originResource->getPos().y, pParticle->pos.x,pParticle->pos.y ,ofColor(100, 100, 100, 25),6, 70, 0.04);
    path.parse();
    
    pParticle->particleToPoint(targetResource->getPos());
    
    float dist = EuclideanDistance(targetResource->getPos(), pParticle->pos);
    if(dist<0.1)
    {
        originResource = targetResource;
        found = true;
        if(availableResources.empty())
        {
            for(int i=0;i<resources.size();i++)
            {
                if (resources[i]!=originResource) {
                    availableResources.push_back(resources[i]);
                }
            }
        }
    }
    
//    for(int i=0;i<availableResources.size();i++)
//    {
//        float dist = EuclideanDistance(availableResources[i]->getPos(), pParticle->pos);
//        if (dist<0.2) {
//                availableResources.erase(availableResources.begin()+i);
//                originResource = availableResources[i];
//
//        }
//    }
	
}

float testApp::EuclideanDistance(const ofPoint& p1, const ofPoint& p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}
//--------------------------------------------------------------
void testApp::draw(){
	
    
	//ofSetColor(100, 100, 100, 25);
    
    ofSetColor(197, 186, 132, 25);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    path.draw();
    
    //ofSetColor(10, 186, 132, 150);
    //ofCircle(pParticle->pos.x,pParticle->pos.y,10);
	
    
    for(int i=0;i<resources.size();i++)
    {
        resources[i]->draw();
    }
    
    for(int i=0;i<repulsors.size();i++)
    {
        repulsors[i]->draw();
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
	mouseDown = true;
	pathX = ofRandomWidth();
    //	bolt.setup(boltX, 0, mouseX, mouseY, 6, ofRandom(90, 110), 0.3);
    //	bolt.parse();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
	mouseDown = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

