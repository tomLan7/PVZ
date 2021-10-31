#pragma once
#include<cocos2d.h>
#include<FairyGUI.h>
class Unit:public cocos2d::Node
{
	//agent��ʵ����ʾ�Ľڵ㡣������
	cocos2d::Node* __agent = nullptr;
	bool __isLoadAllNeedAnimation=false;
	std::string __currentAnimateName;
	protected:
	virtual void loadAllNeededAnimateToCache();
public:
	bool init()override;
	//���ļ�������������ʾ
	bool setAgentWithSpriteWithFileName(const std::string& name);
	Node* getAgent() {
		return __agent;
	}
	//��BUG�����޸���������add���µġ�
	void setAgentWithGMoveClip(fairygui::GMovieClip* Gc);
	void setAnimate(const std::string& animationName);
	const std::string& getCurrentAnimate();
	bool isLoadAllNeededAnimate()
	{
		return __isLoadAllNeedAnimation;
	}
	CREATE_FUNC(Unit);
};

