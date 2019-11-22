
// vertex shader
attribute vec2 in_uv;
varying vec4 out_color;
varying vec2 out_uv;
void main(void)
{
    out_color = gl_Color;
    out_uv = in_uv;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

// fragment shader
varying vec4 out_color;
varying vec2 out_uv;
uniform sampler2D texture_0;
void main (void)
{
    gl_FragColor = texture2D(texture_0, out_uv) * out_color;
}

// pixel blender
src:
dst:

// end of glsl...
//#define GL_SRC_COLOR 0x0300
//#define GL_ONE_MINUS_SRC_COLOR 0x0301
//#define GL_SRC_ALPHA 0x0302
//#define GL_ONE_MINUS_SRC_ALPHA 0x0303
//#define GL_DST_ALPHA 0x0304
//#define GL_ONE_MINUS_DST_ALPHA 0x0305
//#define GL_DST_COLOR 0x0306
//#define GL_ONE_MINUS_DST_COLOR 0x0307
//#define GL_SRC_ALPHA_SATURATE 0x0308