#include "PVZHeader.h"
USING_NS_CC;
USING_NS_FGUI;
Life::Life()
{

}

bool Life::init()
{
	health = UIPackage::createObject("Test", "SimpleLifeBar")->as<GProgressBar>();
	return health!=nullptr;
}

Life::~Life()
{
	health->release();
}

void Life::attachLifeBarToUnit(Unit* main)
{
	auto size = main->getAgent()->getContentSize();
	main->addChild(health->displayObject());
	health->retain();
	
	health->setWidth(size.width);
	health->displayObject()->setPosition(-size.width/2,size.height*0.65);
	health->setValue(0);
	health->tweenValue(100,0.5);
}
