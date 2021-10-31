#include "PVZHeader.h"
#include"Plant.h"
USING_NS_CC;
bool CanContact::init()
{
	if (!Unit::init())
	{
		return false;
	}
	
	return true;
}

CanContact::CanContact()
{
}

//设置刚体的参数数据
void CanContact::setType(PVZUtil::BodyType type) {//设置刚体是什么类型。会自动设置三种掩码
	bodyType = type;
	PVZUtil::setPhysicsBodyFlag(getPhysicsBody(),type);
}

void CanContact::setPhysicBodyBySelfContentSize() {
	auto s = getAgent()->getContentSize();
	auto pb = PhysicsBody::createBox(s);
	pb->setGravityEnable(false);
	setPhysicsBody(pb); 
	setType(PVZUtil::BodyType::Default);
}
