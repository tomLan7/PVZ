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
	auto pb = PhysicsBody::createCircle(12);//����һ���뾶12��Բ�θ���
	setPhysicsBody(pb);//����Ϊ��ǰ
	pb->setGravityEnable(false);
	setType(PVZUtil::BodyType::PlantProjectile);
	
	auto e1 = EventListenerPhysicsContact::create();//���ýӴ��¼�
	e1->onContactBegin = [this](PhysicsContact& contact) {//���ýӴ�ʱ���õĺ���
		auto n=contact.getCurrentTarget();//һ��
		Node* otherOne=nullptr;//��һ��
		//��ײ��һ�и��㶹���Ż��ø��㶹��ʧ
		if (this == contact.getShapeA()->getBody()->getNode()) {
			otherOne = contact.getShapeB()->getBody()->getNode();
		}else if(this==contact.getShapeB()->getBody()->getNode()) {
			otherOne == contact.getShapeA()->getBody()->getNode();
		}
		if (otherOne) {//ȷ����ײ������
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


