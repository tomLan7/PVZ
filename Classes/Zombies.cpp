#include "Sun.h"
#include<PVZHeader.h>

USING_NS_CC;
USING_NS_FGUI;
bool Zombies::__isLoad = false;
void Zombies::loadAllNeededAnimateToCache()
{
	if (!__isLoad) {
		__isLoad = true;

		PVZUtil::createAnimationToCache("ZombieStand1", 11, 1.2);
		PVZUtil::createAnimationToCache("ZombieHead", 12, 1,1);
		PVZUtil::createAnimationToCache("ZombieDie", 10, 1,1);
		PVZUtil::createAnimationToCache("ZombieWalk1", 22,1.8);
		PVZUtil::createAnimationToCache("ZombieAttack", 21, 1.8);
	}
}
Zombies::Zombies()
{

}


bool Zombies::init()
{
	if (!CanContact::init() || !Life::init()) {
		return false;
	}

	return true;
}

bool Zombies::isCatch()
{
	return true;
}

void Zombies::bePickedUp()
{
}

void Zombies::doPlaced()
{
	setType(PVZUtil::BodyType::Zombie);//������ײĿ���� ��2������ֲ���ӵ���������3������home����
	//���ڵ������߶�λ��ǰֲ����㷨��DrawNode* dn = DrawNode::create();getScene()->addChild(dn);dn->setName("drawNode");
	schedule(CC_SCHEDULE_SELECTOR(Zombies::doThink),0.33);
	AudioEngine::play2d("groan5.mp3");
	setAnimate("ZombieWalk1");
}

void Zombies::undoPlace()
{
	removeFromParentAndCleanup(true);
}

void Zombies::doContact(Projectile* pjct)
{
	AudioEngine::play2d("PeaHitZombies1.mp3");
	hurtHp(pjct->getHurtValue());
	if (!Life::isAlive()) {
		died();
	}
}

void Zombies::died()
{
	unschedule(CC_SCHEDULE_SELECTOR(Zombies::doThink));
	setType(PVZUtil::BodyType::Default);
	setAnimate("ZombieDie");

	auto head = Unit::create();
	head->setAnimate("ZombieHead");
	head->setPosition(65,-9);
	head->setAnchorPoint(Vec2(0.5,0.5));
	addChild(head);
	scheduleOnce([head,this](float) {
		head->removeFromParent();
		this->removeFromParent();
	}, 2,"die");

}

void Zombies::doThink(float d)
{
	//��ʱPostion��ռλ�����λ�ã���׼ȷ��Ӧ���ø��������򾭹�ת��������
	auto a1=MoveBy::create(0.25, Vec2(-50, 0));
	runAction(a1);
	a1->setTag(11);
	Vec2 curGlobaPos = getParent()->convertToWorldSpace(getPosition());
	
	bool isNotEat=true;
	getPhysicsBody()->getWorld()->rayCast([this,&isNotEat](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)->bool{
		Vec2 pos = info.shape->getBody()->getNode()->getPosition();
		
		if (info.shape->getBody() == this->getPhysicsBody()) {
			return true;
		}
		if (info.shape->getBody()->getName() == "home") {
			
			return false;
		}
		if ( (info.shape->getBody()->getCategoryBitmask() & PVZUtil::PlantFlag) == 0) {//����ֲ������ɨ����һ��
			return true;
		}
		isNotEat = false;
		stopActionByTag(11);//�����ϰ����ˣ�ֹͣ�ƶ�����ʼ��
		
		Node* n = info.shape->getBody()->getNode();
		auto plant=dynamic_cast<Plant*>(n);
		plant->hurtHp(atk);
		setAnimate("ZombieAttack");
		AudioEngine::play2d("chomp.mp3");
		if (!plant->isAlive()) {
			plant->died();
		}
		return false;
		
		}, curGlobaPos, curGlobaPos+Vec2(0, 0), 0);
	if (isNotEat) {
		setAnimate("ZombieWalk1");
	}
	//static_cast<DrawNode*>(getScene()->getChildByName("drawNode"))->clear();
	//static_cast<DrawNode*>(getScene()->getChildByName("drawNode"))->drawLine(curGlobaPos, curGlobaPos + Vec2(-200, 0),Color4F::BLUE );
}

Zombies::~Zombies()
{
}

