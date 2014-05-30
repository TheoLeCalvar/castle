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
#include <QDir>


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

	/**
	 * @brief Charge un aiNode
	 * 
	 * @param node aiNode à charger
	 * @param pScene aiScene contenant les textures, matériaux et mesh
	 * @param scene Scene à laquelle ajouter les matériaux chargés
	 * @return Node proprement chargé
	 */
	static Node * 		loadNode(const aiNode * node, const aiScene * pScene, Scene * scene);

public:
	/**
	 * @brief Destructeur
	 * @details Détruit les Nodes et Mesh fils
	 */
	~Node();
	

	void draw();


	/**
	 * @brief Retourne la liste des noms des Nodes fils
	 * @return liste des noms des Nodes fils
	 */
    QStringList getChildrenNames() const;

	/**
	 * @brief Retourne le Node enfant à partir de son nom
	 * 
	 * @param name nom du Node enfant
	 * @return retourne NULL si aucun enfant n'existe avec ce nom
	 */
	Node * getChild(const QString & name);

	/**
	 * @brief supprime un Node fils
	 * 
	 * @param name nom du Node à supprimer
	 */
	void removeChild(const QString & name);

	/**
	 * @brief Retourne la liste des noms des Mesh de ce Node
	 * @return liste des noms des Mesh
	 */
	QStringList getMeshNames() const;

	/**
	 * @brief Retourne le Mesh ayant le nom donné
	 * 
	 * @param name nom du Mesh
	 * @return NULL si le Mesh n'appartient pas à ce Node
	 */
	Mesh * getMesh(const QString & name);

	/**
	 * @brief Supprime le Mesh portant le nom
	 * 
	 * @param name nom du Mesh à supprimer
	 */
	void removeMesh(const QString & name);

	/**
	 * @brief Charge le modèle
	 * @details Retourne le Node racine représentant le modèle et ajoute les matériaux à la scène
	 * 
	 * @param path nom du fichier à charger
	 * @param scene Scene qui recevra les matériaux chargés
	 * 
	 * @return Node racine du modèle
	 */
	static Node * loadModel(const QString & path, Scene * scene);

	/**
	 * @brief Récupère le nom du modèle chargé
	 * 
	 * @param node Node dont on veut le nom du modèle
	 * @return nom du fichier charger
	 * @warning  Ne fonctionne que pour les Node racines
	 */
	QString getModelName() const;

};


#endif
