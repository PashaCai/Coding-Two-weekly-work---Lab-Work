

#include "myboid.hpp"

myboid::myboid()
{
    separationWeight = 0.09f;
    cohesionWeight = 0.02f;
    alignmentWeight = 0.02f;
    
    separationThreshold = 200;
    neighbourhoodSize = 30;
    
    position = ofVec3f(ofRandom(1, -1), ofRandom(1, -3));
    velocity = ofVec3f(ofRandom(1, -1), ofRandom(-1, 1));
}

void myboid::draw(){
    ofSetColor(255,235,205);
    ofDrawGrid(position.x, position.y);
}
