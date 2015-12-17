#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    

    // shader
    shaderBlurX.load("shadersGL2/shaderBlurX");
    shaderBlurY.load("shadersGL2/shaderBlurY");


    // buffer
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fboBlurOnePass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fboBlurTwoPass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    fbo.begin();
        ofClear(255, 255, 255, 0);
    fbo.end();
    
    
    // field
    myField.setup();
    
    
    // image & particles
    resetImg(imgID);
    
    
    //node
    testNodes[0].setPosition(200, 200, 400);
    
    
    // camera
    cam.resetTransform();
    cam.clearParent();
    camPosX = 720;
    camPosY = 450;
    camPosZ = -1000;
    cam.setPosition(camPosX, camPosY, camPosZ);
    cam.setParent(testControllers[0]);
    
}

//--------------------------------------------------------------
void ofApp::resetImg(int imgID_){
    
    char str[20];
    
    if (imgID < kNumImgs) {
        imgID_ = imgID;
    }else{
        imgID_ = imgID = 0;
    }
    
    sprintf(str, "test_%02d.jpg", imgID_);
    img.load(str);
    


    pixels = img.getPixels();
    
    
    for (int i = imgParticles+1; i < numParticles; i++){
        _pos[i] = ofVec3f(ofRandom(-1000,1000),
                          ofRandom(-1000,1000),
                          ofRandom(-1000,1000));
        points[i].set(_pos[i]);
        
    }
    
    for (int i=0; i<WIDTH; i++) {
        for (int j=0; j<HEIGHT; j++) {
            
            float r = (float)pixels[j * WIDTH*3 + i * 3] / 256.0;
            float g = (float)pixels[j * WIDTH*3 + i * 3+1] / 256.0;
            float b = (float)pixels[j * WIDTH*3 + i * 3+2] / 256.0;
            float brightness = (r + g + b) / 3.0f;
            
            
            if (pixels[j * WIDTH*3 + i * 3] < 170 ||
                pixels[j * WIDTH*3 + i * 3+2] > 100) {
                
                _initPos[j*WIDTH+i] = _pos[j*WIDTH+i] = ofVec3f(i+200, j+200, brightness * 256.0+400);
                
                points[j*WIDTH+i].set(_pos[j*WIDTH+i]);
                pct[j*WIDTH+i] = 0;
//              myColor[j * WIDTH + i].set(1.0, 1.0, 1.0);
                
            }else{
                
                _pos[j*WIDTH+i] = ofVec3f(ofRandom(1000),
                                          ofRandom(1000),
                                          ofRandom(1000));
                points[j*WIDTH+i].set(_pos[j*WIDTH+i]);
                
            }
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

    for(int i=0; i<kNumControllers; i++) {
        testControllers[i].setPosition(ofVec3f(sin(ofGetElapsedTimef()*0.1),
                                               cos(ofGetElapsedTimef()*0.1),
                                               sin(ofGetElapsedTimef()*0.1)));
        
        testControllers[i].setOrientation(ofVec3f(sin(ofGetElapsedTimef()*0.2),
                                                  cos(ofGetElapsedTimef()*0.2),
                                                  sin(ofGetElapsedTimef()*0.4)));
    }
    
    
    // stirring agent
    ang1 += 3;
    ang2 += 10;
    float rx = centX + (rad1 * cos(ofDegToRad(ang1)));
    float ry = centY + (rad1 * sin(ofDegToRad(ang1)));
    x = rx + (rad2 * cos(ofDegToRad(ang2)));
    y = ry + (rad2 * sin(ofDegToRad(ang2)));
    
    int z = (x+y)/2;
    float diffx = x - prevPointX;
    float diffy = y - prevPointY;
    float diffz = z - prevPointZ;
    
    myField.addVectorCircle((float)x, (float)y, (float)z, diffx*0.5, diffy*0.5,  diffz*0.5, 200, 0.3f);
    
    prevPointX = x;
    prevPointY = y;
    prevPointZ = z;
    
    centX += vel;
    centY += vel;
    if(centX < 0 || centX > 1440){vel *= -1;}
    if(centY < 0 || centY > 900){vel *= -1;}
    
    
    // buffer
    ofEnableAlphaBlending();
    fbo.begin();
        drawFboTest();
    fbo.end();
    
    
    // camera
    cam.lookAt(testNodes[0]);
    
//    float zPosPct;
//    zPosPct += 0.1;
//    float shapedPct = powf(zPosPct, 0.5);
    
    if (zFlag == false) {
        
//      camPosZ = (1.0 - shapedPct) * camPosLmt + (shapedPct) * (camPosLmt*-1);
        camPosZ -=5;
        if (cam.getGlobalPosition().z <= -1000) {
            zFlag = true;
//          zPosPct = 0;
        }
        
    }else if (zFlag == true) {
        
//      camPosZ = (1.0 - shapedPct) * (camPosLmt*-1) + (shapedPct) * camPosLmt;
        camPosZ +=5;
        if (cam.getGlobalPosition().z >= 1000) {
            zFlag = false;
//          zPosPct = 0;
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
        
        _frc[i].x -= _vel[i].x*0.98;
        _frc[i].y -= _vel[i].y*0.98;
        _frc[i].z -= _vel[i].z*0.98;
        
        _vel[i] += _frc[i];
        _pos[i] += _vel[i];
        
        if(!emergeMode){
            points[i].set(_pos[i]);
        }
        
    }
    
    if(emergeMode){
        
        for (int i=0; i<WIDTH; i++) {
            for (int j=0; j<HEIGHT; j++) {
                
                if (pixels[j * WIDTH*3 + i * 3] < 170 ||
                    pixels[j * WIDTH*3 + i * 3+2] > 100) {
                    
                    pct[j*WIDTH+i] += 0.01;
                    _currentPos[j*WIDTH+i] = interpolateByPct(pct[j*WIDTH+i], j*WIDTH+i);
                    
                    if(pct[j*WIDTH+i] < 2.0){
                        points[j*WIDTH+i].set(_currentPos[j*WIDTH+i]);
                    }else{
                        emergeMode = false;
                        pct[j*WIDTH+i] = 0;
                    }
                    
                }
                
            }
        }
        
    }
    
    
    // swap images
    if(timer < 200){
        timer++;
    }else{
        imgID++;
        resetImg(imgID);
        timer = 0;
    }
    
}

//--------------------------------------------------------------
void ofApp::drawFboTest(){
    
    ofEnableAlphaBlending();
    ofClear(255, 255, 255, 0);
    
    cam.begin();
    
        ofSetColor(255);
        p.setVertexData(&points[0], numParticles, GL_DYNAMIC_DRAW);
        p.draw(GL_POINTS, 0, numParticles);
        
        //        ofSetColor(255, 0, 0);
        //        testNodes[0].setScale(5);
        //        testNodes[0].draw();
    
    cam.end();
    
}

//--------------------------------------------------------------
ofVec3f ofApp::interpolateByPct(float _pct, int _id){
    
    ofVec3f pos;
    float shapedPct = powf(_pct, 0.5);
    pos.x = (1.0 - shapedPct) * _startPos[_id].x + (shapedPct) * _initPos[_id].x;
    pos.y = (1.0 - shapedPct) * _startPos[_id].y + (shapedPct) * _initPos[_id].y;
    pos.z = (1.0 - shapedPct) * _startPos[_id].z + (shapedPct) * _initPos[_id].z;
    return pos;
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofHideCursor();
    glPointSize(1.0);
    
    fboBlurOnePass.begin();
    
        ofClear (0, 0);
        shaderBlurX.begin();
        
            shaderBlurX.setUniform1f("blurAmnt", 5);
            ofSetColor (255);
            fbo.draw(0, 0);
        
        shaderBlurX.end();
    
    fboBlurOnePass.end();
    
    
    fboBlurTwoPass.begin();
    
        ofClear ( 0, 0);
        shaderBlurY.begin();
        
            shaderBlurY.setUniform1f("blurAmnt", 1.25);
            ofSetColor(255);
            fboBlurOnePass.draw(0, 0);
        
        shaderBlurY.end();
    
    fboBlurTwoPass.end();
    
    
    ofSetColor(255);
    fbo.draw(0, 0);
    
//    ofSetColor(0, 255, 0);
//    ofDrawCircle(centX, centY, rad1);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == ' '){
        
        for (int i = 0; i < numParticles; i++){
            _pos[i] = ofVec3f(ofRandom(1000),
                              ofRandom(1000),
                              ofRandom(1000));
            points[i].set(_pos[i]);
        }
        
    }else if(key == 'e'){
        
        for (int i=0; i<WIDTH; i++) {
            for (int j=0; j<HEIGHT; j++) {
                _startPos[j*WIDTH+i] = _pos[j*WIDTH+i];
            }
        }
        emergeMode = true;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
