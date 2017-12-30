#version 120

#extension GL_ARB_texture_rectangle : enable
#extension GL_ARB_draw_buffers : enable

uniform sampler2DRect u_currPosTex;
uniform sampler2DRect u_currColTex;
uniform sampler2DRect u_velTex;
uniform sampler2DRect u_nextPosTex;
uniform sampler2DRect u_nextColTex;
uniform vec2  u_resolution;
uniform vec3  u_mousePos;
uniform int   u_overdose;

float ang1, ang2;
float rad1 = 200;
float rad2 = 50;
float prevPointX, prevPointY, prevPointZ;
float centX, centY;
float x, y, z;
float vel = 3;

void main(void){
    vec2 st = gl_TexCoord[0].st;
    
    vec3 currPos  = texture2DRect(u_currPosTex,st).xyz;
    vec3 currCol = texture2DRect(u_currColTex, st).xyz;
    vec3 field  = texture2DRect(u_velTex,st).xyz;
    vec3 nextPos = texture2DRect(u_nextPosTex,st).xyz;
    vec3 nextCol = texture2DRect(u_nextColTex, st).xyz;
    
    float posMapAlpha = texture2DRect(u_currPosTex,st).w;
    float velMapAlpha = texture2DRect(u_currPosTex,st).w;
    
    vec3 mousePos = u_mousePos;
    vec2 resolution = u_resolution;
    float fieldRadius = 0.1 * resolution.x;
    
    int overdose = u_overdose;
//    float lerpSpeed = 0.01;
    float centX = resolution.x * 0.5;
    float centY = resolution.y * 0.5;

    
    // get force from pos
    float xPos = gl_FragCoord.x;
    float yPos = gl_FragCoord.y;
    float zPos = gl_FragCoord.z; // clip space (0-1)
    

    if(overdose == 0){
        // normal mdde
        currPos += field*0.9;
        
    }else if(overdose == 1){
        
        field = vec3(0, 0, 0);
        currPos = nextPos;
        currCol = nextCol;
        /*
        // morphing mode
        if(abs(nextPos.x - currPos.x)>0.1){ field.x = (nextPos.x - currPos.x)*0.05; }else{ field.x=0; }
        if(abs(nextPos.y - currPos.y)>0.1){ field.y = (nextPos.y - currPos.y)*0.05; }else{ field.y=0; }
        if(abs(nextPos.z - currPos.z)>0.1){ field.z = (nextPos.z - currPos.z)*0.05; }else{ field.z=0; }
        // lerp colors
        if(currCol.r < nextCol.r){
            currCol.r += lerpSpeed;
        }else{
            currCol.r -= lerpSpeed;
        }
        if(currCol.g < nextCol.g){
            currCol.g += lerpSpeed;
        }else{
            currCol.g -= lerpSpeed;
        }
        if(currCol.b < nextCol.b){
            currCol.b += lerpSpeed;
        }else{
            currCol.b -= lerpSpeed;
        }*/
    }
    
    
    // add vector circle
    float dist = sqrt((mousePos.x-xPos)*(mousePos.x-xPos) + (mousePos.y-yPos)*(mousePos.y-yPos) + (mousePos.z-zPos)*(mousePos.z-zPos));
    
    if (dist < 0.0001) dist = 0.0001;
    
    if (dist < fieldRadius){
        float pct = 1.0f - (dist / fieldRadius);
        float strongness = 0.9 * pct;
        float unit_px = ( mousePos.x - xPos) / dist;
        float unit_py = ( mousePos.y - yPos) / dist;
        float unit_pz = ( mousePos.z - zPos) / dist;
        field.x += unit_px * strongness;
        field.y += unit_py * strongness;
        field.z += unit_pz * strongness * 5.0;
    }
    
    /* stirring agent
    ang1 += 3;
    ang2 += 10;
    float rx = centX + (rad1 * cos(ang1*0.017));
    float ry = centY + (rad1 * sin(ang1*0.017));
    x = rx + (rad2 * cos(ang2*0.017));
    y = ry + (rad2 * sin(ang2*0.017));
    z = 900 * (x/1440) - 450;   // -450 < z < 450
    
    mousePos = vec3(x, y, z);
    
//    float diffx = x - prevPointX;
//    float diffy = y - prevPointY;
//    float diffz = z - prevPointZ;
//    prevPointX = x;
//    prevPointY = y;
//    prevPointZ = z;

    centX += vel;
    centY += vel;
//    if(centX < 0+rad1 || centX > 1440-rad1){vel *= -1;}
//    if(centY < 0+rad1 || centY > 900-rad1){vel *= -1;}
    */
    
    gl_FragData[0].rgba = vec4(currPos, posMapAlpha);
    gl_FragData[1].rgba = vec4(currCol, 1.0);
    gl_FragData[2].rgba = vec4(field, velMapAlpha);
    gl_FragData[3].rgba = vec4(nextPos, 1.0);
    gl_FragData[4].rgba = vec4(nextCol, 1.0);
}
