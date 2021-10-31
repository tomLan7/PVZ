#pragma once
#include<cocos2d.h>
#include<functional>
class Plant;
class Card;
class CreateFromCard
{
	Card* cd=nullptr;
public:
	//获得冷却时间
	Card* getCard() {
		return cd;
	};
	void setCard(Card* card) {
		cd = card;
	}
	
};

