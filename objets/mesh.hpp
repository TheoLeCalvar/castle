#ifndef MESH_H
#define MESH_H

#include "objet.hpp"

class Mesh: public Objet
{
private:
	GLuint vao;
	GLuint *vbo;
public:
	Mesh();
	~Mesh();
	
	Objet * clone() const;

	void draw();

};


#endif