#ifndef PIECE_H
#define PIECE_H

#include "objet.hpp"
#include "plan.hpp"

#include <QStringList>

/**
 * @brief Pièce, contient un ensemble d'objet qu'elle contient
 * @class Piece
 * 
 */
class Piece: public Objet
{
private:

	vec3 _dimensions; /**< Contient les dimensions de la pièces */

	QMap<QString, Objet *> _children; /** Liste des objets fils de la pièces, contient au moins les murs */

public:
	/**
	 * @brief Constructeur
	 * 
	 */
	Piece(vec3 dimension = vec3(1,1,1), vec3 rotation = vec3(), vec3 position = vec3(), Material * mat = NULL);

	/**
	 * @brief Destructeur
	 */
	~Piece();

	/**
	 * @brief Affiche l'ensemble des fils
	 */
	void draw();

	/**
	 * @brief Ajoute un fils à la pièce
	 * @details Se charge de la destruction de l'objet
	 * 
	 * @param name nom de l'objet
	 * @param objet objet à ajouter
	 */
	void addChild(const QString & name, Objet * objet);

	/**
	 * @brief Ajoute un fils à la pièce
	 * 
	 * @param o objet à ajouter
	 */
	void addChild(Objet * o);

	/**
	 * @brief Récupère la liste des noms des objets fils
     * @todo A revoir !
	 * @return liste des noms des objets
	 */
	QStringList getChildren() const;

	/**
	 * @brief Renvoie un pointeur sur un objet fils
	 * @details Récupère un pointeur sur un objet fils de la pièce
	 * 
	 * @param name nom de l'objet
	 * @return un pointeur valide si l'objet est un fils de la pièce, NULL sinon
	 */
	Objet * 	getChild(const QString & name);

	/**
	 * @brief Retourne les dimensions de la pièce
	 * @return vec3 contenant les dimensions de la pièce
	 */
	const vec3 dimensions() const;

	/**
	 * @brief Retourne les dimensions de la pièce
	 * @return vec3 contenant les dimensions de la pièce
	 */
	vec3 & dimensions();

	/**
	 * @brief Edite les dimensions de la pièce
	 * @param v nouvelles dimensions de la pièce
	 */
	void dimensions(const vec3 v);


	virtual bool collide(const Hitbox &) const;

};

#endif