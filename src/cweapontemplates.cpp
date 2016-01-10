#include "cweapontemplates.h"
#include "ccolors.h"

const WeaponTemplate& WeaponTemplates::SWORD() { static WeaponTemplate w(100, "Sword", 5, 100, Colors::GREEN(), '|', '-'); return w; }
