
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
src:GL_SRC_ALPHA
dst:GL_ONE_MINUS_SRC_ALPHA
