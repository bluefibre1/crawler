#pragma once

#include "cstring.h"
#include <map>

class Faction;
typedef std::shared_ptr<Faction> FactionSharedPtr;

class Faction
{
public:
    Faction(const String& name);

    void setFriendlyness(const FactionSharedPtr& faction, float value);

    bool isEnemy(const FactionSharedPtr& faction) const;

private:
    String m_name;
    typedef std::map<Faction*, float> Friendlynesses;
    Friendlynesses m_friendlynesses;
};

