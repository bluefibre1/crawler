#include "cweaponfactory.h"

#include "cweapontemplate.h"
#include "cmath.h"

WeaponPtr WeaponFactory::create(const WeaponTemplate* t)
{
    WeaponPtr w(new Weapon());
    w->setDamage((int)Math::intervalRandom(t->getMaxDamage(), t->getMinDamage()));

    const char* qualifier[] = {
        " ",
        "Rusted ",
        "Brass ",
        "Iron ",
        "Glass ",
        "Ebonite ",
        "Ultimate "
    };

    int numQualifier = sizeof(qualifier) / sizeof(const char*);
    int idx = numQualifier * w->getDamage() / 1000;
    if (idx > numQualifier)
    {
        idx = numQualifier;
    }

    std::string fullName = qualifier[idx];
    fullName += t->getName();
    w->setName(fullName);

    w->setColor(t->getColor());
    w->setVerticalChar(t->getVerticalChar());
    w->setHorizontalChar(t->getHorizontalChar());

    return w;
}
