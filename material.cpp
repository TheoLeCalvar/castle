#include "material.hpp"

Material::Material(
		vec4 ambient, vec4 diffuse, vec4 specular, 
		float shininess, 
		vec4 emissive, 
		GLuint shader):
	_ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess), _emissive(emissive), _shader(shader)
{}

Material::~Material()
{}

void Material::set(GLenum type, vec4 value)
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

		case GL_EMISSION:
			_emissive = value;
			break;
	}
}

void Material::set(const float shininess)
{
	_shininess = shininess;
}

void Material::set(GLuint shader)
{
	_shader = shader;
}

void Material::update()
{
	if (_shader)
	{
		GLuint ambient_location = glGetUniformLocation(_shader, "ambient_material");
		GLuint diffuse_location = glGetUniformLocation(_shader, "diffuse_material");
		GLuint specular_location = glGetUniformLocation(_shader, "specular_material");
		GLuint emissive_location = glGetUniformLocation(_shader, "emissive_material");

		glUniform3fv(ambient_location, 1, _ambient.v);
		glUniform3fv(diffuse_location, 1, _diffuse.v);
		glUniform3fv(emissive_location, 1, _emissive.v);
		glUniform3fv(specular_location, 1, vec4(_specular, _shininess).v);
	}
}