#version 120
#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect u_currPosTex;
uniform sampler2DRect u_currColTex;

void main() {
    vec2 st = gl_MultiTexCoord0.xy;
    vec3 pos = texture2DRect( u_currPosTex, st ).xyz;
    
    gl_PointSize = 1.0;
    gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
    
    /*
    // gaussian test
    float width = 7.2;
    
    vec2 texcoordM  = st;
    vec2 texcoordB0 = st - width;
    vec2 texcoordF0 = st + width;
    vec2 texcoordB1 = st - width * 2.0;
    vec2 texcoordF1 = st + width * 2.0;
    vec2 texcoordB2 = st - width * 3.0;
    vec2 texcoordF2 = st + width * 3.0;
    
    vec4 sampleM  = texture2DRect(u_currColTex, texcoordM);
    vec4 sampleB0 = texture2DRect(u_currColTex, texcoordB0);
    vec4 sampleF0 = texture2DRect(u_currColTex, texcoordF0);
    vec4 sampleB1 = texture2DRect(u_currColTex, texcoordB1);
    vec4 sampleF1 = texture2DRect(u_currColTex, texcoordF1);
    vec4 sampleB2 = texture2DRect(u_currColTex, texcoordB2);
    vec4 sampleF2 = texture2DRect(u_currColTex, texcoordF2);
     
     gl_FrontColor = 0.1752 * sampleM + 0.1658 * (sampleB0 + sampleF0) + 0.1403 * (sampleB1 + sampleF1) + 0.1063 * (sampleB2 + sampleF2);
    */
    
    /*
    // advect test
    vec4 tex11 = texture2DRect(u_currColTex, gl_MultiTexCoord0.xy );
    vec4 tex21 = texture2DRect(u_currColTex, gl_MultiTexCoord0.zy );
    vec4 tex12 = texture2DRect(u_currColTex, gl_MultiTexCoord0.xw );
    vec4 tex22 = texture2DRect(u_currColTex, gl_MultiTexCoord0.zw );
    
    gl_FrontColor = mix(mix(tex11, tex21, st.x), mix(tex12, tex22, st.x), st.y);
    */
    
    vec3 col = texture2DRect(u_currColTex, st).xyz;
    gl_FrontColor = vec4(col, 1.0);
}
