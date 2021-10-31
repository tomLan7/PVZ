#include "PVZHeader.h"
USING_NS_FGUI;
USING_NS_CC;
bool MainScene::init()
{
    //if ( !Scene::init() ) ¸ü¸ÄÎª
    if (!BaseScene::init(UIPackage::createObject("Test", "MainLayer")))
    {
        return false;
    }
   
    _view->getChild("n5")->addClickListener([this](EventContext*) {
        Director::getInstance()->replaceScene(BattlefieldScene::create());
        });
    _view->getChild("n6")->addClickListener([this](EventContext*) {
        Director::getInstance()->replaceScene(GardenScene::create());
        });
    PVZUtil::getPVZDAO()->refresh();
    return true;
}
