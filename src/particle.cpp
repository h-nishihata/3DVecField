#include "particle.h"
#include "ofMain.h"


//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0,0,0);
	damping = 0.15f;
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y, float z){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
    frc.z = frc.z + z;
}

//------------------------------------------------------------
void particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
    frc.z = frc.z - vel.z * damping;
}

//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float pz, float vx, float vy, float vz){
    pos.set(px,py,pz);
	vel.set(vx,vy,vz);
}

//------------------------------------------------------------
void particle::update(){	
	vel = vel + frc;
	pos = pos + vel;
}

//------------------------------------------------------------
void particle::draw(){
    ofSetColor(255, 255, 255);
    ofCircle(pos.x, pos.y, pos.z, 1);
}


//------------------------------------------------------------
void particle::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
    float minz = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
    float maxz = (ofGetWidth() + ofGetHeight())/2;
	
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
    
    if (pos.z > maxz){
        pos.z = maxz; // move to the edge, (important!)
        vel.z *= -1;
        bDidICollide = true;
    } else if (pos.z < minz){
        pos.z = minz; // move to the edge, (important!)
        vel.z *= -1;
        bDidICollide = true;
    }
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}
