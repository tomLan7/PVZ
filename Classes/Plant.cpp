#include "Plant.h"
#include<PVZHeader.h>
#include<cocos2d.h>
#include"AudioEngine.h"
USING_NS_CC;

bool Plant::init()
{
	if (!CanContact::init()||!Life::init())
	{
		return false;
	}
	//用来调试，先放一个图
	setOpacity(150);
	return true;
}

Plant::Plant()
{
	
}


Plant::~Plant()
{
}


void Plant::undoPlace()
{
	removeFromParentAndCleanup(true);
}

void Plant::bePickedUp()
{
	cocos2d::AudioEngine::play2d("pickUpPlant.mp3");
	
}

void Plant::doPlaced()
{
	cocos2d::AudioEngine::play2d("placePlants.mp3");
	getAgent()->setOpacity(255);
	setType(PVZUtil::BodyType::Plant);
}

bool Plant::isCatch()
{
	return true;
}

void Plant::died()
{
	removeFromParent();
}
