#include<PVZHeader.h>
#include<winsqlite/winsqlite3.h>
USING_NS_CC;
USING_NS_FGUI;
bool BaseScene::init(fairygui::GObject* view)
{
	if (!Scene::initWithPhysics()) {
		return false;
	}
	_groot = GRoot::create(this,0); //核心，渲染中心
	_groot->retain();//因为groot也是用cocos2d::Ref管理内存，升一个。create不会自动增加，所以需要手动增加
	Size size = Director::getInstance()->getWinSize();//获得屏幕大小
	_groot->setSize(size.width, size.height);//设置为_groot的大小为屏幕大小
	_view =view->as<GComponent>();//获取一个用于显示的组件
   //发现fairygui::GObject类和cocos2d::Node类对应，其中有很多同类方法，并且还找到一些很方便使用的方法
	_view->makeFullScreen();//充满屏幕
	_groot->addChild(_view);//设置显示该组件
	auto playerAgent = PVZUtil::getPlayerAgent();
	playerAgent->removeFromParent();
	addChild(playerAgent);
    return true;
}

BaseScene::~BaseScene()
{
	CC_SAFE_RELEASE(_groot);
}
