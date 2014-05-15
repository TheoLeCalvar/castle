#ifndef SCENE_H
#define SCENE_H

#include "helper.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "material.hpp"

#include "objet.hpp"
#include "piece.hpp"


#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#include <QRectF>



class Mesh;
class Node;


/**
 * @class Scene
 * @brief Classe principale 
 * 
 * Se charge de lire le xml et de générer la scène.
 * Nécessite un context OpenGL 3.2 au minimum
 */
class Scene: protected QOpenGLFunctions_3_2_Core
{
private:
	QMap<QString, Piece *>						_pieces; /**< Map des pièces constituant la scène, identifiées par leur nom, doit être unique */ 
	QMap<QString, Light *> 						_lights; /**< Map des lumières constituant la scène, identifiées par leur nom, doit être unique */
	QMap<QString, Material *>					_materials; /**< Map des matériaux constituant la scène, identifiés par leur nom, doit être unique */
	QMap<QString, QOpenGLShaderProgram *> 		_shaders; /**< Map des shader constituant la scène, identifiés par leur nom, doit être unique */

	mat4 										_projectionMatrix; /**< Matrice de projection, recalculée à chaque redimensionnement du widget */

public:
	Camera *									_camera; /**< Caméra de la scène */


public:
	/**
	 * @brief Constructeur vide
	 * @details Construit une scène vide
	 */
	Scene();

	/**
	 * @brief Charge une scène à partir d'un fichier xml la décrivant
	 * @details La scène est chargée à partir d'un fichier xml la décrivant, si le fichier n'est pas trouvé l'exécution s'arrête
	 * 
	 * @param fileName Chemin vers le fichier
	 */
	Scene(const QString & fileName);
	
	/**
	 * @brief Destructeur de la scène
	 * @details Destructeur de la scène
	 */
	~Scene();

	/**
	 * @brief Affiche la scène
	 */
	void draw();


	/**
	 * @brief Récupère un pointeur sur une pièce
	 * 
	 * @param name nom de la pièce
	 * @return Retourne le pointeur si le nom est trouvé, NULL autrement
	 */
	Piece * 	getPiece(const QString & name);


	/**
	 * @brief Récupère un pointeur sur une lumière
	 * 
	 * @param name nom de la lumière
	 * @return Retourne un pointeur valide si le nom est présent, NULL autrement
	 */
	Light * 	getLight(const QString & name);


	/**
	 * @brief Récupère un pointeur sur un material
	 * 
	 * @param name nom du material
	 * @return Retourne un pointeur valide si le nom est présent, NULL autrement
	 */
	Material *	getMaterial(const QString & name);


	/**
	 * @brief Récupère l'id d'un shader
	 * 
	 * @param name nom du shader
	 * @return Retourne l'id d'un shader valide si le nom est présent, 0 autrement
	 */
	GLuint 		getShader(const QString & name);


	/**
	* @brief Retourne la liste des noms des pièces dans la scène
	* @return QStringList contenant les noms des pièces de la scène
	*/
	QStringList getPiecesName() const;


	/**
	* @brief Retourne la liste des noms des lumières dans la scène
	* @return QStringList contenant les noms des lumières de la scène
	*/
	QStringList getLightsNames() const;

	/**
	* @brief Retourne la liste des noms des matériaux dans la scène
	* @return QStringList contenant les noms des matériaux de la scène
	*/
	QStringList getMaterialsNames() const;

	/**
	* @brief Retourne la liste des noms des shaders dans la scène
	* @return QStringList contenant les noms des shaders de la scène
	*/
	QStringList getShadersNames() const;

	/**
	 * @brief Ajoute une pièce à la scène
	 * @details Ajoute une pièce à la scène, le nom ne doit pas être déjà présent dans la scène, si l'est la pièce n'est pas ajoutée
	 * 
	 * @param name nom de l'objet à ajouter
	 * @param o pointeur sur l'objet à ajouter
	 */
	void 		addPiece(const QString & name, Piece * o);

	/**
	 * @brief Ajoute une lumière à la scène
	 * @details Ajoute une lumière à la scène, le nom doit être unique, sinon elle ne sera pas ajoutée
	 * 
	 * @param name nom de la lumière à ajouter
	 * @param l pointeur du la lumière
	 */
	void 		addLight(const QString & name, Light * l);

	/**
	 * @brief Ajoute un material à la scène
	 * @details Ajoute un material à la scène, le nom doit être unique, autrement il ne sera pas ajouté
	 * 
	 * @param name nom du material à ajouter
	 * @param m pointeur sur le material
	 */
	void 		addMaterial(const QString & name, Material * m);

	/**
	 * @brief Ajoute un shadder à la scène
	 * @details Ajoute un shader à la scène, le nom doit être unique, autrement il ne sera pas ajouté
	 * 
	 * @param name nom du shader à ajouter
	 * @param s id du shader
	 */
	void 		addShader(const QString & name, QOpenGLShaderProgram * s);

	/**
	 * @brief Sauvegarde de la scène au format xml
	 * 
	 * @param fileName nom du fichier dans lequel sauvegarde
	 * @warning Pas encore implémenté
	 * @todo  A implémenter
	 */
	void 		saveAsXML(const QString & fileName);


private:
	/**
	 * @brief Charge les lumières
	 * @details Charge les lumières à partir du XML
	 * 
	 * @param dom noeud XML correspondant à <lumieres>
	 */
	void 		loadLights(const QDomElement & dom);

	/**
	 * @brief Charge les materials
	 * @details Charge les materials à partir du XML
	 * 
	 * @param dom noeud XML correspondant à <materiaux>
	 */
	void 		loadMaterials(const QDomElement & dom);

	/**
	 * @brief Charge les pièces
	 * @details Charge les pièces à partir du XML
	 * 
	 * @param dom noeud XML correspondant à <pieces>
	 */
	void 		loadPieces(const QDomElement & dom);

	/**
	 * @brief Charge les shaders
	 * @details Charge les shaders à partir du XML
	 * 
	 * @param dom noeud XML correspondant à <shaders>
	 */
	void 		loadShaders(const QDomElement & dom);
	
};

#endif
