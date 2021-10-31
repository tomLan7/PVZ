
#include<PVZHeader.h>
using namespace std;
using namespace cocos2d;
bool Peashooter::__isLoad = false;
void Peashooter::loadAllNeededAnimateToCache()
{
	if (!__isLoad) {
		__isLoad = true;

		PVZUtil::createAnimationToCache("Peashooter", 12, 1.2);
	}
}
bool Peashooter::init()
{
	if (!Plant::init())
	{
		return false;
	}

	return true;
}

void Peashooter::doPlaced()
{
	Plant::doPlaced();
	schedule(CC_SCHEDULE_SELECTOR(Peashooter::autoProductionBullet),1);
}

void Peashooter::autoProductionBullet(float) {
	AudioEngine::play2d("PeaShooting.mp3");
	auto pea = Pea::create();
	pea->_setLocalZOrder(80);
	pea->setHurtValue(40);
	BattlefieldScene* scene = PVZUtil::getBattleScene();
	scene->addChild(pea);
	pea->getPhysicsBody()->setVelocity(Vec2(400,0));//设置初速度的向量为 400,0 （向右）
	pea->setPosition(getParent()->convertToWorldSpace(getPosition()+Vec2(31,21)));//应该对准嘴
	scheduleOnce([pea](float) {
		pea->removeFromParent();
		}, 10,"TimeOutkillPea");

	//pea->runAction(Sequence::createWithTwoActions(
	//	MoveBy::create(3, Vec2(1000, 0)),
	//	RemoveSelf::create()));
}
