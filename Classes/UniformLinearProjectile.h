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
	//// ������ĳ����λ�Ļص�
	virtual void doHitSomebody(CanContact&) {};
};

