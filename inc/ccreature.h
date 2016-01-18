#pragma once

#include "ccharacter.h"
#include "cwindow.h"

class Creature : public Character
{
public:
    Creature();

    virtual void tick(float dt) override;

    void setMaxVelocity(float maxVel);

    virtual void showStats() override;

private:
    float m_maxVelocity;
    WindowWeakPtr m_statsPopup;
};

typedef std::shared_ptr<Creature> CreaturePtr;
