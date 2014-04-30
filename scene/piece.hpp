#ifndef PIECE_H
#define PIECE_H

#include "objet.hpp"
#include "plan.hpp"

#include <list>


class Piece: public Objet
{
private:
	vec3 _dimensions;
	
	std::list<Plan *> _murs;
	std::list<Objet *> _objets;

public:
	Piece(vec3 dimension = vec3(1,1,1), vec3 rotation = vec3(), vec3 position = vec3(), Material * mat = NULL, Objet * parent = NULL);
	~Piece();

	void draw();

	void addWall(Plan *);
	void addObjet(Objet *);
	
	const vec3 dimensions() const;
	vec3 & dimensions();
	void dimensions(const vec3 v);

};

#endif