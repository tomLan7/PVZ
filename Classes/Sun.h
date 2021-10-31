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
	//����������ֵ�����ݸ���ֵ��ͬ�����������Ҳ��������
	int getSize();
	 //�޸��������ֵ����ѡ������ֵ�������ű�����
	void setSize(int size,bool changeShape=false);
	
	// ͨ�� SelectAble �̳�
	virtual bool isCatch() override;
	//���û����ʱ����
	virtual void bePickedUp() override;
	virtual void doPlaced() override;
	virtual void undoPlace() override;
};

