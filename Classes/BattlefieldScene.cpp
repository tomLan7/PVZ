/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "PVZHeader.h"
#include"CardBar.h"
#include"card.h"
#include"playerAgent.h"
#include"spine/spine-cocos2dx.h"
using namespace std;
USING_NS_CC;
USING_NS_FGUI;
#include<ui/CocosGUI.h>
// Print useful error message instead of segfaulting when files are not there.
// on "init" you need to initialize your instance
bool BattlefieldScene::init()
{
    //////////////////////////////
    // 1. super init first
    //if ( !Scene::init() ) 更改为
	if(!BaseScene::init(UIPackage::createObject("Test", "RearGardenMap")))
    {
        return false;
	}
	/*初始化动画资源
	*/
	
	
	/**/
	//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	/*******************************************************************
	* 
	初始化home区域*/
	auto homeNode=_view->getChild("home")->displayObject();
	auto homeNodePb = PhysicsBody::createBox(homeNode->getContentSize());
	
	PVZUtil::setPhysicsBodyFlag(homeNodePb,PVZUtil::BodyType::home);
	homeNodePb->setName("home");
	homeNodePb->setGravityEnable(false);
	homeNode->setPhysicsBody(homeNodePb);

	auto epc=EventListenerPhysicsContact::create();

	epc->onContactBegin = [homeNode,this](PhysicsContact& contact)->bool {
		Node* other=nullptr;
		if (contact.getShapeA()->getBody()->getNode()==homeNode) {
			other = contact.getShapeB()->getBody()->getNode();
		}else if(contact.getShapeB()->getBody()->getNode() == homeNode) {
			other = contact.getShapeA()->getBody()->getNode();
		}
		if (other) {
			//说明有僵尸接触到了home，此时宣告游戏结束
			gameFail();
		}
		return false;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(epc, homeNode);
	/********************************************************************
	初始化home结束*/
	/*******************************************************************
	卡牌栏初始化
	*/
	
	std::vector<Card*> cardList = {};
	auto c1 = Card::create(5,50,"sunFlower1.png","sunFlower2.png");
	c1->setTargetName("SunFlower",Card::CardType::Plant);
	cardList.push_back(c1);
	auto c2 = Card::create(3,100, "Peashooter1.png", "Peashooter2.png");
	c2->setTargetName("Peashooter", Card::CardType::Plant);
	cardList.push_back(c2);
	
	auto z2 = Card::create(5, 50, "NormalZombies1.png", "NormalZombies2.png");
	
	cardList.push_back(z2);

	auto c3 = Card::create(5, 50, "WallNut1.png", "WallNut2.png");
	cardList.push_back(c3);
	auto c4 = Card::create(5, 50, "Repeater1.png", "Repeater2.png");
	cardList.push_back(c4);

	setCardList(cardList);
	/*********************************************************************
	* 卡牌栏初始化成功
	*/
	
	backgroundMusic=AudioEngine::play2d("backgroundMusic1.mp3");
	/*********************************************************************
	* 产生阳光
	*/
	schedule([this](float) {
		auto s=Sun::create();
		auto size=Director::getInstance()->getWinSizeInPixels();
		s->setPosition(0,size.height+200);
		auto e=EventListenerTouchOneByOne::create();
		e->setSwallowTouches(true);
		e->onTouchBegan = [](Touch*t ,Event*e )->bool {
			if (e->getCurrentTarget()->getBoundingBox().containsPoint(e->getCurrentTarget()->getParent()->convertTouchToNodeSpace(t))) {
				dynamic_cast<SelectAble*>(e->getCurrentTarget()->getParent())->bePickedUp();//因为绑定的是代理，所以获得父对象就是Sun对象
				return true;
			}
			return false;
			
		};
		getEventDispatcher()->addEventListenerWithSceneGraphPriority(e, s->getAgent());
		addChild(s);
		s->runAction(MoveTo::create(1,Vec2(200,200)));
	},2,"createSunByDay"); 
	/*********************************************************************
	*/

	/** 定时随机产生怪物
	*/
	schedule([this](float) {
		auto zombie=PVZUtil::createZombie("Zombie");
		auto ng = getEnterGridByIndex(rand() % 5); 
		zombie->setPosition(ng->getBoundingBox().size / 2);
		ng->addChild(zombie);
		zombie->doPlaced();
		},3,"createZombies");

	return true;
}

cocos2d::Node* BattlefieldScene::getGridByIndex(int xIndex, int yIndex)
{
	//追求左下角的格是(0,0)格。根据网格名字建立对应关系。
	if (xIndex >= 0 && xIndex < getNumberOfGridColumn() && yIndex >= 0 && yIndex < getNumberOfGridRow())
		return _view->getChild("Grid" + std::to_string(xIndex + (getNumberOfGridRow()-1-yIndex) * getNumberOfGridColumn()))->as<GGraph>()->displayObject();
	else
		return nullptr;
}

cocos2d::Node* BattlefieldScene::getEnterGridByIndex(int index)
{
	//下边的出口是0，依次向上
	if (index >= 0 && index <= 4) {
		return _view->getChild("GridEnter" + std::to_string(4 - index))->displayObject();
	}else
	return nullptr;
}

fairygui::GTextField* BattlefieldScene::getSunCounter()
{
	return _view->getChild("sunCounter")->as<GTextField>();
}

cocos2d::Vec2 BattlefieldScene::getSunCounterPos() {
	return Director::getInstance()->convertToGL(getSunCounter()->getPosition());
}

cocos2d::Vec2 BattlefieldScene::getCardBarPos()
{
	return Director::getInstance()->convertToGL(_view->getChild("cardBar")->getPosition());
}

cocos2d::Rect BattlefieldScene::getHomeRect()
{
	return _view->getChild("home")->displayObject()->getBoundingBox();
}

void BattlefieldScene::gameFail()
{
	
	auto w=Window::create();
	w->retain();
	w->setContentPane(UIPackage::createObject("Test","FailWindow")->as<GComponent>());
	w->getCloseButton()->addClickListener([](EventContext* context) {
		Director::getInstance()->replaceScene(MainScene::create());
		});
	w->show();
	w->center(); 
	AudioEngine::play2d("evillaugh.mp3");
	
}

std::pair<int, int> BattlefieldScene::getPlaceholderIndex(cocos2d::Vec2 pos)
{
	auto size=Director::getInstance()->getWinSize();
	auto leftupGird = _view->getChild("Grid0");
	auto correctPos=Vec2(pos.x, size.height - pos.y);//
	auto leftupGirdPos = leftupGird->getPosition();//获得图片左上角坐标，基于左上角原点坐标系
	;//锚点默认0,0。获得某个点距离最左下点的差值
	auto relativePos=Vec2(correctPos.x-leftupGirdPos.x,correctPos.y-leftupGirdPos.y);
	//除法运算下，取整得到索引
	std::pair<int,int> tem=std::make_pair((int)floor(relativePos.x/ leftupGird->getWidth()), getNumberOfGridRow()-1-(int)floor(relativePos.y / leftupGird->getHeight()));
	return tem; 
}

void BattlefieldScene::setCardList(std::vector<Card*> cardList)
{
	if (currentCardBar==nullptr) {
		currentCardBar = CardBar::create();
		currentCardBar->setPosition(getCardBarPos());
	}
	currentCardBar->setLocalZOrder(10);
	for(auto i:cardList){
		currentCardBar->addCard(i);
	}
	currentCardBar->alignItemsVertically();
	currentCardBar->removeFromParent();
	addChild(currentCardBar);
}

void BattlefieldScene::onExit()
{
	BaseScene::onExit();
	AudioEngine::stop(backgroundMusic);
}

