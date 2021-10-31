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
	//e->setSwallowTouches(true);//ΪʲôûЧ����������onTouchBegan������stop
	e->onTouchBegan = [](Touch* t, Event* e)->bool {
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(e->getCurrentTarget()->getParent()->convertTouchToNodeSpace(t))) {
			dynamic_cast<SelectAble*>(e->getCurrentTarget()->getParent())->bePickedUp();//��Ϊ�󶨵��Ǵ������Ի�ø��������Sun����
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
	
	AudioEngine::play2d("pickUpSun.mp3");//�������ⱻ���������
	runAction(ScaleBy::create(0.3,1.25));//��������
	//���ж���������0.35����͸���ȱ�Ϊ0�����Ӽ����Լ�ɾ������
	getAgent()->runAction(Sequence::create(FadeOut::create(0.35), CallFunc::create([this]() {
		PVZUtil::getBattleScene()->getCardBar()->addSun(this);
		})
	, RemoveSelf::create(),NULL));//����������������ݶ������ʱ�����һ���������봫��NULL.
	runAction(MoveTo::create(0.3,PVZUtil::getBattleScene()->getSunCounterPos()));
	//����������ӽ� ��������
	
	
}

void Sun::doPlaced()
{
}

void Sun::undoPlace()
{
}

