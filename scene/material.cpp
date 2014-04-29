#include "material.hpp"

#include <QDebug>

std::map<const QString, QOpenGLTexture *> Material::_texturesLoaded;

Material::Material(
		vec4 ambient, vec4 diffuse, vec4 specular, 
		float shininess, 
		vec4 emissive,
		const QString & texFile):
	_ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess), _emissive(emissive), _texture(0)
{
	initializeOpenGLFunctions();

	set(texFile);
}

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

void Material::set(const QString & texFile)
{
	if (texFile != "")
	{
		auto res = _texturesLoaded.find(texFile);

		if (res != _texturesLoaded.end())
		{
			_texture = res->second;
			qDebug() << "Texture found";
		}
		else
		{
			//inverse l'image sur les y pour l'avoir dans le sens intuitif
			_texture = new QOpenGLTexture(QImage(texFile).mirrored());

			qDebug() << "Texture loaded" << _texture;

			_texturesLoaded.insert(std::make_pair(texFile, _texture));
		}
	}	
}

vec4 Material::get(GLenum type)
{
	switch (type)
	{
		case GL_AMBIENT:
			return _ambient;

		case GL_DIFFUSE:
			return _diffuse;

		case GL_SPECULAR:
			return _specular;

		case GL_EMISSION:
			return _emissive;

		default:
			return vec4();
	}
}

float Material::shininess() const
{
	return _shininess;
}

bool Material::hasTexture() const
{
	return (_texture != NULL);
}

void Material::update()
{
	GLuint shader = getActiveShader();

	GLuint ambient_location = glGetUniformLocation(shader, "Ka");
	GLuint diffuse_location = glGetUniformLocation(shader, "Kd");
	GLuint specular_location = glGetUniformLocation(shader, "Ks");
	GLuint specular_exponnent_location = glGetUniformLocation(shader, "specular_exponent");
	// GLuint emissive_location = glGetUniformLocation(shader, "Ke");

	glUniform3fv(ambient_location, 1, _ambient.v);
	glUniform3fv(diffuse_location, 1, _diffuse.v);
	glUniform3fv(specular_location, 1, _specular.v);
	glUniform1f(specular_exponnent_location, _shininess);
	// glUniform3fv(emissive_location, 1, _emissive.v);

	if (_texture)
	{
		// qDebug() << _texture;
		glBindTexture(GL_TEXTURE_2D, _texture->textureId());
	}
	
}