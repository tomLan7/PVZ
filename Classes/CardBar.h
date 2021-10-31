#pragma once
#include "cocos2d.h"
#include "Card.h"
#include"Sun.h"
#include<Sunflower.h>
//�洢�˵���
class Card;
class CardBar :
	public cocos2d::Menu
{	
	//��ǰ����ʹ�õĿ�
	Card* __currentCard=nullptr;
	int sunSum=0;
	CardBar();
protected:
	virtual bool init();
	void _updateSunCounter();
	public:
	CREATE_FUNC(CardBar);
	~CardBar();
	//���һ�����ƣ������һ������
	void addCard(Card* card);
	//���һ�����⣬ÿ��������ֵ���ǹ̶��ġ�
	void addSun(Sun* sun);
	//ʹ��һ�ſ��ƣ������Ķ�Ӧ������ֵ�����⡣
	void userCard(Card*);
	Card* currentCard();
	//����ʹ��һ�ſ��ƣ��ỹ�ض�Ӧ������ֵ������
	void undoUserCard();
	//���óɹ������״̬
	void didUserCard();
	//��õ�ǰ�������ֵ
	int getSunValue();
	
};

