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
	
	//��ֹ���ã������Ҽ�ȡ������ʱӦ����card��undoPlace()
	void undoPlace() override;

	// ͨ�� SelectAble �̳�
	virtual void bePickedUp() override;
	//��ֲ������ڶ�Ӧ�ĵ㣬�Ժ���Ҫ���ݵ�ͼ�������񡣴�ʱӦ����card��place()
	virtual void doPlaced() override;

	virtual bool isCatch() override;
	virtual void died()override;
};

