#include "material.hpp"

#include <QDebug>

std::map<const QString, QOpenGLTexture *> Material::_texturesLoaded;

Material::Material(
		vec4 ambient, vec4 diffuse, vec4 specular, 
		float shininess, 
		vec4 emissive
		):
	_ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess), _emissive(emissive), _diffuse_texture(NULL), _specular_texture(NULL), _normal_texture(NULL)
{
	initializeOpenGLFunctions();
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

void Material::addTexture(const QString & texFile, unsigned char type)
{
	if (texFile != "")
	{
		auto res = _texturesLoaded.find(texFile);

		if (res != _texturesLoaded.end())
		{
			switch(type)
			{
				case DIFFUSE:
					_diffuse_texture = res->second;
					break;

				case SPECULAR:
					_specular_texture = res->second;
					break;

				case NORMAL:
					_normal_texture = res->second;
					break;
			}
		}
		else
		{
			QOpenGLTexture *texture = new QOpenGLTexture(QImage(texFile).mirrored());
			//inverse l'image sur les y pour l'avoir dans le sens intuitif

			texture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);


			switch(type)
			{
				case DIFFUSE:
					_diffuse_texture = texture;
					break;

				case SPECULAR:
					_specular_texture = texture;
					break;

				case NORMAL:
					_normal_texture = texture;
					break;
			}


			_texturesLoaded.insert(std::make_pair(texFile, texture));
		}
	}	
}

vec4 Material::get(GLenum type) const
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

vec4& Material::get(GLenum type)
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


	}
}

float Material::shininess() const
{
	return _shininess;
}

bool Material::hasTexture(unsigned char type) const
{
	switch(type)
	{
		case 0:
			return (_diffuse_texture != NULL);
			break;

		case 1:
			return (_specular_texture != NULL);
			break;

		case 2:
			return (_normal_texture != NULL);
			break;
	}

	return false;
}

bool Material::hasDiffuseTexture() const
{
	return (_diffuse_texture != NULL);
}

bool Material::hasSpecularTexture() const
{
	return (_specular_texture != NULL);
}

bool Material::hasNormalTexture() const
{
	return (_normal_texture != NULL);
}

void Material::update()
{
	GLuint shader = getActiveShader();

	GLint 	ambient_location = glGetUniformLocation(shader, "Ka");
	GLint 	diffuse_location = glGetUniformLocation(shader, "Kd");
	GLint 	specular_location = glGetUniformLocation(shader, "Ks");
	GLint 	specular_exponnent_location = glGetUniformLocation(shader, "specular_exponent");
	// GLint 	emissive_location = glGetUniformLocation(shader, "Ke");

	GLint 	use_diffuse_texture_location = glGetUniformLocation(shader, "use_diffuse_tex");
	GLint   diffuse_texture_location = glGetUniformLocation(shader, "diffuse_tex");

	GLint 	use_specular_texture_location = glGetUniformLocation(shader, "use_specular_tex");
	GLint   specular_texture_location = glGetUniformLocation(shader, "specular_tex");

	GLint 	use_normal_texture_location = glGetUniformLocation(shader, "use_normal_tex");
	GLint   normal_texture_location = glGetUniformLocation(shader, "normal_tex");
	

	glUniform3fv(ambient_location, 1, _ambient.v);
	glUniform3fv(diffuse_location, 1, _diffuse.v);
	glUniform3fv(specular_location, 1, _specular.v);
	glUniform1f(specular_exponnent_location, _shininess);
	// glUniform3fv(emissive_location, 1, _emissive.v);

	if (hasDiffuseTexture() && (diffuse_texture_location >=0))
	{
		glUniform1f(use_diffuse_texture_location, 1.0);

		glActiveTexture(GL_TEXTURE0);
		glUniform1i (diffuse_texture_location, 0);
		_diffuse_texture->bind();
	}
	else
	{
		glUniform1f(use_diffuse_texture_location, 0.0);
	}

	if (hasSpecularTexture() && (specular_texture_location >=0))
	{
		glUniform1f(use_specular_texture_location, 1.0);

		glActiveTexture(GL_TEXTURE0 + 1);
		glUniform1i (specular_texture_location, 1);
		_specular_texture->bind();
	}
	else
	{
		glUniform1f(use_specular_texture_location, 0.0);
	}

	if (hasNormalTexture() && (normal_texture_location >=0))
	{
		glUniform1f(use_normal_texture_location, 1.0);

		glActiveTexture(GL_TEXTURE0 + 2);
		glUniform1i (normal_texture_location, 2);
		_normal_texture->bind();
	}
	else
	{
		glUniform1f(use_normal_texture_location, 0.0);
	}

	openGL_check_error();
	
}

QDebug operator<<(QDebug dbg, const Material &m)
{
	dbg.nospace() << "(Material " << &m <<" (ambiant" << m._ambient << ", diffuse" << m._diffuse << ", specular" << m._specular << ", emissive" << m._emissive << ", shininess(" <<m._shininess <<"), "<< m._diffuse_texture << "))";

	return dbg.space();
}
