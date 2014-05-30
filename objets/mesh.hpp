#ifndef MESH_H
#define MESH_H


#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include <QString>
#include <QDebug>

#include <QList>
#include <QMap>
#include <QPair>

#include "objet.hpp"
#include "scene.hpp"

/**
 * @class Mesh
 * @brief Charge un modèle 3D
 * @details Permet la lecture de fichiers contenant des modèles 3D
 * @warning Tout les formats de textures ne sont pas supportés, se référé au support de QImage
 * 
 */
class Mesh: public Objet
{
friend class Node;

private:

	typedef struct 
	{
		GLuint 			vao;
		QList<GLuint> 	vbos;
		GLuint 			nbVertices;
		unsigned int 	nbReferences;
	} MeshInfo;

	MeshInfo * _infos;

	/**
	 * @brief Constructeur privé
	 * @details Utiliser Node::load(const QString & fileName, Scene * scene)
	 * @see Node::loadModel()
	 */
	Mesh();


	/**
	 * @brief Constructeur par recopie
	 * 
	 */
	Mesh(const Mesh & m);

	/**
	 * @brief Charge un mesh
	 * 
	 * @param scene scène générée par assimp
	 * 
	 * @return un pointeur sur Mesh, NULL si erreur
	 */
	static Mesh * loadMesh(const aiMesh* scene);


	
public:

	/**
	 * @brief Destructeur
	 */
	~Mesh();
	
	/**
	 * @brief Affiche le modèle
	 */
	void draw();

};


#endif