#include "cweapon.h"
#include "ccharacter.h"
#include "csimulator.h"
#include "cmath.h"

Weapon::Weapon()
    : m_damage(0)
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

void Weapon::use(Object* source, Direction dir)
{
    if (source->isCharacter())
    {
        Character* user = (Character*)source;

        float dx, dy;
        switch (dir)
        {
        case Direction::UP:
            dx = 0;
            dy = -1;
            break;

        case Direction::DOWN:
            dx = 0;
            dy = -1;
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
