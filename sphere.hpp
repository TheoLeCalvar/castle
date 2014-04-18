#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "objet.hpp"


class Sphere: public Objet
{
private:
    static GLuint 	_vao;

    GLdouble m_radius;
    GLint m_slices;
    GLint m_stacks;

    void genVao();
    GLsizei nbvertex;

public:
    Sphere(GLdouble m_radius =1, GLint m_slices=1, GLint m_stacks=1,
           Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3());

    ~Sphere();

    void draw();

};

#endif // SPHERE_HPP
