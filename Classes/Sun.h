#pragma once
#include<cocos2d.h>
#include<Unit.h>
#include<SelectAble.h>
class Sun:public Unit,public SelectAble
{
	int sunValue=50;
protected:
	bool init();
	Sun();
	
public:
	CREATE_FUNC(Sun);
	virtual ~Sun();
	//获得阳光的数值，根据该数值不同，阳光的体型也会有区别
	int getSize();
	 //修改阳光的数值，可选根据数值设置缩放比例。
	void setSize(int size,bool changeShape=false);
	
	// 通过 SelectAble 继承
	virtual bool isCatch() override;
	//被用户点击时调用
	virtual void bePickedUp() override;
	virtual void doPlaced() override;
	virtual void undoPlace() override;
};

