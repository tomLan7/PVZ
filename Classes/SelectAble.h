#pragma once
#include<cocos2d.h>
class PlayerAgent;
//��ʾָ��ľ��飬�������ŵ����ﶼ��hand���ӽڵ㡣�����Ժ����ֻ��Ҫ�ƶ�hand���ɣ����õķ�װ��
class SelectAble
{
public:
	virtual bool isCatch()=0;
	virtual void bePickedUp()=0;
	virtual void doPlaced() {};
	virtual void undoPlace() {};
};
