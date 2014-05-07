#include "piece.hpp"



Piece::Piece(vec3 dimension, vec3 rotation, vec3 position, Material * mat)
:Objet("", mat, rotation, position, NULL), _dimensions(dimension)
{}

Piece::~Piece()
{
	for(auto i: _children)
		delete i;
}

void Piece::draw()
{
	pushMatrix(currentMatrix() * _model);

	for(auto i: _children)
		i->draw();

	popMatrix();
}


void Piece::addChild(Objet * o)
{
	if (o)
	{
		_children << o;
	}
}

QStringList Piece::getChildren() const
{
	QStringList l;

	for(auto i : _children)
		l << i->name();

	return l;
}

Objet * 	Piece::getChild(const QString & name)
{
	for(auto i : _children)
		if (i->name() == name)
		{
			return i;
		}

	return NULL;

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