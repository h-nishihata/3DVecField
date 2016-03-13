#pragma once

#include "ofMain.h"
#include "FlowField.hpp"

//#define kNumCams 2
//#define kNumNodes 1
//#define kNumControllers 1
#define kNumImgs 5

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void drawFboTest();
    ofVec3f interpolateByPct(float _pct, int _id);
    void resetImg(int imgID);
    
    
    
    ofFbo fbo;
    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;
    ofShader shaderBlurX;
    ofShader shaderBlurY;
    
    
    
    FlowField myField;
    ofNode testNodes;
    ofNode testControllers;
    ofCamera cam;
    //    ofLight light[kNumLights];
    
    //    int camToview;
    float camPosX, camPosY, camPosZ;
    float camPosLmt = 800;
    bool zFlag;
    
    
    
    ofImage img;
    static const int WIDTH = 512;
    static const int HEIGHT = 512;
    static const int numParticles = WIDTH * HEIGHT;
    unsigned char * pixels;
    
    
    ofVbo p;
    ofVec3f points[numParticles];
    ofFloatColor myColor[numParticles];
    ofVec3f _initPos[numParticles];
    ofVec3f _pos[numParticles];
    ofVec3f _frc[numParticles];
    ofVec3f _vel[numParticles];

/*
    bool emergeMode;
    ofVec3f _startPos[numParticles];
    ofVec3f _currentPos[numParticles];
    float pct[numParticles];
*/    
    
    
    float x,y;
    float centX = ofGetWidth()/2;
    float centY = ofGetHeight()/2;
    float ang1, ang2;
    float rad1 = 150;
    float rad2 = 30;
    int vel = 5;
    int timer;
    int imgID;
  
    float prevPointX;
    float prevPointY;
    float prevPointZ;
    
};