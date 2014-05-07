#ifndef CUBE_H
#define CUBE_H


#include "objet.hpp"

/**
 * @class Cube
 * @brief Primitive cube
 * @warning Peut être plus utilisable
 */
class Cube: public Objet
{
private:
	/**< Id du Vao du cube */
	static GLuint 	_vao;

	/**
	 * @brief Génère les vbo et le vao pour l'affichage du cube
	 */
	void genVao();

public:
	/**
	 * @brief Constructeur du cube
	 * @details Génère le vao et les vbo s'ils n'ont pas déjà été générés
	 */
	Cube(Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3());

	/**
	 * @brief Destructeur du cube
	 */
	~Cube();

	/**
	 * @brief Affiche le cube
	 */
	void draw();
	
};

#endif