#include "camera.hpp"
#include <cmath>


Camera::Camera(Scene * scene, float eyeX, float eyeY, float eyeZ):
    _eye(eyeX, eyeY, eyeZ),
    _phi(0), _theta(0), _haut(0.0f,1.0f,0.0f), _vitesse(0.10f),
    _scene(scene),
    _avant_presse(false), _arriere_presse(false), _gauche_presse(false), _droite_presse(false), _haut_presse(false), _bas_presse(false)
{
    vectorFromAngle();
}

void Camera::move()
{
    vec3 deplacement;

    if (_avant_presse)
    {
        deplacement += _avant * _vitesse;
    }
    if (_gauche_presse)
    {
        deplacement += _gauche * _vitesse;
    }
    if (_arriere_presse)
    {
        deplacement -= _avant * _vitesse;
    }
    if (_droite_presse)
    {
        deplacement -= _gauche * _vitesse;
    }
    if (_haut_presse)
    {
        deplacement += _haut * _vitesse;
    }
    if (_bas_presse)
    {
        deplacement -= _haut * _vitesse;
    }
    
    _eye += deplacement;

    if(_scene && _scene->collide(*this))
    {
        _eye -= deplacement;
    }

    

    _center = _eye + _avant;
    

}

void Camera::go(float x, float y, float z)
{
    _eye(x, y, z);
    _center = _eye + _avant;
}

void Camera::mouseMoveEvent(int x, int y, int width, int height)
{
    width /= 2;
    height /= 2;


    if ((x - width != 0) ||  (y - height != 0))
    {

        _theta    += (x - width)*0.2f;
        _phi      -= (y - height)*0.2f;

        vectorFromAngle();
    }
}

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


    setViewMatrix(view);


}

vec3 Camera::getP() const
{
    return _center;
}

vec3 Camera::getX() const
{
    return _avant;
}

vec3 Camera::getY() const
{
    return _haut;
}

vec3 Camera::getZ() const
{
    return _gauche;
}

float Camera::getWidth() const
{
    return 0.2f;
}

float Camera::getHeight() const
{
    return 0.5f;
}

float Camera::getDepth() const
{
    return 0.2f;
}
