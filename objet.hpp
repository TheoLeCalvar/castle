#ifndef OBJET
#define OBJET

#include "material.hpp"
#include "math.hpp"


class Objet
{
private:
	Material * 	_mat;
	vec3 		_rotation;
	vec3 		_position;
	mat4		_model;

	GLuint 		_shader;


public:
	Objet(Material * = NULL, vec3 rotation = vec3(), vec3 position = vec3());
	~Objet();

	virtual void 	draw() const;

	vec3 & 			position();
	vec3 			position() const;
	void			position(vec3 p);

	vec3 & 			rotation();
	vec3 			rotation() const;
	void			rotation(vec3 r);	

	mat4 & 			model();
	mat4 			model() const;
	void			model(mat4 m);

	
};

#endif