#include "ccharacterfactory.h"

#include "ccharactertemplate.h"
#include "cbehavior.h"
#include "citemfactory.h"
#include "cmath.h"
#include "cfactions.h"

CharacterSharedPtr CharacterFactory::create(const CharacterTemplateSharedPtr& t)
{
    CharacterSharedPtr c(new Character());
    c->setName(t->getName());
    c->setMapHp((int)Math::intervalRandom(t->getMaxHp(), t->getMinHp()));
    c->heal();
    c->setColor(t->getColor());
    c->setChar(t->getChar());
    c->setFaction(&Factions::WILDERNESS());

    BlackboardReference targetRef = BlackboardReference::TARGET;

    auto findTarget = new BehaviorFindTarget();
    findTarget->setReference(targetRef);
    findTarget->setVisionSqrRadius(25, 9);

    auto attack = new BehaviorAttack();
    attack->setReference(targetRef);

    auto wander = new BehaviorWander();

    auto chase = new BehaviorChase();
    chase->setReference(targetRef);

    auto refPredicate  = new BehaviorReferencePredicate();
    refPredicate->setReference(targetRef);

    auto proximityPredicate = new BehaviorDistancePredicate();
    proximityPredicate->setSqrDistance(1);
    proximityPredicate->setGreaterThan(false);
    proximityPredicate->setReference(targetRef);

    auto attackAlternative = new BehaviorAlternative();
    attackAlternative->setPredicate(proximityPredicate);
    attackAlternative->setTrue(attack);
    attackAlternative->setFalse(chase);

    auto chaseAlternative = new BehaviorAlternative();
    chaseAlternative->setPredicate(refPredicate);
    chaseAlternative->setTrue(attackAlternative);
    chaseAlternative->setFalse(wander);

    auto root = new BehaviorComposite();
    root->add(findTarget);
    root->add(chaseAlternative);
    c->setBehavior(root);

    auto bb = new Blackboard();
    bb->setSelf(c.get());
    c->setBlackboard(bb);

    if (t->getItemTemplates().empty())
    {
        int wIdx = Math::ceilRandom(t->getItemTemplates().size());
        ItemSharedPtr w(ItemFactory::create(t->getItemTemplates()[wIdx]));
        c->equip(w);
    }
    return c;
}
