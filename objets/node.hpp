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

class Node: public Objet
{
private:

	QList<Mesh *> _meshs;
	QMap<QString, Node *> _children;

	static QMultiMap<QString, Node *> _loadedModels;

	Node();
	Node(const Node & node);


	static Material * 	loadMaterial(const aiMaterial * mtl);
	static Node * 		loadNode(const aiNode * node, const aiScene * pScene, Scene * scene);

public:
	~Node();
	

	void draw();

	static Node * loadModel(const QString & path, Scene * scene);


};


#endif
