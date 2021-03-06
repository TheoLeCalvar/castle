#include "node.hpp"
#include <assimp/DefaultLogger.hpp>

QMultiMap<QString, Node *> Node::_loadedModels;

Node::Node(){}

Node::Node(const Node & node):Objet(node)
{
	for(Mesh * i : node._meshs)
	{
		Mesh * mesh = new Mesh(*i);
		mesh->parent(this);
		_meshs << mesh;
	}

	for(auto i = node._children.begin(); i != node._children.end(); ++i)
	{
		Node * child = new Node(*i.value());
		child->parent(this);

		_children.insertMulti(i.key(), child);
	}
}

Node::~Node()
{
	for(Mesh * i : _meshs)
		delete i;

	for(Node * i : _children)
		delete i;


	QString key = _loadedModels.key(this, "non trouvé");

	if(key != "non trouvé")
	{
		_loadedModels.remove(key, this);

	}
}	


Node * Node::loadNode(const aiNode * node, const aiScene * pScene, Scene * scene)
{
	Node * nodeOut = new Node();
	aiMatrix4x4 aiMat = node->mTransformation;
	aiVector3D aiScale, aiTranslation;
	aiQuaternion aiRotation;

	aiMat.Decompose(aiScale, aiRotation, aiTranslation);

	nodeOut->position(vec3(aiTranslation.x, aiTranslation.y, aiTranslation.z));
	nodeOut->scale(vec3(aiScale.x, aiScale.y, aiScale.z));

	#ifdef DEBUG
		qDebug() << "Node info :";
		qDebug() << "Number of children : " << node->mNumChildren;
		qDebug() << "Number of meshes : " << node->mNumMeshes;
	#endif




	for(unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		Node * child = Node::loadNode(node->mChildren[i], pScene, scene);
		aiString name;

		child->parent(nodeOut);


		nodeOut->_children.insertMulti(QString::fromUtf8(node->mChildren[i]->mName.C_Str()) + "_" + QString::number(i), child);
	}


	for(unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		Mesh * mesh = Mesh::loadMesh(pScene->mMeshes[node->mMeshes[i]]);
		Material * mat = nullptr;				
		aiString name;


		if(pScene->HasMaterials())
		{
			aiMaterial * m = pScene->mMaterials[pScene->mMeshes[node->mMeshes[i]]->mMaterialIndex];

			if(AI_SUCCESS == m->Get(AI_MATKEY_NAME, name))
			{
				mat = scene->getMaterial(QString::fromUtf8(node->mName.C_Str()) + "_" + QString::fromUtf8(name.C_Str()));

				if(!mat)
				{
					mat = loadMaterial(m);	
					scene->addMaterial(QString::fromUtf8(node->mName.C_Str()) + "_" + QString::fromUtf8(name.C_Str()), mat);		
				}
			}
		}
		else
		{
			mat = scene->getMaterial("neutre");
		}


		mesh->name(QString::fromUtf8(node->mName.C_Str()) + "_" + QString::number(i));
		mesh->material(mat);
		mesh->parent(nodeOut);

		nodeOut->_meshs << mesh;
	}

	return nodeOut;
}

Material * Node::loadMaterial(const aiMaterial * mtl)
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
	aiTextureType_NORMALS 
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

	if(AI_SUCCESS == mtl->Get(AI_MATKEY_COLOR_EMISSIVE, color)){
		mat->set(GL_EMISSION, vec4(color.r, color.g, color.b, color.a));
	}

	if (AI_SUCCESS == mtl->Get(AI_MATKEY_SHININESS, shininess)){
		mat->set(shininess);
	}

	if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &path))
	{
		mat->addTexture(QString::fromUtf8(path.C_Str()), "diffuse");
	}

	if (AI_SUCCESS == mtl->GetTexture(aiTextureType_SPECULAR, 0, &path))
	{
		mat->addTexture(QString::fromUtf8(path.C_Str()), "specular");
	}

	if (AI_SUCCESS == mtl->GetTexture(aiTextureType_NORMALS, 0, &path))
	{
		mat->addTexture(QString::fromUtf8(path.C_Str()), "normal");
	}

	mat->fromXML(false);

	return mat;
}

Node* Node::loadModel(const QString & file, Scene * scene)
{
	Node * node = NULL;
	Node * res = _loadedModels.value(file);

	if (res)
	{
		qDebug() << "Model déjà chargé, on récupère les infos depuis la map.";

		node = new Node(*res);
	}
	else
	{
		Assimp::Importer importer;
		Assimp::DefaultLogger::create();

		Assimp::Logger* log = Assimp::DefaultLogger::get();
		log->attachStream(Assimp::LogStream::createDefaultStream(aiDefaultLogStream_FILE));


		QStringList dossiers = file.split("/");


		for(auto i = dossiers.begin(); i != dossiers.end() -1; ++i)
		{
			QDir::setCurrent(*i);
		}


		const aiScene* pScene = importer.ReadFile(file.right(file.size() - file.lastIndexOf("/") - 1).toStdString(), 
				aiProcess_Triangulate 				| 
				aiProcess_GenSmoothNormals 			| 
				aiProcess_OptimizeMeshes 			| 
				aiProcess_FixInfacingNormals 		| 
				aiProcess_RemoveRedundantMaterials 	| 
				aiProcess_JoinIdenticalVertices 	| 
				aiProcess_FindInvalidData 			| 
				aiProcess_OptimizeGraph );

		if (!pScene)
		{
			qDebug("Erreur d'importation : %s",importer.GetErrorString());
			qFatal("Impossible de charger le fichier %s", file.toStdString().c_str());
		}
		else
		{
			#ifdef DEBUG
				qDebug() << "Has Animations : " << pScene->HasAnimations() << pScene->mNumAnimations;
				qDebug() << "Has Cameras : " 	<< pScene->HasCameras() << pScene->mNumCameras;
				qDebug() << "Has Lights : " 	<< pScene->HasLights() << pScene->mNumLights;
				qDebug() << "Has Materials : " 	<< pScene->HasMaterials() << pScene->mNumMaterials;
				qDebug() << "Has Meshes : " 	<< pScene->HasMeshes() << pScene->mNumMeshes;
				qDebug() << "Has Textures : " 	<< pScene->HasTextures() << pScene->mNumTextures;


				qDebug() << "Load : " << file;
			#endif


			node = loadNode(pScene->mRootNode, pScene, scene);



		}

		for(auto i = dossiers.begin(); i != dossiers.end() - 1; ++i)
		{
			QDir::setCurrent("..");
		}
		
	}
	
	_loadedModels.insert(file, node);


	return node;
}

void Node::draw()
{
	Objet::draw();
	openGL_check_error();


	mat4 model = currentMatrix();

	model = model * _model;

	pushMatrix(model);

	for(Mesh * i : _meshs)
		i->draw();

	for(Node * i : _children)
		i->draw();

	popMatrix();
}


QStringList Node::getChildrenNames() const
{
	return _children.keys();
}

QStringList Node::getMeshNames() const
{
	QStringList l;

	for(auto i : _meshs)
		l << i->name();

	return l;
}

Node * Node::getChild(const QString & name)
{
	return _children.value(name);
}

Mesh * Node::getMesh(const QString & name)
{
	for(Mesh * i : _meshs)
	{
		if (i->name() == name)
		{
			return i;
		}
	}

	return NULL;
}

void Node::removeChild(const QString & name)
{
	Node * n = _children.value(name);

	if(n)
	{
		delete n;
		_children.remove(name);
	}
}

void Node::removeMesh(const QString & name)
{
	for(auto m = _meshs.begin(); m != _meshs.end() ; ++m)
	{
		if((*m)->name() == name)
		{
			delete *m;

			_meshs.erase(m);
		}
			
	}
}

QString Node::getModelName() const
{
	return _loadedModels.key(const_cast<Node *>(this));
}
