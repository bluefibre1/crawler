#include "cfactions.h"

Faction& Factions::DRAGON()
{
    static Faction f("dragon");
    f.setFriendlyness(&DEFAULT(), -10);
    return f;
}

Faction& Factions::WILDERNESS()
{
    static Faction f("wilderness");
    f.setFriendlyness(&DEFAULT(), -10);
    return f;
}

Faction& Factions::DEFAULT()
{
    static Faction f("default");
    return f;
}
