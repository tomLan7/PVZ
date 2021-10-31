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
		//���Զ�λ�����еĿհ�ͼ��
		auto GridNode=PVZUtil::getBattleScene()->getGridByIndex(PVZUtil::getBattleScene()->getPlaceholderIndex(getPosition()));
		//n->setPosition(convertToWorldSpace(n->getPosition()));
		auto n = getChildren().at(1);
		//�����λ����
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
	
	/*���ĳ�����������ɫ�Ĵ���
	CCLOG("click Pos(%f,%f)", getPosition().x, getPosition().y);
	//�����ս����
	auto bfs=PVZUtil::getHelloWorld();
	//��ö�Ӧ��GGraphͼ�Σ�Ҳ���ǿ�ͼ��
	auto p = bfs->getPlaceholderIndex(getPosition());
	auto gg=bfs->getGGraphByIndex(p);
	CCLOG("Graph Coordinate%d,%d",p.first,p.second);
	CCLOG("getGraph(%x)", gg);
	//�����Ļ���ˣ������ø�ͼ����ɫ
	if(gg)
	gg->drawRect(gg->getWidth(), gg->getHeight(), 5, Color4F::BLUE,Color4F::GREEN );
	*/

}

void PlayerAgent::cancel()
{
	if (!isEmptyHand()) {
		state = PA_free;
		//->setPosition(convertToNodeSpace());
	//CCLOG("current Child��Count%d",getChildrenCount());
		auto n = getChildren().at(1);
		dynamic_cast<CreateFromCard*>(n)->getCard()->undoPlace();
		dynamic_cast<SelectAble*>(n)->undoPlace();
		
	}
		
	
}
