//#version 120
#ifdef GL_ES
precision highp float;
#endif

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;


void main(){
    
    vec4 color = vec4(0.0);
    vec4 textureColor = vec4(0.0);
    
    color += vec4(0.0,0.9,0.5,0.3) * texture2DRect(tex0, texCoordVarying + vec2(0.0, 1.0));
    color += vec4(0.0,0.9,0.5,0.5) * texture2DRect(tex0, texCoordVarying + vec2(0.0, 0.5));
    color += vec4(0.0,0.9,0.5,0.5) * texture2DRect(tex0, texCoordVarying + vec2(0.0, -0.5));
    color += vec4(0.0,0.9,0.5,0.3) * texture2DRect(tex0, texCoordVarying + vec2(0.0, -1.0));

    color += texture2DRect(tex0, texCoordVarying);
    
    gl_FragColor = color;
    
}