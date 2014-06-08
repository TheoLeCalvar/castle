#ifndef MATERIAL_H
#define MATERIAL_H



#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLTexture>
#include <QImage>
#include <QList>
#include <QMap>



#include "helper.hpp"


/**
 * @class Material
 * @brief Matériaux pour la Scene
 * @details Contient les informations nécessaire à la gestion d'un material pour la scène
 * 
 */
class Material: protected QOpenGLFunctions_3_2_Core
{
private:
	vec3 			_ambient;
	vec3			_diffuse;
	vec3			_specular;
	float			_shininess;
	vec3			_emissive;
	QOpenGLTexture* _diffuse_texture;
	QOpenGLTexture* _specular_texture;
	QOpenGLTexture* _normal_texture;
	bool			_fromXML;


	static QMap<QString, QOpenGLTexture *> _texturesLoaded; /**< Ensemble des textures déjà chargées pour réutilisation */


public:
	/**
	 * @brief Constructeur
	 * 
	 * @warning composante emissive pas encore gérée
	 */
	Material(
		vec3 	ambient = vec3(0.2, 0.2, 0.2),
		vec3 	diffuse = vec3(0.8, 0.8, 0.8),
		vec3 	specular = vec3(0.8, 0.8, 0.8),
		float 	shininess = 32.0f,
		vec3 	emissive = vec3(0.0, 0.0, 0.0)
	);

	/**
	 * @brief Destructeur
	 * @todo Gérer libération de la texture quand plus utilisée
	 */
	~Material();

	/**
	 * @brief Met à jour la composante du matériaux
	 * 
	 * @param type la composante qui sera mise à jour, doit être parmis GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR, GL_EMISSION
	 * @param value valeur
	 */
	void set(GLenum type, vec4 value);


	/**
	 * @brief Charge une texture et l'associe à un slot
	 * @details Charge une texture et l'associe à un slot pour le passage au shader
	 * 
	 * @param texFile fichier de texture à charger
	 * @param int indice que la texture doit occuper
	 * @warning Ecrase la texture à l'indice choisie
	 */
	void addTexture(const QString & texFile, const QString & type);

	/**
	 * @brief Met à jour la shniness du Material
	 * 
	 * @param shininess valeur
	 */
	void set(float shininess);

	/**
	 * @brief Récupère la valeur d'un champ
	 * 
	 * @param type doit être parmis GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR
	 * @return dans le cas de GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR retourne un vec3 correspondant à la composante, retourne vec4() autrement
	 */
	vec3 get(GLenum type) const;


	/**
	 * @brief Récupère la valeur d'un champ
	 * 
	 * @param type doit être parmis GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR
	 * @return dans le cas de GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR retourne un vec3 correspondant à la composante, retourne vec4() autrement
	 */
	vec3 &get(GLenum type);

	/**
	 * @brief Valeur du shininess
	 * 
	 * @return valeur du GL_SHININESS
	 */
	float shininess() const;

	bool hasTexture(unsigned char type) const;
	bool hasDiffuseTexture() const;
	bool hasSpecularTexture() const;
	bool hasNormalTexture() const;

	/**
	 * @brief Retourne le path de la texture diffuse
	 * @return nom de la texture diffuse
	 */
	QString getDiffuseTextureName() const;

	/**
	 * @brief Retourne le path de la texture spéculaire
	 * @return nom de la texture spéculaire
	 */	
	QString getSpecularTextureName() const;

	/**
	 * @brief Retourne le path de la normal map
	 * @return nom de la normal map
	 */
	QString getNormalTextureName() const;


	/**
	 * @brief Met à jour le Material courant dans le shader actif
	 */
	void update();	

	/**
	 * @brief Libère les textures chargées
	 */
	static void clear();

	/**
	 * @brief Indique si le Material a été chargé depuis le XML ou pas
	 */
	bool isFromXML() const{return _fromXML;}

	/**
	 * @brief Indique si le Material est issu ou non du XML
	 */
	void fromXML(bool b){_fromXML = b;}

	friend QDebug operator<<(QDebug dbg, const Material &m);
};

QDebug operator<<(QDebug dbg, const Material &m);


#endif
