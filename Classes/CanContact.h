#pragma once
#include<cocos2d.h>
#include<Unit.h>
#include<PVZUtil.h>
class Projectile;
//表示指针的精灵，所有拿着的事物都是hand的子节点。这样以后玩家只需要移动hand即可，更好的封装性
class CanContact :public Unit
{
public:
	PVZUtil::BodyType bodyType;
	//刚体参数，按照顺序来,分别是刚体码，接触码，碰撞码
	
	bool init();
	CanContact();
	virtual void doContact(Projectile*) {
		
	};
	void setType(PVZUtil::BodyType type);
	//设置刚体为自身的大小，
	void setPhysicBodyBySelfContentSize();
};

