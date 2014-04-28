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


class Mesh: public Objet
{
private:

	static std::map<const QString, std::pair<GLuint, unsigned int> > _loadedModels;

	GLuint _vao;
	std::list<GLuint> _vbo;
	unsigned int _nbVertices;


	Mesh();
	
public:
	static Mesh * load(const QString & fileName, Scene * scene);
	static Mesh * loadObj(const aiScene*, const QString &);
	static Mesh * loadPly(const aiScene*, const QString &);

	~Mesh();
	
	void draw();

};


#endif