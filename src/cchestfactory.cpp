#include "cchestfactory.h"

#include "cweaponfactory.h"
#include "cweapontemplates.h"
#include "cmath.h"

ChestSharedPtr ChestFactory::create()
{
    ChestSharedPtr c(new Chest());

    std::vector<const WeaponTemplate*> weapons;
    weapons.push_back(&WeaponTemplates::SPELL());
    weapons.push_back(&WeaponTemplates::SWORD());
    weapons.push_back(&WeaponTemplates::SNOWBALL());

    int n = Math::ceilRandom(3) + 1;
    for (int i = 0; i < n; i++)
    {
        int wIdx = Math::ceilRandom(weapons.size());
        WeaponPtr w(WeaponFactory::create(weapons[wIdx]));
        c->addItem(w);
    }
    return c;
}
