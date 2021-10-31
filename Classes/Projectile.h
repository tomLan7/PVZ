#pragma once
#include<cocos2d.h>
#include<Unit.h>
#include<SelectAble.h>
class Projectile:public CanContact
{
	Unit* __shooter = nullptr;
protected:
	int _hurtValue=0;
public:
	Projectile();
	CREATE_FUNC(Projectile);
	bool init()override;
	virtual ~Projectile();
	void setHurtValue(int value) {
		_hurtValue = value;
	}
	auto getHurtValue()->decltype(_hurtValue){
		return _hurtValue;
	}
	Unit* getShooter() {
		return __shooter;
	}
	void setShooter(Unit* shooter) {
		__shooter = shooter;
	}
	
	
};

