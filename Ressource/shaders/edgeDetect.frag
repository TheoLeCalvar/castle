#version 410


in vec2 st;

uniform sampler2D tex;

out vec4 colorOut;


#define KERNEL_SIZE 9

float kernel[] = float[](
1, 0, -1,
0, 0, 0,
-1,0, 1
);

uniform vec2 pixel_scale; 



void main()
{
	vec3 color = vec3(0,0,0);
	vec2 offset[] = vec2[](
		vec2 (-pixel_scale.s, -pixel_scale.t),
		vec2 (0.0, -pixel_scale.t),
		vec2 (pixel_scale.s, -pixel_scale.t),

		vec2 (-pixel_scale.s, 0.0),
		vec2 (0.0, 0.0),
		vec2 (pixel_scale.s, 0.0),

		vec2 (-pixel_scale.s, pixel_scale.t),
		vec2 (0.0, pixel_scale.t),
		vec2 (pixel_scale.s, pixel_scale.t)
	);

	for(int i = 0; i < KERNEL_SIZE; ++i)
	{
		color += texture(tex, st + offset[i]).rgb * kernel[i];
	}	

	colorOut = vec4(color, 1.0f);
}