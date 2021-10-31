#pragma once
#include<cocos2d.h>
#include<UniformLinearProjectile.h>
class Pea:public UniformLinearProjectile
{
	
public:
	Pea();
	CREATE_FUNC(Pea);
	bool init();
	virtual ~Pea();
	
};

