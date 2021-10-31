#pragma once
#include "cocos2d.h"
#include "Card.h"
#include"Sun.h"
#include<Sunflower.h>
//存储菜单栏
class Card;
class CardBar :
	public cocos2d::Menu
{	
	//当前正在使用的卡
	Card* __currentCard=nullptr;
	int sunSum=0;
	CardBar();
protected:
	virtual bool init();
	void _updateSunCounter();
	public:
	CREATE_FUNC(CardBar);
	~CardBar();
	//添加一个卡牌，多管理一个卡牌
	void addCard(Card* card);
	//获得一份阳光，每份阳光数值不是固定的。
	void addSun(Sun* sun);
	//使用一张卡牌，会消耗对应卡牌数值的阳光。
	void userCard(Card*);
	Card* currentCard();
	//撤销使用一张卡牌，会还回对应卡牌数值的阳光
	void undoUserCard();
	//放置成功，清除状态
	void didUserCard();
	//获得当前阳光的数值
	int getSunValue();
	
};

