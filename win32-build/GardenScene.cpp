
#include<PVZHeader.h>
USING_NS_CC;
USING_NS_FGUI;
bool GardenScene::init()
{
	if (!BaseScene::init(UIPackage::createObject("Test", "PlantGardenLayer"))){
		return false;
	}
	_view->getChild("closeButton")->addClickListener([this](EventContext*) {
		Director::getInstance()->replaceScene(MainScene::create());
		});
    return true;
}
