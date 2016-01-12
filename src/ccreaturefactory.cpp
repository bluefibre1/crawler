#include "ccreaturefactory.h"

#include "ccreaturetemplate.h"
#include "cweaponfactory.h"
#include "cweapon.h"
#include "cmath.h"

CreaturePtr CreatureFactory::create(const CreatureTemplate* t)
{
    CreaturePtr c(new Creature());
    c->setName(t->getName());
    c->setHp((int)Math::intervalRandom(t->getMaxHp(), t->getMinHp()));
    c->setMaxVelocity(t->getMaxVelocity());
    c->setColor(t->getColor());
    c->setChar(t->getChar());

    int wIdx = Math::ceilRandom(t->getWeaponTemplates().size());
    WeaponPtr w(WeaponFactory::create(t->getWeaponTemplates()[wIdx]));
    c->equip(w);
    return c;
}
