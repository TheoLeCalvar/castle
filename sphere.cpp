#include "sphere.hpp"
#include <QDebug>
#include <cmath>
#include <vector>

GLuint Sphere::_vao = 0;



Sphere::Sphere(GLdouble radius, GLint slices, GLint stacks ,Material * mat, vec3 rotation, vec3 position)
    :Objet(mat, rotation, position)
{
    m_radius=radius;
    m_slices=slices;
    m_stacks=stacks;

    if (!_vao)
    {
        genVao();
    }

}

Sphere::~Sphere()
{}

void Sphere::genVao()
{

    std::vector<float> points;
    std::vector<float> normals;


    int cptphi=0;
    int cpttheta=0;

    for (cptphi=0 ; cptphi<m_slices ; cptphi++){

                for(cpttheta=0 ; cpttheta<m_stacks ; cpttheta++) {

                   normals.push_back(cos(2*M_PI/m_stacks*cpttheta) * cos(2*M_PI/m_slices*cptphi));
                   points.push_back (m_radius * normals.back());

                   normals.push_back(sin(2*M_PI/m_stacks*cpttheta)*cos(2*M_PI/m_slices*cptphi));
                   points.push_back (m_radius * normals.back());

                   normals.push_back(sin(2*M_PI/m_slices*cptphi));
                   points.push_back (m_radius * normals.back());


                }
           }
//float angle;

//                for(angle=0 ; angle<2*M_PI ; angle+=(M_PI/100)) {

//                   normals.push_back(cos(angle));
//                   points.push_back (m_radius * normals.back());

//                   normals.push_back(0);
//                   points.push_back (m_radius * normals.back());

//                   normals.push_back(sin(angle));
//                   points.push_back (m_radius * normals.back());


//                }


//float angle = 2*M_PI / 1000;

//    for(int i = 0; i < 1000; ++i)
//    {
//        normals.push_back(sin(i*angle));
//        points.push_back (m_radius * normals.back());

//        normals.push_back(0);
//        points.push_back (0);

//        normals.push_back(cos(i*angle));
//        points.push_back (m_radius * normals.back());
//    }












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

void Sphere::draw()
{
    mat4 model = currentMatrix();

    model = _model * model;

    glUniformMatrix4fv(_model_location, 1, GL_FALSE, model.m);

    glBindVertexArray (_vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader

    glDrawArrays (GL_POINTS, 0,  nbvertex/3);

    glBindVertexArray(0);


}

