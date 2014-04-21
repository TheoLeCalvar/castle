#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "objet.hpp"


class Sphere: public Objet
{
private:
    GLuint 	_vao;

    GLdouble m_radius;
    GLdouble m_radius2;
    GLint m_slices;
    GLint m_stacks;

    void genVao();
    GLsizei nbvertex;

public:
    //rayon horizontal, rayon vertical, nb division vertical, nb division horizontal
    Sphere(GLdouble m_radius =1,GLdouble m_radius2 =1, GLint m_slices=1, GLint m_stacks=1,
           Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3());

    ~Sphere();

   // GLuint Sphere::_vao = 0;
    void draw();

};

#endif // SPHERE_HPP
