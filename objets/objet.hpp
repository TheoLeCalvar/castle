#ifndef OBJET
#define OBJET

#include <QOpenGLFunctions_3_2_Core>
#include "material.hpp"
#include "helper.hpp"


class Objet: protected QOpenGLFunctions_3_2_Core
{
protected:
	Objet * 	_parent;
	Material * 	_mat;
	vec3 		_rotation;
	vec3 		_position;
	mat4		_model;

	GLuint 		_shaderId;
	GLuint 		_model_location;


public:
	Objet(Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3(), Objet * parent = NULL);

	virtual ~Objet(){}

	virtual Objet* clone() const = 0;

	virtual void 	draw();

	vec3 & 			position(){return _position;};
	vec3 			position() const{return _position;}
	void			position(vec3 p);

	vec3 & 			rotation(){return _rotation;}
	vec3 			rotation() const{return _rotation;}
	void			rotation(vec3 r);

	mat4 			model() const{return _model;}

	void 			shaderId(GLuint s){_shaderId = s;}
	void 			modelLocation(GLuint s){_model_location = s;}

	Material *		material(){ return _mat;}
	void 			material(Material * m){_mat = m;}

private:
	void 			updateModel();

};

#endif