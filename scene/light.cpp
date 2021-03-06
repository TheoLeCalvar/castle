#include "light.hpp"

#include <QDebug>

vec3 Light::_ambient;

Light::Light(
	vec3 position, 
	vec3 diffuse, 
	vec3 specular)
	:
	_position(position), _diffuse(diffuse), _specular(specular)
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

// désactiver les lumières non utilisées
void Light::disable(unsigned char number)
{
	QOpenGLFunctions_3_2_Core f;
	f.initializeOpenGLFunctions();

	GLuint 	shader = getActiveShader();
	char 	enable[] = "Lights[0].enabled";
	enable[7] += number;

	GLint enabled_location = f.glGetUniformLocation(shader, enable);

	f.glUniform1i(enabled_location, 0);

	openGL_check_error();
}


void Light::update(unsigned char number)
{
	GLuint 	shader = getActiveShader();
	char	name[] = "Lights[0].Ld";
	char 	enable[] = "Lights[0].enabled";
	//modification du 0 pour avoir le bon indice
	enable[7] += number;
	name[7] += number;

	GLint enabled_location = glGetUniformLocation(shader, enable);
	GLint diffuse_location = glGetUniformLocation(shader, name);

	name[11] = 's';
	GLint specular_location = glGetUniformLocation(shader, name);

	name[11] = 'p';
	GLint position_location = glGetUniformLocation(shader, name);


	glUniform1i(enabled_location, 1);
	glUniform3fv(diffuse_location, 1, _diffuse.v);
	glUniform3fv(specular_location, 1, _specular.v);
	glUniform3fv(position_location, 1, _position.v);

	openGL_check_error();

}

void Light::updateAmbient()
{
	QOpenGLFunctions_3_2_Core f;
	f.initializeOpenGLFunctions();

	GLuint 	shader = getActiveShader();

	GLint ambient_location = f.glGetUniformLocation(shader, "La");

	f.glUniform3fv(ambient_location, 1, _ambient.v);

	openGL_check_error();
}
