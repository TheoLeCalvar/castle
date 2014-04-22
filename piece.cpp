#include "piece.hpp"



Piece::Piece(vec3 dimension, vec3 rotation, vec3 position, Material * mat, Objet * parent)
:Objet(mat, rotation, position, parent), _dimensions(dimension)
{}

Piece::~Piece()
{
	for(std::list<Plan *>::iterator i = _murs.begin(); i != _murs.end(); ++i)
		delete *i;
}

Objet * Piece::clone() const
{

}

void Piece::draw()
{
	for(auto i: _murs)
		i->draw();

	for(auto i: _objets)
		i->draw();
}

void Piece::addWall(Plan * p)
{
	_murs.push_front(p);
}

void Piece::addObjet(Objet * o)
{
	_objets.push_front(o);
}

const vec3 Piece::dimensions() const
{
	return _dimensions;
}

vec3 & Piece::dimensions()
{
	return _dimensions;
}

void Piece::dimensions(const vec3 v)
{
	_dimensions = v;
}