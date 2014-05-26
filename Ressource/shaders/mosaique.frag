#version 410

// texture coordinates from vertex shaders
in vec2 st;

// texture sampler
uniform sampler2D tex;

// output fragment colour RGBA
out vec4 frag_colour;

const float sepiaIntensity = 0.8f;
const mat3 sepiaMatrix = mat3(	0.3588, 0.7044, 0.1368,
								0.2990, 0.5870, 0.1140,
								0.2392, 0.4696, 0.0912);


vec3 greyscale(vec3 inColour)
{
	float coef = 0;

	inColour /= 3.0f;

	coef += inColour.r + inColour.g + inColour.b;

	return vec3(coef, coef, coef);  
}

// Converts color to luminance (grayscale)
float luminance( vec3 c )
{
	return dot( c, vec3(0.22, 0.707, 0.071) );
}

vec3 sepia(vec3 inColour)
{
	vec3 outColour = inColour * sepiaMatrix;

	return (sepiaIntensity * outColour) + ((1.0 - sepiaIntensity) * inColour);
}

vec3 invert(vec3 inColour)
{
	return 1 - inColour;
}


void main () {
	// invert colour of right-hand side
	vec3 colour = texture (tex, st).rgb;

	if (st.s >= 1 && st.t >= 1) 
	{
		float lum = luminance(colour);
		colour = vec3(lum, lum, lum);
	}
	else if(st.s <= 1 && st.t >= 1)
	{
		colour = sepia(colour);
	}
	else if(st.s <= 1 && st.t <= 1)
	{
		colour = invert(colour);
	}

	frag_colour = vec4 (colour, 1.0);
}
