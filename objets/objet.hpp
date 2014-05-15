#ifndef OBJET
#define OBJET

#include <QOpenGLFunctions_3_2_Core>
#include "material.hpp"
#include "helper.hpp"

/**
 * @class Objet
 * @brief Classe de base affichable
 * 
 */
class Objet: protected QOpenGLFunctions_3_2_Core
{
protected:
	Objet * 	_parent;
	Material * 	_mat;
	QString 	_name;
	vec3 		_rotation;
	vec3 		_position;
	mat4		_model;

	GLuint 		_shaderId;

public:
	/**
	 * @brief Constructeur
	 */
	Objet(const QString& name = QString(), Material * mat = NULL, vec3 rotation = vec3(), vec3 position = vec3(), Objet * parent = NULL);

	/**
	 * @brief Constructeur par recopie
	 * 
	 * @param o objet à copier
	 */
	Objet(const Objet & o);

	/**
	 * @brief Destructeur
	 */
	virtual ~Objet(){}

	/**
	 * @brief Affichage de l'Objet
	 * @details Active le shader de l'Objet et applique le material
	 */
	virtual void 	draw();

	/**
	 * @brief Récupère la position de l'Objet
	 * @return position de l'Objet
	 */
	vec3 & 			position(){return _position;};

	/**
	 * @brief Récupère la position de l'Objet
	 * @return position de l'Objet
	 */
	vec3 			position() const{return _position;}

	/**
	 * @brief Change la position de l'Objet
	 * @param p nouvelle position
	 */
	void			position(vec3 p);


	/**
	 * @brief Récupère la rotation de l'Objet
	 * @return rotation de l'Objet
	 */
	vec3 & 			rotation(){return _rotation;}

	/**
	 * @brief Récupère la rotation de l'Objet
	 * @return rotation de l'Objet
	 */
	vec3 			rotation() const{return _rotation;}

	/**
	 * @brief Change la rotation de l'Objet
	 * @param r nouvelle rotation de l'Objet
	 */
	void			rotation(vec3 r);

	/**
	 * @brief Change l'id du shader
	 * 
	 * @param s nouvel id du shader de l'Objet
	 */
	void 			shaderId(GLuint s){_shaderId = s;}

	/**
	 * @brief Récupère le material de l'Objet
	 * @return un pointeur valide ou NULL
	 */
	Material *		material(){ return _mat;}

	/**
	 * @brief Change le Material de l'Objet
	 * 
	 * @param m pointeur sur le nouveau Material
	 */
	void 			material(Material * m){_mat = m;}


	/**
	 * @brief Change l'Objet père
	 * 
	 * @param o père
	 */
	void 			parent(Objet * o){_parent = o;}

	/**
	 * @brief Récupère l'Objet père
	 * @return Objet père ou NULL
	 */
	Objet * 		parent(){return _parent;}

	/**
	 * @brief Récupère le nom de l'Objet
	 * @return nom de l'Objet
	 */
	const QString & name() const{return _name;}

	/**
	 * @brief Change le nom de l'Objet
	 * 
	 * @param n nouveau nom de l'Objet
	 */
	void 			name(const QString & n){_name = n;}

private:
	/**
	 * @brief Met à jour la matrice de model
	 * @details Appellée lors d'une modification des vecteurs position ou rotation
	 */
	void 			updateModel();

	/**
	 * @brief Transmet les information du Material au shader
	 * @details Si l'Objet ne possède pas de Material celui de son père est appliqué, s'il ne possède pas de père le dernier Material est utilisé
	 */
	void 			applyMaterial();

	/**
	 * @brief Change le shader actif
	 * @details Active le shader de l'Objet, reporte les matrices de view et projection
	 */
	void 			activateShader();

};

#endif
