#pragma once
#include<cocos2d.h>
class Plant;
class SelectAble;
//表示鼠标的精灵，所有拿着的事物都是hand的子节点。这样以后玩家只需要移动hand即可，更好的封装性
class PlayerAgent:public Unit
{
	//光标的位置，会一直维护这个位置
	enum { PA_free, PA_busy }state=PA_free;
public:
	bool init();
	CREATE_FUNC(PlayerAgent);
	PlayerAgent();
	//用isCatch方法判断该物品是否应该被拿起，如果可被拿起的，就会拿起
	void bePickedUp(SelectAble*);
	void putDown();
	void cancel();
	//是否空手
	bool isEmptyHand() {
		return getChildrenCount()<=1;
	}
	//可以拿，和是否空手语义有区别，目前是相同的
	bool canPickUp() {
		return  state== PA_free;
	}
};

