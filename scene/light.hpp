#ifndef LIGHT_H
#define LIGHT_H 

#include <QOpenGLFunctions_3_2_Core>

#include "helper.hpp"

/**
 * @brief Lumière pour la Scene
 * @details Gère une lumière pour la scène
 * 
 * @warning seul les lumières positionnelles sont gérées pour l'instant
 * @todo attenuation de la lumière par lumière et plus globale
 */
class Light: protected QOpenGLFunctions_3_2_Core
{
private:
	vec3 	_position;
	static vec3	_ambient; /**< La composante ambient est commune à toutes les lumières */
	vec3	_diffuse;
	vec3 	_specular;


public:
	/**
	 * @brief Constructeur d'une lumière
	 * 
	 * @param position position de la lumière
	 * @param diffuse composante diffuse de la lumière
	 * @param specular composante spéculaire de la lumière
	 * @param number correspond au slot de la lumière qui sera utilisé dans le shader
	 * 
	 * @warning number doit appartenir à [0,7]
     */
	Light(
		vec3 position = vec3(0.0, 0.0, 0.0), 
		vec3 diffuse = vec3(0.8, 0.8, 0.8), 
		vec3 specular = vec3(0.8, 0.8, 0.8)		);

	/**
	 * @brief Destructeur
	 * @todo  Vérifier que la lumière est désactivée dans tout les shader
	 */
	~Light();

	/**
	 * @brief Met à jour une composante de la lumière
	 * 
	 * @param type composante à modifier, doit être parmis (GL_POSITION, GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR)
	 * @param value valeur
	 */
	void set(GLenum type, vec3 value);

	/**
	 * @brief Récupère la valeur d'une composante de la lumière
	 * 
	 * @param type composante voulu, doit être parmis (GL_POSITION, GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR)
	 * @return valeur
	 */
	vec3 get(GLenum type) const;

	/**
	 * @brief Récupère la valeur d'une composante de la lumière
	 * 
	 * @param type composante voulu, doit être parmis (GL_POSITION, GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR)
	 * @return valeur
	 * @warning si le type n'est pas dans les 4 gérés résultat imprévisible
	 */
	vec3 & get(GLenum type);

	/**
	 * @brief Désactive la lumière dans le shader
	 * 
	 * @param number numéro de la lumière à désactiver
	 */
	static void disable(unsigned char number);

	/**
	 * @brief Met à jour le shader avec les infos de la lumière
	 * @param  number slot de lumière à utiliser dans la shader
	 */
	void update(unsigned char number);

	/**
	 * @brief Met à jour la lumière ambient
	 */
	static void updateAmbient();
	
};

#endif
