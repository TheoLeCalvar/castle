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
	if (_children.contains(o->name()))
	{
		qDebug() << "Objet ayant le même nom déjà présent" << o->name();
	}
	else
	{
		qDebug() << "Ajout de " << o->name();
		_children[o->name()] = o;
	}
}

void Piece::addChild(const QString & name, Objet * o)
{
	if (_children.contains(name))
	{
		qDebug() << "Objet ayant le même nom déjà présent" << name;
	}
	else
	{
		qDebug() << "Ajout de " << name;
		_children[name] = o;
	}
}

QStringList Piece::getChildren() const
{
	return _children.keys();
}

void 		Piece::removeChild(const QString & name)
{
	Objet * o = _children.value(name);

	if(o)
	{
		delete o;

		_children.remove(name);
	}
}

Objet * 	Piece::getChild(const QString & name)
{
	return _children.value(name);
}

const vec3 & Piece::dimensions() const
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

bool Piece::collide(const Hitbox & h) const
{
	vec3 center = h.getP();
	vec3 xAxis = h.getX(), yAxis = h.getY(), zAxis = h.getZ();
	float width = h.getWidth(), height = h.getHeight(), depth = h.getDepth();

	vec4 p1 =  vec4(_position, 0.0f);
	vec4 p2 = p1 + vec4(_dimensions, 0.0f); 

	transformVector(p1);
	transformVector(p2);


	for(Objet * i : _children)
	{
		if (i->collide(h))
		{
			return true;
		}
	}
	return false;
}