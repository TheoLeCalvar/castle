#include "donuts.hpp"
#include <QDebug>
#include <cmath>
#include <vector>

GLuint Donuts::_vao = 0;



Donuts::Donuts(GLdouble radius,GLdouble radius_donuts, GLint slices, GLint stacks ,Material * mat, vec3 rotation, vec3 position)
    :Objet(mat, rotation, position)
{
    m_radius=radius;
    m_slices=slices;
    m_stacks=stacks;
    m_radius_donuts=radius_donuts;
    if (!_vao)
    {
        genVao();
    }

}

Donuts::~Donuts()
{}

void Donuts::genVao()
{

    std::vector<float> points;
    std::vector<float> normals;



    float theta;
    float phi;

    for (theta=0 ; theta <= (2*M_PI) ; theta+=((2*M_PI)/m_slices)){

        float xcentre=cos(theta)*m_radius;
        float ycentre=0;
        float zcentre=sin(theta)*m_radius;

            for (phi=0 ; phi <= (2*M_PI) ;phi+=((2*M_PI)/m_stacks)){

                   normals.push_back( xcentre +m_radius_donuts*cos(phi) );
                   points.push_back(m_radius * normals.back());

                   normals.push_back(ycentre+m_radius_donuts* sin(phi));
                   points.push_back (m_radius * normals.back());

                   normals.push_back(zcentre+m_radius_donuts*cos(phi));
                   points.push_back (m_radius * normals.back());
           }

        }


    nbvertex=(GLsizei) normals.size();

    unsigned int vbo_point = 0;
    glGenBuffers (1, &vbo_point);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);
    glBufferData (GL_ARRAY_BUFFER,  points.size() * sizeof (float), points.data(), GL_STATIC_DRAW);

    unsigned int vbo_normals = 0;
    glGenBuffers (1, &vbo_normals);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_normals);
    glBufferData (GL_ARRAY_BUFFER, normals.size() * sizeof (float), normals.data(), GL_STATIC_DRAW);

    glGenVertexArrays (1, &_vao);
    glBindVertexArray (_vao);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);

    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer (GL_ARRAY_BUFFER, vbo_normals);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Donuts::draw()
{
    mat4 model = currentMatrix();

    model = _model * model;

    glUniformMatrix4fv(_model_location, 1, GL_FALSE, model.m);

    glBindVertexArray (_vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader

    glDrawArrays (GL_LINES, 0,  nbvertex/3);

    glBindVertexArray(0);


}
