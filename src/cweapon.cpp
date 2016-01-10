#include "cweapon.h"

Weapon::Weapon()
    : m_damage(0)
{

}

void Weapon::setDamage(int value)
{
    m_damage = value;
}

int Weapon::getDamage() const
{
    return m_damage;
}
