#include "ccharacter.h"
#include "crenderer.h"
#include "ccolors.h"

Character::Character()
    : m_tile(ColorStyle::DIM, Colors::MAGENTA(), Colors::INVALID(), '@')
    , m_hp(10)
    , m_behavior(nullptr)
    , m_name()
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

const std::string& Character::getName() const
{
    return m_name;
}

void Character::setName(const std::string& name)
{
    m_name = name;
}

int Character::getHp() const
{
    return m_hp;
}

void Character::setHp(int hp)
{
    m_hp = hp;
}

void Character::setColor(Color color)
{
    m_tile.setForeground(color);
}

void Character::setStyle(ColorStyle style)
{
    m_tile.setStyle(style);
}

void Character::setChar(char ch)
{
    m_tile.setValue(ch);
}
