#version 410

in VertexData
{
	vec3 position_eye;
	vec3 normal_eye;
} vertexIn;


out vec4 color_out;


uniform mat4 view;

// fixed point light properties
vec3 light_position_world = vec3 (0.0, 2.0, 0.0);
vec3 Ls = vec3 (1.0, 1.0, 1.0); // white specular colour
vec3 Ld = vec3 (0.7, 0.7, 0.7); // dull white diffuse light colour
vec3 La = vec3 (0.2, 0.2, 0.2); // grey ambient colour

// surface reflectance
vec3 Ks = vec3 (1.0, 1.0, 1.0); // fully reflect specular light
vec3 Kd = vec3 (1.0, 0.5, 0.0); // orange diffuse surface reflectance
vec3 Ka = vec3 (1.0, 1.0, 1.0); // fully reflect ambient light
float specular_exponent = 100.0; // specular 'power'


void main () {
	color_out = vec4 (abs(vertexIn.position_eye.xyz), 1.0);


	// ambient intensity
	vec3 Ia = La * Ka;

	// raise light position to eye space
	vec3 light_position_eye = vec3 (view * vec4 (light_position_world, 1.0));
	vec3 distance_to_light_eye = light_position_eye - vertexIn.position_eye;
	vec3 direction_to_light_eye = normalize (distance_to_light_eye);
	float dot_prod = dot (direction_to_light_eye, vertexIn.normal_eye);
	dot_prod = max (dot_prod, 0.0);
	vec3 Id = Ld * Kd * dot_prod; // final diffuse intensity
	

	//specular
	vec3 reflection_eye = reflect (-direction_to_light_eye, vertexIn.normal_eye);
	vec3 surface_to_viewer_eye = normalize (-vertexIn.position_eye);
	float dot_prod_specular = dot (reflection_eye, surface_to_viewer_eye);
	dot_prod_specular = max (dot_prod_specular, 0.0);
	float specular_factor = pow (dot_prod_specular, specular_exponent);
	vec3 Is = Ls * Ks * specular_factor; // final specular intensity
	
	// final colour
	// color_out = vec4 (Is + Id + Ia, 1.0);
}