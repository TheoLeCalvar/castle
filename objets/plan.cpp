#include "plan.hpp"
#include <QDebug>


Plan::Plan(
		int width, int height, 
		int widthDivision, int heightDivision,
		const std::vector<QRectF>& rects, 
		Material * mat, vec3 rotation, vec3 position
		)
			:	Objet("", mat, rotation, position), 
				_vao(0), _nbVertices(0)
{
	std::vector<float> points, normals, texCoord;
	std::vector<unsigned int> indices;

	float widthCell = width/(float)widthDivision;
	float heightCell = height/(float)heightDivision;


	for (int i = 0; i <= heightDivision; ++i)
	{
		for (int j = 0; j <= widthDivision; ++j)
		{
			points.push_back(j * widthCell);
			points.push_back(i * heightCell);
			points.push_back(0.0f);

			normals.push_back(0.0f);
			normals.push_back(0.0f);
			normals.push_back(1.0f);

			texCoord.push_back(j);
			texCoord.push_back(i);

		}
	}

	for (int i = 0; i < heightDivision; ++i)
	{
		for (int j = 0; j < widthDivision; ++j)
		{
			bool insert = true;

			for (std::vector<QRectF>::const_iterator k = rects.begin(); k != rects.end(); ++k)
			{
				if (k->contains(points[3*(j + i*(widthDivision+1))], points[3*(j + i*(widthDivision+1)) + 1]))
				{
					insert = false;
					break;
				}
			}

			

			if (insert)
			{
				indices.push_back(j + i*(widthDivision+1));
				indices.push_back(j + i*(widthDivision+1) + 1);
				indices.push_back(j + (i+1)*(widthDivision+1) + 1);


				indices.push_back(j + i*(widthDivision+1));
				indices.push_back(j + (i+1)*(widthDivision+1) + 1);
				indices.push_back(j + (i+1)*(widthDivision+1));
			}
		}
	}


	_nbVertices = indices.size();


	glGenBuffers(1, &_vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);	

	glGenBuffers(1, &_vbo_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _nbVertices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_vbo_texCoord);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo_texCoord);
	glBufferData(GL_ARRAY_BUFFER, texCoord.size() * sizeof(float), texCoord.data(), GL_STATIC_DRAW);


	glGenVertexArrays (1, &_vao);
    glBindVertexArray (_vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, _vbo_vertices);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, _vbo_normals);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray (2);
    glBindBuffer (GL_ARRAY_BUFFER, _vbo_texCoord);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);



    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_indices);

    glBindVertexArray(0);


}


Plan::~Plan()
{
	glDeleteBuffers(1, &_vao);
	glDeleteBuffers(1, &_vbo_vertices);
	glDeleteBuffers(1, &_vbo_normals);
	glDeleteBuffers(1, &_vbo_indices);
}


void Plan::draw()
{
	Objet::draw();

	mat4 model = currentMatrix();


	model = model * _model;



	setModelMatrix(model);

	glBindVertexArray (_vao);

	glDrawElements(GL_TRIANGLES, _nbVertices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);	
}
