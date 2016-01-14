#include "cweapontemplates.h"
#include "ccolors.h"

const WeaponTemplate& WeaponTemplates::SWORD() { static WeaponTemplate w(100, "Sword", 3, 7, Colors::LIGHT_GREY(), '|', '-'); return w; }
const WeaponTemplate& WeaponTemplates::PUNCH() { static WeaponTemplate w(100, "Sword", 3, 7, Colors::SANDYELLOW(), '.', '.'); return w; }
const WeaponTemplate& WeaponTemplates::SPELL() { static WeaponTemplate w(50, "Spell", 5, 10, Colors::YELLOW(), '*', '*'); return w; }
const WeaponTemplate& WeaponTemplates::CLAW() { static WeaponTemplate w(100, "Claw", 1, 5, Colors::DARK_GREY(), '"', '='); return w; }
const WeaponTemplate& WeaponTemplates::SNOWBALL() { static WeaponTemplate w(100, "Snowball", 5, 100, Colors::WHITE(), 'o', 'o'); return w; }
const WeaponTemplate& WeaponTemplates::FIRE() { static WeaponTemplate w(100, "Fire", 5, 100, Colors::ORANGE(), 's', '~'); return w; }
