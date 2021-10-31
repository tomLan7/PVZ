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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
class PlayerAgent;
class CardBar;
#include<BaseScene.h>
class BattlefieldScene : public BaseScene
{
    CardBar* currentCardBar = nullptr;
public:
   CardBar* getCardBar() {
        return currentCardBar;
   }
    virtual bool init();
	
    // a selector callback
    
    // implement the "static create()" method manually
    CREATE_FUNC(BattlefieldScene);
    
    //通过格子索引获得对应位置的图形对象
    unsigned int getNumberOfGridColumn() {
        return 9;
    }
    unsigned int getNumberOfGridRow() {
        return 5;
    }
    cocos2d::Node* getGridByIndex(int xIndex, int yIndex);
    cocos2d::Node* getGridByIndex(std::pair<int, int>& xyIndex) {
        return getGridByIndex(xyIndex.first,xyIndex.second);
        
    }
    cocos2d::Node* getEnterGridByIndex(int index);
    fairygui::GTextField* getSunCounter();
    cocos2d::Vec2 getSunCounterPos();
    cocos2d::Vec2 getCardBarPos();
    cocos2d::Rect getHomeRect();
    void gameFail();//游戏失败会调用的函数
    std::pair<int,int> getPlaceholderIndex(cocos2d::Vec2 pos);//根据一个点来获得占位符
    //根据卡牌数组来放入
    void setCardList(std::vector<Card*> cardList);
    int backgroundMusic=0;
    void onExit()override;
};

#endif // __HELLOWORLD_SCENE_H__
