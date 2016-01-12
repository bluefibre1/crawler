#include "ccharacter.h"
#include "crenderer.h"
#include "cbehavior.h"
#include "citem.h"
#include "ccolors.h"

Character::Character()
    : m_ch('@')
    , m_color(Colors::MAGENTA())
    , m_hp(10)
    , m_behavior(nullptr)
    , m_name()
    , m_items()
{
    setFriction(1);
}

void Character::draw(Renderer* r)
{
    if (r->isVisible(this))
    {
        r->drawChar(getX(), getY(), getZ(), m_color, Colors::INVALID(), m_ch);
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

void Character::setColor(const Color& color)
{
    m_color = color;
}

void Character::setChar(char ch)
{
    m_ch = ch;
}

void Character::addItem(const ItemPtr& item)
{
    auto i = std::find(m_items.begin(), m_items.end(), item);
    if (i == m_items.end())
    {
        m_items.push_back(item);
    }
}

void Character::removeItem(const ItemPtr& item)
{
    unequip(item);
    auto i = std::find(m_items.begin(), m_items.end(), item);
    if (i != m_items.end())
    {
        m_items.erase(i);
    }
}

void Character::equip(const ItemPtr& item)
{
    addItem(item);
    if (item->isEquipable())
    {
        auto i = std::find(m_equipped.begin(), m_equipped.end(), item);
        if (i == m_equipped.end())
        {
            m_equipped.push_back(item);
        }
    }
}

void Character::unequip(const ItemPtr& item)
{
    auto i = std::find(m_equipped.begin(), m_equipped.end(), item);
    if (i == m_equipped.end())
    {
        m_equipped.push_back(item);
    }
}
