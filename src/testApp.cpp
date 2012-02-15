#include "testApp.h"

testApp::~testApp()
{
    for(int i=0;i<resources.size();i++)
    {
        delete resources[i];
    }
    
    
    for(int i=0;i<visitedResources.size();i++)
    {
        delete visitedResources[i];
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
    }
    
    originResource = resources[0];
    targetResource = originResource;
    visitedResources.push_back(originResource);
    
    pParticle = new particle();
    pParticle->setInitialCondition(originResource->getPos().x, originResource->getPos().y, 0.0f, 0.0f);
    
    found = true;
    

    }

//--------------------------------------------------------------
void testApp::update(){
    
    if(found)
    {
        
        float distance = 100000.0f;
        
        // iterator to vector element:
        vector<Resource*>::iterator it;
        for(int i=0;i<resources.size();i++)
        {
            it = find(visitedResources.begin(),visitedResources.end(),resources[i]);
            if(it==visitedResources.end()) //not found
            {
                //loat currentDist = EuclideanDistance(originResource->getPos(),resources[i]->getPos());
                
                float currentDist = originResource->getPos().distance(resources[i]->getPos());
                if(currentDist<distance)
                {
                    distance = currentDist;
                    targetResource = resources[i];
                }
            }
        }
        
        found = false;
    }
        
        
    
    float d = pParticle->pos.distance(targetResource->getPos());
    if (d < 0.01) 
    {
        visitedResources.push_back(targetResource);
        found = true;
        originResource = targetResource;
        if(visitedResources.size() == resources.size())
        {
            visitedResources.clear();
        }
    }
    
    pParticle->particleToPoint(targetResource->getPos().x, targetResource->getPos().y);
    //pParticle->addDampingForce();
    
    path.setup(originResource->getPos().x, originResource->getPos().y, pParticle->pos.x,pParticle->pos.y ,ofColor(100, 100, 100, 25),10, 70, 0.04);
    path.parse();
	
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
	

    for(int i=0;i<resources.size();i++)
    {
        resources[i]->draw();
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

