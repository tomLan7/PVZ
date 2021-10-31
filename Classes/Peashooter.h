#pragma once
#include "Plant.h"
class Peashooter :
    public Plant
{
    static bool __isLoad;
    void loadAllNeededAnimateToCache()override;
public:  
    CREATE_FUNC(Peashooter);
    bool init()override;
    virtual void doPlaced() override;
    void autoProductionBullet(float);
};

