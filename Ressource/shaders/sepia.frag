#version 410


in vec2 st;

out vec4 colorOut;

uniform sampler2D tex;

const float sepiaIntensity = 0.8f;
const mat3 sepiaMatrix = mat3(	0.3588, 0.7044, 0.1368,
								0.2990, 0.5870, 0.1140,
								0.2392, 0.4696, 0.0912);


vec3 sepia(vec3 inColour)
{
	vec3 outColour = inColour * sepiaMatrix;

	return (sepiaIntensity * outColour) + ((1.0 - sepiaIntensity) * inColour);
}


void main()
{

	colorOut = vec4(sepia( texture(tex, st).rgb), 1);


}