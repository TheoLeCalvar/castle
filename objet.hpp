#ifndef OBJET
#define OBJET

#include <QOpenGLFunctions_3_2_Core>
#include "material.hpp"
#include "math.hpp"


class Objet: protected QOpenGLFunctions_3_2_Core
{
protected:
	Material * 	_mat;
	vec3 		_rotation;
	vec3 		_position;
	mat4		_model;

	GLuint 		_shaderId;
	GLuint 		_model_location;


public:
	Objet(Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3())
		:_mat(mat), _rotation(rotation), _position(position), _model(1)
		{initializeOpenGLFunctions(); updateModel();}

	virtual ~Objet(){}

	virtual Objet* clone() = 0;

	virtual void 	draw() = 0;

	vec3 & 			position(){return _position;};
	vec3 			position() const{return _position;}
	void			position(vec3 p)
	{
		_position = p;
		updateModel();
	}

	vec3 & 			rotation(){return _rotation;}
	vec3 			rotation() const{return _rotation;}
	void			rotation(vec3 r)
	{
		_rotation = r;
		updateModel();
	}

	mat4 			model() const{return _model;}

	void 			shaderId(GLuint s){_shaderId = s;}
	void 			modelLocation(GLuint s){_model_location = s;}

	Material *		material(){ return _mat;}
	void 			material(Material * m){_mat = m;}

private:
	void 			updateModel()
	{
		_model = XrotationMatrix(_rotation[0]);
		_model = Yrotate(_model, _rotation[1]);
		_model = Zrotate(_model, _rotation[2]);

		_model = translate(_model, _position);
	}	

};

#endif