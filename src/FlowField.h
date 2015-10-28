
#pragma once
#include "ofMain.h"

#define width 60
#define height 40
#define depth 60

class FlowField {
    
public:
    
    FlowField();
    
    void setup();
    void update();
    void draw();
    
    
    ofVec3f getForceAtPosition( ofVec3f pos );

    void addVectorCircle(float x, float y, float z, float vx, float vy, float vz, float radius, float strength);
    void clear();
    

    ofVec3f field[depth][width * height];
    
    
    int fieldWidth;
    int fieldHeight;
    int fieldDepth;

};