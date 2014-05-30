#include "mesh.hpp"


Mesh::Mesh()
{}

Mesh::Mesh(const Mesh & m):Objet(m),_infos(m._infos)
{
	_infos->nbReferences++;
}


Mesh* Mesh::loadMesh(const aiMesh * mesh)
{
	QOpenGLFunctions_3_2_Core func;
	Mesh * ret = new Mesh;
	MeshInfo * info = new MeshInfo;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	std::vector<float> texCoord;


	func.initializeOpenGLFunctions();

	ret->_infos = info;

	info->nbFaces = mesh->mNumFaces;
	info->nbReferences = 1;



	#ifdef DEBUG
		qDebug() << "Nombre de vertices : " <<  mesh->mNumVertices; 
		qDebug() << "Nombre de faces : " << mesh->mNumFaces;
	#endif

	if (mesh->HasPositions())
	{
		#ifdef DEBUG
			qDebug() << "Y'a des vertices !";
		#endif

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			const aiVector3D* vp = &(mesh->mVertices[i]);

			vertices.push_back(vp->x);
			vertices.push_back(vp->y);
			vertices.push_back(vp->z);
		}
	}

	if (mesh->HasFaces())
	{
		#ifdef DEBUG
			qDebug() << "Y'a des faces !";
		#endif

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			const aiFace* face = &mesh->mFaces[i];

			indices.push_back(face->mIndices[0]);
			indices.push_back(face->mIndices[1]);
			indices.push_back(face->mIndices[2]);
		}


	}

	if (mesh->HasNormals())	
	{
		#ifdef DEBUG
			qDebug() << "Y'a des normales !";
		#endif

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			const aiVector3D* vp = &(mesh->mNormals[i]);

			normals.push_back(vp->x);
			normals.push_back(vp->y);
			normals.push_back(vp->z);
		}
	}

	if (mesh->HasTextureCoords(0))
	{
		#ifdef DEBUG
			qDebug() << "Coordonées de textures !";
		#endif

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
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

	if (mesh->HasFaces())
	{
		GLuint vbo;

		func.glGenBuffers(1, &vbo);
		func.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		func.glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

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

	model =  model * _model;


	setModelMatrix(model);
	openGL_check_error();


	glBindVertexArray (_infos->vao);

  	glDrawElements (GL_TRIANGLES, _infos->nbFaces * 3, GL_UNSIGNED_INT, 0);

  	openGL_check_error();

}


