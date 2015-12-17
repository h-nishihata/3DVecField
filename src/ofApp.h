#pragma once

#include "ofMain.h"
#include "FlowField.hpp"

#define numParticles 300000
#define kNumNodes 1
#define kNumControllers 1
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
    ofNode testNodes[kNumNodes];
    ofNode testControllers[kNumControllers];
    ofCamera cam;
    //    ofLight light[kNumLights];
    
    float camPosX, camPosY, camPosZ;
    float camPosLmt = 1000;
    bool zFlag;
    
    
    
    ofVbo p;
    ofVec3f points[numParticles];
//    ofFloatColor myColor[numParticles];
    ofVec3f _initPos[numParticles];
    ofVec3f _pos[numParticles];
    ofVec3f _frc[numParticles];
    ofVec3f _vel[numParticles];
    
    
    ofImage img;
    static const int WIDTH = 512;
    static const int HEIGHT = 512;
    static const int imgParticles = WIDTH * HEIGHT;
    unsigned char * pixels;
    
    bool emergeMode;
    ofVec3f _startPos[numParticles];
    ofVec3f _currentPos[numParticles];
    float pct[numParticles];
    
    
    
    float x,y;
    float centX = ofRandom(1440);
    float centY = ofRandom(900);
    float ang1, ang2;
    float rad1 = 200;
    float rad2 = 50;
    int vel = 3;
    int timer;
    int imgID;
  
    float prevPointX;
    float prevPointY;
    float prevPointZ;
    
};