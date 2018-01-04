#include "cfactions.h"

FactionSharedPtr& Factions::DRAGON()
{
    static FactionSharedPtr f(new Faction(CHAR_T("dragon")));
    f->setFriendlyness(DEFAULT(), -10);
    f->setFriendlyness(WILDERNESS(), -10);
    return f;
}

FactionSharedPtr& Factions::WILDERNESS()
{
    static FactionSharedPtr f(new Faction(CHAR_T("wilderness")));
    f->setFriendlyness(DEFAULT(), -10);
    return f;
}

FactionSharedPtr& Factions::DEFAULT()
{
    static FactionSharedPtr f(new Faction(CHAR_T("default")));
    return f;
}
