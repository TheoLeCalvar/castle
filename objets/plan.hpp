#ifndef PLAN_H
#define PLAN_H 

#include "objet.hpp"
#include <QRectF>
#include <vector>

class Plan: public Objet
{
private:
	GLuint _vao;
	GLuint _vbo_vertices;
	GLuint _vbo_normals;
	GLuint _vbo_indices;
	unsigned int _nbVertices;

public:
	Plan(int width = 1, int height = 1, int widthDivision = 1, int heightDivision = 1, const std::vector<QRectF> & rects = std::vector<QRectF>(), Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3());
	~Plan();


	void 	draw();

private:
	Plan(GLuint vao, GLuint vbo_vertices, GLuint vbo_normals, GLuint vbo_indice, unsigned int nbVertices, Material * mat, vec3 rotation, vec3 position);
	
};

#endif