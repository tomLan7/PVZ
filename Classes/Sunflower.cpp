
#include<PVZHeader.h>
using namespace std;
using namespace cocos2d;
bool Sunflower::__isLoad = false;
void Sunflower::loadAllNeededAnimateToCache()
{
	if (!__isLoad) {
		__isLoad=true;
		PVZUtil::createAnimationToCache("SunFlower1", 18, 1.2);
	}
}
bool Sunflower::init()
{
	if (!Plant::init())
	{
		return false;
	}
	
	return true;
}

void Sunflower::doPlaced()
{
	Plant::doPlaced();
	schedule(CC_SCHEDULE_SELECTOR(Sunflower::autoProductionSun),3);
}

void Sunflower::autoProductionSun(float) {
	auto sun = Sun::create();
	BattlefieldScene* scene = PVZUtil::getBattleScene();
	scene->addChild(sun);

	AudioEngine::play2d("SunBeBorn.mp3");//��������������Ч
	this->getAgent()->runAction(//���ж�������0.2���������0.6��䰵
		Sequence::createWithTwoActions(
			TintTo::create(0.2,Color3B(255,255,255)), 
			TintTo::create(0.6, Color3B(150, 150, 150))));

	sun->setPosition(getParent()->convertToWorldSpace(getPosition()));//�����ʼ�������ú�ֲ����ͬ
	sun->getAgent()->setOpacity(150);//�����ʼΪ��͸��
	sun->getAgent()->setScale(0.5);//�����ʼΪ������С��0.5����

	sun->getAgent()->runAction(FadeTo::create(0.8,250));//����һ���������ı�͸����
	sun->getAgent()->runAction(ScaleTo::create(0.8,1));//�ı������С�Ķ���

	Vec2 end = { (-25.f + (random() %150)),(float)(random() % 20) };//���һ���������λ��
	sun->runAction(BezierBy::create(1, ccBezierConfig{end ,{-20,100},{50,100} }));//�������˶���ȥ
}
