#include "ccreature.h"

Creature::Creature()
    : m_maxVelocity(1)
{
}

void Creature::tick(float dt)
{
    Character::tick(dt);
}

void Creature::setMaxVelocity(float maxVel)
{
    m_maxVelocity = maxVel;
}
