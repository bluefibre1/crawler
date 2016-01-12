#pragma once

#include "ccharacter.h"

class Creature : public Character
{
public:
    Creature();

    virtual void tick(float dt) override;

    void setMaxVelocity(float maxVel);

private:
    float m_maxVelocity;
};

typedef std::shared_ptr<Creature> CreaturePtr;
