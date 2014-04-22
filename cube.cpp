#include "cube.hpp"
#include <QDebug>

GLuint Cube::_vao = 0;

Cube::Cube(Material * mat, vec3 rotation, vec3 position)
	:Objet(mat, rotation, position)
{
	if (!_vao)
	{
		genVao();
	}
}

Cube::~Cube()
{}

Objet * Cube::clone() const
{
    Objet * tmp = new Cube(_mat, _rotation, _position);
    tmp->modelLocation(_model_location);

    return tmp;
}

void Cube::genVao()
{
    float points[] = 
    {
        -0.5f, -0.5f, 0.5f,     0.5f, -0.5f, 0.5f,      0.5f, 0.5f, 0.5f,       
        -0.5f, -0.5f, 0.5f,     0.5f, 0.5f, 0.5f,       -0.5f, 0.5f, 0.5f, 

        0.5f, -0.5f, 0.5f,      0.5f, -0.5f, -0.5f,     0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,      0.5f, 0.5f, -0.5f,      0.5f, 0.5f, 0.5f,

        0.5f, -0.5f, -0.5f,     -0.5f, -0.5f, -0.5f,    -0.5f, 0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f,     -0.5f, 0.5f, -0.5f,     0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f,    -0.5f, -0.5f, 0.5f,     -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,    -0.5f, 0.5f, 0.5f,      -0.5f, 0.5f, -0.5f,

        -0.5f, 0.5f, 0.5f,      0.5f, 0.5f, 0.5f,       0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,      0.5f, 0.5f, -0.5f,      -0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,     -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,     0.5f, -0.5f, -0.5f,      0.5f, -0.5f, 0.5f
    };

    float normals[] = 
    {
        0.0f,  0.0f, 1.0f,     0.0f,  0.0f, 1.0f,      0.0f,  0.0f, 1.0f,       
        0.0f,  0.0f, 1.0f,     0.0f,  0.0f, 1.0f,      0.0f,  0.0f, 1.0f, 

        1.0f,  0.0f, 00.0f,     1.0f,  0.0f, 00.0f,      1.0f,  0.0f, 00.0f,       
        1.0f,  0.0f, 00.0f,     1.0f,  0.0f, 00.0f,      1.0f,  0.0f, 00.0f,

        0.0f,  0.0f, -1.0f,     0.0f,  0.0f, 1.0f,      0.0f,  0.0f, 1.0f,       
        0.0f,  0.0f, -1.0f,     0.0f,  0.0f, 1.0f,      0.0f,  0.0f, 1.0f,

        -1.0f,  0.0f, 0.0f,     -1.0f,  0.0f, 0.0f,      -1.0f,  0.0f, 0.0f,       
        -1.0f,  0.0f, 0.0f,     -1.0f,  0.0f, 0.0f,      -1.0f,  0.0f, 0.0f,

        0.0f,  1.0f, 0.0f,     0.0f,  1.0f, 0.0f,      0.0f,  1.0f, 0.0f,       
        0.0f,  1.0f, 0.0f,     0.0f,  1.0f, 0.0f,      0.0f,  1.0f, 0.0f,

        0.0f,  -1.0f, 0.0f,     0.0f,  -1.0f, 0.0f,      0.0f,  -1.0f, 0.0f,       
        0.0f,  -1.0f, 0.0f,     0.0f,  -1.0f, 0.0f,      0.0f,  -1.0f, 0.0f,
    };

    unsigned int vbo_point = 0;
    glGenBuffers (1, &vbo_point);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);
    glBufferData (GL_ARRAY_BUFFER, 6*6*3 * sizeof (float), points, GL_STATIC_DRAW);

    unsigned int vbo_normals = 0;
    glGenBuffers (1, &vbo_normals);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_normals);
    glBufferData (GL_ARRAY_BUFFER, 6*6*3 * sizeof (float), normals, GL_STATIC_DRAW);

    glGenVertexArrays (1, &_vao);
    glBindVertexArray (_vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_normals);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Cube::draw()
{
    Objet::draw();



	mat4 model = currentMatrix();

	model = _model * model;


	glUniformMatrix4fv(_model_location, 1, GL_FALSE, model.m);

	glBindVertexArray (_vao);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays (GL_TRIANGLES, 0, 6*6);

	glBindVertexArray(0);	


}