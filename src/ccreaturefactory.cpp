#include "ccreaturefactory.h"

#include "ccreaturetemplate.h"
#include "ccreature.h"
#include "cmath.h"

Creature* CreatureFactory::create(const CreatureTemplate* t)
{
    Creature* c = new Creature();
    c->setName(t->getName());
    c->setHp((int)Math::intervalRandom(t->getMaxHp(), t->getMinHp()));
    c->setMaxVelocity(t->getMaxVelocity());
    c->setColor(t->getColor());
    c->setStyle(t->getStyle());
    c->setChar(t->getChar());
    return c;
}
