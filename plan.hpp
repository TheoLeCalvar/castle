#ifndef PLAN_H
#define PLAN_H 

#include "objet.hpp"
#include <QRectF>
#include <vector>

class Plan: public Objet
{
public:
	typedef enum {
		Verticale,
		Horizontale
	} horientation;

private:
	GLuint _vao;
	unsigned int _nbVertices;

public:
	Plan(int width = 1, int height = 1, int widthDivision = 1, int heightDivision = 1, std::vector<QRectF> rects = std::vector<QRectF>(), Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3());
	~Plan();

	Objet * clone();


	void 	draw();
	
};

#endif