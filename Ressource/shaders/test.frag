#version 410

layout (location=0) out vec4 color_out;

in VertexData
{
	vec3 position_eye;
	vec3 normal_eye;
	vec2 texCoord;
} vertexIn;


struct light
{
	vec3 Lp;
	vec3 Ls;
	vec3 Ld;
	bool enabled;
};


uniform sampler2D diffuse_tex;
uniform bool use_diffuse_tex;

uniform mat4 view;

uniform vec3 La = vec3(0.2, 0.2, 0.2);

uniform light Lights[8];

uniform float constAtt = 1.0;
uniform float linearAtt = 0.02;
uniform float quadraAtt = 0.0;



// surface reflectance
uniform vec3 Ks = vec3 (1.0, 1.0, 1.0); // fully reflect specular light
uniform vec3 Kd = vec3 (1.0, 0.5, 0.0); // orange diffuse surface reflectance
uniform vec3 Ka = vec3 (1.0, 1.0, 1.0); // fully reflect ambient light
uniform float specular_exponent = 100.0; // specular 'power'


vec4 lights()
{
	vec3 Ia = La * Ka;

	vec4 color = vec4(Ia, 1.0);

	for(int i = 0; i < 8; ++i)
	{

		if(Lights[i].enabled)
		{
			// raise light position to eye space
			vec3 light_position_eye = vec3 (view * vec4 (Lights[i].Lp, 1.0));

			float d = distance(vertexIn.position_eye, light_position_eye);
			float att = 1 / (constAtt + linearAtt * d + quadraAtt * d * d);

			if(att > 0.1)
			{
				vec3 distance_to_light_eye = light_position_eye - vertexIn.position_eye;
				vec3 direction_to_light_eye = normalize (distance_to_light_eye);
				float dot_prod = dot (direction_to_light_eye, vertexIn.normal_eye);
				dot_prod = max (dot_prod, 0.0);
				// dot_prod = abs(dot_prod);
				vec3 Id = vec3(0,0,0);

				if(use_diffuse_tex)
					Id = Lights[i].Ld * texture(diffuse_tex, vertexIn.texCoord).rgb * dot_prod; // final diffuse intensity
				else
					Id = Lights[i].Ld * Kd * dot_prod; // final diffuse intensity
				

				//specular
				vec3 reflection_eye = reflect (-direction_to_light_eye, vertexIn.normal_eye);
				vec3 surface_to_viewer_eye = normalize (-vertexIn.position_eye);
				float dot_prod_specular = dot (reflection_eye, surface_to_viewer_eye);
				dot_prod_specular = max (dot_prod_specular, 0.0);
				float specular_factor = pow (dot_prod_specular, specular_exponent);
				vec3 Is = Lights[i].Ls * Ks * specular_factor; // final specular intensity
				


				// final colour
				color += att * vec4 (Is + Id, 1.0);
			}
		}
	}

	return color;
}

void main () 
{
	color_out = lights();
}
