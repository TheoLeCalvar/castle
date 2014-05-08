#include "material.hpp"

#include <QDebug>

std::map<const QString, QOpenGLTexture *> Material::_texturesLoaded;

Material::Material(
		vec4 ambient, vec4 diffuse, vec4 specular, 
		float shininess, 
		vec4 emissive,
		const QList<QString> & texFile):
	_ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess), _emissive(emissive), _textures(8, NULL)
{
	initializeOpenGLFunctions();


	for(auto i : texFile)
	{
		addTexture(i);
	}
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

void Material::addTexture(const QString & texFile)
{
	if (texFile != "")
	{
		auto res = _texturesLoaded.find(texFile);

		if (res != _texturesLoaded.end())
		{
			_textures << res->second;
		}
		else
		{
			glActiveTexture(GL_TEXTURE0 + _textures.count());
			QOpenGLTexture *texture = new QOpenGLTexture(QImage(texFile).mirrored());
			//inverse l'image sur les y pour l'avoir dans le sens intuitif

			texture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);

			for(int i = 0; i < 8; ++i)
				if (!_textures.at(i)){
					_textures[i] = texture;
					break;
				}

			_texturesLoaded.insert(std::make_pair(texFile, texture));
		}
	}	
}

void Material::addTextureAt(const QString & texFile, unsigned int indice)
{
	if (texFile != "")
	{
		auto res = _texturesLoaded.find(texFile);

		if (res != _texturesLoaded.end())
		{
			_textures << res->second;
		}
		else
		{
			glActiveTexture(GL_TEXTURE0 + _textures.count());
			QOpenGLTexture *texture = new QOpenGLTexture(QImage(texFile).mirrored());
			//inverse l'image sur les y pour l'avoir dans le sens intuitif

			texture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);


			_textures[indice < 8 ? indice : 7] = texture;


			_texturesLoaded.insert(std::make_pair(texFile, texture));
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

bool Material::hasTexture(unsigned int indice) const
{
	return (indice  < 8 ? (_textures.at(indice) != NULL) : false);
}

void Material::update()
{
	GLuint shader = getActiveShader();

	GLuint useTexture_location = glGetUniformLocation(shader, "useTexture");
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

	if (!_textures.empty())
	{
		unsigned int i = 0;
		glUniform1f(useTexture_location, 1.0);

		for (auto tex : _textures)
		{
			if (tex)
			{
				glActiveTexture(GL_TEXTURE0 + i++);
				tex->bind();
			}
		}

	}
	else
	{
		glUniform1f(useTexture_location, 0.0);
	}
	
}