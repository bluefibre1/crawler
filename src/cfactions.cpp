#include "cfactions.h"

FactionSharedPtr& Factions::DRAGON()
{
    static FactionSharedPtr f(new Faction("dragon"));
    f->setFriendlyness(DEFAULT(), -10);
    f->setFriendlyness(WILDERNESS(), -10);
    return f;
}

FactionSharedPtr& Factions::WILDERNESS()
{
    static FactionSharedPtr f(new Faction("wilderness"));
    f->setFriendlyness(DEFAULT(), -10);
    return f;
}

FactionSharedPtr& Factions::DEFAULT()
{
    static FactionSharedPtr f(new Faction("default"));
    return f;
}
