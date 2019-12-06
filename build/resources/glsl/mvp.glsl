
// vertex shader
uniform mat4 model;
uniform mat4 view_pers;
attribute vec4 vertex;
attribute vec4 color;
varying vec4 out_color;

void main(void)
{
	gl_Position = view_pers * model * vertex;
    out_color = color;
}

// fragment shader
varying vec4 out_color;
void main (void)
{	
	gl_FragColor.r = out_color.r;
	gl_FragColor.g = out_color.g;
	gl_FragColor.b = out_color.b;
	gl_FragColor.a = out_color.a;
}

// pixel blender
src:GL_SRC_ALPHA
dst:GL_ONE_MINUS_SRC_ALPHA
