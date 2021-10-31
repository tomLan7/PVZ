#pragma once
#include<FairyGUI.h>
class Life
{
	fairygui::GProgressBar* health = nullptr;//±¾Ìå
public:
	Life();
	static Life* create() 
	{ 
		Life* pRet = new(std::nothrow) Life(); 
		if (pRet && pRet->init()) 
		{
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	}
	
	bool init();
	virtual ~Life();
	void attachLifeBarToUnit(Unit* main);
	virtual double getMaxHp() {
		return health->getMax();
	}

	virtual double getHp() {
		return health->getValue();
	}

	virtual void setHp(double hp) {
		health->setValue(hp);
	}

	virtual void cureHp(double dHp) {
		health->tweenValue(getHp()+dHp,0.3);
	}

	virtual void hurtHp(double dHp) {
		health->tweenValue(getHp() - dHp, 0.1);
	}
	virtual bool isAlive() {
		return getHp() > 0;
	}
	virtual void died(){}
	
};

