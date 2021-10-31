#pragma once
#include<cocos2d.h>
#include<FairyGUI.h>
class BaseScene :
    public cocos2d::Scene
{
protected:
    fairygui::GComponent* _view;
    fairygui::GRoot* _groot;
    bool init(fairygui::GObject* view);
    ~BaseScene();
};

