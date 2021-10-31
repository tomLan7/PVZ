#pragma once
#include<cocos2d.h>
#include<Projectile.h>
class UniformLinearProjectile :public Projectile
{
public:
	UniformLinearProjectile();
	CREATE_FUNC(UniformLinearProjectile);
	bool init();
	virtual ~UniformLinearProjectile();
	//// 击中了某个单位的回调
	virtual void doHitSomebody(CanContact&) {};
};

