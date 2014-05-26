#version 410


in vec2 st;

out vec4 colorOut;

uniform sampler2D tex;



void main()
{

	colorOut = vec4(1 - texture(tex, st).rgb, 1);


}