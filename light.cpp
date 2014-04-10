#include "light.hpp"

Light::Light(
	vec3 position, 
	vec3 ambient, 
	vec3 diffuse, 
	vec3 specular, 
	GLuint shader)
	:
	_position(position), _ambient(ambient), _diffuse(diffuse), _specular(specular), _shader(shader)
{}

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
	}
}

void Light::set(GLuint shader)
{
	_shader = shader;
}


void Light::update()
{
	if (_shader)
	{
		GLuint ambient_location = glGetUniformLocation(_shader, "ambient_light");
		GLuint diffuse_location = glGetUniformLocation(_shader, "diffuse_light");
		GLuint specular_location = glGetUniformLocation(_shader, "specular_light");
		GLuint position_location = glGetUniformLocation(_shader, "position_light");

		glUniform3fv(ambient_location, 1, _ambient.v);
		glUniform3fv(diffuse_location, 1, _diffuse.v);
		glUniform3fv(specular_location, 1, _specular.v);
		glUniform3fv(position_location, 1, _position.v);
	}
}
