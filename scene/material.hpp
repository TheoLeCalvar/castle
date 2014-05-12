#ifndef MATERIAL_H
#define MATERIAL_H



#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLTexture>
#include <QImage>
#include <QList>
#include <map>



#include "helper.hpp"

#ifndef DIFFUSE
#define DIFFUSE 0
#endif

#ifndef SPECULAR
#define SPECULAR 1
#endif

#ifndef NORMAL
#define NORMAL 2
#endif

/**
 * @class Material
 * @brief Matériaux pour la Scene
 * @details Contient les informations nécessaire à la gestion d'un material pour la scène
 * 
 */
class Material: protected QOpenGLFunctions_3_2_Core
{
private:
	vec4 			_ambient;
	vec4			_diffuse;
	vec4			_specular;
	float			_shininess;
	vec4			_emissive;
	QOpenGLTexture* _diffuse_texture;
	QOpenGLTexture* _specular_texture;
	QOpenGLTexture* _normal_texture;


	static std::map<const QString, QOpenGLTexture *> _texturesLoaded; /**< Ensemble des textures déjà chargées pour réutilisation */


public:
	/**
	 * @brief Constructeur
	 * 
	 * @warning composante emissive pas encore gérée
	 */
	Material(
		vec4 	ambient = vec4(0.2, 0.2, 0.2, 1.0),
		vec4 	diffuse = vec4(0.8, 0.8, 0.8, 1.0),
		vec4 	specular = vec4(0.8, 0.8, 0.8, 1.0),
		float 	shininess = 0.0f,
		vec4 	emissive = vec4(0.0, 0.0, 0.0, 1.0)
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
	void addTexture(const QString & texFile, unsigned char type);

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
	 * @return dans le cas de GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR retourne un vec4 correspondant à la composante, retourne vec4() autrement
	 */
	vec4 get(GLenum type);

	/**
	 * @brief Récupère la valeur d'un champ
	 * 
	 * @param type doit être parmis GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR
	 * @return dans le cas de GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR retourne un vec4 correspondant à la composante, retourne vec4() autrement
	 */
	vec4 &get(GLenum type);

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
	 * @brief Met à jour le Material courant dans le shader actif
	 */
	void update();	

	friend QDebug operator<<(QDebug dbg, const Material &m);
};

QDebug operator<<(QDebug dbg, const Material &m);


#endif
