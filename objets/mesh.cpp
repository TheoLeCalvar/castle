#include "mesh.hpp"

std::map<const QString, std::pair<GLuint, unsigned int> > Mesh::_loadedModels;

Mesh::Mesh()
{}

Mesh * Mesh::load(const QString & file, Scene * scene)
{
	Mesh *ret = NULL;
	auto res = _loadedModels.find(file);

	if (res != _loadedModels.end())
	{
		qDebug() << "Model déjà chargé, on récupère le vao depuis la map.";

		ret = new Mesh();
		ret->_nbVertices = res->second.second;
		ret->_vao = res->second.first;
	}
	else
	{
		Assimp::Importer importer;



		const aiScene* pScene = importer.ReadFile(file.toStdString(), 
				aiProcess_Triangulate | aiProcess_GenSmoothNormals );

		if (!pScene)
		{
			qFatal("Impossible de charger le fichier %s", file.toStdString().c_str());
		}
		else
		{
			qDebug() << "Bingo ça charge";

			qDebug() << "Has Animations : " << pScene->HasAnimations() << pScene->mNumAnimations;
			qDebug() << "Has Cameras : " << pScene->HasCameras() << pScene->mNumCameras;
			qDebug() << "Has Lights : " << pScene->HasLights() << pScene->mNumLights;
			qDebug() << "Has Materials : " << pScene->HasMaterials() << pScene->mNumMaterials;
			qDebug() << "Has Meshes : " << pScene->HasMeshes() << pScene->mNumMeshes;
			qDebug() << "Has Textures : " << pScene->HasTextures() << pScene->mNumTextures;


			qDebug() << "Root node :";
			qDebug() << "Number of children : " << pScene->mRootNode->mNumChildren;
			qDebug() << "Number of meshes : " << pScene->mRootNode->mNumMeshes;

			if (file.endsWith(".ply"))
			{
				qDebug() << "Load ply : " << file;
				ret = loadPly(pScene, file);
			}
			else if (file.endsWith(".obj"))
			{
				qDebug() << "Load obj : " << file;
				ret = loadObj(pScene, file);
			}

		}
	}

	return ret;
}

Mesh* Mesh::loadObj(const aiScene * pScene, const QString & file)
{
	QOpenGLFunctions_3_2_Core func;
	Mesh * ret = new Mesh;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	aiNode * node = pScene->mRootNode->mChildren[0];
	aiMesh * mesh = pScene->mMeshes[node->mMeshes[0]];


	func.initializeOpenGLFunctions();
	ret->_nbVertices = mesh->mNumVertices;




	qDebug() << "Nombre de vertices : " <<  ret->_nbVertices; 

	if (mesh->HasPositions())
	{
		qDebug() << "Y'a des vertices !";
		for (unsigned int i = 0; i < ret->_nbVertices; ++i)
		{
			const aiVector3D* vp = &(mesh->mVertices[i]);

			vertices.push_back(vp->x);
			vertices.push_back(vp->y);
			vertices.push_back(vp->z);
		}
	}

	if (mesh->HasNormals())	
	{
		qDebug() << "Y'a des normales !";
		for (unsigned int i = 0; i < ret->_nbVertices; ++i)
		{
			const aiVector3D* vp = &(mesh->mNormals[i]);

			normals.push_back(vp->x);
			normals.push_back(vp->y);
			normals.push_back(vp->z);
		}
	}

	func.glGenVertexArrays(1, &(ret->_vao));
	func.glBindVertexArray(ret->_vao);



	if (mesh->HasPositions())
	{
		GLuint vbo;

		func.glGenBuffers(1, &vbo);
		func.glBindBuffer(GL_ARRAY_BUFFER, vbo);

		func.glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		func.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		func.glEnableVertexAttribArray(0);

		ret->_vbo.push_back(vbo);
	}

	if (mesh->HasNormals())
	{
		GLuint vbo;

		func.glGenBuffers(1, &vbo);
		func.glBindBuffer(GL_ARRAY_BUFFER, vbo);

		func.glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
		func.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		func.glEnableVertexAttribArray(1);
		ret->_vbo.push_back(vbo);
	}

	func.glBindVertexArray(0);


	_loadedModels.insert(std::make_pair(file, std::make_pair(ret->_vao, ret->_nbVertices)));	

	return ret;
}

Mesh * Mesh::loadPly(const aiScene * pScene, const QString & file)
{
	QOpenGLFunctions_3_2_Core func;
	Mesh * ret = new Mesh;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	aiMesh * mesh = pScene->mMeshes[pScene->mRootNode->mMeshes[0]];


	func.initializeOpenGLFunctions();
	ret->_nbVertices = mesh->mNumVertices;




	qDebug() << "Nombre de vertices : " <<  ret->_nbVertices; 

	if (mesh->HasPositions())
	{
		qDebug() << "Y'a des vertices !";
		for (unsigned int i = 0; i < ret->_nbVertices; ++i)
		{
			const aiVector3D* vp = &(mesh->mVertices[i]);

			vertices.push_back(vp->x);
			vertices.push_back(vp->y);
			vertices.push_back(vp->z);
		}
	}

	if (mesh->HasNormals())	
	{
		qDebug() << "Y'a des normales !";
		for (unsigned int i = 0; i < ret->_nbVertices; ++i)
		{
			const aiVector3D* vp = &(mesh->mNormals[i]);

			normals.push_back(vp->x);
			normals.push_back(vp->y);
			normals.push_back(vp->z);
		}
	}

	func.glGenVertexArrays(1, &(ret->_vao));
	func.glBindVertexArray(ret->_vao);



	if (mesh->HasPositions())
	{
		GLuint vbo;

		func.glGenBuffers(1, &vbo);
		func.glBindBuffer(GL_ARRAY_BUFFER, vbo);

		func.glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		func.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		func.glEnableVertexAttribArray(0);

		ret->_vbo.push_back(vbo);
	}

	if (mesh->HasNormals())
	{
		GLuint vbo;

		func.glGenBuffers(1, &vbo);
		func.glBindBuffer(GL_ARRAY_BUFFER, vbo);

		func.glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
		func.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		func.glEnableVertexAttribArray(1);
		ret->_vbo.push_back(vbo);
	}

	func.glBindVertexArray(0);


	_loadedModels.insert(std::make_pair(file, std::make_pair(ret->_vao, ret->_nbVertices)));	

	return ret;
}

Mesh::~Mesh()
{}

void Mesh::draw()
{
	Objet::draw();
	  	openGL_check_error();


	mat4 model = currentMatrix();

	model = _model * model;


	setModelMatrix(model);
	  	openGL_check_error();


	glBindVertexArray (_vao);

  	glDrawArrays (GL_TRIANGLES, 0, _nbVertices);

  	openGL_check_error();
}



