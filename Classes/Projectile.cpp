
#include<PVZHeader.h>

USING_NS_CC;


Projectile::Projectile()
{
}


bool Projectile::init()
{
	if (!Unit::init()) {
		return false;
	}
	return true;
}

Projectile::~Projectile()
{
}