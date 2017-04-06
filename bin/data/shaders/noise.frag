vec2 resolution = vec2(1440, 900);
vec2 fieldResolution = vec2(60, 40);

vec2 field[60*40];

void setupField(){    
    for (int i = 0; i < fieldResolution.x * fieldResolution.y; i++){
        vec2 pt = vec2(0, 0);
//        field[i] = pt;
    }
}

vec2 getForceAtPosition(float xPos, float yPos){
    vec2 frc = vec2(0, 0);
    
    float xPct = xPos / resolution.x;
    float yPct = yPos / resolution.y;
    
    // if we are less then 0 or greater then 1 in x or y, return no force.
    if ((xPct < 0.0 || xPct > 1.0) || (yPct < 0.0 || yPct > 1.0)){
        return frc;
    }
    
    // where are we in the array
    float fieldPosX = xPct * fieldResolution.x;
    float fieldPosY = yPct * fieldResolution.y;
    
    // saftey :)
    fieldPosX = max(0.0, min(fieldPosX, fieldResolution.x-1.0));
    fieldPosY = max(0.0, min(fieldPosY, fieldResolution.y-1.0));
    
    // pos in array
    int pos = int(fieldPosY * fieldResolution.x + fieldPosX);
    
    frc = vec2(field[pos].x * 0.1, field[pos].y * 0.1 );  // scale here as values are pretty large.
    
    return frc;
}


void addVectorCircle(float x, float y, float vx, float vy, float radius, float strength){
    
    // x y and radius are in external dimensions.  Let's put them into internal dimensions:
    // first convert to pct:
    
    float pctx			= x / resolution.x;
    float pcty			= y / resolution.y;
    float radiusPct		= radius / resolution.x;
    
    // then, use them here:
    int fieldPosX		= int(pctx * fieldResolution.x);
    int fieldPosY		= int(pcty * fieldResolution.y);
    float fieldRadius	= radiusPct * fieldResolution.x;
    
    // we used to do this search through every pixel, ie:
    //    for (int i = 0; i < fieldWidth; i++){
    //    for (int j = 0; j < fieldHeight; j++){
    // but we can be smarter :)
    // now, as we search, we can reduce the "pixels" we look at by
    // using the x y +/- radius.
    // use min and max to make sure we don't look over the edges
 
    int startx	= int(max(fieldPosX - fieldRadius, 0.0));
    int starty	= int(max(fieldPosY - fieldRadius, 0.0));
    int endx	= int(min(fieldPosX + fieldRadius, fieldResolution.x));
    int endy	= int(min(fieldPosY + fieldRadius, fieldResolution.y));

    
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
            
            int pos = int(j * fieldResolution.x + i);
            float dist = sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
            if (dist < 0.0001) dist = 0.0001;  // since we divide by distance, do some checking here, devide by 0 is BADDDD
            
            if (dist < fieldRadius){
                float pct = 1.0f - (dist / fieldRadius);
                float strongness = strength * pct;
                field[pos].x += vx * strongness;
                field[pos].y += vy * strongness;
            }
        }
    }
//    return 0;
}

