#include "ccharacter.h"
#include "crenderer.h"

Character::Character()
    : m_tile(ColorStyle::BRIGHT, Color::MAGENTA, Color::INVALID, '0')
    , m_behavior(nullptr)
{
    setFriction(1);
}

void Character::draw(Renderer* r)
{
    if (r->isVisible(this))
    {
        r->draw(getX(), getY(), getZ(), &m_tile);
    }
}

void Character::tick(float dt)
{
    if (m_behavior)
    {
        m_behavior->tick(dt, this);
    }

    Object::tick(dt);
}

void Character::setBehavior(Behavior* behavior)
{
    delete m_behavior;
    m_behavior = behavior;
}
