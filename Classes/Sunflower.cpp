
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

	AudioEngine::play2d("SunBeBorn.mp3");//播放阳光生产音效
	this->getAgent()->runAction(//序列动作，先0.2秒变亮，再0.6秒变暗
		Sequence::createWithTwoActions(
			TintTo::create(0.2,Color3B(255,255,255)), 
			TintTo::create(0.6, Color3B(150, 150, 150))));

	sun->setPosition(getParent()->convertToWorldSpace(getPosition()));//阳光初始坐标设置和植物相同
	sun->getAgent()->setOpacity(150);//阳光初始为半透明
	sun->getAgent()->setScale(0.5);//阳光初始为正常大小的0.5倍。

	sun->getAgent()->runAction(FadeTo::create(0.8,250));//阳光一个动画，改变透明度
	sun->getAgent()->runAction(ScaleTo::create(0.8,1));//改变阳光大小的动画

	Vec2 end = { (-25.f + (random() %150)),(float)(random() % 20) };//随机一个阳光落地位置
	sun->runAction(BezierBy::create(1, ccBezierConfig{end ,{-20,100},{50,100} }));//贝塞尔运动过去
}
