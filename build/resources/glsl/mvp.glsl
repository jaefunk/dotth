
// vertex shader
uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
attribute vec4 position;
attribute vec4 color;
varying vec4 out_color;

void main(void)
{
	gl_Position = proj * view * model * position;
    out_color = color;
}

// fragment shader
varying vec4 out_color;
void main (void)
{	
	gl_FragColor.a = out_color.a;
	gl_FragColor.r = out_color.r;
	gl_FragColor.g = out_color.g;
	gl_FragColor.b = out_color.b;
}

// pixel blender
src:GL_SRC_ALPHA
dst:GL_ONE_MINUS_SRC_ALPHA
