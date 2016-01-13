#include "ccreaturetemplates.h"
#include "cweapontemplates.h"
#include "ccolors.h"

const CreatureTemplate& CreatureTemplates::DRAGON()
{
    std::vector<const WeaponTemplate*> weapons;
    weapons.push_back(&WeaponTemplates::FIRE());
    weapons.push_back(&WeaponTemplates::CLAW());

    static CreatureTemplate c(10, "Dragon", 10, 20, 1, Colors::GREY(), 'D', weapons);
    return c;
}

const CreatureTemplate& CreatureTemplates::BAT()
{
    std::vector<const WeaponTemplate*> weapons;
    weapons.push_back(&WeaponTemplates::CLAW());

    static CreatureTemplate c(50, "Bat", 5, 5, 1, Colors::BLACK(), 'b', weapons);
    return c;
}

const CreatureTemplate& CreatureTemplates::VILLAGER()
{
    std::vector<const WeaponTemplate*> weapons;
    weapons.push_back(&WeaponTemplates::SNOWBALL());
    weapons.push_back(&WeaponTemplates::PUNCH());

    static CreatureTemplate c(100, "Villager", 15, 25, 1, Colors::LIGHT_BLUE(), 'V', weapons);
    return c;
}

const CreatureTemplate& CreatureTemplates::KID()
{
    std::vector<const WeaponTemplate*> weapons;
    weapons.push_back(&WeaponTemplates::SNOWBALL());

    static CreatureTemplate c(100, "Kid", 1, 2, 1, Colors::LIGHT_BLUE(), 'v', weapons);
    return c;
}

