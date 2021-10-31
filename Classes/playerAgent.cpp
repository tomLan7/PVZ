#include "PVZHeader.h"
USING_NS_CC;
bool PlayerAgent::init()
{
	if (!Unit::init())
	{
		return false;
	}
	setAgentWithSpriteWithFileName("mouse.png");
	getAgent()->setAnchorPoint(Vec2(0.06, 1 - 0.06f));
	state = PA_free;
	auto em = EventListenerMouse::create();
	em->onMouseMove = [this](EventMouse* event) {
		setPosition(event->getLocationInView());
	};
	em->onMouseDown = [this](EventMouse* event) {
		
		switch (event->getMouseButton())
		{
		case cocos2d::EventMouse::MouseButton::BUTTON_LEFT:
			this->putDown();
			break;
		case cocos2d::EventMouse::MouseButton::BUTTON_RIGHT:
			this->cancel();
			break;
		default:
			break;
		}
	};
	ShowCursor(false);

	setName("hand");
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(em, 1);

	return true;
}
PlayerAgent::PlayerAgent()
{
		
}

void  PlayerAgent::bePickedUp(SelectAble * p)
{
	if (canPickUp()) {
		if (p->isCatch()) {
			state = PA_busy;
			auto np = dynamic_cast<Node*>(p);
			if (np) {
				addChild(np);
			}
		}

	}
		
}

void PlayerAgent::putDown()
{
	if (!isEmptyHand()) {
		//尝试定位网格中的空白图形
		auto GridNode=PVZUtil::getBattleScene()->getGridByIndex(PVZUtil::getBattleScene()->getPlaceholderIndex(getPosition()));
		//n->setPosition(convertToWorldSpace(n->getPosition()));
		auto n = getChildren().at(1);
		//如果定位到了
		if (GridNode) {
			

			state = PA_free;
			n->retain();
			n->removeFromParentAndCleanup(false);
			n->setPosition(GridNode->getBoundingBox().size/2);
			GridNode->addChild(n);
			dynamic_cast<CreateFromCard*>(n)->getCard()->place();
			dynamic_cast<SelectAble*>(n)->doPlaced();
			n->release();
		}
		else {
		
		}
		//->addChild(n);
		


	}
	
	/*点击某个网格让其变色的代码
	CCLOG("click Pos(%f,%f)", getPosition().x, getPosition().y);
	//获得主战场，
	auto bfs=PVZUtil::getHelloWorld();
	//获得对应的GGraph图形，也就是空图形
	auto p = bfs->getPlaceholderIndex(getPosition());
	auto gg=bfs->getGGraphByIndex(p);
	CCLOG("Graph Coordinate%d,%d",p.first,p.second);
	CCLOG("getGraph(%x)", gg);
	//如果真的获得了，就设置该图形颜色
	if(gg)
	gg->drawRect(gg->getWidth(), gg->getHeight(), 5, Color4F::BLUE,Color4F::GREEN );
	*/

}

void PlayerAgent::cancel()
{
	if (!isEmptyHand()) {
		state = PA_free;
		//->setPosition(convertToNodeSpace());
	//CCLOG("current Child　Count%d",getChildrenCount());
		auto n = getChildren().at(1);
		dynamic_cast<CreateFromCard*>(n)->getCard()->undoPlace();
		dynamic_cast<SelectAble*>(n)->undoPlace();
		
	}
		
	
}
