#include "citemfactory.h"

#include "citemtemplate.h"
#include "cweapontemplate.h"
#include "cweapon.h"
#include "cmath.h"

ItemSharedPtr ItemFactory::create(const ItemTemplateSharedPtr& t)
{
    switch (t->getType())
    {
    case ItemTemplate::Type::WEAPON:
        return createWeapon((WeaponTemplate*)t.get());

    case ItemTemplate::Type::POTION:
        return createPotion((PotionTemplate*)t.get());

    default:
        return nullptr;
    };
}

ItemSharedPtr ItemFactory::createWeapon(const WeaponTemplate* t)
{
    Weapon* w = new Weapon();
    w->setDamage((int)Math::intervalRandom(t->getMinDamage(), t->getMaxDamage()));

    const char* qualifier[] = {
        "",
        "Rusted ",
        "Brass ",
        "Iron ",
        "Glass ",
        "Diamond ",
        "Ebonite ",
        "Ultimate "
    };

    int numQualifier = sizeof(qualifier) / sizeof(const char*);
    int idx = numQualifier * w->getDamage() / 100;
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

    return ItemSharedPtr(w);
}

ItemSharedPtr ItemFactory::createPotion(const PotionTemplate* t)
{
    return ItemSharedPtr();
}
