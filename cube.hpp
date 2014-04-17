#ifndef CUBE_H
#define CUBE_H


#include "objet.hpp"


class Cube: public Objet
{
private:
	static GLuint 	_vao;

	void genVao();

public:
	Cube(Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3());
	~Cube();

	Objet * clone();

	void draw();
	
};

#endif