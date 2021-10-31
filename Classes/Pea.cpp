#include "Sun.h"
#include<PVZHeader.h>

USING_NS_CC;


Pea::Pea()
{
}


bool Pea::init()
{
	if (!UniformLinearProjectile::init()) {
		return false;
	}
	
	setAgentWithSpriteWithFileName("Pea01.png");
	auto pb = PhysicsBody::createCircle(12);//创建一个半径12的圆形刚体
	setPhysicsBody(pb);//设置为当前
	pb->setGravityEnable(false);
	setType(PVZUtil::BodyType::PlantProjectile);
	
	auto e1 = EventListenerPhysicsContact::create();//设置接触事件
	e1->onContactBegin = [this](PhysicsContact& contact) {//设置接触时调用的函数
		auto n=contact.getCurrentTarget();//一方
		Node* otherOne=nullptr;//另一个
		//碰撞其一有该豌豆，才会让该豌豆消失
		if (this == contact.getShapeA()->getBody()->getNode()) {
			otherOne = contact.getShapeB()->getBody()->getNode();
		}else if(this==contact.getShapeB()->getBody()->getNode()) {
			otherOne == contact.getShapeA()->getBody()->getNode();
		}
		if (otherOne) {//确认是撞到人了
			auto canContactObj=dynamic_cast<CanContact*>(otherOne);
			canContactObj->doContact(this);
			this->doHitSomebody(*canContactObj);
			n->removeFromParent();
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(e1, this);

	return true;
}

Pea::~Pea()
{
}


