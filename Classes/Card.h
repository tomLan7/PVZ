#pragma once
#include<cocos2d.h>
#include<functional>
class Plant;
/*
* Card 继承了菜单项可以点击。以后不会让他继承菜单项。先这样简单使用
*/
class CardBar;
class Card:public cocos2d::MenuItemImage
{
	float maxCd=5;
	float remainCD=5;
	int sunValue=0;
	bool _ready=true;
	cocos2d::ProgressTimer* cdP=nullptr;
	std::string targetName="默认";
protected:
	bool initWithTwoPicture(const std::string& normal, const std::string& disable);
	bool init()override;
public:
	enum class CardType {//卡牌类型
		Plant, Zombie
	}cardType;

	CREATE_FUNC(Card);
	//maxCd是植物CD。sunValue是阳光消耗。normal是普通时图片，disable是转动的图片,initCd是初始CD的百分比0：初始灰色，1初始可用
	static Card* create(float maxCd,int sunValue,const std::string& normal,const std::string& disable,float initCd=1) {
		auto c=Card::create();
		c->initWithTwoPicture(normal,disable);
		c->setCardConfig(maxCd,sunValue,1);
		return c;
	}

	void doCdComplete(float=0) {
		_ready = true;
		setEnabled(true);
	}
	void setTargetName(const std::string& name, CardType type) {
		targetName = name;
		cardType = type;
	}
	void setCardConfig(float CD,int sunValue, float initCd);
	void update(float f)override;
	Card();
	//默认调试用的初始化
	bool isEnoughPaySun();
	//使用两个文件名来初始化
	virtual ~Card();
	//获得冷却时间
	float getCD(); 
	//获得还剩多久才能卡牌才能冷却完毕。
	float RemainingCD();
	int getSunValue();
	//判断是否准备就绪
	bool isReady();
	//点击按钮会调用的函数。把当前对象放手中。
	void onClick();
	//当前click的植物被放置。开始冷却计时。
	void place();
	//撤销放置植物。不开始冷却计时。
	void undoPlace();
	CardBar* getCardBar();
};

