#ifndef HITBOX
#define HITBOX 

#include "helper.hpp"

class Hitbox
{
public:
	/**
	 * @brief Calcule la collision des deux OBB
	 * @details utilise l'algorithme des SAT, plus d'info sur http://goldensuneur.fr/divers/Separating%20Axis%20Theorem%20for%20Oriented%20Bounding%20Boxes.pdf
	 * 
	 * @param h seconde Hitbox
	 * @warning actuellement non fonctionnel
	 */
	virtual bool collide(const Hitbox & h) const
	{
		vec3 aP = getP(), aX = getX(), aY = getY(), aZ = getZ();
		float aW = getWidth(), aH = getHeight(), aD = getDepth();

		vec3 bP = h.getP(), bX = h.getX(), bY = h.getY(), bZ = h.getZ();
		float bW = h.getWidth(), bH = h.getHeight(), bD = h.getDepth();

		vec3 T = bP - aP;

		float rXX = aX * bX, rXY = aX * bY, rXZ = aX * bZ;
		float rYX = aY * bX, rYY = aY * bY, rYZ = aY * bZ;
		float rZX = aZ * bX, rZY = aZ * bY, rZZ = aZ * bZ;

		// cas 1
		if(abs(T * aX) > aW + abs(bW * rXX) + abs(bH * rXY) + abs(bD * rXZ))
			return false;

		//cas 2
		if(abs(T * aY) > aH + abs(bW * rYX) + abs(bH * rYY) + abs(bD * rYZ))
			return false;

		//cas 3
		if(abs(T * aZ) > aD + abs(bW * rZX) + abs(bH * rZY) + abs(bD * rZZ))
			return false;

		//cas 4
		if(abs(T * bX) > bW + abs(aW * rXX) + abs(aH * rYX) + abs(aD * rZX))
			return false;

		//cas 5
		if(abs(T * bY) > bH + abs(aW * rXY) + abs(aH * rYY) + abs(aD * rZY))
			return false;

		//cas 6
		if(abs(T * bZ) > bD + abs(aW * rXZ) + abs(aH * rYZ) + abs(aD * rZZ))
			return false;

		//cas 7
		if(abs(T * (aX ^ bX)) > abs(aH * rZX) + abs(aD * rYX) + abs(bH * rXZ) + abs(bD * rXY))
			return false;

		//cas 8
		if(abs(T * (aX ^ bY)) > abs(aH * rZY) + abs(aD * rYY) + abs(bW * rXZ) + abs(bD * rXX))
			return false;

		//cas 9
		if(abs(T * (aX ^ bZ)) > abs(aH * rZZ) + abs(aD * rYZ) + abs(bW * rXY) + abs(bH * rXX))
			return false;

		//cas 10
		if(abs(T * (aY ^ bX)) > abs(aW * rZX) + abs(aD * rXX) + abs(bH * rYZ) + abs(bD * rYY))
			return false;

		//cas 11
		if(abs(T * (aY ^ bY)) > abs(aW * rZY) + abs(aD * rXY) + abs(bW * rYZ) + abs(bD * rYX))
			return false;

		//Cas 12
		if(abs(T * (aY ^ bZ)) > abs(aW * rZZ) + abs(aD * rXZ) + abs(bW * rYY) + abs(bH * rYX))
			return false;	

		//cas 13
		if(abs(T * (aZ ^ bX)) > abs(aW * rYX) + abs(aH * rXX) + abs(bH * rZZ) + abs(bD * rZY))
			return false;

		//cas 11
		if(abs(T * (aZ ^ bY)) > abs(aW * rYY) + abs(aH * rXY) + abs(bW * rZZ) + abs(bD * rZY))
			return false;

		//Cas 12
		if(abs(T * (aZ ^ bZ)) > abs(aW * rYZ) + abs(aH * rXZ) + abs(bW * rZY) + abs(bH * rZX))
			return false;	


		return true;
	}

protected:
	/**
	 * @brief Retourne le centre de la Hitbox
	 */
	virtual vec3 getP() const = 0;

	/**
	 * @brief vec3 unitaire X
	 */
	virtual vec3 getX() const = 0;

	/**
	 * @brief vec3 unitaire Y
	 */
	virtual vec3 getY() const = 0;

	/**
	 * @brief vec3 unitaire Z
	 */
	virtual vec3 getZ() const = 0;

	/**
	 * @brief renvoie la demie largeur de la hitbox
	 */
	virtual float getWidth() const = 0;

	/**
	 * @brief renvoie la demie hauteur de la hitbox
	 */
	virtual float getHeight() const = 0;

	/**
	 * @brief renvoie la demie profondeur de la hitbox
	 */
	virtual float getDepth() const = 0;
	
};


#endif