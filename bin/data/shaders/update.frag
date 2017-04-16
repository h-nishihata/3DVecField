#version 120

#extension GL_ARB_texture_rectangle : enable
#extension GL_ARB_draw_buffers : enable

uniform sampler2DRect u_posTex;
uniform sampler2DRect u_velTex;
uniform sampler2DRect u_nextPosTex;
uniform float u_time;
uniform vec2  u_resolution;
uniform vec3  u_mousePos;

void main(void){
    vec2 st = gl_TexCoord[0].st;
    
    vec4 position = texture2DRect(u_posTex,st);
    vec4 vectorField = texture2DRect(u_velTex,st);
    vec4 nextPos  = texture2DRect(u_nextPosTex,st);
    
    vec3 pos  = position.xyz;
    vec3 field  = vectorField.xyz;
    vec3 next = nextPos.xyz;
    
    float posMapAlpha = position.w;
    float velMapAlpha = vectorField.w;
    
    vec2 resolution = u_resolution;
    float time = u_time;    
    vec3 mousePos = u_mousePos;
    float fieldRadius = 0.1 * resolution.x;
    
    
    // get force from pos
    float xPos = gl_FragCoord.x;
    float yPos = gl_FragCoord.y;
    float zPos = gl_FragCoord.z; // clip space (0-1)

    vec3 vel;
    vec3 _frc;
    
    // add force
    _frc += field;
    
    // add damping force
    _frc -= vel*0.9;
    
    // update
    vel += _frc;
    pos += vel;
    
    
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

    
    gl_FragData[0].rgba = vec4(pos, posMapAlpha);
    gl_FragData[1].rgba = vec4(field, velMapAlpha);
    gl_FragData[2].rgba = vec4(next, 0);
}
