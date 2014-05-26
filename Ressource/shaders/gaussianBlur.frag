#version 410

// //calcul la matrice avec un sigma donné
// void gauss(double sigma, int size)
// {
//     double sum = 0;
//     std::cout << "float kernel[] = float[](\n";
//     for(int i = -size/2; i <= size/2; i++)
//     {
//         for(int j = -size/2; j <= size/2; j++)
//         {
//             double val = exp(-(j * j + i * i) / (2.0 * sigma * sigma)) / (2.0 * M_PI * sigma * sigma);
//             sum += val;
//             std::cout << val;
//             if(i != size/2 || j != size/2)
//                 std::cout << ", ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << ");\n\nfloat kernel_correction = " << 1/sum << ";";
// }



in vec2 st;

uniform sampler2D tex;

out vec4 colorOut;


#define KERNEL_SIZE 25
// float kernel[] = float[](
// 0.000480065, 0.00500239, 0.0109262, 0.00500239, 0.000480065, 
// 0.00500239, 0.0521261, 0.113854, 0.0521261, 0.00500239, 
// 0.0109262, 0.113854, 0.24868, 0.113854, 0.0109262, 
// 0.00500239, 0.0521261, 0.113854, 0.0521261, 0.00500239, 
// 0.000480065, 0.00500239, 0.0109262, 0.00500239, 0.000480065
// );

// float kernel_correction = 1.00176;

float kernel[] = float[](
0.00140822, 0.00897264, 0.0166342, 0.00897264, 0.00140822, 
0.00897264, 0.0571701, 0.105987, 0.0571701, 0.00897264, 
0.0166342, 0.105987, 0.196488, 0.105987, 0.0166342, 
0.00897264, 0.0571701, 0.105987, 0.0571701, 0.00897264, 
0.00140822, 0.00897264, 0.0166342, 0.00897264, 0.00140822
);

float kernel_correction = 1.00698;

uniform vec2 pixel_scale; 



void main()
{
	vec3 color = vec3(0,0,0);
	vec2 offset[] = vec2[](
		vec2 (-pixel_scale.s * 2.0, -pixel_scale.t * 2.0),
		vec2 (-pixel_scale.s, -pixel_scale.t * 2.0),
		vec2 (0.0, -pixel_scale.t * 2.0),
		vec2 (pixel_scale.s, -pixel_scale.t * 2.0),
		vec2 (pixel_scale.s * 2.0, -pixel_scale.t * 2.0),

		vec2 (-pixel_scale.s * 2.0, -pixel_scale.t),
		vec2 (-pixel_scale.s, -pixel_scale.t),
		vec2 (0.0, -pixel_scale.t),
		vec2 (pixel_scale.s, -pixel_scale.t),
		vec2 (pixel_scale.s * 2.0, -pixel_scale.t),

		vec2 (-pixel_scale.s * 2.0, 0.0),
		vec2 (-pixel_scale.s, 0.0),
		vec2 (0.0, 0.0),
		vec2 (pixel_scale.s, 0.0),
		vec2 (pixel_scale.s * 2.0, 0.0),

		vec2 (-pixel_scale.s * 2.0, pixel_scale.t),
		vec2 (-pixel_scale.s, pixel_scale.t),
		vec2 (0.0, pixel_scale.t),
		vec2 (pixel_scale.s, pixel_scale.t),
		vec2 (pixel_scale.s * 2.0, pixel_scale.t),

		vec2 (-pixel_scale.s * 2.0, pixel_scale.t * 2.0),
		vec2 (-pixel_scale.s, pixel_scale.t * 2.0),
		vec2 (0.0, pixel_scale.t * 2.0),
		vec2 (pixel_scale.s, pixel_scale.t * 2.0),
		vec2 (pixel_scale.s * 2.0, pixel_scale.t * 2.0)
	);

	for(int i = 0; i < KERNEL_SIZE; ++i)
	{
		color += texture(tex, st + offset[i]).rgb * kernel[i] * kernel_correction;
	}	

	colorOut = vec4(color, 1.0f);
}