#include "plan.hpp"
#include <QDebug>


Plan::Plan(
		int width, int height, 
		int widthDivision, int heightDivision,
		std::vector<QRectF> rects, 
		Material * mat, vec3 rotation, vec3 position
		)
			:	Objet(mat, rotation, position), 
				_vao(0), _nbVertices(0)
{
	std::vector<float> points, normals;
	std::vector<unsigned short> indices;

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

		}
	}

	for (int i = 0; i < heightDivision; ++i)
	{
		for (int j = 0; j < widthDivision; ++j)
		{
			bool insert = true;

			for (std::vector<QRectF>::iterator k = rects.begin(); k != rects.end(); ++k)
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


	indices.shrink_to_fit();
	_nbVertices = indices.size();



	unsigned int vbo_vertices = 0, vbo_normals = 0, vbo_indices = 0;

	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);	

	glGenBuffers(1, &vbo_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _nbVertices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


	glGenVertexArrays (1, &_vao);
    glBindVertexArray (_vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_normals);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);

    glBindVertexArray(0);


}

Plan::~Plan()
{}

Objet * Plan::clone()
{}


void Plan::draw()
{
	glUseProgram(_shaderId);

	mat4 model = currentMatrix();

	model = _model * model;

	glUniformMatrix4fv(_model_location, 1, GL_FALSE, model.m);

	glBindVertexArray (_vao);

	glDrawElements(GL_TRIANGLES, _nbVertices, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);	
}
