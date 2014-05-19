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
	std::vector<float> normals;
	std::vector<float> texCoord;


	func.initializeOpenGLFunctions();

	ret->_infos = info;

	info->nbVertices = mesh->mNumVertices;
	info->nbReferences = 1;


	info->maxP = vec3(10e-10, 10e-10, 10e-10);
	info->minP = vec3(10e10, 10e10, 10e10);


	#ifdef DEBUG
		qDebug() << "Nombre de vertices : " <<  info->nbVertices; 
	#endif

	if (mesh->HasPositions())
	{
		#ifdef DEBUG
			qDebug() << "Y'a des vertices !";
		#endif

		for (unsigned int i = 0; i < info->nbVertices; ++i)
		{
			const aiVector3D* vp = &(mesh->mVertices[i]);

			vertices.push_back(vp->x);
			vertices.push_back(vp->y);
			vertices.push_back(vp->z);

			if(vp->x < info->minP[0])
				info->minP[0] = vp->x;

			if(vp->y < info->minP[1])
				info->minP[1] = vp->y;

			if(vp->z < info->minP[2])
				info->minP[2] = vp->z;

			if(vp->x > info->maxP[0])
				info->maxP[0] = vp->x;

			if(vp->y > info->maxP[1])
				info->maxP[1] = vp->y;

			if(vp->z > info->maxP[2])
				info->maxP[2] = vp->z;
		}
	}

	if (mesh->HasNormals())	
	{
		#ifdef DEBUG
			qDebug() << "Y'a des normales !";
		#endif

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
		#ifdef DEBUG
			qDebug() << "Coordonées de textures !";
		#endif

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

vec3 Mesh::getP() const
{
	vec4 centre((_infos->minP + _infos->maxP)/2.0f, 0.0f);
	transformVector(centre);

	return centre;
}

float Mesh::getWidth() const
{
	return (_infos->maxP[0] - _infos->minP[0]) / 2.0f;
}

float Mesh::getHeight() const
{
	return (_infos->maxP[1] - _infos->minP[1]) / 2.0f;
}

float Mesh::getDepth() const
{
	return (_infos->maxP[2] - _infos->minP[2]) / 2.0f;
}


