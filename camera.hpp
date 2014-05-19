#ifndef CAMERA_H
#define CAMERA_H

#include "helper.hpp"
#include "hitbox.hpp"
#include "scene.hpp"


/**
 * @class Camera
 * @brief Camera pour Scene
 * 
 */
class Camera: public Hitbox
{
protected:
	vec3 	_eye;
	vec3   	_center;

	float 	_phi;
	float 	_theta;

	vec3  	_avant;
	vec3  	_gauche;
	vec3  	_haut;
	float 	_vitesse;

	Scene * _scene;

public:
	bool    _avant_presse; 	/**< Indique si la caméra doit avancer au prochain affichage */
	bool	_arriere_presse;/**< Indique si la caméra doit reculer au prochain affichage */
	bool	_gauche_presse; /**< Indique si la caméra doit aller à gauche au prochain affichage */
	bool	_droite_presse; /**< Indique si la caméra doit aller à droite au prochain affichage */
	bool 	_haut_presse;	/**< Indique si la caméra doit monter au prochain affichage */
	bool	_bas_presse;	/**< Indique si la caméra doit descendre au prochain affichage */	



public:
	/**
	 * @brief Constructeur
	 * 
	 */
	Camera(Scene * scene = NULL, float eyeX = 0.0f, float eyeY = 0.0f, float eyeZ = 0.0f);

	/**
	 * @brief Destructeur
	 */
	~Camera(){}

	/**
	 * @brief Actualise la caméra
	 * @details Met à jour la position de la caméra en fonction des booléens de déplacement et actualise la matrice view
	 */
	void display();

	/**
	 * @brief Fonction de déplacement de la caméra à la souris
	 * 
	 * @param x position en X du curseur de la souris
	 * @param y position en Y du curseur de la souris
	 * @param width largeur de la fenêtre
	 * @param height hauteur de la fenêtre
	 */
	void mouseMoveEvent(int x, int y, int width, int height);

private:
	/**
	 * @brief Calcul le déplacement de la Camera
	 */
	void 	move();

	/**
	 * @brief Déplace la caméra aux coordonnées données
	 */
	void 	go(float x, float y, float z);

	/**
	 * @brief Recalcul les vecteurs avant/côté pour le mouvement
	 */
	void 	vectorFromAngle();

protected:
	virtual vec3 getP() const;
	virtual vec3 getX() const;
	virtual vec3 getY() const;
	virtual vec3 getZ() const;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual float getDepth() const;


};

#endif
