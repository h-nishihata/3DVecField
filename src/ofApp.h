#pragma once

#include "ofMain.h"
#include "FlowField.h"

#define numParticles 300000
#define kNumNodes 1
#define kNumControllers 1

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void drawFboTest();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofVec3f interpolateByPct(float _pct, int _id);
    
    

    static const int WIDTH = 512;
    static const int HEIGHT = 512;
    static const int imgParticles = WIDTH * HEIGHT;
    unsigned char * pixels;
    
    ofFbo fbo;
    
    FlowField myField;
    ofNode testNodes[kNumNodes];
    ofNode testControllers[kNumControllers];
//    ofLight light[kNumLights];
    
    ofCamera cam;
    
    ofVbo p;
    ofVec3f points[numParticles];
    ofFloatColor myColor[numParticles];
    ofVec3f _initPos[numParticles];
    ofVec3f _pos[numParticles];
    ofVec3f _vel[numParticles];
    ofVec3f _frc[numParticles];
    
    ofImage img;
    
    float camPosX, camPosY, camPosZ;
    bool xFlag, yFlag, zFlag;

    float prevMouseX;
    float prevMouseY;
    float prevMouseZ;
    
    bool emergeMode;
    ofVec3f _startPos[numParticles];
    ofVec3f _currentPos[numParticles];
    float pct[numParticles];
};