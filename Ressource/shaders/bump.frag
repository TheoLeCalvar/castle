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

uniform sampler2D normal_tex;
uniform bool use_normal_tex;

uniform sampler2D specular_tex;
uniform bool use_specular_tex;


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


// http://www.thetenthplanet.de/archives/1180
mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv)
{
    // récupère les vecteurs du triangle composant le pixel
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );

    // résout le système linéaire
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

    // construit une trame invariante à l'échelle 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

// http://geeks3d.developpez.com/normal-mapping-glsl/
vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord )
{
    // N, la normale interpolée et
    // V, le vecteur vue (vertex dirigé vers l'œil)
    vec3 map = texture(normal_tex, texcoord ).xyz;
    map = map * 255./127. - 128./127.;
    mat3 TBN = cotangent_frame(N, -V, texcoord);
    return normalize(TBN * map);
}



vec4 lights(vec3 position, vec3 normal, vec2 texCoord)
{
	vec3 Ia = La * Ka;

	vec4 color = vec4(Ia, 1.0);

	for(int i = 0; i < 8; ++i)
	{

		if(Lights[i].enabled)
		{
			// raise light position to eye space
			vec3 light_position_eye = vec3 (view * vec4 (Lights[i].Lp, 1.0));

			float d = distance(position, light_position_eye);
			float att = 1 / (constAtt + linearAtt * d + quadraAtt * d * d);

			if(att > 0.1)
			{
				vec3 distance_to_light_eye = light_position_eye - position;
				vec3 direction_to_light_eye = normalize (distance_to_light_eye);

				vec3 perturbed_normal = normal;

				if(use_normal_tex)
					perturbed_normal = perturb_normal(normal, position, vertexIn.texCoord);

				float dot_prod = dot (direction_to_light_eye, perturbed_normal);
				dot_prod = max (dot_prod, 0.0);
				// dot_prod = abs(dot_prod);
				vec3 Id = vec3(0,0,0);

				if(use_diffuse_tex)
					Id = Lights[i].Ld * texture(diffuse_tex, texCoord).rgb * dot_prod; // final diffuse intensity
				else
					Id = Lights[i].Ld * Kd * dot_prod; // final diffuse intensity
				

				//specular
				vec3 reflection_eye = reflect (-direction_to_light_eye, perturbed_normal);
				vec3 surface_to_viewer_eye = normalize (-position);
				float dot_prod_specular = dot (reflection_eye, surface_to_viewer_eye);
				dot_prod_specular = max (dot_prod_specular, 0.0);
				float specular_factor = pow (dot_prod_specular, specular_exponent);

				vec3 Is = vec3(0,0,0);
				if(use_specular_tex)
					Is = Lights[i].Ls * texture(specular_tex, texCoord).rgb * specular_factor; // final specular intensity
				else
					Is = Lights[i].Ls * Ks * specular_factor; // final specular intensity

				


				// final colour
				color += att * vec4 (Is + Id, 1.0);
			}
		}
	}

	return color;
}

void main () 
{
	color_out = lights(vertexIn.position_eye, vertexIn.normal_eye, vertexIn.texCoord);
}
