#ifndef MATERIAL_H
#define MATERIAL_H


#include <GL/glew.h>

#include "math.hpp"

class Material
{
private:
	vec4 			_ambient;
	vec4			_diffuse;
	vec4			_specular;
	float			_shininess;
	vec4			_emissive;
	GLuint		 	_shader;


public:
	Material(
		vec4 	ambient = vec4(0.2, 0.2, 0.2, 1.0),
		vec4 	diffuse = vec4(0.8, 0.8, 0.8, 1.0),
		vec4 	specular = vec4(0.8, 0.8, 0.8, 1.0),
		float 	shininess = 0.0f,
		vec4 	emissive = vec4(0.0, 0.0, 0.0, 1.0),
		GLuint 	location = 0
	);
	~Material();

	void set(GLenum type, vec4 value);
	void set(float shininess);
	void set(GLuint shader);

	void update();
	
};



#endif