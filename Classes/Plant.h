#pragma once
#include<cocos2d.h>
#include<CanContact.h>
#include<CreateFromCard.h>
#include<SelectAble.h>
#include<Life.h>
class Life;
class Plant:public CanContact,public CreateFromCard,public SelectAble,public Life
{
public:
	
	bool init()override;
	CREATE_FUNC(Plant);
	Plant();
	virtual ~Plant();
	
	//终止放置，比如右键取消，此时应调用card的undoPlace()
	void undoPlace() override;

	// 通过 SelectAble 继承
	virtual void bePickedUp() override;
	//将植物放置在对应的点，以后需要根据地图计算网格。此时应调用card的place()
	virtual void doPlaced() override;

	virtual bool isCatch() override;
	virtual void died()override;
};

