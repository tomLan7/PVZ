#include "Sun.h"
#include<PVZHeader.h>

USING_NS_CC;


UniformLinearProjectile::UniformLinearProjectile()
{
}


bool UniformLinearProjectile::init()
{
	if (!Projectile::init()) {
		return false;
	}
	return true;
}

UniformLinearProjectile::~UniformLinearProjectile()
{
}

