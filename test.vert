#version 410

layout (location=0) in vec3 vertex_position;
layout (location=1) in vec3 vertex_normal;
layout (location=2) in vec2 vertex_texCoord;



out VertexData
{
	vec3 position_eye;
	vec3 normal_eye;
	vec2 texCoord;
} vertexOut;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;



void main () 
{
	vertexOut.position_eye = vec3 ( view * model * vec4(vertex_position, 1.0));
	vertexOut.normal_eye = vec3 (view * model * vec4 (vertex_normal, 0.0));
	vertexOut.texCoord = vertex_texCoord;



	gl_Position = projection * view * model * vec4(vertex_position, 1.0);


}
