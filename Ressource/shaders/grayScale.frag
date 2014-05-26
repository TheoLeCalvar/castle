#version 410


in vec2 st;

out vec4 colorOut;

uniform sampler2D tex;

const vec3 luminanceCoef = vec3(0.2126, 0.7152, 0.0722);


void main()
{
	float lum = dot(texture(tex, st).rgb, luminanceCoef);

	colorOut = vec4(lum, lum, lum, 1);


}