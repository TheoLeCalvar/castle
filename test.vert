#version 410

layout (location=0) in vec3 vertex_position;
layout (location=1) in vec3 vertex_normal;



out VertexData
{
	vec3 position_eye;
	vec3 normal_eye;
} vertexOut;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;



void main () 
{
	vertexOut.position_eye = vertex_position;
	vertexOut.normal_eye = vec3 (view * model * vec4 (vertex_normal, 0.0));



	gl_Position = projection * view * model * vec4(vertex_position, 1.0);


}
