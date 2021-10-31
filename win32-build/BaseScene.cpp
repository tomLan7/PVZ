#include<PVZHeader.h>
#include<winsqlite/winsqlite3.h>
USING_NS_CC;
USING_NS_FGUI;
bool BaseScene::init(fairygui::GObject* view)
{
	if (!Scene::initWithPhysics()) {
		return false;
	}
	_groot = GRoot::create(this,0); //���ģ���Ⱦ����
	_groot->retain();//��ΪgrootҲ����cocos2d::Ref�����ڴ棬��һ����create�����Զ����ӣ�������Ҫ�ֶ�����
	Size size = Director::getInstance()->getWinSize();//�����Ļ��С
	_groot->setSize(size.width, size.height);//����Ϊ_groot�Ĵ�СΪ��Ļ��С
	_view =view->as<GComponent>();//��ȡһ��������ʾ�����
   //����fairygui::GObject���cocos2d::Node���Ӧ�������кܶ�ͬ�෽�������һ��ҵ�һЩ�ܷ���ʹ�õķ���
	_view->makeFullScreen();//������Ļ
	_groot->addChild(_view);//������ʾ�����
	auto playerAgent = PVZUtil::getPlayerAgent();
	playerAgent->removeFromParent();
	addChild(playerAgent);
    return true;
}

BaseScene::~BaseScene()
{
	CC_SAFE_RELEASE(_groot);
}
