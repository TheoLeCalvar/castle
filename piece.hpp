#ifndef PIECE_H
#define PIECE_H

#include "objet.hpp"


class Piece: public Objet
{
private:
	unsigned int width;
	unsigned int height;
	
	GLuint 	_vao;
public:
	Piece();
	~Piece();


	
};

#endif