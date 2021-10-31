#pragma once
#include "Unit.h"
#include"cocos2d.h"
class PVZBase :
    public Unit
{
public:
    
	PVZBase();
	CREATE_FUNC(PVZBase);
	bool init();
	virtual ~PVZBase();
};

