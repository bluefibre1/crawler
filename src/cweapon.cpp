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
    m_type = Item::Type::WEAPON;
    m_action = Item::Action::EQUIPPABLE;
}

void Weapon::setDamage(int value)
{
    m_damage = value;
}

int Weapon::getDamage() const
{
    return m_damage;
}

void Weapon::setVerticalChar(Char c)
{
    m_verticalChar = c;
}

void Weapon::setHorizontalChar(Char c)
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

    r->draw(
        getOwner()->getX()+dx,
        getOwner()->getY()+dy,
        getOwner()->getZ()+1,
        m_color,
        Colors::INVALID(),
        ch);
}

void Weapon::use(Direction dir)
{
    if (getOwner() && getOwner()->getObjectType() & Object::OBJECT_TYPE_CHARACTER)
    {
        Character* owner = (Character*)getOwner();

        m_dir = dir;
        show();

        float dx, dy;
        getDeltas(dx, dy);

        ObjectWeakPtrs objects;
        if (Simulator::get().listObjectsAt(
                owner->getX() + dx,
                owner->getY() + dy,
                owner->getZ(),
                &objects))
        {
            std::for_each(
                objects.begin(), objects.end(),
                [this, owner](const ObjectWeakPtr& o)
                {
                    ObjectSharedPtr object = o.lock();
                    if (object->getObjectType() & Object::OBJECT_TYPE_CHARACTER)
                    {
                        int damage = Math::ceilRandom(m_damage);

                        Character* target = (Character*)object.get();

                        Math::clamp(damage, 0, target->getHp());
                        target->onReceiveHit(owner, damage);
                        owner->onGiveHit(target, damage);
                    }
                });
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
