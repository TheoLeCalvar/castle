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
 * @warning Ne supporte pas tout les formats, seul les .ply sont totalement gérés, les .obj le sont partiellement
 * Ne lièbre pas (encore les vao/vbo)
 * 
 */
class Mesh: public Objet
{
private:

	typedef struct
	{
		GLuint vao;
		QList<GLuint> vbos;
		GLuint nbVertices;
		unsigned int nbReferences;
	} MeshInfo;

	static QMap<QString, MeshInfo*> _loadedModels; /**< Ensemble des VAO des modèles chargés */

	MeshInfo * _infos; /**< Information sur le model représenté par ce Mesh */

	/**
	 * @brief Constructeur privé
	 * @details Utiliser load(const QString & fileName, Scene * scene)
	 * @see load
	 */
	Mesh();

	/**
	 * @brief Charge un mesh
	 * 
	 * @param scene scène générée par assimp
	 * @param fileName nom du fichier
	 * 
	 * @return un pointeur sur Mesh, NULL si erreur
	 */
	static Mesh * load(const aiMesh* scene, const QString & fileName);

	/**
	 * @brief Charge un Material
	 * 
	 * @param mat material à charger
	 * @return NULL si erreur
	 */
	static Material * loadMaterial(const aiMaterial * mat);

	
public:

	/**
	 * @brief Charge un modèle 3D
	 * @details Charge un modèle 3D et retourne le Mesh * associé
	 * 
	 * @param fileName nom du fichier à charger
	 * @param scene Scene à laquelle ajouté les matériaux (pas encore géré)
	 * 
	 * @warning Ne gère pas les matériaux contenus dans la scène
	 * 
	 * @return un pointeur sur Mesh ou NULL si une erreur s'est produite, peut aussi stoper le programme
	 */
	static QList<Mesh *> loadMesh(const QString & fileName, Scene * scene);


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