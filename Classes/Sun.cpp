#include<PVZHeader.h>

USING_NS_CC;


Sun::Sun()
{
}


bool Sun::init()
{
	if (!Unit::init()) {
		return false;
	}
	setAgentWithSpriteWithFileName("Sun.png");

	auto e = EventListenerTouchOneByOne::create();
	//e->setSwallowTouches(true);//为什么没效果？必须在onTouchBegan中设置stop
	e->onTouchBegan = [](Touch* t, Event* e)->bool {
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(e->getCurrentTarget()->getParent()->convertTouchToNodeSpace(t))) {
			dynamic_cast<SelectAble*>(e->getCurrentTarget()->getParent())->bePickedUp();//因为绑定的是代理，所以获得父对象就是Sun对象
			e->stopPropagation();
			return true;
		}
		return false;

	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(e, this->getAgent());

	return true;
}

Sun::~Sun()
{
}

int Sun::getSize()
{
	return sunValue;
}

void Sun::setSize(int size, bool changeShape)
{
	sunValue = size;
	if (changeShape) {
		setScale(size/25.f);
	}
}

bool Sun::isCatch()
{
	return false;
}

void Sun::bePickedUp()
{	
	
	AudioEngine::play2d("pickUpSun.mp3");//播放阳光被捡起的声音
	runAction(ScaleBy::create(0.3,1.25));//让阳光变大
	//序列动作：先用0.35秒让透明度变为0，增加计数以及删除自身
	getAgent()->runAction(Sequence::create(FadeOut::create(0.35), CallFunc::create([this]() {
		PVZUtil::getBattleScene()->getCardBar()->addSun(this);
		})
	, RemoveSelf::create(),NULL));//连续动作，如果传递多个动作时，最后一个动作必须传入NULL.
	runAction(MoveTo::create(0.3,PVZUtil::getBattleScene()->getSunCounterPos()));
	//将该阳光添加进 卡牌栏中
	
	
}

void Sun::doPlaced()
{
}

void Sun::undoPlace()
{
}

