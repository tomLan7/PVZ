#pragma once
#include<cocos2d.h>
#include<Unit.h>
#include<PVZUtil.h>
class Projectile;
//��ʾָ��ľ��飬�������ŵ����ﶼ��hand���ӽڵ㡣�����Ժ����ֻ��Ҫ�ƶ�hand���ɣ����õķ�װ��
class CanContact :public Unit
{
public:
	PVZUtil::BodyType bodyType;
	//�������������˳����,�ֱ��Ǹ����룬�Ӵ��룬��ײ��
	
	bool init();
	CanContact();
	virtual void doContact(Projectile*) {
		
	};
	void setType(PVZUtil::BodyType type);
	//���ø���Ϊ����Ĵ�С��
	void setPhysicBodyBySelfContentSize();
};

