#pragma once
#include "BaseScene.h"
class GardenScene :
    public BaseScene
{
   protected:
    virtual bool init();
    public:
    CREATE_FUNC(GardenScene);
};

