#pragma once
#include "Plant.h"
class Sunflower :
    public Plant
{
    static bool __isLoad;
    void loadAllNeededAnimateToCache()override;
public:
    CREATE_FUNC(Sunflower);
    bool init()override;
    virtual void doPlaced() override;
    void autoProductionSun(float);
};

