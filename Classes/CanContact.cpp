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

//���ø���Ĳ�������
void CanContact::setType(PVZUtil::BodyType type) {//���ø�����ʲô���͡����Զ�������������
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
