

#include "boid.h"
#include "ofMain.h"

Boid::Boid()
{
	separationWeight = 3.0f;
	cohesionWeight = 0.009f;
	alignmentWeight = 0.0002f;
    arrow.moveTo(10, -25);
    arrow.lineTo(10, 7);
    arrow.lineTo(-10, 20);
    arrow.close();
    
	separationThreshold = 30;
	neighbourhoodSize = 1;
	
	position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
	velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1));
}

Boid::Boid(ofVec3f &pos, ofVec3f &vel)
{
	separationWeight = 1.0f;
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;
	
	separationThreshold = 15;
	neighbourhoodSize = 100;
	
	position = pos;
	velocity = vel;
}

Boid::~Boid()
{
	
}

float Boid::getSeparationWeight()
{
	return separationWeight;
}
float Boid::getCohesionWeight()
{
	return cohesionWeight;
}

float Boid::getAlignmentWeight()
{
	return alignmentWeight;
}


float Boid::getSeparationThreshold()
{
	return separationThreshold;
}

float Boid::getNeighbourhoodSize()
{
	return neighbourhoodSize;
}


void Boid::setSeparationWeight(float f)
{
	separationWeight = f;
}
void Boid::setCohesionWeight(float f)
{
	cohesionWeight = f;
}

void Boid::setAlignmentWeight(float f)
{
	alignmentWeight = f;
}


void Boid::setSeparationThreshold(float f)
{
	separationThreshold = f;
}

void Boid::setNeighbourhoodSize(float f)
{
	neighbourhoodSize = f;
}


ofVec3f Boid::getPosition()
{
	return position;
}

ofVec3f Boid::getVelocity()
{
	return velocity;
}

ofVec3f Boid::separation(std::vector<Boid *> &otherBoids)
{
	// finds the first collision and avoids that
	// should probably find the nearest one
	// can you figure out how to do that?
    
    ofVec3f v(0,0,0); // create v
    
	for (int i = 0; i < otherBoids.size(); i++)
	{	
		if(position.distance(otherBoids[i]->getPosition()) < separationThreshold)
		{
			//ofVec3f v = position -  otherBoids[i]->getPosition();
            v = position -  otherBoids[i]->getPosition();
			v.normalize();
			//return v;
		}
	}
    return v; // return v
}


ofVec3f Boid::separationBetweenTypes(std::vector<Boid *> &boids1, std::vector<Boid *> &boids2)
{
    ofVec3f totalSeparation;
    int count = 0;
    for (auto boid1 : boids1) {
        for (auto boid2 : boids2) {
            if (boid1 != boid2) {
                float dist = boid1->getPosition().distance(boid2->getPosition());
                if (dist < separationThreshold) {
                    ofVec3f diff = boid1->getPosition() - boid2->getPosition();
                    diff.normalize();
                    diff /= dist;
                    totalSeparation += diff;
                    count++;
                }
            }
        }
    }
    if (count > 0) {
        totalSeparation /= count;
    }
    return totalSeparation;
}


ofVec3f Boid::cohesion(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(10,10,10);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getPosition();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v =  average - position;
	v.normalize();
	return v;
}

ofVec3f Boid::alignment(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getVelocity();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v =  average - velocity;
	v.normalize();
	return v;
}

void Boid::update(std::vector<Boid *> &otherBoids, std::vector<Boid *> &sameTypeBoids, ofVec3f &min, ofVec3f &max)
{
//	velocity += separationWeight*separation(otherBoids);
//	velocity += cohesionWeight*cohesion(otherBoids);
//	velocity += alignmentWeight*alignment(otherBoids);
	
    velocity += separationWeight * separation(otherBoids) * 0.5; // attract to all other boids with half weight
    velocity += cohesionWeight * cohesion(sameTypeBoids) * 2; // attract to same-type boids with double weight
    velocity += alignmentWeight * alignment(sameTypeBoids) * 0.5; // align with same-type boids with half weight
    velocity -= separationWeight * separation(sameTypeBoids) * 2; // repel from same-type boids with double weight
    velocity -= separationWeight * separationBetweenTypes(otherBoids, sameTypeBoids) * 0.5; // repel from different-type boids with half weight
    
	walls(min, max);
	position += velocity;
}

void Boid::walls(ofVec3f &min, ofVec3f &max)
{
	if (position.x < min.x){
		position.x = min.x;
		velocity.x *= -1;
	} else if (position.x > max.x){
		position.x = max.x;
		velocity.x *= -1;
	}
	
	if (position.y < min.y){
		position.y = min.y;
		velocity.y *= -1;
	} else if (position.y > max.y){
		position.y = max.y;
		velocity.y *= -1;
	}
	
	
}

void Boid::draw()
{
    ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofRotateRad(velocity.angleRad(ofVec2f(1,0)));
        ofSetColor(132, 112, 255);
        arrow.draw();
        ofPopMatrix();
}
