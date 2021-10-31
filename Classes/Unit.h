#pragma once
#include<cocos2d.h>
#include<FairyGUI.h>
class Unit:public cocos2d::Node
{
	//agent是实际显示的节点。可以是
	cocos2d::Node* __agent = nullptr;
	bool __isLoadAllNeedAnimation=false;
	std::string __currentAnimateName;
	protected:
	virtual void loadAllNeededAnimateToCache();
public:
	bool init()override;
	//用文件创建精灵来显示
	bool setAgentWithSpriteWithFileName(const std::string& name);
	Node* getAgent() {
		return __agent;
	}
	//有BUG，已修复，是忘了add导致的。
	void setAgentWithGMoveClip(fairygui::GMovieClip* Gc);
	void setAnimate(const std::string& animationName);
	const std::string& getCurrentAnimate();
	bool isLoadAllNeededAnimate()
	{
		return __isLoadAllNeedAnimation;
	}
	CREATE_FUNC(Unit);
};

