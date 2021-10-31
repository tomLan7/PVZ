#include<PVZHeader.h>
#include"AudioEngine.h"
USING_NS_CC;





void Card::setCardConfig(float CD, int sunValue, float initCd)
{
	maxCd = CD;
	this->sunValue=sunValue;
	remainCD = initCd * CD;
	_ready = false;
	//auto pt=ProgressTimer::create(,);
}

inline void Card::update(float f) {
	MenuItemImage::update(f);

	if (isEnoughPaySun()) {//是否需要变颜色
		setColor(Color3B::WHITE);
	}
	else {
		setColor(Color3B::ORANGE);
	}
	if (_ready == false) {//走CD
		remainCD += f;
		cdP->setPercentage((1 - (remainCD / maxCd)) * 100);
		if (remainCD >= maxCd) {
			_ready = true;
			doCdComplete();
		}
	}
}

Card::Card()
{
}

bool Card::isEnoughPaySun()
{
	if (dynamic_cast<CardBar*>(getParent())->getSunValue() < getSunValue()) {
		return false;
	}
	return true;
}

bool Card::init()
{
	if (!MenuItemImage::init())
	{
		return false;
	}
		return true;
}

bool Card::initWithTwoPicture(const std::string& normal, const std::string& disable)
{
	scheduleUpdate();
	cdP = ProgressTimer::create(Sprite::create(disable));
	auto noP = Sprite::create(normal);
	cdP->setAnchorPoint(Vec2(0, 0));
	noP->addChild(cdP);
	if (!MenuItemImage::initWithNormalSprite(Sprite::create(normal), Sprite::create(disable), noP, [this](Ref* r) {onClick(); }))
	{
		return false;
	}
	return true;
}


Card::~Card()
{
}

float Card::getCD()
{
	return maxCd;
}

float Card::RemainingCD()
{
	return 0;
}

int Card::getSunValue()
{
	return sunValue;
}

bool Card::isReady()
{
	//浮点数比较不准确，需要和FLT_EPSILON比较
	return _ready;
}
void Card::onClick()
{
	if (!isEnoughPaySun()) {//阳光不够，无法执行放置卡牌操作
		cocos2d::AudioEngine::play2d("sunNotEnough.mp3");
		return;
	}
	auto p = PVZUtil::createSelectAble(targetName,cardType);
	auto cfc=dynamic_cast<CreateFromCard*>(p);
	if (cfc) {
		cfc->setCard(this);
	}
	getCardBar()->userCard(this);
	//植物的被点击了回调
	p->bePickedUp();
	PVZUtil::getPlayerAgent()->bePickedUp(p);
}

void Card::place()
{
	_ready = false;
	setEnabled(false);
	remainCD =0;
	cdP->setPercentage(100);
	getCardBar()->didUserCard();
}

void Card::undoPlace()
{
	getCardBar()->undoUserCard();
}

CardBar* Card::getCardBar()
{
	return dynamic_cast<CardBar*>(getParent());
}
