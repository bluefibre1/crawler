#pragma once

#include "cobject.h"
#include "ctile.h"
#include "cbehavior.h"


class Character : public Object
{
public:
    Character();

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

    virtual void setBehavior(Behavior* behavior);

protected:
    Tile m_tile;
    int m_hp;
    Behavior* m_behavior;
};
