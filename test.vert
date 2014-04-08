#version 410


in vec3 vp;
out vec4 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;



void main () 
{




	gl_Position = projection * view * model * vec4 ( vp , 1.0);

	position = 0.5 * (gl_Position + vec4 (1,1,1,1));
}
