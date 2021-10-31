#pragma once
#include<cocos2d.h>
class Plant;
class SelectAble;
//��ʾ���ľ��飬�������ŵ����ﶼ��hand���ӽڵ㡣�����Ժ����ֻ��Ҫ�ƶ�hand���ɣ����õķ�װ��
class PlayerAgent:public Unit
{
	//����λ�ã���һֱά�����λ��
	enum { PA_free, PA_busy }state=PA_free;
public:
	bool init();
	CREATE_FUNC(PlayerAgent);
	PlayerAgent();
	//��isCatch�����жϸ���Ʒ�Ƿ�Ӧ�ñ���������ɱ�����ģ��ͻ�����
	void bePickedUp(SelectAble*);
	void putDown();
	void cancel();
	//�Ƿ����
	bool isEmptyHand() {
		return getChildrenCount()<=1;
	}
	//�����ã����Ƿ��������������Ŀǰ����ͬ��
	bool canPickUp() {
		return  state== PA_free;
	}
};

