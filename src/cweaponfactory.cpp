#include "cweaponfactory.h"

#include "cweapontemplate.h"
#include "cweapon.h"
#include "cmath.h"

Weapon* WeaponFactory::create(const WeaponTemplate* t)
{
    Weapon* w = new Weapon();
    w->setDamage((int)Math::intervalRandom(t->getMaxDamage(), t->getMinDamage()));

    int rangeDamage = t->getMaxDamage() - t->getMinDamage();
    if (rangeDamage > 0)
    {
        const char* qualifier[] = {
            "Rusted ",
            "Brass ",
            "Iron ",
            "Glass ",
            "Ebonite ",
            "Ultimate "
        }

        int numQualifier = sizeof(qualifier) / sizeof(const char*);
        int idx = numQualifier * (w->getDamage() - t->getMinDamage()) / rangeDamage;
        std::name fullName = qualifier[idx];
        fullName += t->getName();
        w->setName(fullName);
    }
    else
    {
        w->setName(t->getName());
    }

    return w;
}
