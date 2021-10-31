#pragma once
#include<cocos2d.h>
#include<CanContact.h>
#include<CreateFromCard.h>
#include<SelectAble.h>
#include<Life.h>

class Zombies :public CanContact, public CreateFromCard, public SelectAble,public Life
{
	int atk=30;
	static bool __isLoad;
	void loadAllNeededAnimateToCache()override;
public:
	Zombies();
	CREATE_FUNC(Zombies);
	bool init();
	virtual ~Zombies();
	virtual void hurtHp(double dHp) {
		Life::hurtHp(dHp);
	}
	// Í¨¹ý SelectAble ¼Ì³Ð
	virtual bool isCatch() override;
	virtual void bePickedUp() override;
	virtual void doPlaced() override;
	virtual void undoPlace() override;
	virtual void doContact(Projectile* pjct)override;
	virtual void died()override;
	virtual void doThink(float f);
};

