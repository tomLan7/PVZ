#pragma once
#include<cocos2d.h>
#include<functional>
class Plant;
class Card;
class CreateFromCard
{
	Card* cd=nullptr;
public:
	//�����ȴʱ��
	Card* getCard() {
		return cd;
	};
	void setCard(Card* card) {
		cd = card;
	}
	
};

