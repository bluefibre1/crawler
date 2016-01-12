#include "ccreaturetemplates.h"
#include "cweapontemplates.h"
#include "ccolors.h"

const CreatureTemplate& CreatureTemplates::DRAGON()
{
    std::vector<const WeaponTemplate*> weapons;
    weapons.push_back(&WeaponTemplates::SWORD());

    static CreatureTemplate c(10, "Dragon", 100, 200, 1, Colors::GREEN(), 'D', weapons);
    return c;
}

const CreatureTemplate& CreatureTemplates::VILLAGER()
{
    std::vector<const WeaponTemplate*> weapons;
    weapons.push_back(&WeaponTemplates::SWORD());

    static CreatureTemplate c(100, "Villager", 100, 200, 1, Colors::BLUE(), 'V', weapons);
    return c;
}

const CreatureTemplate& CreatureTemplates::KID()
{
    std::vector<const WeaponTemplate*> weapons;
    weapons.push_back(&WeaponTemplates::SWORD());

    static CreatureTemplate c(100, "Kid", 100, 200, 1, Colors::BLUE(), 'v', weapons);
    return c;
}
