#include "cweapontemplates.h"

const WeaponTemplate& WeaponTemplates::SWORD() { static WeaponTemplate w(100, "Sword", 5, 100, 1, Color::GREEN, ColorStyle::BRIGHT, 'D'); return w; }
