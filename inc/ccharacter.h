#pragma once

#include "cobject.h"
#include "ctile.h"

class Character : public Object
{
public:
    Character();

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

protected:
    Tile m_tile;
    int m_hp;
};
