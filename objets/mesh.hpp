#ifndef MESH_H
#define MESH_H


#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include <QString>
#include <QDebug>

#include <map>
#include <utility>

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

	static std::map<const QString, std::pair<GLuint, unsigned int> > _loadedModels; /**< Ensemble des VAO des modèles chargés */

	GLuint _vao; /**< VAO du model */
	std::list<GLuint> _vbo; /**< VBOs du model */
	unsigned int _nbVertices; /**< Nombre de vertices du model, tuilisé pour glDraw */

	/**
	 * @brief Constructeur privé
	 * @details Utiliser load(const QString & fileName, Scene * scene)
	 * @see load
	 */
	Mesh();

	/**
	 * @brief Charge un modèle 3D au format obj
	 * @warning Ne gère pas tout les obj, les groupes ne sont pas géré, seul le premier mesh est chargé, ne gère pas les matériaux
	 * 
	 * @param scene scène générée par assimp
	 * @param fileName nom du fichier
	 * 
	 * @return un pointeur sur Mesh, NULL si erreur
	 */
	static Mesh * loadObj(const aiScene* scene, const QString & fileName);

	/**
	 * @brief Charge un modèle 3D au format ply
	 * 
	 * @param scene scène générée par assimp
	 * @param fileName nom du fichier
	 * 
	 * @return un pointeur sur Mesh, NULL si erreur
	 */
	static Mesh * loadPly(const aiScene* scene, const QString & fileName);
	
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
	static Mesh * load(const QString & fileName, Scene * scene);


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