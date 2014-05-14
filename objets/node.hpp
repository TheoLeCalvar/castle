#ifndef NODE_HPP
#define NODE_HPP

#include "mesh.hpp"
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include <QString>
#include <QDebug>

#include <QList>
#include <QMultiMap>
#include <QPair>

/**
 * @class Node
 * @brief Contient un node de modèle 3D
 * @details Un node possède un ensemble de meshes et de Node fils
 * 
 */
class Node: public Objet
{
private:

	QList<Mesh *> _meshs; /**< Liste des Mesh de ce node **/
	QMap<QString, Node *> _children; /**< Fils du Node **/

	static QMultiMap<QString, Node *> _loadedModels; /**< Modèles déjà chargés, recnstruit un ensemble de Node par recopie **/

	/**
	 * @brief Constructeur par défaut
	 */
	Node();

	/**
	 * @brief Constructeur par recopie
	 * 
	 * @param node Node à recopier
	 */
	Node(const Node & node);

	/**
	 * @brief Charge un Material depuis une aiMaterial d'ASSIMP 
	 * 
	 * @param mtl material à charger
	 * @return Material créé
	 */
	static Material * 	loadMaterial(const aiMaterial * mtl);
	static Node * 		loadNode(const aiNode * node, const aiScene * pScene, Scene * scene);

public:
	~Node();
	

	void draw();

	static Node * loadModel(const QString & path, Scene * scene);


};


#endif
