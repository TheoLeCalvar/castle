#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.hpp>


class MeshLoader
{
public:
	static Objet * loadMesh(const std::string & fileName);
	
};

#endif