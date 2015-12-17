#include "FlowField.hpp"

FlowField::FlowField() {
    
}


void FlowField::setup() {
    
    fieldWidth = width;
    fieldHeight = height;
    fieldDepth = depth;
    
    //    clear();
    
    for( int z = 0; z < fieldDepth; z++){
        ofVec3f dir;
        
        for( int i=0; i<fieldWidth * fieldHeight; i++){
            dir.set(0, 0, 0);
            field[z][i].set(dir);
            
        }
    }
    
}


ofVec3f FlowField::getForceAtPosition(ofVec3f pos) {
    
    ofVec3f newPos;
    newPos.set(0, 0, 0);
    
    float pctX = pos.x / ofGetWidth();
    float pctY = pos.y / ofGetHeight();
    float pctZ = pos.z / (ofGetWidth() + ofGetHeight())/2;
    
    
    if ((pctX < 0 || pctX > 1) || (pctY < 0 || pctY > 1) || (pctZ < 0 || pctZ > 1)){
        return newPos;
    }
    
    /*
     ofVec3f bouncePos;
     if (pctX < 0 || pctX > 1){
     bouncePos.set(pos.x*-1, pos.y, pos.z);
     return bouncePos;
     
     }else if(pctY < 0 || pctY > 1){
     bouncePos.set(pos.x, pos.y*-1, pos.z);
     return bouncePos;
     
     }else if (pctZ < 0 || pctZ > 1){
     bouncePos.set(pos.x, pos.y, pos.z*-1);
     return bouncePos;
     
     }
     */
    
    int fieldPosX = (int)(pctX * fieldWidth);
    int fieldPosY = (int)(pctY * fieldHeight);
    int fieldPosZ = (int)(pctZ * fieldDepth);
    
    
    fieldPosX = MAX(0, MIN(fieldPosX, fieldWidth-1));
    fieldPosY = MAX(0, MIN(fieldPosY, fieldHeight-1));
    fieldPosZ = MAX(0, MIN(fieldPosZ, fieldDepth-1));
    
    
    int posInArray = fieldPosY * fieldWidth + fieldPosX;
    
    newPos.set(field[fieldPosZ][posInArray].x * 0.1, field[fieldPosZ][posInArray].y * 0.1, field[fieldPosZ][posInArray].z * 0.1);
    
    
    return newPos;
    
}


void FlowField::addVectorCircle(float x, float y, float z, float vx, float vy, float vz, float radius, float strength){
    
    // x y and radius are in external dimensions.  Let's put them into internal dimensions:
    // first convert to pct:
    float pctx			= x / ofGetWidth();
    float pcty			= y / ofGetHeight();
    float pctz          = z / (ofGetWidth()+ofGetHeight())/2;
    float radiusPct		= radius / ofGetWidth();
    
    
    // then, use them here:
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
    int fieldPosZ		= (int)(pctz * (float)fieldDepth);
    float fieldRadius	= (float)(radiusPct * fieldWidth);
    
    
    // we used to do this search through every pixel, ie:
    //    for (int i = 0; i < fieldWidth; i++){
    //    for (int j = 0; j < fieldHeight; j++){
    // but we can be smarter :)
    // now, as we search, we can reduce the "pixels" we look at by
    // using the x y +/- radius.
    // use min and max to make sure we don't look over the edges
    int startx	= MAX(fieldPosX - fieldRadius, 0);
    int starty	= MAX(fieldPosY - fieldRadius, 0);
    int startz	= MAX(fieldPosZ - fieldRadius, 0);
    int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
    int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
    int endz	= MIN(fieldPosZ + fieldRadius, fieldDepth);
    
    for (int i = startz; i < endz; i++){
        for (int j = startx; j < endx; j++){
            for (int k = starty; k < endy; k++){
                
                int pos = k * fieldWidth + j;
                
                ofVec3f posCursor(fieldPosX, fieldPosY, fieldPosZ);
                ofVec3f posVec(j,k,i);
                
                float distance = posCursor.distance(posVec);
                
                //                float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                //                                             (fieldPosY-j)*(fieldPosY-j));
                
                
                if (distance < 0.0001) distance = 0.0001;  // since we divide by distance, do some checking here, devide by 0 is BADDDD
                
                
                if (distance < fieldRadius){
                    
                    float pct = 1.0f - (distance / fieldRadius);
                    float strongness = strength * pct;
                    
                    
                    field[i][pos].x += vx * strongness;
                    field[i][pos].y += vy * strongness;
                    field[i][pos].z += vz * strongness;
                    
                }
                
            }
        }
    }
    
}


void FlowField::clear(){
    
    for (int i = 0; i < fieldDepth; i++){
        for (int j = 0; j < fieldWidth*fieldHeight; j++){
            field[j][i].set(0,0,0);
        }
    }
    
}
