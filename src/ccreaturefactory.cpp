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

    /*auto findTarget = new BehaviorFindTarget();
    findTarget->setVisionSqrRadius(8, 3);

    auto attack = new BehaviorAttack();
    auto wander = new BehaviorWander();

    auto ifTarget = new BehaviorIf();
    ifTarget->setObject(attack->getTargetVar());
    ifTarget->setTrue(attack);
    ifTarget->setFalse(wander);

    auto root = new BehaviorComposite();
    root->add(findTarget);
    root->add(ifTarget);
    c->setBehavior(root);

    auto bb = new Blackboard();
    bb->setSelf(c);
    c->setBlackBoard(bb);
    */

    int wIdx = Math::ceilRandom(t->getWeaponTemplates().size());
    WeaponPtr w(WeaponFactory::create(t->getWeaponTemplates()[wIdx]));
    c->equip(w);
    return c;
}
