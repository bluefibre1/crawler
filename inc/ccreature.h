#pragma once

#include "ccharacter.h"
#include "cwindow.h"

class Creature : public Character
{
public:
    Creature();

    virtual void tick(float dt) override;


private:
};

typedef std::shared_ptr<Creature> CreaturePtr;
