
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);

    
    // buffer
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
        ofClear(255, 255, 255, 0);
    fbo.end();
    
    
    // field
    myField.setup();


    // particles
    for (int i = 0; i < numParticles; i++){
        _pos[i] = ofVec3f(ofRandom(1000),
                                 ofRandom(1000),
                                 ofRandom(1000));
        points[i].set(_pos[i]);

    }


    // camera
    cam.resetTransform();
    camPosX = 720;
    camPosY = 450;
    camPosZ = 0;
    cam.setPosition(camPosX, camPosY, camPosZ);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofEnableAlphaBlending();
    
    
    fbo.begin();
        drawFboTest();
    fbo.end();
    
    
    // camera
    cam.lookAt(ofVec3f(720,450,500));
    
    if (xFlag == false) {
        camPosX --;
        if (cam.getGlobalPosition().x < -100) {
            xFlag = true;
        }
    }else if (xFlag == true) {
        camPosX ++;
        if (cam.getGlobalPosition().x > 1500) {
            xFlag = false;
        }
    }
    
    if (yFlag == false) {
        camPosY --;
        if (cam.getGlobalPosition().y < -100) {
            yFlag = true;
        }
    }else if (yFlag == true) {
        camPosY ++;
        if (cam.getGlobalPosition().y > 1000) {
            yFlag = false;
        }
    }
    
    if (zFlag == false) {
        camPosZ --;
        if (cam.getGlobalPosition().z < -800) {
            zFlag = true;
        }
    }else if (zFlag == true) {
        camPosZ ++;
        if (cam.getGlobalPosition().z > 800) {
            zFlag = false;
        }
    }
    cam.setPosition(camPosX, camPosY, camPosZ);
    

    // particles
    for (unsigned int i=0; i<numParticles; i++) {
        
        _frc[i].set(0,0,0);
        
        ofVec3f frc;
        frc = myField.getForceAtPosition(points[i]);
        
        _frc[i].x += frc.x;
        _frc[i].y += frc.y;
        _frc[i].z += frc.z;
        
        _frc[i].x -= _vel[i].x*0.9;
        _frc[i].y -= _vel[i].y*0.9;
        _frc[i].z -= _vel[i].z*0.9;
        
        _vel[i] += _frc[i];
        _pos[i] += _vel[i];
        
        points[i].set(_pos[i]);
        
    }

}

//--------------------------------------------------------------
void ofApp::drawFboTest(){
    
    ofHideCursor();
    ofEnableAlphaBlending();
    
    
    ofClear(255, 255, 255, 0);
    
    cam.begin();
    
        ofSetColor(255);
        p.setVertexData(&points[0], numParticles, GL_DYNAMIC_DRAW);
        p.draw(GL_POINTS, 0, numParticles);
    
    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofHideCursor();
    glPointSize(3.0);
    ofSetColor(255, 255, 255);
    fbo.draw(0,0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    int z = (x+y)/2;
    
    float diffx = x - prevMouseX;
    float diffy = y - prevMouseY;
    float diffz = z - prevMouseZ;
    
    myField.addVectorCircle((float)x, (float)y, (float)z, diffx*0.5, diffy*0.5,  diffz*0.5, 500, 1.2f);
    
    prevMouseX = x;
    prevMouseY = y;
    prevMouseZ = z;
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}