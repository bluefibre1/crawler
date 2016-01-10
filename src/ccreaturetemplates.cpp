#include "ccreaturetemplates.h"
#include "ccolors.h"

const CreatureTemplate& CreatureTemplates::DRAGON() { static CreatureTemplate c(10, "Dragon", 100, 200, 1, Colors::GREEN(), 'D'); return c; }
const CreatureTemplate& CreatureTemplates::VILLAGER() { static CreatureTemplate c(100, "Villager", 100, 200, 1, Colors::BLUE(), 'V'); return c; }
const CreatureTemplate& CreatureTemplates::KID() { static CreatureTemplate c(100, "Kid", 100, 200, 1, Colors::BLUE(), 'v'); return c; }
