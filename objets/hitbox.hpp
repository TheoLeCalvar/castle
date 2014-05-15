#ifndef HITBOX
#define HITBOX 

#include "helper.hpp"

class Hitbox
{
public:
	virtual bool collide(const Hitbox & h) const
	{
		vec3 aP = getP(), aX = getX(), aY = getY(), aZ = getZ();
		float aW = getWidth(), aH = getHeight(), aD = getDepth();

		vec3 bP = h.getP(), bX = h.getX(), bY = h.getY(), bZ = h.getZ();
		float bW = h.getWidth(), bH = h.getHeight(), bD = h.getDepth();

		vec3 t = bP - aP;


		return false;
	}

	virtual vec3 getP() const = 0;
	virtual vec3 getX() const = 0;
	virtual vec3 getY() const = 0;
	virtual vec3 getZ() const = 0;
	virtual float getWidth() const = 0;
	virtual float getHeight() const = 0;
	virtual float getDepth() const = 0;
	
};


#endif