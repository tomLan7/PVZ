#include "PVZHeader.h"
USING_NS_CC;


bool CardBar::init()
{
	if (!Menu::init())
	{
		return false;
	}
	
	//auto size = Director::getInstance()->getWinSizeInPixels();
	//setAnchorPoint(Vec2(1,0));
	//setIgnoreAnchorPointForPosition(false);
	//setPosition(Vec2(size.width/15,size.height/2));
	return true;
}

void CardBar::_updateSunCounter()
{
	PVZUtil::getBattleScene()->getSunCounter()->setText(std::to_string(getSunValue()));
}

CardBar::CardBar()
{
	
}


CardBar::~CardBar()
{
	
}


void CardBar::addCard(Card *c)
{
	addChild(c);
}

void CardBar::addSun(Sun * s)
{
	sunSum += s->getSize(); 
	_updateSunCounter();
}

void CardBar::userCard(Card * c)
{
	if (__currentCard == nullptr) {
		__currentCard = c;
		sunSum -= c->getSunValue();
		_updateSunCounter();
	}

}

Card* CardBar::currentCard()
{
	return __currentCard;
}

void CardBar::undoUserCard()
{
	if (__currentCard) {
		sunSum += __currentCard->getSunValue();
		__currentCard = nullptr;
		_updateSunCounter();
	}
}

void CardBar::didUserCard()
{
	if (__currentCard) {
		__currentCard = nullptr;
	}
}

int CardBar::getSunValue()
{
	return sunSum;
}
