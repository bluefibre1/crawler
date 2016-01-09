#pragma once
#include "ccharacter.h"

class Creature : public Character
{
public:
    Creature();

    virtual void tick(float dt) override;

};
