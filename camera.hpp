#ifndef CAMERA_H
#define CAMERA_H

#include "math.hpp"

#include <QOpenGLFunctions_3_2_Core>


#ifdef __APPLE__
	#include <ApplicationServices/ApplicationServices.h>
#endif




class Camera: protected QOpenGLFunctions_3_2_Core
{
protected:
	vec3 	 _eye;
	vec3   _center;

	float _phi;
	float _theta;

	vec3  _avant;
	vec3  _gauche;
	vec3  _haut;



public:
	bool    _avant_presse;
	bool	_arriere_presse;
	bool	_gauche_presse;
	bool	_droite_presse;
	bool 	_haut_presse;
	bool	_bas_presse;

protected:
	float _vitesse;

	GLuint _view_location;




public:
	Camera(float eyeX = 0.0f, float eyeY = 0.0f, float eyeZ = 0.0f);
	virtual ~Camera(){}

protected:
	virtual void 	move();
	void 	go(float x, float y, float z);
	void 	vectorFromAngle();

public:
	virtual void display();

	void setProjection(GLuint p){_view_location = p;}

	void mouseMoveEvent(int x, int y, int width, int height);
	
};

#endif
