#include "light.hpp"

#include <QDebug>

vec3 Light::_ambient;

Light::Light(
	vec3 position, 
	vec3 diffuse, 
	vec3 specular,
	char number)
	:
	_position(position), _diffuse(diffuse), _specular(specular), _lightNum(number)
{
	initializeOpenGLFunctions();


}

Light::~Light()
{}

void Light::set(GLenum type, vec3 value)
{
	switch (type)
	{
		case GL_AMBIENT:
			_ambient = value;
			break;

		case GL_DIFFUSE:
			_diffuse = value;
			break;

		case GL_SPECULAR:
			_specular = value;
			break;

		case GL_POSITION:
			_position = value;
			break;
	}
}

vec3 Light::get(GLenum type) const
{
	switch (type)
	{
		case GL_AMBIENT:
			return _ambient;

		case GL_DIFFUSE:
			return 	_diffuse;

		case GL_SPECULAR:
			return _specular;

		case GL_POSITION:
			return _position;

		default:
			return vec3();
	}
}

vec3& Light::get(GLenum type)
{
	switch (type)
	{
		case GL_AMBIENT:
			return _ambient;

		case GL_DIFFUSE:
			return 	_diffuse;

		case GL_SPECULAR:
			return _specular;

		case GL_POSITION:
			return _position;
	}
}

void Light::setNumber(char num)
{
	_lightNum = num;
}


void Light::update()
{
	GLuint 	shader = getActiveShader();
	char	name[] = "Lights[0].Ld";
	char 	enable[] = "Lights[0].enabled";
	//modification du 0 pour avoir le bon indice
	enable[7] += _lightNum;
	name[7] += _lightNum;

	GLint enabled_location = glGetUniformLocation(shader, enable);
	GLint ambient_location = glGetUniformLocation(shader, "La");
	GLint diffuse_location = glGetUniformLocation(shader, name);

	name[11] = 's';
	GLint specular_location = glGetUniformLocation(shader, name);

	name[11] = 'p';
	GLint position_location = glGetUniformLocation(shader, name);


	glUniform1i(enabled_location, 1);
	glUniform3fv(ambient_location, 1, _ambient.v);
	glUniform3fv(diffuse_location, 1, _diffuse.v);
	glUniform3fv(specular_location, 1, _specular.v);
	glUniform3fv(position_location, 1, _position.v);

	openGL_check_error();

}
