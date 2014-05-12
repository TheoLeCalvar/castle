#include "mesh.hpp"

QMap<QString, Mesh::MeshInfo*> Mesh::_loadedModels;

Mesh::Mesh()
{}

QList<Mesh *> Mesh::loadMesh(const QString & file, Scene * scene)
{
	QList<Mesh *> list;

	MeshInfo* res = _loadedModels.value(file);

	if (res)
	{
		qDebug() << "Model déjà chargé, on récupère les infos depuis la map.";

		Mesh * tmp = new Mesh();
		tmp->_infos = res;
		list << tmp;
		res->nbReferences++;
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
				list << load(pScene->mMeshes[pScene->mRootNode->mMeshes[0]], file);
			}
			else if (file.endsWith(".obj"))
			{
				aiNode * root = pScene->mRootNode;
				qDebug() << "Load obj : " << file;
				for(unsigned int i = 0; i < pScene->mRootNode->mNumChildren; ++i){
					Mesh * mesh = load(pScene->mMeshes[root->mChildren[i]->mMeshes[0]], file);
					Material * mat = loadMaterial(pScene->mMaterials[pScene->mMeshes[root->mChildren[i]->mMeshes[0]]->mMaterialIndex]);

					mesh->name(QString::fromUtf8(root->mChildren[i]->mName.C_Str()));
					mesh->material(mat);
					scene->addMaterial(file + '_' + QString::number(i),mat);

					list << mesh;
				}
			}

		}
	}


	return list;
}

Material * Mesh::loadMaterial(const aiMaterial * mtl)
{
	Material * mat = new Material();

	aiString path;
	aiColor4t<float> color;
	float shininess;
/*
AI_MATKEY_NAME
AI_MATKEY_COLOR_AMBIENT 
AI_MATKEY_COLOR_DIFFUSE
AI_MATKEY_COLOR_SPECULAR
AI_MATKEY_COLOR_EMISSIVE
AI_MATKEY_SHININESS 
aiTextureType_DIFFUSE 
aiTextureType_SPECULAR
aiTextureType_NORMAL 
*/
	if(AI_SUCCESS == mtl->Get(AI_MATKEY_COLOR_AMBIENT, color)){
		mat->set(GL_AMBIENT, vec4(color.r, color.g, color.b, color.a));
	}

	if(AI_SUCCESS == mtl->Get(AI_MATKEY_COLOR_DIFFUSE, color)){
		mat->set(GL_DIFFUSE, vec4(color.r, color.g, color.b, color.a));
	}

	if(AI_SUCCESS == mtl->Get(AI_MATKEY_COLOR_SPECULAR, color)){
		mat->set(GL_SPECULAR, vec4(color.r, color.g, color.b, color.a));
	}

	if(AI_SUCCESS == mtl->Get(AI_MATKEY_COLOR_EMISSIVE, color))
		mat->set(GL_EMISSION, vec4(color.r, color.g, color.b, color.a));

	if (AI_SUCCESS == mtl->Get(AI_MATKEY_SHININESS, shininess)){
		mat->set(shininess);
	}

	if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &path))
	{
		mat->addTexture(QString::fromUtf8(path.C_Str()), DIFFUSE);
	}

	return mat;
}

Mesh* Mesh::load(const aiMesh * mesh, const QString & file)
{
	QOpenGLFunctions_3_2_Core func;
	Mesh * ret = new Mesh;
	MeshInfo * info = new MeshInfo;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoord;


	func.initializeOpenGLFunctions();

	ret->_infos = info;

	info->nbVertices = mesh->mNumVertices;
	info->nbReferences = 1;




	qDebug() << "Nombre de vertices : " <<  info->nbVertices; 

	if (mesh->HasPositions())
	{
		qDebug() << "Y'a des vertices !";
		for (unsigned int i = 0; i < info->nbVertices; ++i)
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
		for (unsigned int i = 0; i < info->nbVertices; ++i)
		{
			const aiVector3D* vp = &(mesh->mNormals[i]);

			normals.push_back(vp->x);
			normals.push_back(vp->y);
			normals.push_back(vp->z);
		}
	}

	if (mesh->HasTextureCoords(0))
	{
		qDebug() << "Texture !";

		for (unsigned int i = 0; i < info->nbVertices; ++i)
		{
			aiVector3D* vp = &(mesh->mTextureCoords[0][i]);

			texCoord.push_back(vp->x);
			texCoord.push_back(vp->y);
		}
	}

	func.glGenVertexArrays(1, &(info->vao));
	func.glBindVertexArray(info->vao);



	if (mesh->HasPositions())
	{
		GLuint vbo;

		func.glGenBuffers(1, &vbo);
		func.glBindBuffer(GL_ARRAY_BUFFER, vbo);

		func.glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		func.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		func.glEnableVertexAttribArray(0);

		info->vbos << vbo;
	}

	if (mesh->HasNormals())
	{
		GLuint vbo;

		func.glGenBuffers(1, &vbo);
		func.glBindBuffer(GL_ARRAY_BUFFER, vbo);

		func.glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
		func.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		func.glEnableVertexAttribArray(1);
		info->vbos << vbo;
	}

	if (mesh->HasTextureCoords(0))
	{
		GLuint vbo;

		func.glGenBuffers(1, &vbo);
		func.glBindBuffer(GL_ARRAY_BUFFER, vbo);

		func.glBufferData(GL_ARRAY_BUFFER, texCoord.size() * sizeof(float), texCoord.data(), GL_STATIC_DRAW);
		func.glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		func.glEnableVertexAttribArray(2);
		info->vbos << vbo;
	}

	func.glBindVertexArray(0);


	_loadedModels.insert(file, info);	

	return ret;
}

Mesh::~Mesh()
{
	_infos->nbReferences--;

	if (_infos->nbReferences == 0)
	{
		for (auto i : _infos->vbos)
		{
			glDeleteBuffers(1, &i);
		}

		glDeleteBuffers(1, &_infos->vao);

		delete _infos;
	}
}

void Mesh::draw()
{
	Objet::draw();
	  	openGL_check_error();


	mat4 model = currentMatrix();

	model = _model * model;


	setModelMatrix(model);
	  	openGL_check_error();


	glBindVertexArray (_infos->vao);

  	glDrawArrays (GL_TRIANGLES, 0, _infos->nbVertices);

  	openGL_check_error();
}



