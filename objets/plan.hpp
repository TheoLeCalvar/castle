#ifndef PLAN_H
#define PLAN_H 

#include "objet.hpp"
#include <QRectF>
#include <QList>
#include <vector>


/**
 * @brief Plan utilisé par la Piece
 * @details Gère un plan, avec des trous pour les fenêtres
 */
class Plan: public Objet
{
private:
	GLuint _vao;
	GLuint _vbo_vertices;
	GLuint _vbo_normals;
	GLuint _vbo_indices;
	GLuint _vbo_texCoord;
	unsigned int _nbVertices;

	vec3 	_minP;
	vec3 	_maxP;


public:
	/**
	 * @brief Constructeur
	 * 
	 * @param width largeur du plan
	 * @param height hauteur du plan
	 * @param widthDivision nombre de division selon width
	 * @param heightDivision nombre de division selon height
	 * @param rects QRectF rectangles définissant les fenêtres du plan
	 * @param mat Material à utiliser
	 * @param rotation rotation à appliquer au plan
	 * @param position position du plan dans le monde
	 */
	Plan(int width = 1, int height = 1, int widthDivision = 1, int heightDivision = 1, const QList<QRectF> rects = QList<QRectF>(), Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3());
	
	/**
	 * @brief Destructeur
	 * @details Détruit le plan et libère les vbo/vba
	 */
	~Plan();

	/**
	 * @brief Affiche le plan
	 */
	void 	draw();


protected:

	virtual vec3 getP() const;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual float getDepth() const;

};

#endif