#include "cbehavior.h"
#include "ccharacter.h"
#include "cmath.h"

#include <stdio.h>

BehaviorWander::BehaviorWander()
    : m_initialized(false)
    , m_anchorX(0)
    , m_anchorY(0)
    , m_ropeLength(10)
    , m_moveTime(0)
    , m_velocity(1)
{

}

const char* BehaviorWander::getName() const
{
    return "Wander";
}

void BehaviorWander::tick(float dt, Character* object)
{
    if (!m_initialized)
    {
        m_initialized = true;
        m_anchorX = object->getX();
        m_anchorY = object->getY();
    }

    m_moveTime += dt;
    if (m_moveTime < 0.5f)
    {
        return;
    }

    m_moveTime = 0;

    // do we move?
    if (Math::wrapRandom() > 0)
    {
        return;
    }


//        printf("allo");

    // which direction?
    if (Math::wrapRandom() > 0)
    {
        // left - right
        if (Math::wrapRandom() > 0)
        {
            object->setVelocity(m_velocity/dt, 0, 0);
        }
        else
        {
            object->setVelocity(-m_velocity/dt, 0, 0);
        }
    }
    else
    {
        // up - down
        if (Math::wrapRandom() > 0)
        {
            object->setVelocity(0, m_velocity/dt, 0);
        }
        else
        {
            object->setVelocity(0, -m_velocity/dt, 0);
        }
    }

    float newX = object->getVelocityX() * dt + object->getX();
    float newY = object->getVelocityY() * dt + object->getY();

    if (Math::distance(newX, newY, m_anchorX, m_anchorY) > m_ropeLength)
    {
        object->setVelocity(0, 0, 0);
    }
}


BehaviorAttack::BehaviorAttack()
{

}

const char* BehaviorAttack::getName() const
{
    return "Attack";
}

void BehaviorAttack::tick(float dt, Character* object)
{

}
