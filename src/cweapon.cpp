#include "cweapon.h"
#include "ccharacter.h"
#include "csimulator.h"
#include "cmath.h"
#include "crenderer.h"
#include "ccolors.h"

Weapon::Weapon()
    : m_dir(Direction::LEFT)
    , m_damage(0)
    , m_visible(false)
    , m_showTimer()
{
    m_isWeapon = true;
    m_isEquipable = true;
}

void Weapon::setDamage(int value)
{
    m_damage = value;
}

int Weapon::getDamage() const
{
    return m_damage;
}

void Weapon::setVerticalChar(char c)
{
    m_verticalChar = c;
}

void Weapon::setHorizontalChar(char c)
{
    m_horizontalChar = c;
}

void Weapon::setColor(const Color& color)
{
    m_color = color;
}

void Weapon::draw(Renderer* r)
{
    if (!m_visible || !getOwner())
    {
        return;
    }

    if (m_showTimer.elapsed() >= 0.3f)
    {
        m_visible = false;
        return;
    }

    float dx, dy;
    getDeltas(dx, dy);

    char ch = (m_dir == Direction::LEFT || m_dir == Direction::RIGHT) ?
        m_horizontalChar : m_verticalChar;

    r->drawChar(getOwner()->getX()+dx,
                getOwner()->getY()+dy,
                getOwner()->getZ(),
                m_color,
                Colors::INVALID(),
                ch);
}

void Weapon::use(Direction dir)
{
    if (getOwner() && getOwner()->isCharacter())
    {
        Character* user = (Character*)getOwner();

        m_dir = dir;
        show();

        float dx, dy;
        getDeltas(dx, dy);

        Object* dest = nullptr;
        if (Simulator::get()->findTarget(user->getX() + dx, user->getY() + dy, user->getZ(), &dest))
        {
            if (dest->isCharacter())
            {
                int damage = Math::ceilRandom(m_damage);

                Character* target = (Character*)dest;
                target->onReceiveHit(user, damage);
                user->onGiveHit(target, damage);
            }
        }
    }
}

void Weapon::show()
{
    m_visible = true;
    m_showTimer.reset();
}

void Weapon::getDeltas(float& dx, float& dy)
{
    switch (m_dir)
    {
    case Direction::UP:
        dx = 0;
        dy = -1;
        break;

    case Direction::DOWN:
        dx = 0;
        dy = 1;
        break;

    case Direction::LEFT:
        dx = -1;
        dy = 0;
        break;

    case Direction::RIGHT:
        dx = 1;
        dy = 0;
        break;
    }
}
