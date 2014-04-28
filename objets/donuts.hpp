#ifndef DONUTS_HPP
#define DONUTS_HPP

#include "objet.hpp"


class Donuts: public Objet
{
private:
    GLuint 	_vao;


    GLdouble m_radius;
    GLdouble m_radius_donuts;
    GLint m_slices;
    GLint m_stacks;

    void genVao();
    GLsizei nbvertex;

public:
    Donuts(GLdouble m_radius =1,GLdouble m_radius_donuts=1, GLint m_slices=1, GLint m_stacks=1,
           Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3());

    ~Donuts();


    void draw();

};

#endif // DONUTS_HPP
