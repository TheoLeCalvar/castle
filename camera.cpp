#include "camera.hpp"
#include <cmath>

Camera * Camera::_activeCamera = NULL;

Camera::Camera( float eyeX, float eyeY, float eyeZ):
    _eye(eyeX, eyeY, eyeZ),
    _phi(0), _theta(0), _haut(0.0f,1.0f,0.0f), 
    _avant_presse(false), _arriere_presse(false), _gauche_presse(false), _droite_presse(false), _haut_presse(false), _bas_presse(false),
    _vitesse(0.10f), _view_location(0)
{
    if (!_activeCamera)
    {
        _activeCamera = this;
    }
    initializeOpenGLFunctions();
    vectorFromAngle();
}

void Camera::move()
{

    if (_avant_presse)
    {
        _eye = _eye + _avant * _vitesse;
    }
    if (_gauche_presse)
    {
        _eye = _eye + _gauche * _vitesse;
    }
    if (_arriere_presse)
    {
        _eye = _eye - _avant * _vitesse;
    }
    if (_droite_presse)
    {
        _eye = _eye - _gauche * _vitesse;
    }
    if (_haut_presse)
    {
        _eye = _eye + _haut * _vitesse;
    }
    if (_bas_presse)
    {
        _eye = _eye - _haut * _vitesse;
    }


    _center = _eye + _avant;
}

void Camera::go(float x, float y, float z)
{
    _eye(x, y, z);
    _center = _eye + _avant;
}

// void Camera::mouse_event(GLFWwindow * w, double x, double y)
// {
//     int width, height;
//     glfwGetWindowSize(w, &width, &height);
//     width /= 2;
//     height /= 2;


//     if ((x - width != 0) ||  (y - height != 0))
//     {

//         _activeCamera->_theta    += (x - width)*0.2f;
//         _activeCamera->_phi      -= (y - height)*0.2f;

//         _activeCamera->vectorFromAngle();

//         #ifdef __APPLE__    
//             int xpos, ypos;
//             glfwGetWindowPos(w, &xpos, &ypos);

//             CGPoint warpPoint = CGPointMake(width + xpos, height + ypos);
//             CGWarpMouseCursorPosition(warpPoint);
//             CGAssociateMouseAndMouseCursorPosition(true);
//         #else
//             glfwSetCursorPos (w, width, height);
//         #endif
//     }
// }

void Camera::vectorFromAngle()
{
    static vec3 up(0.0f,1.0f,0.0f);

    if (_phi > 89.0f)
    {
        _phi = 89.0f;
    }
    else if (_phi < -89.0f)
    {
        _phi = -89.0f;
    }


    double tmp = cos(_phi * M_PI/180);


    _avant(tmp * cos(_theta * M_PI/180), sin(_phi * M_PI/180), tmp * sin(_theta * M_PI/180));
    _avant.normalize();

    _gauche = up ^ _avant;
    _gauche.normalize();

    _center = _eye + _avant;
}

void Camera::display()
{
    move();


    mat4 view = viewMatrix(_eye, _center, vec3(0.0f, 1.0f, 0.0f));


    if (_view_location)
    {
        glUniformMatrix4fv(_view_location, 1, GL_FALSE, view.m);
    }

}
