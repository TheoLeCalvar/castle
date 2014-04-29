#ifndef LIGHT_H
#define LIGHT_H 

#include <QOpenGLFunctions_3_2_Core>

#include "helper.hpp"

class Light: protected QOpenGLFunctions_3_2_Core
{
private:
	vec3 	_position;
	static vec3	_ambient;
	vec3	_diffuse;
	vec3 	_specular;
	char 	_lightNum;


public:
	Light(
		vec3 position = vec3(0.0, 0.0, 0.0), 
		vec3 diffuse = vec3(0.8, 0.8, 0.8), 
		vec3 specular = vec3(0.8, 0.8, 0.8),
		char number = 0
		);
	~Light();


	void set(GLenum type, vec3 value);
	void setNumber(char num);

	void update();
	
};

#endif
