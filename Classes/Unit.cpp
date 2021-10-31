#include "PVZHeader.h"

USING_NS_CC;

bool Unit::init()
{
	if (!Node::init())
	{
		return false;
	}
	if (!isLoadAllNeededAnimate()) {
		__isLoadAllNeedAnimation = true;
		loadAllNeededAnimateToCache();
	}
	return true;
}

bool Unit::setAgentWithSpriteWithFileName(const std::string & filename)
{
	if (__agent != nullptr) {
		__agent->removeFromParentAndCleanup(true);
	}
	__agent =Sprite::create(filename);
	if (__agent == nullptr) {
		return false;
	}
	addChild(__agent);
	
	return true;
}

void  Unit::setAgentWithGMoveClip(fairygui::GMovieClip* Gc) {
	if (__agent != nullptr) {
		__agent->removeFromParentAndCleanup(true);
		
	}
	Gc->retain();
	__agent = Gc->displayObject();
	__agent->setPosition(0,0); 
	__agent->setAnchorPoint(Vec2(0.5,0.5));
	addChild(__agent);
	Gc->setPlaySettings();
	Gc->setPlaying(true);
}

void Unit::setAnimate(const std::string& animationName) {
	if (__agent == nullptr) {
		__agent = Sprite::create("animation/"+animationName+"_0000.png");
		addChild(__agent);
	}
	if (animationName == __currentAnimateName) {
		return;
	}
	else {
		__currentAnimateName = animationName;
		getAgent()->stopAllActionsByTag(123);
		auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
		animate->setTag(123);
		getAgent()->runAction(animate);
	}

}

const std::string& Unit::getCurrentAnimate()
{
	return __currentAnimateName;
}

void Unit::loadAllNeededAnimateToCache()
{
	
}

