#pragma once
#include<cocos2d.h>
class PlayerAgent;
//表示指针的精灵，所有拿着的事物都是hand的子节点。这样以后玩家只需要移动hand即可，更好的封装性
class SelectAble
{
public:
	virtual bool isCatch()=0;
	virtual void bePickedUp()=0;
	virtual void doPlaced() {};
	virtual void undoPlace() {};
};
