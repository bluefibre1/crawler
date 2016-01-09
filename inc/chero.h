#pragma once

#include "ccharacter.h"

class Hero : public Character
{
public:
    Hero();

    virtual void tick(float dt) override;

};
